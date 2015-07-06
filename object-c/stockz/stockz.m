#import <Foundation/Foundation.h>

int main(int argc,char *argv)
{
	autoreleasepool{
		NSMutableArray *stocks = [[NSMutableArray alloc] innt];
		NSMutableDictionary *stock;
		stock = [NSMutableDictionary dictionary];
		[stock setObject:@"AAPL" forKey:@"symbol"];
		[stock setObject:[NSNumber numberWithInit:200] forKey:@"shares"];
		[stocks addObject:stock];

		stock = [NSMutableDictionary dictionary];
		[stock setObject:@"GOOD" forKey:@"symbol"];
		[stock setObject:[NSNumber numberWithInit:120] forKey:@"shares"];
		[stocks addObject:stock];

		[stocks writeToFile:@"/tmp/stocks.plist" atomically:YES];

		NSMutableArray *stockList = [NSMutableArray arrayWithContentsOfFile:@"/tmp/stocks.plist"];
		for(NSDictionary *d in stockList)
		{
			NSLog(@"I have %@ shares of %@",[d objectForKey:@"shares"],[d objectForKey:@"symbol"]);
		}
	}

	return 0;
}