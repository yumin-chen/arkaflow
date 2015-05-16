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
                   ../../Classes/Element/SmartString.cpp \
                   ../../Classes/Element/Ring.cpp \
                   ../../Classes/Element/Target.cpp \
                   ../../Classes/Element/Brick.cpp \
                   ../../Classes/Element/Triangle.cpp \
                   ../../Classes/Element/Diamond.cpp \
                   ../../Classes/Scene/BaseScene.cpp \
                   ../../Classes/Scene/SplashScene.cpp \
                   ../../Classes/Scene/WelcomeScene.cpp \
                   ../../Classes/Scene/MainGameScene.cpp \
                   ../../Classes/Scene/SettingsScene.cpp \
                   ../../Classes/Scene/LevelPickerScene.cpp \
                   ../../Classes/Scene/AboutScene.cpp \
                   ../../Classes/Levels/BaseLevel.cpp \
                   ../../Classes/Levels/Levels.cpp \
                   ../../Classes/Levels/Level1.cpp \
                   ../../Classes/Levels/Level2.cpp \
                   ../../Classes/Levels/Level3.cpp \
                   ../../Classes/Levels/Level4.cpp \
                   ../../Classes/Levels/Level5.cpp \
                   ../../Classes/Levels/Level6.cpp \
                   ../../Classes/Levels/Level7.cpp \
                   ../../Classes/Levels/Level8.cpp \
                   ../../Classes/Levels/Level9.cpp \
                   ../../Classes/Levels/Level10.cpp \
                   ../../Classes/Levels/Level11.cpp \
                   ../../Classes/Levels/Level12.cpp \
                   ../../Classes/Levels/Level13.cpp \
                   ../../Classes/Levels/Level14.cpp \
                   ../../Classes/Levels/Level15.cpp \
                   ../../Classes/Levels/Level16.cpp \
                   ../../Classes/Levels/Level17.cpp \
                   ../../Classes/Levels/Level18.cpp \
                   ../../Classes/Levels/Level19.cpp \
                   ../../Classes/Levels/Level20.cpp \
                   ../../Classes/Levels/Level21.cpp \
                   ../../Classes/Levels/Level22.cpp \
                   ../../Classes/Levels/Level23.cpp \
                   ../../Classes/Levels/Level24.cpp \

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
