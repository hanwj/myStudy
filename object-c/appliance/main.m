#import <Foundation/Foundation.h>
#import "Appliance.h"

int main(int argc,char *argv[])
{
	@autoreleasepool {
		Appliance *a = [[Appliance alloc] init];
		NSLog(@"a is %@",a);
		[a setProduceName:@"washing machine"];
		[a setVoltage:240];
		NSLog(@"a is %@",a);
	}

	return 0;
}