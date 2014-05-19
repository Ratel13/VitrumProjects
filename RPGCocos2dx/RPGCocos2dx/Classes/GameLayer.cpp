//
//  GameLayer.cpp
//  RPGCocos2dx
//
//  Created by NSS on 5/9/14.
//
//

#include "GameLayer.h"
#include "Globals.h"

using namespace cocos2d;
using namespace std;

/*
 * Given a point on the map, returns the tile coordinate for that point.
 */
CCPoint GameLayer::_tileCoordForPosition(CCPoint position)
{
    int x = position.x / (_tileMap->getTileSize().width);
    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / (_tileMap->getTileSize().height);
    return ccp(x, y);
}

/*
 * Given a tile coordinate, returns the position on screen
 */
CCPoint GameLayer::_positionForTileCoord(CCPoint tileCoord)
{
    int x = (tileCoord.x * _tileMap->getTileSize().width) + _tileMap->getTileSize().width;
    int y = (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - (tileCoord.y * _tileMap->getTileSize().height) - _tileMap->getTileSize().height;
    return ccp(x, y);
}

GameLayer::GameLayer()
{
    _init();
}

void GameLayer::_init()
{
    _chatBox = NULL;
    _tileMap = NULL;
    _loadMapNamed(kStartingRoom);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("character.plist");
    
    _hero = CCSprite::createWithSpriteFrameName("male_walkcycle_s_01.png");
    _hero->setPosition(ccp(32 * 6 + 16, 64 + 16));
    _hero->setScale(0.5);
    _hero->setZOrder(0);
    addChild(_hero, _tileMap->layerNamed("floor")->getZOrder());
    
    setTouchEnabled(true);
    
    _canWalk = true;
    
    scheduleUpdate();
}

void GameLayer::_loadMapNamed(const char* map)
{
    
    if(getChildByTag(kTagChat) != NULL)
        removeChild(getChildByTag(kTagChat));    
    
    CCString* name = CCString::createWithFormat("%s.tmx", map);
    
    if(_tileMap != NULL)
    {
        _tileMap->removeAllChildrenWithCleanup(true);
        removeChild(_tileMap, true);
        _tileMap = NULL;
    }
    
    _tileMap = CCTMXTiledMap::create(name->getCString());
    _tileMap->setAnchorPoint(CCPointZero);
    addChild(_tileMap, -1);
    
    _metaLayer = _tileMap->layerNamed("meta");
    _metaLayer->setVisible(false);
    
    _npcLayer = _tileMap->layerNamed("npc");
    
    _tileSize = _tileMap->getTileSize().width;
    
    _exitGroup = _tileMap->objectGroupNamed("exits");
    
}

void GameLayer::_setViewpointCenter(CCPoint position)
{
    CCSize size = WIN_SIZE();
    
    int x = MAX(position.x, size.width * 0.5f);
    int y = MAX(position.y, size.height * 0.5f);
    
    x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - size.width * 0.5f);
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - size.height * 0.5f);
    
    CCPoint actualPosition = ccp(x, y);
    CCPoint centerOfView = ccp(size.width * 0.5f, size.height * 0.5f);
    
    CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
    
    setPosition(viewPoint);
    
}

void GameLayer::_setPlayerPosition(CCPoint position)
{
    if(!_canWalk)
        return;
    
    CCPoint tileCoord = _tileCoordForPosition(position);
    //CCLog("tileCoord: %f ; %f", tileCoord.x, tileCoord.y);
    int tileGid = _metaLayer->tileGIDAt(tileCoord);
    if(tileGid)
    {
        CCDictionary* properties = _tileMap->propertiesForGID(tileGid);
        if(properties)
        {
            const CCString* collision = properties->valueForKey("collidable");
            if(collision && collision->compare("true") == 0)
                return;
        }
    }
    
    tileGid = _npcLayer->tileGIDAt(tileCoord);
    if(tileGid)
    {
        _npc("Soldier", "Please, save the princess!;You must save her and... Tro lo lololololololol lalalalalalala ohohohohoh");
        return;
    }
    
    _canWalk = false;
    // Animate the player
    CCMoveTo* moveAction = CCMoveTo::create(0.5f, position);
    
    // Play actions
    _playHeroMoveAnimationFromPosition(_hero->getPosition(), position);
    _hero->runAction(CCSequence::create(moveAction, NULL));
    //_hero->setPosition(position);
    
}

