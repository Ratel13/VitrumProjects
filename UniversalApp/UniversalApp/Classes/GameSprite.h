//
//  GameSprite.h
//  UniversalApp
//
//  Created by NSS on 10/30/13.
//
//

#ifndef __UniversalApp__GameSprite__
#define __UniversalApp__GameSprite__

#include "cocos2d.h"

class GameSprite : public cocos2d::CCSprite
{
protected:
    cocos2d::CCSize _screenSize;
    bool userData;
    
public:
    GameSprite();
    virtual ~GameSprite();
    
    static GameSprite* gameSpriteWithFile(const char *pszFileName);
    void setUserData(GameSprite *mole, bool flag);
    bool getUserData(GameSprite *mole);
};

#endif /* defined(__UniversalApp__GameSprite__) */
