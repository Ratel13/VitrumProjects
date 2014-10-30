//
//  CocosUtils.cpp
//  ShipGameCocos
//
//  Created by NSS on 9/4/14.
//
//

#include "CocosUtils.h"

USING_NS_CC;
using namespace CocosDenshion;

#pragma mark - Singleton
CocosUtils& CocosUtils::getInstance() {
    static CocosUtils _instance;
    return _instance;
}

#pragma mark - Application
Application* CocosUtils::getApplication() {
    return Application::getInstance();
}

#pragma mark - Director
Director* CocosUtils::getDirector() {
    return Director::getInstance();
}

GLView* CocosUtils::getOpenGLView() {
    return getDirector()->getOpenGLView();
}

Size CocosUtils::getWinSize() {
    return getDirector()->getWinSize();
}

Size CocosUtils::getVisibleSize() {
    return getDirector()->getVisibleSize();
}

Size CocosUtils::getFrameSize() {
    return getOpenGLView()->getFrameSize();
}

Vec2 CocosUtils::getVisibleOrigin() {
    return getDirector()->getVisibleOrigin();
}

Vec2 CocosUtils::getVisibleCenter() {
    
    Vec2 vec = Vec2();
    vec.x = getVisibleOrigin().x + getVisibleSize().width * 0.5f;
    vec.y = getVisibleOrigin().y + getVisibleSize().height * 0.5f;    
    return vec;
}

void CocosUtils::replaceScene(Scene* scene) {
    getDirector()->replaceScene(scene);
}

#pragma mark - Audio Engine
SimpleAudioEngine* CocosUtils::getAudioEngine() {
    return SimpleAudioEngine::getInstance();
}

void CocosUtils::playBackgroundMusic(const char* music, bool loop) {
    if(!isBackgroundMusicPlaying())
        getAudioEngine()->playBackgroundMusic(music, loop);
}

void CocosUtils::stopBackgroundMusic() {
    if(isBackgroundMusicPlaying())
        getAudioEngine()->stopBackgroundMusic();
}

void CocosUtils::rewindBackgroundMusic() {
    getAudioEngine()->rewindBackgroundMusic();
}

void CocosUtils::pauseBackgroundMusic() {
    if(isBackgroundMusicPlaying())
        getAudioEngine()->pauseBackgroundMusic();
}

void CocosUtils::resumeBackgroundMusic() {
    if(!isBackgroundMusicPlaying())
        getAudioEngine()->resumeBackgroundMusic();
}

bool CocosUtils::isBackgroundMusicPlaying() {
    return getAudioEngine()->isBackgroundMusicPlaying();
}

int CocosUtils::playEffect(const char* sfx, bool loop, float pitch, float pan, float gain ) {
    int soundID = getAudioEngine()->playEffect(sfx, loop, pitch, pan, gain);
    return soundID;
}

void CocosUtils::stopEffect(int soundID) {
    getAudioEngine()->stopEffect(soundID);
}

void CocosUtils::unloadEffect(const char* sfx) {
    getAudioEngine()->unloadEffect(sfx);
}

void CocosUtils::pauseEffect(int soundID) {
    getAudioEngine()->pauseEffect(soundID);
}

void CocosUtils::resumeEffect(int soundID) {
    getAudioEngine()->resumeEffect(soundID);
}

void CocosUtils::pauseAllEffects() {
    getAudioEngine()->pauseAllEffects();
}

void CocosUtils::resumeAllEffects() {
    getAudioEngine()->resumeAllEffects();
}

void CocosUtils::stopAllEffects() {
    getAudioEngine()->stopAllEffects();
}

void CocosUtils::setBackgroundMusicVolume(float volume) {
    getAudioEngine()->setBackgroundMusicVolume(volume);
}

void CocosUtils::setEffectsVolume(float volume) {
    getAudioEngine()->setEffectsVolume(volume);
}

void CocosUtils::preloadBackgroundMusic(const char* music) {
    getAudioEngine()->preloadBackgroundMusic(music);
}

