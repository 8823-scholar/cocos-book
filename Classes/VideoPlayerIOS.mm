#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "cocos2d.h"
#import <MediaPlayer/MediaPlayer.h>
#import "CCEAGLView.h"
#import "VideoPlayerIOS.h"

@implementation VideoPlayerWrapper

@synthesize controller=controller_;

-(id) init
{
    auto director = cocos2d::Director::getInstance();
    CCEAGLView* eaglview = (CCEAGLView*)director->getOpenGLView()->getEAGLView();

    self.controller = [[MPMoviePlayerController alloc] init];
    self.controller.view.frame = CGRectMake(0, 0, eaglview.frame.size.height, eaglview.frame.size.width);
    self.controller.fullscreen = YES;
    self.controller.scalingMode = MPMovieScalingModeNone;
    self.controller.controlStyle = MPMovieControlStyleNone;

    return self;
}

-(void) play:(NSString *)path
{
    NSURL* url = [NSURL fileURLWithPath:path];
    self.controller.contentURL = url;
    [self.controller play];

    [(CCEAGLView*)cocos2d::Director::getInstance()->getOpenGLView()->getEAGLView() addSubview:self.controller.view];

    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(remove)
                                                 name:MPMoviePlayerPlaybackStateDidChangeNotification object:nil];
}

- (void) remove
{
    if (self.controller.playbackState == MPMoviePlaybackStatePaused || self.controller.playbackState == MPMoviePlaybackStateStopped) {

        NSLog(@"Remove Video");

        [self.controller.view removeFromSuperview];

        [[NSNotificationCenter defaultCenter] removeObserver:self
                                                        name:MPMoviePlayerPlaybackStateDidChangeNotification
                                                      object:nil];

        if (cocos2d::Director::getInstance()->isPaused()) {
            cocos2d::Director::getInstance()->resume();
        }
    }
}
@end
#endif // CC_PLATFORM_IOS
