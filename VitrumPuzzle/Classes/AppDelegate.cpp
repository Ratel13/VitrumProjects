#include "AppDelegate.h"
#include "GameConfig.h"
#include "CocosUtils.h"
#include "GameScreen.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create( GAME_NAME );
        director->setOpenGLView( glview  );
    }

    // turn on display FPS
    director->setDisplayStats(DISPLAY_STATS);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // Search Path
    std::vector<std::string> searchPaths;
    searchPaths.push_back("Common");
    
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    
    glview->setDesignResolutionSize(SCREEN_WIDTH, SCREEN_HEIGHT, ResolutionPolicy::NO_BORDER);
    // create a scene. it's an autorelease object
    auto scene = GameScreen::scene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    CocosUtils::getInstance().pauseBackgroundMusic();
    CocosUtils::getInstance().pauseAllEffects();

}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    
    CocosUtils::getInstance().resumeBackgroundMusic();
    CocosUtils::getInstance().resumeAllEffects();

}
