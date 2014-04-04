//
//  GameScreen.h
//  VitrumRoadKill
//
//  Created by NSS on 4/3/14.
//
//

#ifndef __VitrumRoadKill__GameScreen__
#define __VitrumRoadKill__GameScreen__

#include "cocos2d.h"

enum
{
    kZHudLayer = 9999,
    kZGameLayer = 999
};

class GameScreen : public cocos2d::CCScene
{
public:
    GameScreen();
    static GameScreen* scene();
};

#endif /* defined(__VitrumRoadKill__GameScreen__) */
