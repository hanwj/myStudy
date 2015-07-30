#import <Foundation/Foundation.h>
#import "NSString+VowelCounting.h"

int main(int argc,char *argv[])
{
	@autoreleasepool{
		NSString *string = @"hello,world!";
		NSLog(@"%@ has %d vowels",string,[string vowelCount]);
	}
	return 0;
}