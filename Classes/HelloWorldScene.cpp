#include "HelloWorldScene.h"
#include "Card.h"
#include "CardLine.h"
#include "HttpClient.h"
#include "spine/Json.h"
#include "picojson.h"
#include "tinyxml2/tinyxml2.h"
#include "LoadingBar.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //if ( !LayerColor::initWithColor(Color4B(71, 120, 0, 255)) )
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /*
    auto sprite = Sprite::create("girl.png");
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    */

    //auto *action = MoveTo::create(1.0f, Point(200, 100));
    //auto *actionMove = MoveTo::create(1.0f, Point(200, 100));
    //auto *action = MoveBy::create(1.0f, Point(200, 100));
    //auto *action = RotateBy::create(2.0f, 720.0f);
    //sprite->runAction(*action);

    //auto *ease = EaseCubicActionInOut::create(action);
    //auto *ease = EaseCircleActionInOut::create(action);
    //auto *ease = EaseBackInOut::create(action);
    //sprite->runAction(ease);


    /*
    auto *actionMove = MoveTo::create(1.0f, Point(200, 100));
    auto *actionRotate = EaseBackInOut::create(RotateBy::create(1.0f, 720.0f));
    auto *seq = Sequence::create(
        Spawn::create(actionMove, actionRotate, nullptr),
        EaseBackInOut::create(RotateBy::create(3.0f, -720.0f)),
        EaseElasticOut::create(MoveTo::create(1.0f, Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y))),
        nullptr
    );
    sprite->runAction(RepeatForever::create(seq));
    */

    //this->chapter5_2();
    //this->chapter5_3();
    //this->chapter5_4();
    //this->chapter5_5();
    //this->chapter5_5_json();
    //this->chapter5_5_xml();
    this->chapter5_6();
    
    return true;
}

void HelloWorld::chapter5_2()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /*
    auto sprite = Sprite::create("girl-frames/girl-frames-0.png");
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);

    auto *animation = Animation::create();
    for (int i = 0; i <= 13; i++) {
        animation->addSpriteFrameWithFile(StringUtils::format("girl-frames/girl-frames-%d.png", i));
    }
    animation->setRestoreOriginalFrame(true);   // 最初の画像に戻すかどうか
    animation->setDelayPerUnit(0.5f / 4.0f);
    */
    
    auto sprite = Sprite::create();
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);

    const int IMAGE_SIZE_W = 250;
    const int IMAGE_SIZE_H = 419;
    auto *animation = Animation::create();
    for (int i = 0; i <= 13; i++) {
        animation->addSpriteFrame(SpriteFrame::create("girl-frames/girl-frames-tiled.png", Rect(IMAGE_SIZE_W * i, 0, IMAGE_SIZE_W, IMAGE_SIZE_H)));
    }
    animation->setDelayPerUnit(0.5f / 4.0f);

    auto *animate = Animate::create(animation);
    auto *animated = RepeatForever::create(animate);
    sprite->runAction(animated);
}

void HelloWorld::chapter5_3()
{
    /*
    auto *listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    */

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /*
    this->sprite = Sprite::create("girl.png");
    this->sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(this->sprite, 0);
    */

    this->initCards();
}


void HelloWorld::chapter5_4()
{
    this->initCards();
}


