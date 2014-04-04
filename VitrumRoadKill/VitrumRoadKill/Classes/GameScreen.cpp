//
//  GameScreen.cpp
//  VitrumRoadKill
//
//  Created by NSS on 4/3/14.
//
//

#include "GameScreen.h"
#include "GameEngineLayer.h"
#include "HudGameLayer.h"


using namespace cocos2d;

GameScreen::GameScreen()
{
    HudGameLayer* hudGameLayer = new HudGameLayer();
    hudGameLayer->autorelease();
    addChild(hudGameLayer, kZHudLayer);
    
    GameEngineLayer* gameEngineLayer = new GameEngineLayer();
    gameEngineLayer->autorelease();
    addChild(gameEngineLayer, kZGameLayer);
}

GameScreen* GameScreen::scene()
{
    GameScreen* gameScreen = new GameScreen();
    gameScreen->autorelease();
    return gameScreen;
}