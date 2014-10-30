//
//  BaseScreen.h
//  Invaders
//
//  Created by NorthSouth Studios on 9/19/14.
//
//

#ifndef __Invaders__BaseScreen__
#define __Invaders__BaseScreen__

#include "cocos2d.h"

class BaseScreen : public cocos2d::Layer {
public:
    BaseScreen();
    virtual ~BaseScreen();
    virtual void setupLayout() = 0;
    
    CC_SYNTHESIZE(cocos2d::Size, visibleSize, VisibleSize);
    CC_SYNTHESIZE(cocos2d::Vec2, visibleCenter, VisibleCenter);
    CC_SYNTHESIZE(cocos2d::Vec2, visibleOrigin, VisibleOrigin);
    CC_SYNTHESIZE(float, topScreen, TopScreen);
    CC_SYNTHESIZE(float, rightScreen, RightScreen);
    
};

#endif /* defined(__Invaders__BaseScreen__) */
