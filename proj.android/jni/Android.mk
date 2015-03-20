LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/stdafx.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/EngineHelper.cpp \
                   ../../Classes/UI/TitleBar.cpp \
                   ../../Classes/UI/BallButton.cpp \
                   ../../Classes/UI/EdgedBallButton.cpp \
                   ../../Classes/UI/BallSlider.cpp \
                   ../../Classes/UI/BallDialog.cpp \
                   ../../Classes/Element/MainBall.cpp \
                   ../../Classes/Element/SmartString.cpp \
                   ../../Classes/Element/Ring.cpp \
                   ../../Classes/Element/Target.cpp \
                   ../../Classes/Element/Block.cpp \
                   ../../Classes/Element/Triangle.cpp \
                   ../../Classes/Scene/BaseScene.cpp \
                   ../../Classes/Scene/WelcomeScene.cpp \
                   ../../Classes/Scene/MainGameScene.cpp \
                   ../../Classes/Scene/SettingsScene.cpp \
                   ../../Classes/Levels/BaseLevel.cpp \
                   ../../Classes/Levels/Levels.cpp \
                   ../../Classes/Levels/Level1.cpp \
                   ../../Classes/Levels/Level2.cpp \
                   ../../Classes/Levels/Level3.cpp \
                   ../../Classes/Levels/Level4.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
