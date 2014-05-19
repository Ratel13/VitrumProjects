//
//  Tube.cpp
//  FapBird
//
//  Created by NSS on 2/10/14.
//
//

#include "Tube.h"
#include "AppMacros.h"

using namespace cocos2d;

Tube::Tube()
{
    setAnchorPoint(ccp(0, 0));
    _createTubes();
}

Tube::~Tube()
{
    
}

Tube* Tube::create()
{
    Tube* tube = new Tube();
    tube->autorelease();
    return tube;
}

void Tube::reset()
{
    this->removeAllChildren();
    _createTubes();
}

void Tube::_createTubes()
{
    tubePassed = false;
    tubeWidth = 0;
    
    float y = 0;
    CCSprite* tube;
    
    int bottomTube = (int) (CCRANDOM_0_1() * 9 + 2);
    
    for(int i = 0; i < bottomTube; i++)
    {
        
        tube = CCSprite::create("part_tube.png");
        tube->setAnchorPoint(ccp(0, 0));
        tube->setPositionY(y);
        addChild(tube);
        
        y += tube->getContentSize().height - 1;
        
        if(tubeWidth == 0)
            tubeWidth = tube->getContentSize().width;
        
    }
    
    tube = CCSprite::create("top_tube.png");
    tube->setAnchorPoint(ccp(0, 0));
    tube->setPositionY(y);
    addChild(tube);
    
    tubeBottomCollision = CCRectMake(0, 0, tubeWidth, y + tube->getContentSize().height);
    
    y += tube->getContentSize().height * 4.5f;
    
    float startTopY = y;
    
    tube = CCSprite::create("top_tube.png");
    tube->setFlipY(true);
    tube->setAnchorPoint(ccp(0, 0));
    tube->setPositionY(y);
    addChild(tube);
    
    y += tube->getContentSize().height - 1;
    
    while(y < SCREEN_HEIGHT + tube->getContentSize().height)
    {
        tube = CCSprite::create("part_tube.png");
        tube->setFlipY(true);
        tube->setAnchorPoint(ccp(0, 0));
        tube->setPositionY(y);
        addChild(tube);
        
        y += tube->getContentSize().height - 1;
    }
    
    tubeTopCollision = CCRectMake(0, startTopY, tubeWidth, y);
    
}