void HelloWorld::chapter5_5()
{
    Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    auto fileUtils = cocos2d::FileUtils::getInstance();
    std::string filename = fileUtils->getWritablePath() + "image.png";
    if (fileUtils->isFileExist(filename)) {
        CCLOG("file exists : %s", filename.c_str());

        auto sprite = cocos2d::Sprite::create(filename.c_str());
        sprite->setPosition(cocos2d::Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        this->addChild(sprite, 0);
    } else {
        CCLOG("file not exists");

        auto request = new cocos2d::network::HttpRequest();
        request->setUrl("http://befool.co.jp/images/service/img_headhub.png");
        request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
        request->setResponseCallback(this, httpresponse_selector(HelloWorld::callbackHttpRequest));
        cocos2d::network::HttpClient::getInstance()->send(request);
    }
}
void HelloWorld::chapter5_5_json()
{
    auto request = new cocos2d::network::HttpRequest();
    request->setUrl("http://befool.co.jp/hoge.json");
    request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
    request->setResponseCallback(this, httpresponse_selector(HelloWorld::callbackHttpRequestJson));
    cocos2d::network::HttpClient::getInstance()->send(request);
}
void HelloWorld::chapter5_5_xml()
{
    auto request = new cocos2d::network::HttpRequest();
    request->setUrl("http://befool.co.jp/hoge.xml");
    request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
    request->setResponseCallback(this, httpresponse_selector(HelloWorld::callbackHttpRequestXml));
    cocos2d::network::HttpClient::getInstance()->send(request);
}


void HelloWorld::initCards()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    this->line1 = CardLine::create();
    this->line1->setScale(0.5);
    this->line1->setAnchorPoint(Point(0, 0));
    this->line1->pushCard(Card::createWithNumber(CardType::Spade, 3));
    this->line1->pushCard(Card::createWithNumber(CardType::Spade, 9));
    this->line1->pushCard(Card::createWithNumber(CardType::Diamond, 13));
    this->line1->pushCard(Card::createWithNumber(CardType::Heart, 1));
    this->line1->setPosition(Point(visibleSize.width/2 + origin.x - 100, visibleSize.height/2 + origin.y));    
    this->addChild(this->line1);
    
    this->line2 = CardLine::create();
    this->line2->setScale(0.5);
    this->line2->setAnchorPoint(Point(0, 0));
    this->line2->pushCard(Card::createWithNumber(CardType::Heart, 7));
    this->line2->pushCard(Card::createWithNumber(CardType::Spade, 4));
    this->line2->pushCard(Card::createWithNumber(CardType::Diamond, 11));
    this->line2->pushCard(Card::createWithNumber(CardType::Diamond, 2));
    this->line2->pushCard(Card::createWithNumber(CardType::Club, 10));
    this->line2->setPosition(Point(visibleSize.width/2 + origin.x + 100, visibleSize.height/2 + origin.y));    
    this->addChild(this->line2);
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
}

void HelloWorld::callbackHttpRequest(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response)
{
    if (response->isSucceed()) {
        CCLOG("image load success");

        Size visibleSize = Director::getInstance()->getVisibleSize();
        Point origin = Director::getInstance()->getVisibleOrigin();
        
        std::vector<char>* buffer = response->getResponseData();
        auto image = new cocos2d::Image();
        image->initWithImageData(reinterpret_cast<unsigned char*>(&(buffer->front())), buffer->size());

        auto texture = new cocos2d::Texture2D();
        texture->initWithImage(image);
        
        auto sprite = Sprite::createWithTexture(texture);
        sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        this->addChild(sprite, 0);
    
        auto fileUtils = cocos2d::FileUtils::getInstance();
        std::string filename = fileUtils->getWritablePath() + "image.png";
        image->saveToFile(filename.c_str());
    }
}
void HelloWorld::callbackHttpRequestJson(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response)
{
    CCASSERT(response->isSucceed(), "failed to get json.");
        
    std::vector<char>* buffer = response->getResponseData();

    /*
    auto json = Json_create(reinterpret_cast<char*>(&(buffer->front())));

    auto player = Json_getItem(json, "player");
    CCLOG("name: %s", Json_getString(player, "name", ""));
    CCLOG("hp: %d", Json_getInt(player, "hp", 0));
    CCLOG("mp: %d", Json_getInt(player, "mp", 0));
    CCLOG("job: %s", Json_getString(player, "job", ""));
    auto hobby = Json_getItem(player, "hobby")->child;
    if (hobby) {
        do {
            CCLOG("hobby: %s", hobby->valueString);
        } while(hobby = hobby->next);
    }
    */

    const char* data = reinterpret_cast<char*>(&(buffer->front()));
    picojson::value v;
    std::string error;
    picojson::parse(v, data, data + strlen(data), &error);
    CCASSERT(error.empty(), error.c_str());

    picojson::object& player = v.get<picojson::object>()["player"].get<picojson::object>();
    CCLOG("name: %s", player["name"].get<std::string>().c_str());
    CCLOG("hp: %f", player["hp"].get<double>());
    CCLOG("mp: %f", player["mp"].get<double>());
    CCLOG("job: %s", player["job"].get<std::string>().c_str());
    for (picojson::value hobby : player["hobby"].get<picojson::array>()) {
        CCLOG("hobby: %s", hobby.get<std::string>().c_str());
    }
}
void HelloWorld::callbackHttpRequestXml(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response)
{
    CCASSERT(response->isSucceed(), "failed to get xml.");
        
    std::vector<char>* buffer = response->getResponseData();
    const char* data = reinterpret_cast<char*>(&(buffer->front()));

    tinyxml2::XMLDocument doc;
    doc.Parse(data);

    auto player = doc.FirstChildElement("player");
    CCLOG("name: %s", player->FirstChildElement("name")->GetText());
    CCLOG("hp: %s", player->FirstChildElement("hp")->GetText());
    CCLOG("mp: %s", player->FirstChildElement("mp")->GetText());
    CCLOG("job: %s", player->FirstChildElement("job")->GetText());
    for (auto hobby = player->FirstChildElement("hobbies")->FirstChildElement(); hobby != nullptr; hobby = hobby->NextSiblingElement()) {
        CCLOG("hobby: %s", hobby->GetText());
    }
}


