//
//  GameScene.h
//  FapBird
//
//  Created by NSS on 2/10/14.
//
//

#ifndef __FapBird__GameScene__
#define __FapBird__GameScene__

#include "cocos2d.h"
#include "Bird.h"

class GameScene : public cocos2d::CCLayerColor
{
public:
    GameScene();
    virtual ~GameScene();
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    static cocos2d::CCScene* scene();
    
    void reset();
    void draw();
    void update(float dt);
    
private:
    int _score;
    Bird* _bird;
    bool _gameOver;
    bool _isGameStarted;
    
    cocos2d::CCArray* _tubesArray;
    cocos2d::CCArray* _parallaxArray;
    
};

#endif /* defined(__FapBird__GameScene__) */
