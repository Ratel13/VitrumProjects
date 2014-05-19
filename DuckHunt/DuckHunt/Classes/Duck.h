//
//  Duck.h
//  DuckHunt
//
//  Created by NSS on 1/14/14.
//
//

#ifndef __DuckHunt__Duck__
#define __DuckHunt__Duck__

#include "cocos2d.h"

enum DuckType
{
    kRedDuck = 0,
    kBlueDuck = 1,
    kGreenDuck = 2
};

enum DuckStateAnimation
{
    kAnimationNone = 0,
    kAnimationLeft = 1,
    kAnimationRight = 2,
    kAnimationDLeft = 3,
    kAnimationDRight = 4,
    kAnimationEscape = 5
};

enum DuckState
{
    kStateAlive = 0,
    kStateDying = 1,
    kStateFalling = 2
};

class Duck : public cocos2d::CCSprite
{
public:
    Duck(DuckType type = kRedDuck);
    ~Duck();
    
    static Duck* create(DuckType type = kRedDuck);
    
    void detectCollision(cocos2d::CCPoint position);
    void update(float dt);
    void reset();
    
private:
    
    float speed;
    float cuakSFX;
    
    DuckState currentState;
    DuckStateAnimation currentAnimation;
    bool canEscape;
        
    std::vector<cocos2d::CCPoint> _paths;
    
    cocos2d::CCAnimation* _rightAnimation;
    cocos2d::CCAnimation* _diagonalRightAnimation;
    cocos2d::CCAnimation* _escapingAnimation;
    
    cocos2d::CCAction* _currentActionAnimation;
    
    cocos2d::CCTexture2D* _dyingTexture;
    cocos2d::CCTexture2D* _fallingTexture;
    
private:
    void _runAnimation();
    void _fallingAction();
    
};

#endif /* defined(__DuckHunt__Duck__) */