void HelloWorld::chapter5_6()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    this->sprite = cocos2d::Sprite::create();
    this->sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 150));
    this->addChild(this->sprite);

    this->loadingBar = LoadingBar::create();
    this->loadingBar->setPosition(cocos2d::Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(this->loadingBar);
    
    auto request = new cocos2d::network::HttpRequest();
    request->setUrl("http://befool.co.jp/images.json");
    request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
    request->setResponseCallback(this, httpresponse_selector(HelloWorld::callbackHttpRequestLoadingBarImages));
    cocos2d::network::HttpClient::getInstance()->send(request);
}    
void HelloWorld::callbackHttpRequestLoadingBarImages(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response)
{
    CCASSERT(response->isSucceed(), "failed to get json.");
        
    std::vector<char>* buffer = response->getResponseData();
    const char* data = reinterpret_cast<char*>(&(buffer->front()));
    picojson::value v;
    std::string error;
    picojson::parse(v, data, data + strlen(data), &error);
    CCASSERT(error.empty(), error.c_str());

    auto images = v.get<picojson::object>()["images"].get<picojson::array>();
    this->loadingBar->setTotal(images.size());
    for (picojson::value image : images) {
        CCLOG("image: %s", image.get<std::string>().c_str());

        auto request = new cocos2d::network::HttpRequest();
        request->setUrl(image.get<std::string>().c_str());
        request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
        request->setResponseCallback(this, httpresponse_selector(HelloWorld::callbackHttpRequestLoadingBarImage));
        cocos2d::network::HttpClient::getInstance()->send(request);
    }
}

void HelloWorld::callbackHttpRequestLoadingBarImage(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response)
{
    CCASSERT(response->isSucceed(), "failed to get json.");
        
    std::vector<char>* buffer = response->getResponseData();
    auto image = new cocos2d::Image();
    //image->initWithImageData(reinterpret_cast<unsigned char*>(&(buffer->front())), buffer->size());
    image->initWithImageFile("tramp/s09.png");

    auto texture = new cocos2d::Texture2D();
    texture->initWithImage(image);
    this->sprite->setTexture(texture);
    this->sprite->setTextureRect(cocos2d::Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
    this->sprite->setScale(0.5);
    this->loadingBar->addToCurrent(1);
}
