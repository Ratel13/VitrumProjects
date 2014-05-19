//
//  Tube.h
//  FapBird
//
//  Created by NSS on 2/10/14.
//
//

#ifndef __FapBird__Tube__
#define __FapBird__Tube__

#include "cocos2d.h"

class Tube : public cocos2d::CCNode
{
public:
    Tube();
    ~Tube();
    
    static Tube* create();
    
    void reset();
        
    CC_SYNTHESIZE_READONLY(cocos2d::CCRect, tubeBottomCollision, TubeBottomCollision);
    CC_SYNTHESIZE_READONLY(cocos2d::CCRect, tubeTopCollision, TubeTopCollision);
    CC_SYNTHESIZE_READONLY(float, tubeWidth, TubeWidth);
    CC_SYNTHESIZE(bool, tubePassed, TubePassed);
    
private:
    void _createTubes();
    
};

#endif /* defined(__FapBird__Tube__) */
