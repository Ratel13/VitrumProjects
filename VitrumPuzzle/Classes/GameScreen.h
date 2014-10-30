//
//  GameScreen.h
//  VitrumPuzzle
//
//  Created by NorthSouth Studios on 10/15/14.
//
//

#ifndef __VitrumPuzzle__GameScreen__
#define __VitrumPuzzle__GameScreen__

#include "BaseScreen.h"

class GameScreen : public BaseScreen {
public:
    GameScreen();
    static GameScreen* create();
    static cocos2d::Scene* scene();
    void setupLayout();
};

#endif /* defined(__VitrumPuzzle__GameScreen__) */
