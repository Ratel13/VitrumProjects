//
//  GameScene.h
//  DuckHunt
//
//  Created by NSS on 1/14/14.
//
//

#ifndef __DuckHunt__GameScene__
#define __DuckHunt__GameScene__

#include "cocos2d.h"
#include "Duck.h"

enum
{
    kZorderBackground = -100,
    kZorderForeground = 9999
};

class GameScene : public cocos2d::CCLayer
{
public:
    GameScene();
    virtual ~GameScene();
    
    static cocos2d::CCScene* scene();
    
    virtual void update(float dt);
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
private:
    void _seedRandom();
    void _loadBackgroundAndForeground();
    
    void _testCase();
    
private:
    Duck* _duck;
    
};

#endif /* defined(__DuckHunt__GameScene__) */
