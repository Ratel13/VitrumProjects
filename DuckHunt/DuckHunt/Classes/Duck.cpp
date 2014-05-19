//
//  Duck.cpp
//  DuckHunt
//
//  Created by NSS on 1/14/14.
//
//

#include "Duck.h"
#include "AppMacros.h"
#include <algorithm>
#include <vector>
#include "Utils.h"
#include "SimpleAudioEngine.h"

#define FALLING_SPEED 100.0f
#define SPEED_INCREMENT 20.0f
#define TAG_ACTION_MOVE 10000

using namespace cocos2d;
using namespace CocosDenshion;

Duck* Duck::create(DuckType type)
{
    Duck* duck = new Duck(type);
    duck->autorelease();
    return duck;
}

Duck::~Duck()
{
    CC_SAFE_RELEASE(_rightAnimation);
    CC_SAFE_RELEASE(_diagonalRightAnimation);
    CC_SAFE_RELEASE(_escapingAnimation);
    
    CC_SAFE_RELEASE(_dyingTexture);
    CC_SAFE_RELEASE(_fallingTexture);
}

Duck::Duck(DuckType type)
{
    initWithFile("red_duck01.png");
    
    _rightAnimation = NULL;
    _diagonalRightAnimation = NULL;
    _escapingAnimation = NULL;
    _dyingTexture = NULL;
    _fallingTexture = NULL;
    
    
    // Loading Right Animation
    _rightAnimation = CCAnimation::create();
    _rightAnimation->setDelayPerUnit(1.0f / 10.0f);
    _rightAnimation->setRestoreOriginalFrame(false);
    _rightAnimation->addSpriteFrameWithFileName("red_duck01.png");
    _rightAnimation->addSpriteFrameWithFileName("red_duck02.png");
    _rightAnimation->addSpriteFrameWithFileName("red_duck03.png");
    _rightAnimation->addSpriteFrameWithFileName("red_duck04.png");
    _rightAnimation->retain();
    
    // Loading Diagonal Right Animation
    _diagonalRightAnimation = CCAnimation::create();
    _diagonalRightAnimation->setDelayPerUnit(1.0f / 10.0f);
    _diagonalRightAnimation->setRestoreOriginalFrame(false);
    _diagonalRightAnimation->addSpriteFrameWithFileName("red_duck05.png");
    _diagonalRightAnimation->addSpriteFrameWithFileName("red_duck06.png");
    _diagonalRightAnimation->retain();
    
    // Loading Escaping Animation
    _escapingAnimation = CCAnimation::create();
    _escapingAnimation->setDelayPerUnit(1.0f / 10.0f);
    _escapingAnimation->setRestoreOriginalFrame(false);
    _escapingAnimation->addSpriteFrameWithFileName("red_duck07.png");
    _escapingAnimation->addSpriteFrameWithFileName("red_duck08.png");
    _escapingAnimation->addSpriteFrameWithFileName("red_duck09.png");
    _escapingAnimation->retain();
    
    // Set dying texture
    CCSprite* dyingSprite = CCSprite::create("red_duck10.png");
    _dyingTexture = dyingSprite->getTexture();
    _dyingTexture->retain();
    
    // Set falling texture
    CCSprite* fallingSprite = CCSprite::create("red_duck11.png");
    _fallingTexture = fallingSprite->getTexture();
    _fallingTexture->retain();
    
    speed = 70.0f;
    
    reset();
}

void Duck::reset()
{
    stopAllActions();
    
    speed += SPEED_INCREMENT;
    
    currentState = kStateAlive;
    canEscape = false;
    cuakSFX = 0.0f;
    
    // Set path and locate in the map
    
    float x, y;
    
    _paths.clear();
    
    
    for(int i = 1; i <= 7; i++)
    {
        x = Utils::getNumberBetween(MIN_X, MAX_X);
        y = Utils::getNumberBetween(MIN_Y, MAX_Y);
        
        _paths.push_back(ccp(x, y));
        
    }
    
    random_shuffle(_paths.begin(), _paths.end());
    
    x = Utils::getNumberBetween(MIN_X, MAX_X);
    y = START_DUCK_Y + getContentSize().height * 0.25f;
    _paths.insert(_paths.begin(), ccp(x, y));
    
    setPositionX(Utils::getNumberBetween(MIN_X, MAX_X));
    setPositionY(START_DUCK_Y);
    
    currentAnimation = kAnimationNone;
    _currentActionAnimation = NULL;
    
}

