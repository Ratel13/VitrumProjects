//
//  FapBirdAppDelegate.cpp
//  FapBird
//
//  Created by NSS on 2/10/14.
//  Copyright __MyCompanyName__ 2014. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "AppMacros.h"

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
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCEGLView* pEglView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEglView);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    pEglView->setDesignResolutionSize(SCREEN_WIDTH, SCREEN_HEIGHT, kResolutionNoBorder);
    
    std::vector<std::string> vectorSearchPaths;
    vectorSearchPaths.push_back("iphonehd");
    
    CCFileUtils::sharedFileUtils()->setSearchPaths(vectorSearchPaths);

    // create a scene. it's an autorelease object
    CCScene *pScene = GameScene::scene();

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
