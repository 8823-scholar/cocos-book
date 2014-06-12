#include "HelloWorldScene.h"
#include "Card.h"
#include "CardLine.h"
#include "HttpClient.h"
#include "spine/Json.h"
#include "picojson.h"
#include "tinyxml2/tinyxml2.h"
#include "LoadingBar.h"
#include "sqlite/sqlite3.h"
#include "spine/spine-cocos2dx.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    //auto scene = Scene::createWithPhysics();
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    //layer->initPhysics();

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
    //this->chapter5_6();
    //this->chapter5_7();
    //this->chapter5_8();
    //this->chapter5_9();
    this->chapter5_11();
    
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
    /*
    request->setUrl("http://befool.co.jp/images.json");
    request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
    request->setResponseCallback(this, httpresponse_selector(HelloWorld::callbackHttpRequestLoadingBarImages));
    */
    request->setUrl("http://befool.co.jp/archive.json");
    request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
    request->setResponseCallback(this, httpresponse_selector(HelloWorld::callbackHttpRequestLoadingBarArchive));
    
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

void HelloWorld::callbackHttpRequestLoadingBarArchive(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response)
{
    CCASSERT(response->isSucceed(), "failed to get json.");
        
    std::vector<char>* buffer = response->getResponseData();
    const char* data = reinterpret_cast<char*>(&(buffer->front()));
    picojson::value v;
    std::string error;
    picojson::parse(v, data, data + strlen(data), &error);
    CCASSERT(error.empty(), error.c_str());

    auto archive = v.get<picojson::object>()["archive"].get<picojson::object>();
    CCLOG("archive: %s", archive["url"].get<std::string>().c_str());
    this->loadingBar->setTotal(archive["size"].get<double>());

    this->request = new cocos2d::network::HttpRequest();
    this->request->setUrl(archive["url"].get<std::string>().c_str());
    this->request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
    this->request->setResponseCallback(this, httpresponse_selector(HelloWorld::callbackHttpRequestLoadingBarArchiveDone));
    cocos2d::network::HttpClient::getInstance()->send(this->request);

    this->schedule(schedule_selector(HelloWorld::callbackHttpRequestLoadingBarArchiveStep));
}
void HelloWorld::callbackHttpRequestLoadingBarArchiveDone(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response)
{
    CCASSERT(response->isSucceed(), "failed to get archive.");

    CCLOG("archive download done.");
    this->unschedule(schedule_selector(HelloWorld::callbackHttpRequestLoadingBarArchiveStep));
    CCLOG("downloading: %d", (int)this->request->getRequestDataSize());
}
void HelloWorld::callbackHttpRequestLoadingBarArchiveStep(float dt)
{
    CCLOG("downloading: %d", (int)this->request->getRequestDataSize());
    CCLOG("downloading: %f", dt);
}


