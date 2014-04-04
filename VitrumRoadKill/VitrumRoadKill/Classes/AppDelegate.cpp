//
//  VitrumRoadKillAppDelegate.cpp
//  VitrumRoadKill
//
//  Created by NSS on 4/3/14.
//  Copyright __MyCompanyName__ 2014. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"
#include "Constants.h"
#include "GameScreen.h"
#include <vector>
#include <string>

USING_NS_CC;
using namespace CocosDenshion;
using namespace std;

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
    
    // Carga de recursos por resolución
    
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
    
    CCSize frameSize = pEGLView->getFrameSize();
    float ratio = frameSize.width / frameSize.height;
    CCLog("ratio: %f", ratio);
    
    vector<string> searchPaths;
    
    if(frameSize.height > res_ratio_ipad.size.height)
    {
        searchPaths.push_back(res_ratio_ipadhd.directory);
    }
    else if(frameSize.height > res_ratio_178.size.height)
    {
        searchPaths.push_back(res_ratio_ipad.directory);
    }
    else if(frameSize.height > res_ratio_16.size.height)
    {
        searchPaths.push_back(res_ratio_178.directory);
    }
    else
    {
        searchPaths.push_back(res_ratio_16.directory);
    }
    
    searchPaths.push_back("audio");
    
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
    
    // Finaliza carga de recursos por resolución

    // turn on display FPS
    pDirector->setDisplayStats(SHOW_FPS);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = GameScreen::scene();

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
