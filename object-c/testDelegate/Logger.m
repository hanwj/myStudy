#import "Logger.h"

@implementation Logger

- (void)sayOuch:(NSTimer *)t
{
	NSLog(@"sayOuch");
}

//收到一定字节数据后会调用
-(void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
	NSLog(@"received %lu bytes",[data length]);
	if(!incomingData)
	{
		incomingData = [[NSMutableData alloc] init];	
	}

	[incomingData appendData:data];
}

//最后一部分数据处理完后调用
-(void)connectionDidFinishLoading(NSURLConnection *)connection
{
	NSLog(@"Go it all");
	NSString *string = [[NSString alloc] initWithData:incomingData encoding:NSUTF8StringEncoding];
	incomingData = nil;
	NSLog(@"string has %lu characters",[string length]);
	NSLog(@"The whole string is %@",string);
}
//获取数据失败会被调用
-(void)connection(NSURLConnection *)connection didFailWithError:(NSError *)error
{
	NSLog(@"connection failed:@",[error localizedDescription]);
	incomingData = nil;
}

-(void)zoneChange:(NSNotification *)note
{
	NSLog(@"The system time zone has changed");
}

@end