void HelloWorld::chapter5_7()
{
    /*
    auto user = cocos2d::UserDefault::getInstance();
    user->setStringForKey("name", "木内 智史之介");
    user->setIntegerForKey("hp", 100);
    user->setBoolForKey("connected-facebook", true);
    user->setFloatForKey("height", 172.5);
    user->setDoubleForKey("weight", 67.5);
    user->flush();
    */
    /*
    CCLOG("name: %s", user->getStringForKey("name").c_str());
    CCLOG("hp: %d", user->getIntegerForKey("hp"));
    CCLOG("bool: %d", user->getBoolForKey("connected-facebook"));
    CCLOG("height: %f", user->getFloatForKey("height"));
    CCLOG("weight: %f", user->getDoubleForKey("weight"));
    */

    /*
    auto fileUtils = cocos2d::FileUtils::getInstance();
    std::string filePath = fileUtils->getWritablePath() + "valuemap.plist";
    cocos2d::ValueMap map;
    map["name"] = "木内 智史之介";
    map["hp"] = 100;
    map["facebook-connected"] = true;
    map["height"] = 172.5;
    map["weight"] = 67.5;
    fileUtils->writeToFile(map, filePath);

    map = fileUtils->getValueMapFromFile(filePath);
    CCLOG("name: %s", map["name"].asString().c_str());
    CCLOG("hp: %d", map["hp"].asInt());
    CCLOG("bool: %d", map["connected-facebook"].asBool());
    CCLOG("height: %f", map["height"].asFloat());
    CCLOG("weight: %f", map["weight"].asDouble());
    */

    
    auto fileUtils = cocos2d::FileUtils::getInstance();
    std::string filePath = fileUtils->getWritablePath() + "sqlite3.db";
    CCLOG("sqlite database path: %s", filePath.c_str());

    sqlite3* db;
    auto status = sqlite3_open(filePath.c_str(), &db);
    CCASSERT(status == SQLITE_OK, "failed to open sqlite3 database.");

    // テーブル作成
    std::string sql;
    char* error;
    /*
    sql = "CREATE TABLE player(id integer primary key autoincrement, name nvarchar(128), age int(2));";
    status = sqlite3_exec(db, sql.c_str(), NULL, NULL, &error);
    CCASSERT(status == SQLITE_OK, error);
    */

    // インサート
    /*
    sql = "INSERT INTO player(name, age) VALUES('木内 智史之介', 30);";
    status = sqlite3_exec(db, sql.c_str(), NULL, NULL, &error);
    CCASSERT(status == SQLITE_OK, error);
    */
    
    sqlite3_stmt* stmt;
    sql = "SELECT * FROM player WHERE id = 1;";
    status = sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL);
    CCASSERT(status == SQLITE_OK, "failed to select.");
    while(sqlite3_step(stmt) == SQLITE_ROW) {
        CCLOG("id: %d", sqlite3_column_int(stmt, 0));
        CCLOG("name: %s", sqlite3_column_text(stmt, 1));
        CCLOG("age: %d", sqlite3_column_int(stmt, 2));
    }
}

void HelloWorld::chapter5_8()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto sprite = cocos2d::Sprite::create("girl.png");
    sprite->setScale(0.5);
    sprite->setFlippedX(true);
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 200));
    this->addChild(sprite, 1);

    // 物理設定
    auto body = PhysicsBody::createBox(cocos2d::Size(sprite->getContentSize().width * 0.5, sprite->getContentSize().height * 0.5 - 20));
    body->setMass(1.0f);
    sprite->setPhysicsBody(body);

    // 地面
    auto ground = cocos2d::Sprite::create();
    ground->setAnchorPoint(cocos2d::Point(0.5, 0));
    ground->setPosition(Point(visibleSize.width/2 + origin.x, 0));
    this->addChild(ground);

    auto draw = cocos2d::DrawNode::create();
    cocos2d::Point points[] = {
        cocos2d::Point(0, 0),
        cocos2d::Point(0, 50),
        cocos2d::Point(visibleSize.width + 100, 50),
        cocos2d::Point(visibleSize.width + 100, 0)
    };
    draw->drawPolygon(points, 4, cocos2d::Color4F(cocos2d::Color4B(0, 0, 0, 255)), 0, cocos2d::Color4F(cocos2d::Color4B(0, 0, 0, 0)));
    ground->addChild(draw);
    ground->setContentSize(cocos2d::Size(visibleSize.width + 100, 50));

    auto groundBody = PhysicsBody::createBox(ground->getContentSize());
    groundBody->setDynamic(false);
    ground->setPhysicsBody(groundBody);

    // ジャンプ
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [sprite](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
        CCLOG("tap");
        
        sprite->getPhysicsBody()->applyImpulse(cocos2d::Vect(0, 180.0f));

        return true;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);

    // 障害物
    auto hurdle = cocos2d::Sprite::create();
    hurdle->setPosition(Point(visibleSize.width/2 + origin.x + 200, 10));
    this->addChild(hurdle);

    auto draw2 = cocos2d::DrawNode::create();
    cocos2d::Point points2[] = {
        cocos2d::Point(0, 0),
        cocos2d::Point(0, 1000),
        cocos2d::Point(50, 1000),
        cocos2d::Point(50, 0)
    };
    draw2->drawPolygon(points2, 4, cocos2d::Color4F(cocos2d::Color4B(0, 0, 0, 255)), 0, cocos2d::Color4F(cocos2d::Color4B(0, 0, 0, 0)));
    hurdle->addChild(draw2);
    hurdle->setContentSize(cocos2d::Size(50, 1000));

    auto hurdleBody = cocos2d::PhysicsBody::createBox(hurdle->getContentSize());
    hurdleBody->setDynamic(false);
    hurdle->setPhysicsBody(hurdleBody);
    hurdleBody->setTag(5);

    // 衝突リスナー
    body->setContactTestBitmask(1);
    hurdleBody->setContactTestBitmask(1);
    auto contactListener = cocos2d::EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [this](cocos2d::PhysicsContact& contact) -> bool {
        CCLOG("contacted: shapeA(%d), shapeB(%d)", contact.getShapeA()->getBody()->getTag(), contact.getShapeB()->getBody()->getTag());

        // 障害物との衝突の場合、ゲームーオーバー
        auto shapeA = contact.getShapeA()->getBody();
        auto shapeB = contact.getShapeB()->getBody();
        if (shapeA->getTag() == 5 || shapeB->getTag() == 5) {
            //this->gameOver();
        }

        return true;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, sprite);

    // 右へ飛ばす
    sprite->getPhysicsBody()->applyImpulse(cocos2d::Vect(180.0f, 0));
}

