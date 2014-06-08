#ifndef __LOADING_BAR_H__
#define __LOADING_BAR_H__

#include "cocos2d.h"

class LoadingBar : public cocos2d::Sprite
{
public:
    CREATE_FUNC(LoadingBar);
    virtual bool init();

    virtual void setTotal(int number);
    virtual void setCurrent(int number);
    virtual void addToCurrent(int number);

private:
    int _total;
    int _current;
    int _width;
    int _height;
    cocos2d::DrawNode* _box;
    cocos2d::DrawNode* _bar;
};

#endif // __LOADING_BAR_H__
