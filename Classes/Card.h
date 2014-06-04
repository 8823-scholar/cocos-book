#ifndef __CARD_H__
#define __CARD_H__

#include "cocos2d.h"

enum CardType { Spade, Diamond, Club, Heart, Joker };

class Card : public cocos2d::Sprite
{
public:
    CardType type;
    int number;

    CREATE_FUNC(Card);
    static Card* createWithNumber(CardType type, int number)
    {
        std::string prefix = "x";
        switch (type) {
            case CardType::Spade:
                prefix = "s";
                break;
            case CardType::Diamond:
                prefix = "d";
                break;
            case CardType::Club:
                prefix = "c";
                break;
            case CardType::Heart:
                prefix = "h";
                break;
        }

        auto card = Card::create();
        auto filename = cocos2d::StringUtils::format("tramp/%s%02d.png", prefix.c_str(), number);
        card->initWithFile(filename);
        card->type = type;
        card->number = number;
        return card;
    }

    virtual void viewBack();

    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif // __CARD_H__
