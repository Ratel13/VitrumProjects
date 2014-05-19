//
//  Bird.h
//  FapBird
//
//  Created by NSS on 2/10/14.
//
//

#ifndef __FapBird__Bird__
#define __FapBird__Bird__

#include "cocos2d.h"

class Bird : public cocos2d::CCSprite
{
public:
    Bird();
    virtual ~Bird();
    
    void jump();
    
    void update(float dt);
    
    void reset();
    
private:
    float speedY;
    
};

#endif /* defined(__FapBird__Bird__) */
