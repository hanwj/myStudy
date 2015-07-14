#import "Appliance.h"

@implementation Appliance

@synthesize produceName,voltage;

-(id)init
{
	return [self initWithProduceName:@"unKnown"];
}

-(id)initWithProduceName:(NSString *)produceName
{
	self = [super init];
	if (self)
	{
		produceName = produceName;
		voltage = 120;
	}
	return self;
}

-(NSString *)description
{
	return [NSString stringWithFormat:@"%@: %d volts",produceName,voltage];
}	

@end