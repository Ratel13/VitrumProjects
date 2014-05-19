//
//  GameScene.cpp
//  FapBird
//
//  Created by NSS on 2/10/14.
//
//

#include "GameScene.h"
#include "Tube.h"
#include "AppMacros.h"

using namespace cocos2d;

GameScene::GameScene()
{
    
    initWithColor(ccc4(173, 216, 230, 255));
    
    srand(time(0));
    
    _tubesArray = CCArray::createWithCapacity(MAX_TUBES);
    _tubesArray->retain();
    
    int i;
    float x = START_TUBE_X;
    
    for(i = 0; i < MAX_TUBES; i++)
    {
        Tube* tube = Tube::create();
        tube->setPositionX(x);
        addChild(tube);
        _tubesArray->addObject(tube);
        x += DISTANCE_TUBE_X;
    }
    
    _parallaxArray = CCArray::createWithCapacity(3);
    _parallaxArray->retain();
    
    x = 0;
    for(i = 0; i < 3; i++)
    {
        CCSprite* spriteParallax = CCSprite::create("parallax.png");
        spriteParallax->setAnchorPoint(ccp(0, 0));
        spriteParallax->setPosition(ccp(x, 0));
        x += spriteParallax->getContentSize().width;
        addChild(spriteParallax, 10);
        _parallaxArray->addObject(spriteParallax);
    }
    
    _bird = new Bird();
    _bird->setPositionX(SCREEN_WIDTH * 0.25f);
    _bird->setPositionY(SCREEN_HEIGHT * 0.5f);
    _bird->autorelease();
    
    addChild(_bird);
    
    reset();
    
    scheduleUpdate();
    
    setTouchEnabled(true);
    
}

GameScene::~GameScene()
{
    CC_SAFE_RELEASE(_tubesArray);
    CC_SAFE_RELEASE(_parallaxArray);
}

CCScene* GameScene::scene()
{
    CCScene* scene = CCScene::create();
    GameScene* layer = new GameScene();
    layer->autorelease();
    scene->addChild(layer);
    return scene;
}

void GameScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch* touch = (CCTouch *) pTouches->anyObject();
    if(touch && !_gameOver)
    {
        if(!_isGameStarted)
            _isGameStarted = true;
        
        _bird->jump();
    }
}

void GameScene::reset()
{
    _score = 0;
    _gameOver = false;
    _isGameStarted = false;
}

void GameScene::update(float dt)
{
    
    CCObject* objectParallax;
    
    if(!_gameOver)
    {
        
        // Move parallax
        CCARRAY_FOREACH(_parallaxArray, objectParallax)
        {
            CCSprite* spriteParallax = (CCSprite*) objectParallax;
            float x = spriteParallax->getPositionX() - GAME_SPEED * dt;
            if(x < -spriteParallax->getContentSize().width)
            {
                float diff = spriteParallax->getContentSize().width + x;
                x = spriteParallax->getContentSize().width * 2 + diff;
            }
            spriteParallax->setPositionX(x);
            
        }
        
        if(_isGameStarted)
        {
            
            // Move tubes
            
            Tube* toRemove = NULL;
            Tube* lastTube = (Tube *) _tubesArray->objectAtIndex(MAX_TUBES - 1);
            
            CCARRAY_FOREACH(_tubesArray, objectParallax)
            {
                Tube* tube = (Tube *) objectParallax;
                
                CCRect tubeBottomCollision = tube->getTubeBottomCollision();
                CCRect tubeTopCollision = tube->getTubeTopCollision();
                
                tubeBottomCollision.setRect(tubeBottomCollision.getMinX() + tube->getPositionX(), tubeBottomCollision.getMinY(), tubeBottomCollision.getMaxX() + tube->getPositionX(), tubeBottomCollision.getMaxY());
                
                tubeTopCollision.setRect(tubeTopCollision.getMinX() + tube->getPositionX(), tubeTopCollision.getMinY(), tubeTopCollision.getMaxX() + tube->getPositionX(), tubeTopCollision.getMaxY());
                
                if(_bird->boundingBox().intersectsRect(tubeBottomCollision) || _bird->boundingBox().intersectsRect(tubeTopCollision))
                {
                    _gameOver = true;
                    break;
                }
                else
                {
                    float x = tube->getPositionX() - GAME_SPEED * dt;
                    if(x < -tube->getTubeWidth())
                    {
                        tube->setPositionX(lastTube->getPositionX() + DISTANCE_TUBE_X);
                        tube->reset();
                        toRemove = tube;
                    }
                    else
                    {
                        tube->setPositionX(x);
                    }
                    
                    if(!tube->getTubePassed() && tube->getPositionX() < _bird->getPositionX())
                    {
                        _score++;
                        CCLog("Current Score: %d", _score);
                        tube->setTubePassed(true);
                    }
                    
                }
                
            }
            
            if(toRemove != NULL)
            {
                _tubesArray->removeObjectAtIndex(0);
                _tubesArray->addObject(toRemove);
            }
            
            // Update bird
            _bird->update(dt);
            
        }
    }
    else
    {
        
    }
    
    
}

void GameScene::draw()
{
    CCLayer::draw();
    
    CCObject* object;
    CCPoint origin;
    CCPoint destination;
    
    CCARRAY_FOREACH(_tubesArray, object)
    {
        Tube* tube = (Tube *) object;
        
        CCRect tubeBottomCollision = tube->getTubeBottomCollision();
        CCRect tubeTopCollision = tube->getTubeTopCollision();
        
        origin = ccp(tubeBottomCollision.getMinX() + tube->getPositionX(), tubeBottomCollision.getMinY());
        destination = ccp(tubeBottomCollision.getMaxX() + tube->getPositionX(), tubeBottomCollision.getMaxY());
        
        ccDrawSolidRect(origin, destination, ccc4f(255, 0, 0, 128));
        
        origin = ccp(tubeTopCollision.getMinX() + tube->getPositionX(), tubeTopCollision.getMinY());
        destination = ccp(tubeTopCollision.getMaxX() + tube->getPositionX(), tubeTopCollision.getMaxY());
        
        ccDrawSolidRect(origin, destination, ccc4f(0, 0, 255, 128));
        
    }
    
    origin = ccp(_bird->boundingBox().getMinX(), _bird->boundingBox().getMinY());
    destination = ccp(_bird->boundingBox().getMaxX(), _bird->boundingBox().getMaxY());
    ccDrawSolidRect(origin, destination, ccc4f(0, 255, 0, 128));
    
}