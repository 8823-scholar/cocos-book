#include "EventListenerTouchOneByOneGesture.h"
#include "cocos2d.h"

const std::string EventListenerTouchOneByOneGesture::LISTENER_ID = "__ext_touch_one_by_one_gesture";

EventListenerTouchOneByOneGesture::EventListenerTouchOneByOneGesture()
: onTap(nullptr)
, onLongTap(nullptr)
, onDoubleTap(nullptr)
, onSwipe(nullptr)
{
}

EventListenerTouchOneByOneGesture* EventListenerTouchOneByOneGesture::create()
{
    auto ret = new EventListenerTouchOneByOneGesture();
    if (ret && ret->init())
    {
        ret->autorelease();

        auto listener = cocos2d::EventListenerTouchOneByOne::create();
        listener->onTouchBegan = CC_CALLBACK_2(EventListenerTouchOneByOneGesture::onTouchBegan, ret);
        listener->onTouchMoved = CC_CALLBACK_2(EventListenerTouchOneByOneGesture::onTouchMoved, ret);
        listener->onTouchEnded = CC_CALLBACK_2(EventListenerTouchOneByOneGesture::onTouchEnded, ret);
        cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 100);
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool EventListenerTouchOneByOneGesture::init()
{
    if (EventListenerCustom::init(LISTENER_ID, nullptr))
    {
        return true;
    }
    
    return false;
}


bool EventListenerTouchOneByOneGesture::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CCLOG("%s : %s", "EventListenerTouchOneByOneGesture", "onTouchBegan");
    return true;
}
void EventListenerTouchOneByOneGesture::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CCLOG("%s : %s", "EventListenerTouchOneByOneGesture", "onTouchMoved");
}
void EventListenerTouchOneByOneGesture::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CCLOG("%s : %s", "EventListenerTouchOneByOneGesture", "onTouchEnded");
}
