//
//  GameScreen.cpp
//  VitrumPuzzle
//
//  Created by NorthSouth Studios on 10/15/14.
//
//

#include "GameScreen.h"
#include "GameLayer.h"

USING_NS_CC;

GameScreen::GameScreen() {

    setupLayout();
    
}

GameScreen* GameScreen::create() {
    GameScreen* mGameScreen = new GameScreen();
    mGameScreen->autorelease();
    return mGameScreen;
}

Scene* GameScreen::scene() {
    Scene* scene = Scene::create();
    
    GameScreen* mGameScreen = create();
    scene->addChild( mGameScreen );
    
    return scene;
}

void GameScreen::setupLayout() {
    
    GameLayer* mGameLayer = GameLayer::create();
    this->addChild( mGameLayer, 10 );
    
}