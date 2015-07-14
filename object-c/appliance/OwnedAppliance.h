#import "Appliance"

@interface OwendAppliance: Appliance 
{
	NSMutableSet *ownerNames;
}

-(id)initWithProduceName:(NSString *)produceName;

//指定初始化方法
-(id)initWithProduceName:(NSString *)produceName firstOwnerName:(NSString *)ownerName;

-(void)addOwnerNamesObject:(NSString *)ownerName;

-(void)removeOwnerNamesObject:(NSString *)ownerName;