void CocosUtils::preloadEffect(const char* sfx) {
    getAudioEngine()->preloadEffect(sfx);
}

float CocosUtils::getBackgroundMusicVolume() {
    return getAudioEngine()->getEffectsVolume();
}

float CocosUtils::getEffectsVolume() {
    return getAudioEngine()->getBackgroundMusicVolume();
}

#pragma mark - Platform
int CocosUtils::getPlatform() {
    return CC_TARGET_PLATFORM;
}

bool CocosUtils::isAndroid() {
    return getPlatform() == CC_PLATFORM_ANDROID;
}

bool CocosUtils::isMarmalade() {
    return getPlatform() == CC_PLATFORM_MARMALADE;
}

bool CocosUtils::isWin32() {
    return getPlatform() == CC_PLATFORM_WIN32;
}

bool CocosUtils::isWindowsPhone() {
    return getPlatform() == CC_PLATFORM_WP8;
}

bool CocosUtils::isIOS() {
    return getPlatform() == CC_PLATFORM_IOS;
}

bool CocosUtils::isBlackberry() {
    return getPlatform() == CC_PLATFORM_BLACKBERRY;
}

bool CocosUtils::isLinux() {
    return getPlatform() == CC_PLATFORM_LINUX;
}

bool CocosUtils::isMac() {
    return getPlatform() == CC_PLATFORM_MAC;
}

bool CocosUtils::isTizen() {
    return getPlatform() == CC_PLATFORM_TIZEN;
}

CocosUtilsDevice CocosUtils::getDevice() {
    
    CocosUtilsDevice device = DEVICE_UNKNOWN;
    Size size = getFrameSize();
    float width = size.width;
    float height = size.height;
    
    if(isIOS()) {
        
        if( (width == 2048 && height == 1536) ||
           (width == 1536 && height == 2048))
            return DEVICE_IPAD_RETINA;
        
        if( (width == 1024 && height == 768) ||
            (width == 768 && height == 1024))
            return DEVICE_IPAD_NORMAL;
        
        if( (width == 960 && height == 480) ||
           (width == 480 && height == 960))
            return DEVICE_IPHONE_RETINA;
        
        if( (width == 480 && height == 320) ||
           (width == 320 && height == 480))
            return DEVICE_IPAD_NORMAL;
        
        if( (width == 1136 && height == 640) ||
           (width == 640 && height == 1136))
            return DEVICE_IPHONE_5;
        
        if( (width == 1334 && height == 750) ||
           (width == 750 && height == 1334))
            return DEVICE_IPHONE_6;
        
    }else if(isAndroid()) {
        device = DEVICE_ANDROID;        
    }
    
    if( (width == 1024 && height == 600) ||
       (width == 600 && height == 1024))
        return DEVICE_1024x600;
    
    if( (width == 800 && height == 600) ||
       (width == 600 && height == 800))
        return DEVICE_800x600;
    
    if( (width == 800 && height == 480) ||
       (width == 480 && height == 800))
        return DEVICE_800x480;
    
    if( (width == 1280 && height == 800) ||
       (width == 800 && height == 1280))
        return DEVICE_1280x800;
    
    if( (width == 2560 && height == 1600) ||
       (width == 1600 && height == 2560))
        return DEVICE_2560x1600;
    
    if( (width == 1920 && height == 1280) ||
       (width == 1280 && height == 1920))
        return DEVICE_1920x1280;
    
    if( (width == 1920 && height == 1200) ||
       (width == 1200 && height == 1920))
        return DEVICE_1920x1200;
    
    if( (width == 1280 && height == 720) ||
       (width == 720 && height == 1280))
        return DEVICE_1280x720;
    
    if( (width == 1920 && height == 1080) ||
       (width == 1080 && height == 1920))
        return DEVICE_1920x1080;
    
    if( (width == 1280 && height == 768) ||
       (width == 768 && height == 1280))
        return DEVICE_1280x768;

    return device;
}

