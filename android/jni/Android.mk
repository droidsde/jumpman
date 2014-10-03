LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame


LOCAL_SRC_FILES := main.cpp \
					../../Classes/AppDelegate.cpp \
					../../Classes/MainScene.cpp \
					../../Classes/GameOverScene.cpp \
					../../Classes/GameScene.cpp \
					../../Classes/MainMenuScene.cpp \
					../../Classes/PauseMenuScene.cpp \
					../../Classes/SharedData.cpp
				

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \


LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocos_extension_static cocosdenshion_static box2d_static curl_static_prebuilt
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_store_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) 
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,cocos2dx) 
$(call import-module,extensions)

$(call import-module, extensions/cocos2dx-store/android/jni)

