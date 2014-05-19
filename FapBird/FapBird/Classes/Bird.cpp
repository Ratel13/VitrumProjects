//
//  Bird.cpp
//  FapBird
//
//  Created by NSS on 2/10/14.
//
//

#include "Bird.h"
#include "AppMacros.h"

using namespace cocos2d;

Bird::Bird()
{
    initWithFile("kirby.png");
    reset();
}

Bird::~Bird()
{
    
}

void Bird::jump()
{
    speedY += GRAVITY * 20;
}

void Bird::update(float dt)
{
    speedY -= GRAVITY;
    
    if(speedY > MAX_SPEED_Y)
        speedY = MAX_SPEED_Y;
    
    else if(speedY < -MAX_SPEED_Y)
        speedY = -MAX_SPEED_Y;
    
    float rotation = -speedY * 5;
    
    if(rotation > 10)
        rotation = 10;
    else if(rotation < -10)
        rotation = -10;
    
    setRotation(rotation);
    
    setPositionY(getPositionY() + speedY);
    
}

void Bird::reset()
{
    speedY = 0;
    setRotation(speedY);
}