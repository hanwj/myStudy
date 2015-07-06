#import <Foundation/Foundation.h>

@interface Logger:NSObject{
	NSMutableData *incommingData;
}
- (void)sayOuch:(NSTimer *)t;
@end