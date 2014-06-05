#include "CardLine.h"
#include "Card.h"
#include "EventListenerTouchOneByOneGesture.h"
#include "cocos2d.h"

void CardLine::pushCard(Card* card)
{
    const int DIFF_SIZE = 50;
    for (cocos2d::Node* node : this->getChildren()) {
        auto child = dynamic_cast<Card*>(node);
        child->viewBack();
    }

    auto size = this->getChildren().size();
    auto cardSize = card->getContentSize();
    this->addChild(card, size);
    this->setContentSize(cocos2d::Size(cardSize.width, size * DIFF_SIZE + cardSize.height));
    card->setPosition(cocos2d::Point(0, 0 - size * DIFF_SIZE));
    
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Card::onTouchBegan, card);
    listener->onTouchMoved = CC_CALLBACK_2(Card::onTouchMoved, card);
    listener->onTouchEnded = CC_CALLBACK_2(Card::onTouchEnded, card);
    listener->setSwallowTouches(true);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, card);

    /*
    auto listener = EventListenerTouchOneByOneGesture::create();
    listener->onTapBegan = CC_CALLBACK_2(Card::onTouchBegan, card);
    listener->onTap = CC_CALLBACK_2(Card::onTap, card);
    listener->onLongTap = CC_CALLBACK_2(Card::onLongTap, card);
    listener->onDoubleTap = CC_CALLBACK_2(Card::onDoubleTap, card);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, card);
    */
}

void CardLine::putCard(Card* card)
{
    const int DIFF_SIZE = 50;
    auto size = this->getChildren().size();
    auto cardSize = card->getContentSize();
    this->addChild(card, size);
    this->setContentSize(cocos2d::Size(cardSize.width, size * DIFF_SIZE + cardSize.height));
    card->setPosition(cocos2d::Point(0, 0 - size * DIFF_SIZE));
}

void CardLine::removeCard(Card* card)
{
    card->retain();
    this->removeChild(card, false);
}

