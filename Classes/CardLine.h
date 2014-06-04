#ifndef __CARD_LINE_H__
#define __CARD_LINE_H__

#include "cocos2d.h"
#include "Card.h"

class CardLine : public cocos2d::Sprite
{
public:
    std::vector<Card*> cards;

    CREATE_FUNC(CardLine);

    void pushCard(Card* card);
};

#endif // __CARD_LINE_H__
