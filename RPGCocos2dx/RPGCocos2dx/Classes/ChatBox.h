//
//  ChatBox.h
//  RPGCocos2dx
//
//  Created by NSS on 5/9/14.
//
//

#ifndef __RPGCocos2dx__ChatBox__
#define __RPGCocos2dx__ChatBox__

#include "cocos2d.h"

enum Tags
{
    kTagChat = 1000
};

class ChatBox : public cocos2d::CCNode
{
public:
    static ChatBox* create(std::string npc, std::string text);
    void advanceTextOrHide();
    
private:
    ChatBox(std::string npc, std::string text);
    std::vector<std::string> split(std::string str, std::string value);
    
private:
    std::string _npc;
    std::vector<std::string> _textArray;
    cocos2d::CCLabelTTF* _label;
    
};

#endif /* defined(__RPGCocos2dx__ChatBox__) */
