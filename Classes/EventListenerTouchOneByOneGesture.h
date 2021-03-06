#ifndef __EVENT_LISTENER_TOUCH_ONE_BY_ONE_GESTURE_H__
#define __EVENT_LISTENER_TOUCH_ONE_BY_ONE_GESTURE_H__

#include "cocos2d.h"

class EventListenerTouchOneByOneGesture : public cocos2d::EventListenerCustom
{
public:
    static const std::string LISTENER_ID;
    static EventListenerTouchOneByOneGesture* create();

public:
    std::function<bool(cocos2d::Touch*, cocos2d::Event*)> onTapBegan;
    std::function<void(cocos2d::Touch*, cocos2d::Event*)> onTap;
    std::function<void(cocos2d::Touch*, cocos2d::Event*)> onLongTap;
    std::function<void(cocos2d::Touch*, cocos2d::Event*)> onDoubleTap;
    std::function<void(cocos2d::Touch*, cocos2d::Event*)> onSwipe;
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onLongTouchBegan(float dt);

public:
    virtual bool checkAvailable() override;

private:
    EventListenerTouchOneByOneGesture();
    bool init();
    long getNowMillisecondTime();

private:
    cocos2d::Scheduler* _scheduler;
    cocos2d::Touch* _touch;
    cocos2d::Event* _event;
    bool _touchStart;
    long _touchStartTime;
    int _tapTime;
    int _doubleTapTime;
    int _longTapTime;
    int _touchCount;
    virtual void _tapHandler(float dt);
};

#endif // __EVENT_LISTENER_TOUCH_ONE_BY_ONE_GESTURE_H__
