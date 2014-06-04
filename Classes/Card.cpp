#include "Card.h"

void Card::viewBack()
{
    this->initWithFile("tramp/z01.png");
}

bool Card::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    auto box = this->getBoundingBox();
    auto point = this->getParent()->convertTouchToNodeSpaceAR(touch);
    if (! box.containsPoint(point)) return false;
    CCLOG("%s : %s(%d:%d)", "Card", "onTouchBegan", this->type, this->number);

    return true;
}
void Card::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CCLOG("%s : %s(%d:%d)", "Card", "onTouchMoved", this->type, this->number);
}
void Card::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CCLOG("%s : %s(%d:%d)", "Card", "onTouchEnded", this->type, this->number);
}


void Card::onTap(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CCLOG("%s : %s(%d:%d)", "Card", "onTap", this->type, this->number);
}
