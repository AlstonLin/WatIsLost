LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := stlport
LOCAL_MODULE    := graph
LOCAL_SRC_FILES := graph.cpp
LOCAL_SHARED_LIBRARIES := stlport
LOCAL_CPP_FEATURES += exceptions
LOCAL_CPPFLAGS += -fexceptions
LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)