void HelloWorld::initPhysics()
{
    auto scene = this->getScene();

    // 重力場の設定
    cocos2d::Vect gravity;
    auto world = scene->getPhysicsWorld();
    gravity.setPoint(0, -50);
    world->setGravity(gravity);
    //world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    world->setSpeed(6.0f);
}

void HelloWorld::chapter5_9()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto girl = spine::SkeletonAnimation::createWithFile("girl-spine/skeleton.json", "girl-spine/skeleton.atlas");
    girl->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 200));
    this->addChild(girl);

    girl->debugBones = true;
    girl->findBone("left_leg")->rotation = 90;
    girl->setMix("skill2", "idle", 1.0f);
    auto hoge = girl->setAnimation(0, "skill2", false);
    //girl->addAnimation(0, "run", true, 3.0f);
    girl->addAnimation(0, "idle", true, hoge->animation->duration);
    //girl->setAnimation(1, "idle", true);

    //girl->setAnimationListener(this, animationStateEvent_selector(HelloWorld::onAnimationStateEvent));
    girl->setAnimationListener(this, spine::SEL_AnimationStateEvent(&HelloWorld::onAnimationStateEvent));
    
    /*
    auto boarder = spine::SkeletonAnimation::createWithFile("snowboard-spine/skeleton.json", "snowboard-spine/skeleton.atlas");
    boarder->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 200));
    this->addChild(boarder);
    */
}
    
void HelloWorld::onAnimationStateEvent(spine::SkeletonAnimation* node, int trackIndex, spEventType type, spEvent *event, int loopCount)
{
    switch (type) {
        case ANIMATION_START:
            CCLOG("animation started.");
            break;
        case ANIMATION_END:
            CCLOG("animation ended(or aborted).");
            break;
        case ANIMATION_COMPLETE:
            CCLOG("animation completed.");
            break;
        case ANIMATION_EVENT:
            CCLOG("animation custom event.");
            if (strcmp(event->data->name, "jump") == 0) {
                CCLOG("jump! integer:%d, float:%f, string:%s", event->intValue, event->floatValue, event->stringValue);
            }
            break;
    }
}


void HelloWorld::chapter5_11()
{
    auto app = cocos2d::Application::getInstance();
    app->playVideo("sample", "mp4");
}
