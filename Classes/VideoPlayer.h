#ifndef __VIDEO_PLAYER_H__
#define __VIDEO_PLAYER_H__

#include "cocos2d.h"

class VideoPlayer : public cocos2d::Node
{
public:
    CREATE_FUNC(VideoPlayer);
    virtual bool init();
    virtual void play(const char* path, const char* type);

    // get wrapper instance.
    void* getWrapper() const { return this->_wrapper; };

private:
    // media controller wrapper instance
    void* _wrapper;
};

#endif // __VIDEO_PLAYER_H__
