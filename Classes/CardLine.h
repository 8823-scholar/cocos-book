#pragma once
#ifndef __CARD_LINE_H__
#define __CARD_LINE_H__

#include "Card.h"
#include "cocos2d.h"
class Card;

class CardLine : public cocos2d::Sprite
{
public:
    std::vector<Card*> cards;

    CREATE_FUNC(CardLine);

    void pushCard(Card* card);
    void putCard(Card* card);
    void removeCard(Card* card);
};

#endif // __CARD_LINE_H__
