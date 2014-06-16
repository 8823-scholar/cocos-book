LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
				   ../../Classes/CardLine.cpp \
				   ../../Classes/Card.cpp \
				   ../../Classes/EventListenerTouchOneByOneGesture.cpp \
				   ../../Classes/LoadingBar.cpp \
				   ../../Classes/VideoPlayer.cpp \
				   ../../Classes/sqlite/sqlite3.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_CPPFLAGS += -fexceptions

$(call import-add-path,../webview_plugin)
LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_webview_plugin_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,Box2D)
$(call import-module,network)
$(call import-module,editor-support/spine)
$(call import-module,webview_plugin/android)
