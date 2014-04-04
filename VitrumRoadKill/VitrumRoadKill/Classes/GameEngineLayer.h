//
//  GameEngineLayer.h
//  VitrumRoadKill
//
//  Created by NSS on 4/3/14.
//
//

#ifndef __VitrumRoadKill__GameEngineLayer__
#define __VitrumRoadKill__GameEngineLayer__

#include "cocos2d.h"

#define LAYER_OBJECTS "Objects"

#define GAME_ELEMENT_COIN "COIN"
#define GAME_ELEMENT_AIR_COIN "AIR COIN"
#define GAME_ELEMENT_WALL "WALL"
#define GAME_ELEMENT_AIR_COIN "AIR COIN"

enum GameDeeps
{
    kZIndexMap = -9999
};

class GameEngineLayer : public cocos2d::CCLayer
{
public:
    GameEngineLayer();
    virtual ~GameEngineLayer();
    
    void update(float dt);
    void draw();
    
private:
    void _readObjects();
    void _reset();
    void _initMap();
    
private:
    cocos2d::CCTMXTiledMap* _layerMap;
    
    float _mapSpeed;
    
    std::vector<cocos2d::CCRect> _vectorObstacles;
    
};

#endif /* defined(__VitrumRoadKill__GameEngineLayer__) */
