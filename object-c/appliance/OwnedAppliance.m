#import "OwnedAppliance.h"

@implementation OwnedAppliance

-(id)initWithProduceName:(NSString *)produceName
{
	return [self initWithProduceName:produceName firstOwnerName:nil];
}

-(id)initWithProduceName:(NSString *)produceName firstOwnerName:(NSString *)ownerName
{
	self = [super initWithProduceName:produceName];
	
	if(self)
	{
		ownerNames = [[NSMutableSet alloc] init];
		if(ownerName)
		{
			[ownerNames addObject:ownerName];
		}
	}
	return self;
}

-(void)addOwnerNamesObject:(NSString *)ownerName
{
	[ownerNames addObject:ownerName];
}

-(void)removeOwnerNamesObject:(NSString *)ownerName
{
	[ownerNames removeObject:ownerName];
}

@end