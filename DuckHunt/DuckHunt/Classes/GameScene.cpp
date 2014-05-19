//
//  GameScene.cpp
//  DuckHunt
//
//  Created by NSS on 1/14/14.
//
//

#include "GameScene.h"
#include "AppMacros.h"
#include <cstdlib>
#include <ctime>

using namespace cocos2d;
using namespace std;

#pragma mark - Constructor, Destructor and static scene controller
CCScene* GameScene::scene()
{
    CCScene* scene = CCScene::create();
    CCLayer* layer = new GameScene();
    layer->autorelease();
    scene->addChild(layer);
    return scene;
}

GameScene::GameScene()
{
    _seedRandom();
    _loadBackgroundAndForeground();
    
    _testCase();
    
    setTouchEnabled(true);
    scheduleUpdate();
    
}

GameScene::~GameScene()
{
    CCLog("Deallocating memory");
}

#pragma mark - Methods to control logic and touch

void GameScene::update(float dt)
{
    _duck->update(dt);
}

void GameScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch* touch = (CCTouch*) pTouches->anyObject();
    if(touch)
    {
        if(_duck != NULL)
        {
            CCPoint position = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
            _duck->detectCollision(position);
        }
    }
}

#pragma mark - Methods to configure the game
void GameScene::_seedRandom()
{
    srand(time(0));
}

void GameScene::_loadBackgroundAndForeground()
{
    CCSprite* background = CCSprite::create("bgduckhuntgame.jpg");
    background->setAnchorPoint(ccp(0, 0));
    addChild(background, kZorderBackground);
    
    CCSprite* foreground = CCSprite::create("foreground.png");
    foreground->setAnchorPoint(ccp(0, 0));
    foreground->setPositionY(100);
    addChild(foreground, kZorderForeground);
    
}

void GameScene::_testCase()
{
    _duck = Duck::create();
    addChild(_duck);
}

