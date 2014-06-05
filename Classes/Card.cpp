#include "Card.h"
#include "CardLine.h"
#include "HelloWorldScene.h"

void Card::viewBack()
{
    this->initWithFile("tramp/z01.png");
}

CardLine* Card::getLine()
{
    return dynamic_cast<CardLine*>(this->getParent());
}

bool Card::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    auto box = this->getBoundingBox();
    auto point = this->getParent()->convertTouchToNodeSpace(touch);
    if (! box.containsPoint(point)) return false;
    CCLOG("%s : %s(%d:%d)", "Card", "onTouchBegan", this->type, this->number);

    // つかむ
    this->_stashPosition = this->getPosition();
    this->setGlobalZOrder(100);
    this->setPosition(point);

    return true;
}

void Card::gobackToStashPosition()
{
    auto seq = cocos2d::Sequence::create(
        cocos2d::EaseOut::create(cocos2d::MoveTo::create(0.3f, this->_stashPosition), 2),
        cocos2d::CallFunc::create(
            [this]() {
                this->setGlobalZOrder(0);
            }
        ),
        nullptr
    );
    this->runAction(seq);
}


void Card::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
    // 追従
    auto point = this->getParent()->convertTouchToNodeSpace(touch);
    this->setPosition(point);
}

void Card::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CCLOG("%s : %s(%d:%d)", "Card", "onTouchEnded", this->type, this->number);
    
    // ラインとのあたり判定
    HelloWorld* world = dynamic_cast<HelloWorld*>(this->getParent()->getParent());
    cocos2d::Vector<CardLine*> ite;
    ite.pushBack(world->line1);
    ite.pushBack(world->line2);
    for (CardLine* line : ite) {
        if (line == this->getLine()) continue;

        auto box1 = line->getBoundingBox();
        auto box2 = this->getBoundingBox();
        auto origin = this->getParent()->convertToNodeSpace(box1.origin);

        // カードとラインが重なっている場合はラインの移動
        if (box2.intersectsRect(cocos2d::Rect(origin.x, origin.y, box1.size.width, box1.size.height))) {
            this->getLine()->removeCard(this);
            line->putCard(this);
            this->setGlobalZOrder(0);
            return;
        }
    }
    this->gobackToStashPosition();
}


void Card::onTap(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CCLOG("%s : %s(%d:%d)", "Card", "onTap", this->type, this->number);
}

void Card::onLongTap(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CCLOG("%s : %s(%d:%d)", "Card", "onLongTap", this->type, this->number);
}

void Card::onDoubleTap(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CCLOG("%s : %s(%d:%d)", "Card", "onDoubleTap", this->type, this->number);
}
