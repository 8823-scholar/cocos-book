#include "LoadingBar.h"
#include "cocos2d.h"

bool LoadingBar::init()
{
    CCASSERT(Sprite::init(), "failed to init sprite.");

    this->_total = 100;
    this->_current = 0;
    this->_width = 300;
    this->_height = 10;

    this->_box = cocos2d::DrawNode::create();
    this->addChild(this->_box, 1);
    cocos2d::Point points[] = {
        cocos2d::Point(0, 0),
        cocos2d::Point(0, this->_height),
        cocos2d::Point(this->_width, this->_height),
        cocos2d::Point(this->_width, 0)
    };
    this->_box->drawPolygon(points, 4, cocos2d::Color4F(cocos2d::Color4B(0, 0, 0, 0)), 1, cocos2d::Color4F(cocos2d::Color4B(0, 0, 0, 255)));
    this->setContentSize(cocos2d::Size(this->_width, this->_height));

    this->_bar = cocos2d::DrawNode::create();
    this->addChild(this->_bar, 0);
}

void LoadingBar::setTotal(int number)
{
    this->_total = number;
}

void LoadingBar::setCurrent(int number)
{
    this->_current = number;

    if (this->_current == this->_total) this->_current = this->_total - 2;
    
    this->_bar->clear();
    cocos2d::Point points[] = {
        cocos2d::Point(0, 0),
        cocos2d::Point(0, this->_height),
        cocos2d::Point(this->_width * (static_cast<float>(this->_current)/this->_total), this->_height),
        cocos2d::Point(this->_width * (static_cast<float>(this->_current)/this->_total), 0)
    };
    this->_bar->drawPolygon(points, 4, cocos2d::Color4F(cocos2d::Color4B(0, 0, 0, 255)), 0, cocos2d::Color4F(cocos2d::Color4B(0, 0, 0, 0)));
}

void LoadingBar::addToCurrent(int number)
{
    this->setCurrent(this->_current + number);
}
