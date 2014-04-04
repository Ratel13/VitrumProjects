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

class GameEngineLayer : public cocos2d::CCLayer
{
public:
    GameEngineLayer();
    virtual ~GameEngineLayer();
    
private:
    void _reset();
    void _initMap();
    
private:
    cocos2d::CCTMXLayer* _layerMap;
    
    float _mapSpeed;
    
};

#endif /* defined(__VitrumRoadKill__GameEngineLayer__) */
