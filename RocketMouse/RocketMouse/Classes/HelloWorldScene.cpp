//
//  HelloWorldScene.cpp
//  RocketMouse
//
//  Created by NSS on 5/15/14.
//  Copyright __MyCompanyName__ 2014. All rights reserved.
//
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

HelloWorld::HelloWorld()
{
    setTouchEnabled( true );
    setAccelerometerEnabled( true );
    
    this->initPhysics();
    
    loader = new LevelHelperLoader("level01.plhs");
    loader->addObjectsToWorld(world, this);
    
    scheduleUpdate();
}

HelloWorld::~HelloWorld()
{
    
    loader->release();
    loader = NULL;
    
    delete world;
    world = NULL;
    
    //delete m_debugDraw;
}

void HelloWorld::initPhysics()
{

    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    world = new b2World(gravity);

    // Do we want to let bodies sleep?
    world->SetAllowSleeping(true);

    world->SetContinuousPhysics(true);
}

void HelloWorld::draw()
{
    //
    // IMPORTANT:
    // This is only for debug purposes
    // It is recommend to disable it
    //
    CCLayer::draw();

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

    kmGLPushMatrix();

    world->DrawDebugData();

    kmGLPopMatrix();
}

void HelloWorld::update(float dt)
{
    //It is recommended that a fixed time step is used with Box2D for stability
    //of the simulation, however, we are using a variable time step here.
    //You need to make an informed choice, the following URL is useful
    //http://gafferongames.com/game-physics/fix-your-timestep/
    
    int velocityIterations = 8;
    int positionIterations = 1;
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    world->Step(dt, velocityIterations, positionIterations);
    
    //Iterate over the bodies in the physics world
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {
            //Synchronize the AtlasSprites position and rotation with the corresponding body
            CCSprite* myActor = (CCSprite*)b->GetUserData();
            myActor->setPosition( CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }    
    }
}

void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    //Add a new body/atlas sprite at the touched location
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++) 
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint location = touch->getLocationInView();
        
        location = CCDirector::sharedDirector()->convertToGL(location);
    }
}

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new HelloWorld();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
