//
//  Globals.h
//  RPGCocos2dx
//
//  Created by NSS on 5/9/14.
//
//

#ifndef __RPGCocos2dx__Globals__
#define __RPGCocos2dx__Globals__

#include "cocos2d.h"

#define kStartingRoom "room"

#define ORIGIN() cocos2d::CCDirector::sharedDirector()->getVisibleOrigin()
#define SIZE() cocos2d::CCDirector::sharedDirector()->getVisibleSize()
#define WIN_SIZE() CCDirector::sharedDirector()->getWinSize()

#endif /* defined(__RPGCocos2dx__Globals__) */