float CocosUtils::getRatio() {
    Size size = getFrameSize();
    float width = size.width;
    float height = size.height;
    
    if(width > height)
        return width / height;
    return height / width;
}

#pragma mark - Language
LanguageType CocosUtils::getCurrentLanguage() {
    return getApplication()->getCurrentLanguage();
}

bool CocosUtils::isEnglish() {
    return getCurrentLanguage() == LanguageType::ENGLISH;
}

bool CocosUtils::isChinese() {
    return getCurrentLanguage() == LanguageType::CHINESE;
}

bool CocosUtils::isFrench() {
    return getCurrentLanguage() == LanguageType::FRENCH;
}

bool CocosUtils::isGerman() {
    return getCurrentLanguage() == LanguageType::GERMAN;
}

bool CocosUtils::isItalian() {
    return getCurrentLanguage() == LanguageType::ITALIAN;
}

bool CocosUtils::isRussian() {
    return getCurrentLanguage() == LanguageType::RUSSIAN;
}

bool CocosUtils::isSpanish() {
    return getCurrentLanguage() == LanguageType::SPANISH;
}

bool CocosUtils::isKorean() {
    return getCurrentLanguage() == LanguageType::KOREAN;
}

bool CocosUtils::isJapanese() {
    return getCurrentLanguage() == LanguageType::JAPANESE;
}

bool CocosUtils::isHungarian() {
    return getCurrentLanguage() == LanguageType::HUNGARIAN;
}

bool CocosUtils::isPortuguese() {
    return getCurrentLanguage() == LanguageType::PORTUGUESE;
}

bool CocosUtils::isArabic() {
    return getCurrentLanguage() == LanguageType::ARABIC;
}

bool CocosUtils::isNorwegian() {
    return getCurrentLanguage() == LanguageType::NORWEGIAN;
}

bool CocosUtils::isPolish() {
    return getCurrentLanguage() == LanguageType::POLISH;
}

bool CocosUtils::isDutch() {
    return getCurrentLanguage() == LanguageType::DUTCH;
}

#pragma mark - User Default or LocalStorage
UserDefault* CocosUtils::getUserDefault() {
    return UserDefault::getInstance();
}

void CocosUtils::setStringForKey(std::string key, std::string value) {
    getUserDefault()->setStringForKey(key.c_str(), value);
    flush();
}

void CocosUtils::setIntegerForKey(std::string key, int value) {
    getUserDefault()->setIntegerForKey(key.c_str(), value);
    flush();
}

void CocosUtils::setFloatForKey(std::string key, float value) {
    getUserDefault()->setFloatForKey(key.c_str(), value);
    flush();
}

void CocosUtils::setDoubleForKey(std::string key, double value) {
    getUserDefault()->setDoubleForKey(key.c_str(), value);
    flush();
}

void CocosUtils::setBoolForKey(std::string key, bool value) {
    getUserDefault()->setBoolForKey(key.c_str(), value);
    flush();
}

std::string CocosUtils::getStringForKey(std::string key, std::string defaultValue) {
    return getUserDefault()->getStringForKey(key.c_str(), defaultValue);
}

int CocosUtils::getIntegerForKey(std::string key, int defaultValue) {
    return getUserDefault()->getIntegerForKey(key.c_str(), defaultValue);
}

float CocosUtils::getFloatForKey(std::string key, float defaultValue) {
    return getUserDefault()->getFloatForKey(key.c_str(), defaultValue);
}

double CocosUtils::getDoubleForKey(std::string key, double defaultValue) {
    return getUserDefault()->getDoubleForKey(key.c_str(), defaultValue);
}

bool CocosUtils::getBoolForKey(std::string key, bool defaultValue) {
    return getUserDefault()->getBoolForKey(key.c_str(), defaultValue);
}

// Save the data in the memory. Use after set the data in the User Default
void CocosUtils::flush() {
    getUserDefault()->flush();
}

