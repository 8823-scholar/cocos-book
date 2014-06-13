#include "cocos2d.h"
#import <MediaPlayer/MediaPlayer.h>

@interface VideoPlayerWrapper : NSObject
{
@private
    MPMoviePlayerController* controller_;
}

@property (nonatomic, retain) MPMoviePlayerController* controller;

-(id) init;
//virtual void play(const char* path, const char* type);
-(void) play:(NSString *) path;
-(void) remove;

@end
