//
//  GameLayer.h
//  VitrumPuzzle
//
//  Created by NorthSouth Studios on 10/15/14.
//
//

#ifndef __VitrumPuzzle__GameLayer__
#define __VitrumPuzzle__GameLayer__

#include "BaseScreen.h"
#include "GameConfig.h"

struct GameObject {
    int id_object;
    std::string type;
    std::string name;
    int col;
    int row;
    float x;
    float y;
    float width;
    float height;
    int tag;
};

class GameLayer : public BaseScreen {
public:
    GameLayer();
    static GameLayer* create();
    void setupLayout();
    
    void update(float dt);
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * event);
    void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * event);
    
private:
    void _createWorld();
    void _movePlayerToDirection(DirectionState direction);
    void _callbackDirection(cocos2d::Node* node, DirectionState direction);
    cocos2d::Vec2 _getTilePosition(cocos2d::Vec2 position);
    cocos2d::Vec2 _getViewPoint(cocos2d::Vec2 position);
    void _calculateSwipe(cocos2d::Vec2 lastLocation);
    void _updatePlayerDirection(DirectionState direction);
    void _drawWorldElements();
    
private:
    int _level;
    bool _gameOver;
    bool _isTouching;
    float _touchingTime;
    bool _is_character_moving;
    cocos2d::Vec2 _startTouchPoint;
    cocos2d::TMXTiledMap* _tiled_map;
    cocos2d::TMXLayer* _layer_muros;
    cocos2d::TMXLayer* _layer_elementos;
    cocos2d::TMXObjectGroup* _layer_objetos;
    cocos2d::Size _tile_size;
    cocos2d::Size _map_size;
    DirectionState _direction;
    std::vector<GameObject> _vector_game_object;
    std::vector<GameObject> _vector_obstacles;
    std::vector<GameObject> _vector_game_elements;
    GameObject _start;
    GameObject _end;
    cocos2d::Sprite* _sp_player;
    
};

#endif /* defined(__VitrumPuzzle__GameLayer__) */
