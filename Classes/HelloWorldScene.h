#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CardLine.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    cocos2d::Sprite* sprite;
    CardLine* line1;

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    virtual void chapter5_2();
    virtual void chapter5_3();
    virtual void initCards();

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
};

#endif // __HELLOWORLD_SCENE_H__
