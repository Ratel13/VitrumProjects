//
//  GameEngineLayer.cpp
//  VitrumRoadKill
//
//  Created by NSS on 4/3/14.
//
//

#include "GameEngineLayer.h"

using namespace cocos2d;

#pragma mark - Constructor y Destructor
GameEngineLayer::GameEngineLayer()
{
    _initMap();
    _readObjects();
    _reset();
    
    scheduleUpdate();
}

GameEngineLayer::~GameEngineLayer()
{
    
}

#pragma mark - Parámetros para resetear e iniciar el mapa.

void GameEngineLayer::_initMap()
{
    _layerMap = CCTMXTiledMap::create("level1test.tmx");
    _layerMap->setAnchorPoint(ccp(0, 0));
    _layerMap->setPosition(CCPointZero);
    addChild(_layerMap, kZIndexMap);
}


void GameEngineLayer::_reset()
{
    _mapSpeed = 350.0f;
}

void GameEngineLayer::_readObjects()
{
    CCObject* object = NULL;
    CCDictionary* dictionary = NULL;
    float x, y, width, height;
    const char* name;
    const char* type;
    
    CCTMXObjectGroup* layerObjects = _layerMap->objectGroupNamed(LAYER_OBJECTS);
    if(layerObjects)
    {
        CCARRAY_FOREACH(layerObjects->getObjects(), object)
        {
            dictionary = (CCDictionary *) object;
            if(dictionary)
            {
                x = dictionary->valueForKey("x")->floatValue();
                y = dictionary->valueForKey("y")->floatValue();
                width = dictionary->valueForKey("width")->floatValue();
                height = dictionary->valueForKey("height")->floatValue();
                name = dictionary->valueForKey("name")->getCString();
                type = dictionary->valueForKey("type")->getCString();
                
                _vectorObstacles.push_back(CCRectMake(x, y, width, height));
            }
        }
    }
}

#pragma mark - Game Logic and Update
void GameEngineLayer::update(float dt)
{
    float sizeWidth = CCDirector::sharedDirector()->getWinSize().width;
    float width = _layerMap->getTileSize().width * _layerMap->getMapSize().width;
    float nextPosition = _layerMap->getPositionX() - _mapSpeed * dt;
    if(fabsf(nextPosition) + sizeWidth <= width)
        _layerMap->setPositionX(nextPosition);
}

void GameEngineLayer::draw()
{
    CCLayer::draw();
    
    for(int i = 0; i < (int) _vectorObstacles.size(); i++)
    {
        CCRect rect = _vectorObstacles[i];
        
        CCPoint origin = ccp(rect.getMinX() + _layerMap->getPositionX(), rect.getMinY() + _layerMap->getPositionY());
        
        CCPoint destination = ccp(rect.getMaxX() + _layerMap->getPositionX(), rect.getMaxY() + _layerMap->getPositionY());
        
        ccDrawSolidRect(origin, destination, ccc4f(1.0f, 0.0f, 0.0f, 1.0f));
        
        
    }
}