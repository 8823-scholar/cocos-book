#import <MediaPlayer/MediaPlayer.h>

@interface VideoPlayerWrapper : NSObject
{
@private
    MPMoviePlayerController* controller_;
}

@property (nonatomic, retain) MPMoviePlayerController* controller;

-(id) init;
-(void) play:(NSString *) path;
-(void) remove;

@end
