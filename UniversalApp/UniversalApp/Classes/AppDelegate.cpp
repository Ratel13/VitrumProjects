//
//  UniversalAppAppDelegate.cpp
//  UniversalApp
//
//  Created by NSS on 10/30/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"

USING_NS_CC;
using namespace CocosDenshion;

typedef struct tagResource
{
    cocos2d::CCSize size;
    char directory[100];
} Resource;


AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    
    static Resource smallResource  =  { cocos2d::CCSizeMake(480, 320),   "sd" };
    static Resource mediumResource =  { cocos2d::CCSizeMake(1024, 768),  "hd"   };
    static Resource largeResource  =  { cocos2d::CCSizeMake(2048, 1536), "hd" };
    static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(480, 320);
    
    std::vector<std::string> searchPath;
    CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
    
    CCDirector *pDirector = CCDirector::sharedDirector();
    
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    
    pDirector->setOpenGLView(pEGLView);
    
    // Set the design resolution
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);

    CCSize frameSize = pEGLView->getFrameSize();
    
	if (frameSize.height > mediumResource.size.height)
	{
        searchPath.push_back(largeResource.directory);
        
        pDirector->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width) * 0.5f);
	}
    // if the frame's height is larger than the height of small resource size, select medium resource.
    else if (frameSize.height > smallResource.size.height)
    {
        searchPath.push_back(mediumResource.directory);
        
        pDirector->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
	else
    {
        searchPath.push_back(smallResource.directory);
        
        pDirector->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
    }
    
    searchPath.push_back("WhackAMoleSounds");
    
    // set searching path
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
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
