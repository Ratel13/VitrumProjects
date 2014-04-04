//
//  AppMacros.h
//  VitrumRoadKill
//
//  Created by NSS on 4/3/14.
//
//

#ifndef VitrumRoadKill_AppMacros_h
#define VitrumRoadKill_AppMacros_h

#include "cocos2d.h"

typedef struct tagResource
{
    cocos2d::CCSize size;
    char directory[100];
} Resource;

static Resource res_ratio_16      =  { cocos2d::CCSizeMake(1280, 800),   "1280x800"   }; // 1.6
static Resource res_ratio_178     =  { cocos2d::CCSizeMake(1280, 720),   "1280x720"   }; // 1.78
static Resource res_ratio_ipad    =  { cocos2d::CCSizeMake(1024, 768),   "1024x768"   }; // 1.33
static Resource res_ratio_ipadhd  =  { cocos2d::CCSizeMake(2048, 1536),  "2048x1536"  }; // 1.33

static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(1024, 768);

#define TITLE_FONT_SIZE  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 24)

#endif
