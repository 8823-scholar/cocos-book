#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "VideoPlayer.h"
#import "VideoPlayerIOS.h"

bool VideoPlayer::init()
{
    this->_wrapper = [[VideoPlayerWrapper alloc] init];
    return true;
}

void VideoPlayer::play(const char* path, const char* type)
{
    NSString *videoPath, *stringPath, *stringType;

    stringPath = [NSString stringWithUTF8String:path];
    stringType = [NSString stringWithUTF8String:type];
    videoPath = [[NSBundle mainBundle] pathForResource:stringPath ofType:stringType];
    
    [(VideoPlayerWrapper*)this->getWrapper() play:videoPath];
}
#endif // CC_PLATFORM_IOS
