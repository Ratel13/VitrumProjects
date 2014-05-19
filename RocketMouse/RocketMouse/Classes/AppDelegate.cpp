//
//  RocketMouseAppDelegate.cpp
//  RocketMouse
//
//  Created by NSS on 5/15/14.
//  Copyright __MyCompanyName__ 2014. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);
    
    //
    
    pEGLView->setDesignResolutionSize(480, 320, kResolutionNoBorder);
    
    std::vector<std::string> searchPaths;
    
    searchPaths.push_back("assets/Images");
    searchPaths.push_back("assets/Images/animations/bunny");
    searchPaths.push_back("assets/Images/animations/laser");
    searchPaths.push_back("assets/Images/animations/player");
    searchPaths.push_back("assets/Images/background");
    searchPaths.push_back("assets/Images/objects");
    
    searchPaths.push_back("assets/Levels");
    
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
