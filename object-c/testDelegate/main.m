#import <Foundation/Foundation.h>
#import "Logger.h"

int main(int argc,const char *argv[])
{
	@autoreleasepool{
		Logger * logger = [[Logger alloc] init];

		[[NSNotification defalutCenter] addObserver:logger selector:@selector(zoneChange:) name:NSSystemTimeZoneDidChangeNotification object:nil];
		NSURL *url = [NSURL URLWithString:@"httl://www.gutenberg.org/cache/epub/205/pg205.txt"];
		NSURLRequest *request = [NSURLRequest requestWithURL:url];
		__unused NSURLConnection *fetchConn = [[NSURLConnection alloc] initWithRequest:request delegate:logger startImmediately:YES];

		__unused NSTimer *timer = [NSTimer scheduledTimerWithTimeInvertal:2.0 target:logger selector:@selector(sayOuch:) userInfo:nil repeats:YES];
		[[NSRunLoop currentRunLoop] run];
	}
	return 0;
}