void Duck::update(float dt)
{
    if(currentState == kStateAlive)
    {
        
        if(!canEscape)
        {
            
            cuakSFX += dt;
            
            if(cuakSFX >= 1.5f)
            {
                SimpleAudioEngine::sharedEngine()->playEffect("cuak.mp3");
                cuakSFX = 0.0f;
            }
            
            
            if(getActionByTag(TAG_ACTION_MOVE) == NULL)
            {
                CCPoint newPosition;
                float distance, time;
                
                if(!_paths.empty())
                {
                    
                    DuckStateAnimation newState = kAnimationRight;
                    
                    newPosition = _paths[_paths.size() - 1];
                    _paths.pop_back();
                    
                    distance = ccpDistance(newPosition, getPosition());
                    time = distance / speed;
                    
                    float angle = atan2f(newPosition.y - getPositionY(), newPosition.x - getPositionX()) * 180 / PI + 180;
                    
                    
                    bool left = newPosition.x < getPositionX();
                    
                    if(left && angle < 180)
                        newState = kAnimationLeft;
                    else if(left && angle >= 180)
                        newState = kAnimationDLeft;
                    else if(!left && angle >= 180)
                        newState = kAnimationDRight;
                    
                    
                    if(newState != currentAnimation)
                    {
                        currentAnimation = newState;
                        _runAnimation();
                    }
                    
                    CCMoveTo* moveToAction = CCMoveTo::create(time, newPosition);
                    moveToAction->setTag(TAG_ACTION_MOVE);
                    runAction(moveToAction);
                    
                }
                else
                {
                    canEscape = true;
                    
                    if(getPositionY() < END_DUCK_Y)
                    {
                        
                        currentAnimation = kAnimationEscape;
                        _runAnimation();
                        
                        newPosition = ccp(getPositionX(), END_DUCK_Y);
                        
                        distance = ccpDistance(newPosition, getPosition());
                        time = distance / speed;
                        
                        CCMoveTo* moveToAction = CCMoveTo::create(time, newPosition);
                        moveToAction->setTag(TAG_ACTION_MOVE);
                        runAction(moveToAction);
                    }
                    
                }
                
            }
        }
    }
    
    if(canEscape && getPositionY() + getContentSize().height * 1.5f >= END_DUCK_Y)
    {
        speed -= SPEED_INCREMENT;
        reset();
    }
}

void Duck::_runAnimation()
{
    
    if(_currentActionAnimation != NULL)
    {
        stopAction(_currentActionAnimation);
        _currentActionAnimation = NULL;
    }
    
    setFlipX(false);
    
    switch(currentAnimation)
    {
        case kAnimationLeft:
        case kAnimationRight:
            _currentActionAnimation = CCRepeatForever::create(CCAnimate::create(_rightAnimation));
            if(currentAnimation == kAnimationLeft)
                setFlipX(true);
            
            break;
            
        case kAnimationDLeft:
        case kAnimationDRight:
            _currentActionAnimation = CCRepeatForever::create(CCAnimate::create(_diagonalRightAnimation));
            if(currentAnimation == kAnimationDLeft)
                setFlipX(true);
            break;
            
        case kAnimationEscape:
            _currentActionAnimation = CCRepeatForever::create(CCAnimate::create(_escapingAnimation));
            break;
            
        default:
            break;
    };
    
    if(_currentActionAnimation != NULL)
        runAction(_currentActionAnimation);
}

void Duck::detectCollision(cocos2d::CCPoint position)
{
    if(currentState == kStateAlive && !canEscape)
    {
        // CCLog("Position Touch: %f ; %f", position.x, position.y);
        if(boundingBox().containsPoint(position))
        {
            
            SimpleAudioEngine::sharedEngine()->playEffect("shoot_hit.mp3");
            
            currentState = kStateDying;
            stopAllActions();
            setTexture(_dyingTexture);
            runAction(CCSequence::create(
                        CCDelayTime::create(1.5f),
                        CCCallFuncO::create(this, callfuncO_selector(Duck::_fallingAction), NULL),
                        NULL));
        }
        else
        {
            SimpleAudioEngine::sharedEngine()->playEffect("shoot_miss.mp3");
        }
    }
}

void Duck::_fallingAction()
{
    if(currentState != kStateFalling)
    {
        currentState = kStateFalling;
        setTexture(_fallingTexture);
        
        CCSequence* seq = CCSequence::create(CCMoveBy::create(0.05f, ccp(-1, 0)), CCMoveBy::create(0.05f, ccp(1, 0)), NULL);
        
        runAction(CCRepeatForever::create(seq));
        
    }

    CCPoint newPosition = ccp(getPositionX(), START_DUCK_Y);
    
    float distance = ccpDistance(newPosition, getPosition());
    float time = distance / FALLING_SPEED;
    
    runAction(CCSequence::create(CCMoveTo::create(time, newPosition), CCCallFuncO::create(this, callfuncO_selector(Duck::reset), NULL),
                                 NULL));
    
}
