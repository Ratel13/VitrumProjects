#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    const char* cDataTowers = "TowersPosition.plist";
    CCArray* arrayTowers = CCArray::createWithContentsOfFile(cDataTowers);
    if(arrayTowers)
    {
        
        for(int i = 0; i < arrayTowers->count(); i++)
        {
            CCDictionary* dict = (CCDictionary*) arrayTowers->objectAtIndex(i);
            if(dict)
            {
                //CCLog("dict in %d passed", i);
                
                int x = dict->valueForKey("x")->intValue();
                int y = dict->valueForKey("x")->intValue();
                CCLog("X ; Y value on %d: %d ; %d", i, x, y);
            }
            else
            {
                //CCLog("dict in %d failed", i);
            }
        }
    }
    
    const char* cDataWaves = "Waves.plist";
    CCArray* arrayWaves = CCArray::createWithContentsOfFile(cDataWaves);
    if(arrayWaves)
    {
        
        for(int i = 0; i < arrayWaves->count(); i++)
        {
            CCArray* array = (CCArray *) arrayWaves->objectAtIndex(i);
            if(!array)
            {
                CCLog("Error on %d", i);
                continue;
            }
            
            for(int j = 0; j < array->count(); j++)
            {
                CCDictionary* dict = (CCDictionary*) array->objectAtIndex(j);
                if(dict)
                {
                    //CCLog("dict in %d passed", i);
                    
                    std::string data = dict->valueForKey("data")->getCString();
                    float number = dict->valueForKey("spawnTime")->floatValue();
                    
                    CCLog("data, number value on %d - %d: %s ; %f", i, j, data.c_str(), number);
                }
                else
                {
                    //CCLog("dict in %d failed", i);
                }
            }
            
        }
    }
    
    //CCLog("arrayDict: %d", arrayDict->count());
    
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
