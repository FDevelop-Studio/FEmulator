import org.jetbrains.kotlin.gradle.dsl.JvmTarget

plugins {
    alias(libs.plugins.kotlinMultiplatform)
    alias(libs.plugins.androidMultiplatformLibrary)
    alias(libs.plugins.composeMultiplatform)
    alias(libs.plugins.composeCompiler)
}

kotlin {
    jvm()

    android {
        namespace = "org.fdevelop.emulator.shared"
        compileSdk = libs.versions.android.compileSdk.get().toInt()
        minSdk = libs.versions.android.minSdk.get().toInt()

        androidResources {
            enable = true
        }
        compilerOptions {
            jvmTarget = JvmTarget.JVM_11
        }
        withHostTest {
            isIncludeAndroidResources = true
        }
        withDeviceTestBuilder {
            sourceSetTreeName = "test"
        }.configure {
            instrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
        }
    }

    sourceSets {
        androidMain.dependencies {
            implementation(libs.compose.uiToolingPreview)
            implementation(libs.compose.uiTooling)
        }
        commonMain.dependencies {
            implementation(libs.compose.runtime)
            implementation(libs.compose.foundation)
            implementation(libs.compose.material3)
            implementation(libs.compose.ui)
            implementation(libs.compose.components.resources)
            implementation(libs.compose.uiToolingPreview)
            implementation(libs.androidx.lifecycle.viewmodelCompose)
            implementation(libs.androidx.lifecycle.runtimeCompose)
            implementation(libs.okio)
        }
        commonTest.dependencies {
            implementation(libs.kotlin.test)
        }
    }
}

tasks.register<Exec>("compileNativeCore") {
    group = "build"
    description = "Compiles monolithic jni.cpp core using native CMake engine"
    workingDir = file("src/commonMain/cpp")
    commandLine = if (org.gradle.internal.os.OperatingSystem.current().isWindows) {
        listOf("cmd", "/c", "cmake . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release")
    } else {
        listOf("sh", "-c", "cmake . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release")
    }
}

tasks.matching { it.name.contains("compileKotlin") }.configureEach {
    dependsOn("compileNativeCore")
}

dependencies {
    androidRuntimeClasspath(libs.compose.uiTooling)
}