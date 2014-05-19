//
//  HelloWorldScene.h
//  RocketMouse
//
//  Created by NSS on 5/15/14.
//  Copyright __MyCompanyName__ 2014. All rights reserved.
//
#ifndef __HELLO_WORLD_H__
#define __HELLO_WORLD_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"
#include "LevelHelperLoader.h"

#define PTM_RATIO 32.0f

class HelloWorld : public cocos2d::CCLayer {
public:
    ~HelloWorld();
    HelloWorld();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    
    void initPhysics();
    virtual void draw();
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void update(float dt);
    
private:
    b2World* world;
    cocos2d::CCTexture2D* m_pSpriteTexture; // weak ref
    LevelHelperLoader* loader;
};

#endif // __HELLO_WORLD_H__
