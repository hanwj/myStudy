#import <Foundation/Foundation.h>

@interface Appliance:NSObject
{
	NSString *produceName;
	int voltage;
}

@property (copy) NSString *produceName;
@property int voltage;

//指定初始化方法
-(id)initWithProduceName:(NSString *)produceName;
