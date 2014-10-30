//
//  BaseScreen.cpp
//  Invaders
//
//  Created by NorthSouth Studios on 9/19/14.
//
//

#include "BaseScreen.h"
#include "CocosUtils.h"

USING_NS_CC;

BaseScreen::BaseScreen() {
    
    visibleSize = CocosUtils::getInstance().getVisibleSize();
    visibleCenter = CocosUtils::getInstance().getVisibleCenter();
    visibleOrigin = CocosUtils::getInstance().getVisibleOrigin();
    topScreen = visibleCenter.y + visibleSize.height * 0.5f;
    rightScreen = visibleCenter.x + visibleSize.width * 0.5f;
    
}

BaseScreen::~BaseScreen() {
    
}