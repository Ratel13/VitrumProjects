//
//  GameLayer.h
//  RPGCocos2dx
//
//  Created by NSS on 5/9/14.
//
//

#ifndef __RPGCocos2dx__GameLayer__
#define __RPGCocos2dx__GameLayer__

#include "cocos2d.h"
#include "ChatBox.h"

class GameLayer : public cocos2d::CCLayer
{
public:
    ~GameLayer();
    
    static cocos2d::CCScene* scene();
    static GameLayer* create();
    void update(float dt);
    void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
private:
    GameLayer();
    
private:
    void _init();
    void _loadMapNamed(const char* map);
    void _setViewpointCenter(cocos2d::CCPoint position);
    void _setPlayerPosition(cocos2d::CCPoint position);
    cocos2d::CCPoint _tileCoordForPosition(cocos2d::CCPoint position);
    cocos2d::CCPoint _positionForTileCoord(cocos2d::CCPoint tileCoord);
    void _playHeroMoveAnimationFromPosition(cocos2d::CCPoint fromPosition, cocos2d::CCPoint toPosition);
    void _heroIsDoneWalking();
    void _npc(std::string npc, std::string text);
    
private:
    bool _canWalk;
    float _tileSize;
    ChatBox* _chatBox;
    cocos2d::CCTMXTiledMap* _tileMap;
    cocos2d::CCTMXLayer* _metaLayer;
    cocos2d::CCTMXLayer* _npcLayer;
    cocos2d::CCTMXObjectGroup* _exitGroup;
    cocos2d::CCSprite* _hero;
    
};

#endif /* defined(__RPGCocos2dx__GameLayer__) */
