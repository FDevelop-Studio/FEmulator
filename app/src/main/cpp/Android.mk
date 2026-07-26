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
    $(LOCAL_PATH)/pixman/pixman \
    $(LOCAL_PATH)/compat

LOCAL_SRC_FILES := compat/glibc_compat.h

LOCAL_CFLAGS += -include $(LOCAL_PATH)/compat/glibc_compat.h
LOCAL_STATIC_LIBRARIES := pixman
LOCAL_CFLAGS += -O3 -DANDROID -DCONFIG_KVM
LOCAL_LDLIBS := -llog -lz

include $(BUILD_SHARED_LIBRARY)