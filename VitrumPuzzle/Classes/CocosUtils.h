//
//  CocosUtils.h
//  ShipGameCocos
//
//  Created by NSS on 9/4/14.
//
//

#ifndef __ShipGameCocos__CocosUtils__
#define __ShipGameCocos__CocosUtils__

#include "cocos2d.h"

enum CocosUtilsDevice {
    DEVICE_UNKNOWN = 0,
    DEVICE_IPAD_RETINA = 1,
    DEVICE_IPAD_NORMAL = 2,
    DEVICE_IPHONE_5 = 3,
    DEVICE_IPHONE_RETINA = 4,
    DEVICE_IPHONE_NORMAL = 5,
    DEVICE_1024x600 = 6,
    DEVICE_800x600 = 7,
    DEVICE_800x480 = 8,
    DEVICE_1280x800 = 9,
    DEVICE_2560x1600 = 10,
    DEVICE_1920x1280 = 11,
    DEVICE_1920x1200 = 12,
    DEVICE_1280x720 = 13,
    DEVICE_1920x1080 = 14,
    DEVICE_1280x768 = 15,
    DEVICE_ANDROID = 16,
    DEVICE_IPHONE_6 = 17,
    DEVICE_OTHER = 9999
};

class CocosUtils {
public:
    static CocosUtils& getInstance();
    
    // Application
    cocos2d::Application* getApplication();
    
    // Director
    cocos2d::Director* getDirector();
    cocos2d::GLView* getOpenGLView();
    cocos2d::Size getWinSize();
    cocos2d::Size getVisibleSize();
    cocos2d::Size getFrameSize();
    cocos2d::Vec2 getVisibleOrigin();
    cocos2d::Vec2 getVisibleCenter();
    void replaceScene(cocos2d::Scene* scene);
    
    
    // Audio Engine
    CocosDenshion::SimpleAudioEngine* getAudioEngine();
    void playBackgroundMusic(const char* music, bool loop = false);
    void stopBackgroundMusic();
    void rewindBackgroundMusic();
    void pauseBackgroundMusic();
    void resumeBackgroundMusic();
    bool isBackgroundMusicPlaying();
    int playEffect(const char* sfx, bool loop = false, float pitch = 1, float pan = 1, float gain = 1);
    void stopEffect(int soundID);
    void unloadEffect(const char* sfx);
    void pauseEffect(int soundID);
    void resumeEffect(int soundID);
    void pauseAllEffects();
    void resumeAllEffects();
    void stopAllEffects();
    void setBackgroundMusicVolume(float volume);
    void setEffectsVolume(float volume);
    void preloadBackgroundMusic(const char* music);
    void preloadEffect(const char* sfx);
    float getBackgroundMusicVolume();
    float getEffectsVolume();
    
    // Platform
    int getPlatform();
    bool isAndroid();
    bool isMarmalade();
    bool isWin32();
    bool isWindowsPhone();
    bool isIOS();
    bool isBlackberry();
    bool isLinux();
    bool isMac();
    bool isTizen();
    CocosUtilsDevice getDevice();
    float getRatio();
    
    // Language
    cocos2d::LanguageType getCurrentLanguage();
    bool isEnglish();
    bool isChinese();
    bool isFrench();
    bool isGerman();
    bool isItalian();
    bool isRussian();
    bool isSpanish();
    bool isKorean();
    bool isJapanese();
    bool isHungarian();
    bool isPortuguese();
    bool isArabic();
    bool isNorwegian();
    bool isPolish();
    bool isDutch();
    
    // User Default
    cocos2d::UserDefault* getUserDefault();
    void flush();
    void setStringForKey(std::string key, std::string value);
    void setIntegerForKey(std::string key, int value);
    void setFloatForKey(std::string key, float value);
    void setDoubleForKey(std::string key, double value);
    void setBoolForKey(std::string key, bool value);
    std::string getStringForKey(std::string key, std::string defaultValue = "");
    int getIntegerForKey(std::string key, int defaultValue = 0);
    float getFloatForKey(std::string key, float defaultValue = 0.0f);
    double getDoubleForKey(std::string key, double defaultValue = 0.0);
    bool getBoolForKey(std::string key, bool defaultValue = true);
    
private:
    CocosUtils() {};
    CocosUtils(CocosUtils const&);
    void operator=(CocosUtils const&);
};

#endif /* defined(__ShipGameCocos__CocosUtils__) */
