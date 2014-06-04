#include "EventListenerTouchOneByOneGesture.h"
#include "cocos2d.h"

const std::string EventListenerTouchOneByOneGesture::LISTENER_ID = "__ext_touch_one_by_one_gesture";

EventListenerTouchOneByOneGesture::EventListenerTouchOneByOneGesture()
: onTap(nullptr)
, onLongTap(nullptr)
, onDoubleTap(nullptr)
, onSwipe(nullptr)
, onTapBegan(nullptr)
, _touchStart(false)
, _touchCount(0)
{
    this->_tapTime = 100;
    this->_doubleTapTime = 190;
    this->_longTapTime = 2000;
        
    auto director = cocos2d::Director::getInstance();
    this->_scheduler = director->getScheduler();
}

EventListenerTouchOneByOneGesture* EventListenerTouchOneByOneGesture::create()
{
    auto ret = new EventListenerTouchOneByOneGesture();
    if (ret && ret->init())
    {
        ret->autorelease();

        auto director = cocos2d::Director::getInstance();
        auto listener = cocos2d::EventListenerTouchOneByOne::create();
        listener->onTouchBegan = CC_CALLBACK_2(EventListenerTouchOneByOneGesture::onTouchBegan, ret);
        listener->onTouchMoved = CC_CALLBACK_2(EventListenerTouchOneByOneGesture::onTouchMoved, ret);
        listener->onTouchEnded = CC_CALLBACK_2(EventListenerTouchOneByOneGesture::onTouchEnded, ret);
        director->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 100);
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

bool EventListenerTouchOneByOneGesture::checkAvailable()
{
    if (this->onTapBegan == nullptr) {
        CCASSERT(false, "Invalid EventListenerTouchOneByOneGesture!");
        return false;
    }
    return true;
}

long EventListenerTouchOneByOneGesture::getNowMillisecondTime()
{
    struct timeval now;
    gettimeofday(&now, nullptr);
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}


bool EventListenerTouchOneByOneGesture::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    if (! this->onTapBegan(touch, event)) return false;

    this->_touch = touch;
    this->_event = event;

    this->_touchStart = true;
    this->_touchStartTime = this->getNowMillisecondTime();
    
    //this->_scheduler->schedule(schedule_selector(EventListenerTouchOneByOneGesture::onLongTouchBegan), this, 0.0f, 0, this->_longTapTime / 1000, false);

    return true;
}
void EventListenerTouchOneByOneGesture::onLongTouchBegan(float delay)
{
    CCLOG("onLongTouchBegan");
    if (!this->_touchStart) return;

    this->_touchStart = false;
    // this->onLongTap(this->_touch, this->_event);
}
void EventListenerTouchOneByOneGesture::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
}

void EventListenerTouchOneByOneGesture::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    if (! this->_touchStart) return;

    this->_touch = touch;
    this->_event = event;

    long endTime = this->getNowMillisecondTime();
    long diffTime = endTime - this->_touchStartTime;

    if (diffTime > this->_longTapTime) {
        if (this->onLongTap) {
            this->onLongTap(this->_touch, this->_event);
        }
    } else {
        if (this->_touchCount == 0) {
            this->_scheduler->schedule(schedule_selector(EventListenerTouchOneByOneGesture::_tapHandler), this, 0.0f, 0, this->_doubleTapTime / 1000.0f, false);
        }
        this->_touchCount++;
    }
}

void EventListenerTouchOneByOneGesture::_tapHandler(float dt)
{
    this->_scheduler->unschedule(schedule_selector(EventListenerTouchOneByOneGesture::_tapHandler), this);

    if (this->_touchCount == 1) {
        this->_touchCount = 0;
        if (this->onTap) this->onTap(this->_touch, this->_event);
    } else if (this->_touchCount == 2) {
        this->_touchCount = 0;
        if (this->onDoubleTap) this->onDoubleTap(this->_touch, this->_event);
    } else {
        this->_touchCount = 0;
    }
}

