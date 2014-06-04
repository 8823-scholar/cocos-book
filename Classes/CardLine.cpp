#include "CardLine.h"
#include "Card.h"
#include "cocos2d.h"

void CardLine::pushCard(Card* card)
{
    for (cocos2d::Node* node : this->getChildren()) {
        auto child = dynamic_cast<Card*>(node);
        child->viewBack();
    }

    auto size = this->getChildren().size();
    card->setPosition(cocos2d::Point(0, 0 - size * 50));
    this->addChild(card, size);
    
    auto *listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Card::onTouchBegan, card);
    listener->onTouchMoved = CC_CALLBACK_2(Card::onTouchMoved, card);
    listener->onTouchEnded = CC_CALLBACK_2(Card::onTouchEnded, card);
    listener->setSwallowTouches(true);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, card);
}

