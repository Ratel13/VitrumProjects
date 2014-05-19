//
//  Utils.cpp
//  DuckHunt
//
//  Created by NSS on 1/14/14.
//
//

#include "Utils.h"

using namespace cocos2d;

float Utils::getNumberBetween(float min, float max)
{
    float randomNumber = min + CCRANDOM_0_1() * (max - min + 1);
    return randomNumber;
}