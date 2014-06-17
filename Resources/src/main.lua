require "Cocos2d"
require "Cocos2dConstants"
require "src/log"

cclog("hogehoge");

function foo()
    cclog("foo called");
end

function sum(x, y)
    return x + y
end

function bar(layer)
    local visibleSize = cc.Director:getInstance():getVisibleSize()
    local origin = cc.Director:getInstance():getVisibleOrigin()
    local draw = cc.DrawNode:create()
    local points = {cc.p(0, 0), cc.p(0, 50), cc.p(visibleSize.width + 100, 50), cc.p(visibleSize.width + 100, 0)}
    layer:addChild(draw)
    draw:drawPolygon(points, #points, cc.c4f(0,0,0,1), 0, cc.c4f(0,0,0,1))
    draw:setContentSize(visibleSize.width + 100, 50)

    local sprite = cc.Sprite:create("girl.png");
    sprite:setScale(0.5)
    sprite:setPosition(visibleSize.width/2, 140)
    layer:addChild(sprite)
end
