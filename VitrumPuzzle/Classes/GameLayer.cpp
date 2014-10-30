//
//  GameLayer.cpp
//  VitrumPuzzle
//
//  Created by NorthSouth Studios on 10/15/14.
//
//

#include "GameLayer.h"
#include "CocosUtils.h"

USING_NS_CC;

#pragma mark - GameLayer creator
GameLayer* GameLayer::create() {
    GameLayer* mGameLayer = new GameLayer();
    mGameLayer->autorelease();
    return mGameLayer;
}

GameLayer::GameLayer() {
    
    setupLayout();
    
}

#pragma mark - Setup world
void GameLayer::setupLayout() {
    
    _vector_obstacles.clear();
    _vector_game_object.clear();
    
    _direction = kDirectionNone;
    _is_character_moving = false;
    _isTouching = false;
    _gameOver = false;
    
    _createWorld();
    
    EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(GameLayer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GameLayer::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(GameLayer::onTouchesEnded, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(GameLayer::onTouchesCancelled, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->scheduleUpdate();
    
}

void GameLayer::_createWorld() {
    
    _tiled_map = TMXTiledMap::create("Level_sample_001.tmx");
    _tiled_map->setPosition( getVisibleOrigin() );
    this->addChild( _tiled_map, MIN_ZINDEX );
    
    // Tile Size
    _tile_size = _tiled_map->getTileSize();
    
    float width = _tile_size.width * _tiled_map->getMapSize().width;
    float height = _tile_size.height * _tiled_map->getMapSize().height;
    
    _map_size = Size(width, height);
    
    // Layer de muros
    _layer_muros = _tiled_map->getLayer( TMX_LAYER_MUROS );
    
    // Layer elementos
    _layer_elementos = _tiled_map->getLayer( TMX_LAYER_ELEMENTOS );
    
    // Layer de objetos
    _layer_objetos = _tiled_map->getObjectGroup( TMX_OBJECT_OBJETOS );
    
    int gameTag = 1000;
    
    ValueVector& data = _layer_objetos->getObjects();
    for(Value& obj : data) {
        ValueMap& dict = obj.asValueMap();
        
        float x = dict["x"].asFloat() + getVisibleOrigin().x;
        float y = dict["y"].asFloat() + getVisibleOrigin().y;
        float width = dict["width"].asFloat();
        float height = dict["height"].asFloat();
        
        Vec2 coordinate = _getTilePosition( Vec2( x + width * 0.5f, y + height * 0.5f ));
        
        
        GameObject mGameObject;
        mGameObject.x = x;
        mGameObject.y = y;
        mGameObject.width = width;
        mGameObject.height = height;
        mGameObject.row = coordinate.y;
        mGameObject.col = coordinate.x;
        mGameObject.id_object = -1;
        mGameObject.type = dict["type"].asString();
        mGameObject.name = dict["name"].asString();
        mGameObject.tag = gameTag;
        gameTag++;
        
        if( mGameObject.name == NAME_PLAYER_START ) {
            _start = mGameObject;
        }
        else if( mGameObject.name == NAME_PLAYER_END ) {
            _end = mGameObject;
        }
        else
        {
            if( mGameObject.type == TYPE_OBSTACLE )
                _vector_obstacles.push_back( mGameObject );
            else
                _vector_game_object.push_back( mGameObject );
            
            _vector_game_elements.push_back( mGameObject );
        }
        
    }
    
    _drawWorldElements();
    
    // Player
    _sp_player = Sprite::create("player.png", Rect(0, 0, 64, 64));
    _sp_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    _sp_player->setPositionX(_start.x);
    _sp_player->setPositionY(_start.y);
    this->addChild( _sp_player, MIN_ZINDEX + 150);
    
    _touchingTime = 0;
    
    this->setPosition( _getViewPoint(_sp_player->getPosition()) );
    
}

void GameLayer::_drawWorldElements() {
    
    // Start
    
    // End
    
    // World elements
    int i;
    int total = (int) _vector_game_elements.size();
    
    for( i = 0; i < total; i++ ) {
        
        GameObject object = _vector_game_elements[i];
        Sprite* sprite = nullptr;
        
        if( object.type == TYPE_MONEY ) {
            
            sprite = Sprite::create("coin.png");
            
        }
        else if( object.type == TYPE_OBSTACLE ) {
            
            sprite = Sprite::create("rock.jpg");
            
        }
        else if( object.type == TYPE_TRAP ) {
            
            sprite = Sprite::create("hole.png");
            
        }
        else if( object.type == TYPE_ARROW ) {
            
            sprite = Sprite::create("arrow-right.png");
            
            if( object.name == NAME_ARROW_DOWN ) {
                sprite->setRotation( -270 );
            }
            else if( object.name == NAME_ARROW_LEFT ) {
                sprite->setRotation( -180 );
            }
            else if( object.name == NAME_ARROW_RIGHT ) {
                sprite->setRotation( 0 );
            }
            else if( object.name == NAME_ARROW_UP ) {
                sprite->setRotation( -90 );
            }
            
            
        }
        
        if( sprite != nullptr ) {
            
            sprite->setTag( object.tag );
            sprite->setPositionX( object.x + _tile_size.width * 0.5f );
            sprite->setPositionY( object.y + _tile_size.height * 0.5f );
            
            Vec2 coord = Vec2( object.col, object.row);
            
            int gid = _layer_elementos->getTileGIDAt( coord );
            if( gid ) {
                _layer_elementos->removeTileAt( Vec2( object.col, object.row ) );
            }
            
            this->addChild( sprite, MIN_ZINDEX + 100 );
            
        }
        
        
    }
    
    // Debug Walls
    if( _layer_muros ) {
        
        int x, y;
        Size size = _layer_muros->getLayerSize();
        
        for(x = 0; x < size.width; x++) {
            
            for(y = 0; y < size.height; y++) {
                
                int gid = _layer_muros->getTileGIDAt( Vec2(x, y) );
                
                if( gid ) {
                    
                    int inverted_y = _tiled_map->getMapSize().height - y - 1;
                    
                    Sprite* sprite = Sprite::create("rock.jpg");
                    sprite->setPositionX( x * _tile_size.width + _tile_size.width * 0.5f );
                    sprite->setPositionY( inverted_y * _tile_size.height + _tile_size.height * 0.5f );
                    this->addChild( sprite, MIN_ZINDEX + 90 );
                }

            }
        }
        
    }
    
}

#pragma mark - Player Movement
void GameLayer::_movePlayerToDirection(DirectionState direction) {
    
    _updatePlayerDirection(direction);
    
    _is_character_moving = true;
    
    if( direction == kDirectionNone ) {
        
        _is_character_moving = false;
        
    }
    else
    {
     
        int i;
        int gid;
        int dx = 0;
        int dy = 0;
        bool game_object_found = false;
        
        GameObject game_object;
        Vec2 tile_position = _getTilePosition( _sp_player->getPosition() );
        
        if( tile_position.x == _end.col && tile_position.y == _end.row ) {
            _gameOver = true;
            CCLOG("Game End");
            return;
        }
        else
        {
            
            int index = -1;
            for( i = 0; i < (int) _vector_game_object.size(); i++ ) {
                
                game_object = _vector_game_object[i];
                
                if( game_object.row == tile_position.y &&
                   game_object.col == tile_position.x ) {
                    index = i;
                    game_object_found = true;
                    break;
                }
                
            }
            
            if( game_object_found ) {
                
                Vec2 coord = Vec2( game_object.col, game_object.row );
                                
                if( game_object.type == TYPE_MONEY ) {
                    
                    _vector_game_object.erase( _vector_game_object.begin() + index );
                    CCLOG("MONEY IN: %d ; %d", (int) tile_position.x, (int) tile_position.y );
                    this->removeChildByTag( game_object.tag );
                
                }
                else if( game_object.type == TYPE_TRAP ) {
                    
                    CCLOG("TRAP IN: %d ; %d", (int) tile_position.x, (int) tile_position.y );
                    
                    _sp_player->stopAllActions();
                    _sp_player->setPosition( Vec2( _start.x, _start.y ));
                    
                    _is_character_moving = false;
                    return;
                    
                }
                else if( game_object.type == TYPE_ARROW ) {
                    
                    if( game_object.name == NAME_ARROW_LEFT ) {
                        direction = kDirectionLeft;
                    }
                    else if( game_object.name == NAME_ARROW_UP ) {
                        direction = kDirectionUp;
                    }
                    
                }
                
            }
            
        }

        
        if ( direction == kDirectionDown )
            dy = -1;
        else if( direction == kDirectionUp )
            dy = 1;
        else if( direction == kDirectionLeft )
            dx = -1;
        else if( direction == kDirectionRight )
            dx = 1;
        
        int next_x = dx * _tile_size.width + _sp_player->getPositionX();
        int next_y = dy * _tile_size.height + _sp_player->getPositionY();
        
        Vec2 coordinate = _getTilePosition( Vec2( next_x, next_y ) );

        
        if( coordinate.x >= 0 &&
            coordinate.y >= 0 &&
            coordinate.x <= _tiled_map->getMapSize().width &&
            coordinate.y <= _tiled_map->getMapSize().height ) {
            
            
            gid = _layer_muros->getTileGIDAt( coordinate );
            
            if( gid ) {
                _movePlayerToDirection( kDirectionNone );
                return;
            }
            else
            {
                
                game_object_found = false;
                
                for( i = 0; i < (int) _vector_obstacles.size(); i++ ) {
                 
                    game_object = _vector_obstacles[i];

                    if( game_object.row == coordinate.y &&
                       game_object.col == coordinate.x ) {
                        game_object_found = true;
                        break;
                    }
                    
                }
                
                if( game_object_found ) {
                    _movePlayerToDirection( kDirectionNone );
                    return;
                }
                
                MoveTo* move = MoveTo::create(0.05f, Vec2( next_x, next_y ));
                CallFuncN* callback = CallFuncN::create(CC_CALLBACK_1( GameLayer::_callbackDirection, this, direction));
                Sequence* sequence = Sequence::create( move, DelayTime::create( 0.0f ), callback, NULL);
                _sp_player->runAction( sequence );
                
            }
            
        }
        else
        {
            _movePlayerToDirection( kDirectionNone );
            return;
        }
        
    }
    
}

void GameLayer::_updatePlayerDirection(DirectionState direction) {
    
}

void GameLayer::_callbackDirection(cocos2d::Node* node, DirectionState direction) {
    _movePlayerToDirection( direction );
}

void GameLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event * event) {
    
    if(_gameOver || _is_character_moving)
        return;
    
    Touch* touch = touches[0];
    Vec2 location = touch->getLocation();
    _startTouchPoint = location;
    _touchingTime = 0;
    _isTouching = true;
}

void GameLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event * event) {
    
    if(_gameOver || _is_character_moving)
        return;
    
    Touch* touch = touches[0];
    Vec2 location = touch->getLocation();
}

void GameLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event * event) {
    
    if(_gameOver || _is_character_moving)
        return;
    
    Touch* touch = touches[0];
    Vec2 location = touch->getLocation();
    
    if(_isTouching && _touchingTime <= SWIPE_TIME) {
        _calculateSwipe(location);
    }
    
    _touchingTime = 0;
    _isTouching = false;
}