void GameLayer::_playHeroMoveAnimationFromPosition(CCPoint fromPosition, CCPoint toPosition)
{
    const char* direction = "n";
    if(toPosition.x > fromPosition.x)
        direction = "e";
    else if(toPosition.x < fromPosition.x)
        direction = "w";
    else if(toPosition.y < fromPosition.y)
        direction = "s";
    
    CCString* walkCycle;
    CCAnimation* animation = CCAnimation::create();
    animation->setDelayPerUnit(0.05f);
    animation->setRestoreOriginalFrame(true);
    
    for(int i = 1; i <= 9; i++)
    {
        walkCycle = CCString::createWithFormat("male_walkcycle_%s_%02d.png", direction, i);
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(walkCycle->getCString()));
    }
    
    CCAnimate* animate = CCAnimate::create(animation);
    CCCallFuncO* doneAction = CCCallFuncO::create(this, callfuncO_selector(GameLayer::_heroIsDoneWalking), NULL);
    _hero->runAction(CCSequence::create(animate, doneAction, NULL));
}

void GameLayer::_heroIsDoneWalking()
{
    _canWalk = true;
    
    CCObject* exits;
    CCARRAY_FOREACH(_exitGroup->getObjects(), exits)
    {
        CCDictionary* dict = (CCDictionary *) exits;
        if(dict)
        {
            float x = dict->valueForKey("x")->floatValue();
            float y = dict->valueForKey("y")->floatValue();
            float w = dict->valueForKey("width")->floatValue();
            float h = dict->valueForKey("height")->floatValue();
            
            CCRect exitRect = CCRectMake(x, y, w, h);
            if(exitRect.containsPoint(_hero->getPosition()))
            {
                const CCString* name = dict->valueForKey("destination");
                float startX = dict->valueForKey("startx")->floatValue() * _tileSize + _tileSize * 0.5f;
                float startY = dict->valueForKey("starty")->floatValue() * _tileSize + _tileSize * 0.5f;
                CCPoint heroPoint = ccp(startX, startY);
                _hero->setPosition(heroPoint);
                _loadMapNamed(name->getCString());
                return;
            }
        }
    }
    
}

void GameLayer::_npc(string npc, string text)
{
    _chatBox = ChatBox::create(npc, text);
    _chatBox->setTag(kTagChat);
    addChild(_chatBox, 100);
    _chatBox->advanceTextOrHide();
}

GameLayer::~GameLayer()
{
    
}

CCScene* GameLayer::scene()
{
    CCScene* scene = CCScene::create();
    scene->addChild(create());
    return scene;
}

GameLayer* GameLayer::create()
{
    GameLayer* layer = new GameLayer();
    layer->autorelease();
    return layer;
}

void GameLayer::update(float dt)
{
    _setViewpointCenter(_hero->getPosition());
}

void GameLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    /*
    for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); it++)
    {
        
    }*/
    
    /*
    CCSetIterator it = pTouches->begin();
    for(int i = 0; i < pTouches->count(); i++)
    {
        CCTouch* t = (CCTouch *) (*it);
        it++;
    }*/
    
    if(getChildByTag(kTagChat) != NULL && _chatBox && _chatBox->isVisible())
    {
        _chatBox->advanceTextOrHide();
        return;
    }
    
    CCTouch* touch = (CCTouch*) pTouches->anyObject();
    CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    touchLocation = convertToNodeSpace(touchLocation);
    
    CCPoint playerPos = _hero->getPosition();
    CCPoint diff = ccpSub(touchLocation, playerPos);
    
    if(fabs(diff.x) > fabs(diff.y))
    {
        if(diff.x > 0)
            playerPos.x += _tileMap->getTileSize().width;
        else
            playerPos.x -= _tileMap->getTileSize().width;
    }
    else
    {
        if(diff.y > 0)
            playerPos.y += _tileMap->getTileSize().height;
        else
            playerPos.y -= _tileMap->getTileSize().height;
    }
    
    if(playerPos.x < _tileMap->getMapSize().width * _tileMap->getTileSize().width &&
       playerPos.y < _tileMap->getMapSize().height * _tileMap->getTileSize().height &&
       playerPos.y > 0 &&
       playerPos.x > 0)
    {
        _setPlayerPosition(playerPos);
    }
    
}




