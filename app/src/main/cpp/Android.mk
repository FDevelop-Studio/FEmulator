LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := pixman
LOCAL_C_INCLUDES := $(LOCAL_PATH)/pixman/pixman
LOCAL_SRC_FILES := \
    pixman/pixman/pixman.c \
    pixman/pixman/pixman-image.c \
    pixman/pixman/pixman-bits-image.c
LOCAL_CFLAGS += -O3 -DHAVE_CONFIG_H
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := qemu_core

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/qemu \
    $(LOCAL_PATH)/qemu/include \
    $(LOCAL_PATH)/qemu/target/i386 \
    $(LOCAL_PATH)/qemu/target/arm \
    $(LOCAL_PATH)/pixman/pixman \
    $(LOCAL_PATH)/compat

LOCAL_SRC_FILES := \
    native-core.cpp \
    qemu/exec.c \
    qemu/cpu-exec.c \
    qemu/accel/accel.c \
    qemu/accel/kvm/kvm-all.c \
    qemu/accel/tcg/tcg-all.c \
    qemu/block/block-backend.c \
    qemu/hw/core/machine.c \
    qemu/hw/i386/pc.c \
    qemu/hw/pci/pci.c

LOCAL_CFLAGS += -O3 -flto -DANDROID \
                -DCONFIG_KVM -DCONFIG_TCG \
                -DCONFIG_X86_64 -DCONFIG_ARM64 \
                -include $(LOCAL_PATH)/compat/glibc_compat.h

LOCAL_LDFLAGS += -flto -Wl,--gc-sections
LOCAL_STATIC_LIBRARIES := pixman
LOCAL_LDLIBS := -llog -lz

include $(BUILD_SHARED_LIBRARY)