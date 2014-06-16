#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CardLine.h"
#include "network/HttpClient.h"
#include "LoadingBar.h"
#include "spine/spine-cocos2dx.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    cocos2d::Sprite* sprite;
    CardLine* line1;
    CardLine* line2;
    LoadingBar* loadingBar;
    cocos2d::network::HttpRequest* request;

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    virtual void chapter5_2();
    virtual void chapter5_3();
    virtual void chapter5_4();
    virtual void chapter5_5();
    virtual void chapter5_5_json();
    virtual void chapter5_5_xml();
    virtual void chapter5_6();
    virtual void chapter5_7();
    virtual void chapter5_8();
    virtual void chapter5_9();
    virtual void chapter5_11();
    virtual void chapter5_12();
    virtual void initCards();
    virtual void callbackHttpRequest(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    virtual void callbackHttpRequestJson(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    virtual void callbackHttpRequestXml(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    virtual void callbackHttpRequestLoadingBarImages(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    virtual void callbackHttpRequestLoadingBarImage(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    virtual void callbackHttpRequestLoadingBarArchive(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    virtual void callbackHttpRequestLoadingBarArchiveDone(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    virtual void callbackHttpRequestLoadingBarArchiveStep(float dt);
    virtual void onAnimationStateEvent(spine::SkeletonAnimation* node, int trackIndex, spEventType type, spEvent* event, int loopCount);
    virtual void initPhysics();

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
};

#endif // __HELLOWORLD_SCENE_H__