void GameLayer::onTouchesCancelled(const std::vector<Touch*>& touches, Event * event) {
    
    if(_gameOver || _is_character_moving)
        return;
    
    _isTouching = false;
    onTouchesEnded(touches, event);
}

void GameLayer::_calculateSwipe(Vec2 lastLocation){
    float dX = lastLocation.x - _startTouchPoint.x;
    float dY = lastLocation.y - _startTouchPoint.y;
    
    if(fabsf(dX) > fabsf(dY) && fabsf(dX) >= SWIPE_FORCE) {

        if(dX > 0)
            _movePlayerToDirection(kDirectionRight);
        else
            _movePlayerToDirection(kDirectionLeft);
    }
    else if(fabsf(dY) > fabsf(dX) && fabsf(dY) >= SWIPE_FORCE) {

        if(dY > 0)
            _movePlayerToDirection(kDirectionUp);
        else
            _movePlayerToDirection(kDirectionDown);
    }
}

void GameLayer::update(float dt) {
    
    this->setPosition( _getViewPoint(_sp_player->getPosition()) );
    
    if(_isTouching) {
        _touchingTime += dt;
    }
    
}

#pragma mark - Helper
Vec2 GameLayer::_getTilePosition(Vec2 position) {    
    int x = floorf( position.x / _tile_size.width );
    int y = _tiled_map->getMapSize().height - 1 - floorf( position.y / _tile_size.height );
    return Vec2( x, y );
}

Vec2 GameLayer::_getViewPoint(Vec2 position) {
    
    float width = getVisibleOrigin().x + getVisibleSize().width;
    float height = getVisibleOrigin().y + getVisibleSize().height;
    
    int x = MAX(position.x, width * 0.5f);
    int y = MAX(position.y, height * 0.5f);
    
    x = MIN(x, _map_size.width - width * 0.5f + visibleOrigin.x);
    y = MIN(y, _map_size.height - height * 0.5f + visibleOrigin.y);
    
    Vec2 actualPosition = Vec2(x, y);
    Vec2 centerOfView = Vec2(width * 0.5f, height * 0.5f);
    Vec2 viewPoint;
    Vec2::subtract(centerOfView, actualPosition, &viewPoint);
    
    return viewPoint;
}

