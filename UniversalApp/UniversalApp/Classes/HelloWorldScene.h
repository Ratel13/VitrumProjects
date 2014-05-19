#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameSprite.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    float convertFontSize(float fontSize);
    cocos2d::CCPoint convertPoint(cocos2d::CCPoint point);
    void tryPopMoles(float dt);
    void popMole(GameSprite* mole);
    cocos2d::CCAnimation* animationFromPlist_delay(const char *animPlist, float delay);
    void setTappable(void *sender);
    void unSetTappable(void *sender);
    
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
    
    virtual ~HelloWorld();
    
private:
    int _score;
    int _totalSpawns;
    bool _gameOver;
    cocos2d::CCSize _winSize;
    cocos2d::CCArray* _moles;
    cocos2d::CCAnimation* _laughAnim;
    cocos2d::CCAnimation* _hitAnim;
    cocos2d::CCLabelTTF* _label;
    
};

#endif // __HELLOWORLD_SCENE_H__
