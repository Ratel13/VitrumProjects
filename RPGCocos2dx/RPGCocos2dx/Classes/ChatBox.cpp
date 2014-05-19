//
//  ChatBox.cpp
//  RPGCocos2dx
//
//  Created by NSS on 5/9/14.
//
//

#include "ChatBox.h"
#include <algorithm>
#include <string>

using namespace cocos2d;
using namespace std;

ChatBox* ChatBox::create(string npc, string text)
{
    ChatBox* box = new ChatBox(npc, text);
    box->autorelease();
    return box;
}

ChatBox::ChatBox(string npc, string text)
{
    _npc = npc;
    _textArray = split(text, ";");
    
    CCSprite* backgroundSprite = CCSprite::create("chat-box.png");
    backgroundSprite->getTexture()->setAliasTexParameters();
    backgroundSprite->setScale(5);
    backgroundSprite->setPosition(ccp(0, 240));
    backgroundSprite->setAnchorPoint(CCPointZero);
    addChild(backgroundSprite, 0);
    
    _label = CCLabelTTF::create("", "Helvetica", 18, CCSizeMake(400, 60), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    _label->setColor(ccWHITE);
    _label->setAnchorPoint(CCPointZero);
    _label->setPosition(ccp(50, 250));
    addChild(_label, 1);
    
}

void ChatBox::advanceTextOrHide()
{
    if(_textArray.size() == 0)
    {
        setVisible(false);
        if(getParent())
            getParent()->removeChild(this, false);
        return;
    }
    
    string text = _textArray[0];
    _textArray.erase(_textArray.begin(), _textArray.begin() + 1);
    
    string str_npc = _npc;
    std::transform(str_npc.begin(), str_npc.end(), str_npc.begin(), ::toupper);
    
    CCString* message = CCString::createWithFormat("%s: %s", str_npc.c_str(), text.c_str());
    _label->setString(message->getCString());
}

vector<string> ChatBox::split(string str, string value)
{
    vector<string> split;
    char *line = strtok(const_cast<char*>(str.c_str()), value.c_str());
    while (line) {
        split.push_back(line);
        line = strtok(NULL, value.c_str());
    }
    return split;
}