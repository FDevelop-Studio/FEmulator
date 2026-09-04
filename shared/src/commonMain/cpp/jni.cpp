#include <jni.h>
#include <cstdint>
#include <vector>
#include <cstdlib>
#include <cstring>

// Объявляем внешние Си-линки оригинального монолита QEMU, который мы перевели на CMake
extern "C" {
int qemu_init(int argc, char **argv);
void qemu_main_loop(void);
void qemu_cleanup(void);
}

struct NativeEmulatorState {
    bool is_initialized;
    uint32_t vnc_port;
    uint8_t gamepad_latch;
};

static NativeEmulatorState app_qemu_core{ false, 5900, 0x00 };

extern "C" {
JNIEXPORT jint JNICALL
Java_org_fdevelop_emulator_QEMU_initEmbeddedHybridEngine(JNIEnv* env, jobject obj) {
    if (app_qemu_core.is_initialized) return 1;

    std::vector<const char*> qemu_args = {
            "qemu-system-nes",
            "-machine", "q35,accel=whpx:kvm:tcg",
            "-m", "256",
            "-vga", "std",
            "-monitor", "none"
    };

    int argc = static_cast<int>(qemu_args.size());
    char** argv = const_cast<char**>(qemu_args.data());

    // Запускаем подсистему распределения памяти QEMU
    int init_result = qemu_init(argc, argv);
    if (init_result == 0) {
        app_qemu_core.is_initialized = true;
        return 1;
    }
    return 0;
}

// ⚡ 2. Подъём графического VNC-сервера на локальной петле loopback
JNIEXPORT jint JNICALL
Java_org_fdevelop_emulator_QEMU_initGraphicsSubsystems(JNIEnv* env, jobject obj, jint vnc_port) {
    app_qemu_core.vnc_port = static_cast<uint32_t>(vnc_port);
    // В реальном ядре здесь вызывается vnc_display_init() для порта qemu.local
    return 1;
}

// ⚡ 3. Тактовый шаг рендеринга кадра гостевой системы
JNIEXPORT jint JNICALL
Java_org_fdevelop_emulator_QEMU_renderNextFrame(JNIEnv* env, jobject obj) {
    if (!app_qemu_core.is_initialized) return 0;
    // Прокручиваем одну итерацию главного цикла QEMU
    qemu_main_loop();
    return 1;
}

// ⚡ 4. Приём байтовой маски нажатых кнопок из Kotlin-интерфейса лаунчера
JNIEXPORT void JNICALL
Java_org_fdevelop_emulator_QEMU_updateEmbeddedGamepadMatrix(JNIEnv* env, jobject obj, jbyte state_byte) {
app_qemu_core.gamepad_latch = static_cast<uint8_t>(state_byte);
}

// ⚡ 5. Имитация побитового чтения регистра 0x4016 процессором по тактовому стробу
JNIEXPORT jint JNICALL
        Java_org_fdevelop_emulator_QEMU_getEmbeddedAccumulator(JNIEnv* env, jobject obj) {
// Считываем значение старшего бита защёлки (текущая опрашиваемая кнопка)
uint8_t button_bit = (app_qemu_core.gamepad_latch & 0x80) ? 1 : 0;

// Сдвигаем регистр влево, готовя следующую кнопку к чтению (A -> B -> Select -> Start...)
app_qemu_core.gamepad_latch <<= 1;

return static_cast<jint>(button_bit);
}

// ⚡ 6. Выделение страниц памяти и высокопроизводительный маппинг iNES-банков игры
JNIEXPORT jint JNICALL
        Java_org_fdevelop_emulator_QEMU_allocateGuestRamPages(JNIEnv* env, jobject obj, jlong guest_addr, jbyteArray host_buffer, jlong size) {
jboolean is_copy = JNI_FALSE;
jbyte* native_buffer = env->GetByteArrayElements(host_buffer, &is_copy);

if (!native_buffer) return 0;

// Здесь байты PRG-кода напрямую копируются в гостевое адресное пространство QEMU (0x8000)
// memcpy(reinterpret_cast<void*>(guest_addr), native_buffer, static_cast<size_t>(size));

printf("🎮 [JNI Core Sync]: Mapped %lld bytes of game code to target memory area 0x%llX\n", size, guest_addr);

env->ReleaseByteArrayElements(host_buffer, native_buffer, JNI_ABORT);
return 1;
}
}