#import "BNRAppDelegate.h"

NSString *docPath()
{
	NSArray *pathList = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask,YES);
	return [[pathList objectAtIndex:0] stringByAppendingPathComponent:@"data.td"];
}

@implementation BNRAppDelegate

-(void)addTask:(id)sender
{
	NSString *t = [taskField text];
	if([t isEqualToString:@""])
	{
		return;
	}

	[tasks addObject:t];
	[taskTable reloadData];
	[taskField setText:@""];
	[taskField resignFirstResponder]; //关闭键盘
}

#pragma mark --应用委托对象回调方法 
-(BOOL)application:(UIApplication *)application didfinishLauchingWithOptions:(NSDictionary *)lauchOptions
{
	NSArray *plist = [NSArray arrayWithContentsOfFile:docPath()];
	if(plist)
	{
		tasks = [plist mutableCopy];
	}
	else
	{
		tasks = [[NSMutableArray alloc] init];
	}

	if([tasks count] == 0)
	{
		[tasks addObject:@"Walk the dogs"];
		[tasks addObject:@"Feed the hogs"];
		[tasks addObject:@"Chop the logs"];
	}

	//创建并设置UIWindow实例
	//CGRect是C结构，其下两个成员也是C结构:origin(x,y) size(width,height)
	CGRect windowFrame = [[UIScreen mainScreen] bounds];
	UIWindow *theWindow = [[UIWindow alloc] initWithFrame:windowFrame];
	[self setWindow:theWindow];

	CGRect tableFrame = CGRectMake(0,80,320,380);
	CGRect fieldFrame = CGRectMake(20,40,20,31);
	CGRect buttonFrame = CGRectMake(228,40,72,31);

	taskTable = [[UITableView alloc] initWithFrame:tableFrame style:UITableViewStylePlain];
	[taskTable setSeparatorStyle:UITableViewCellSeparatorStyleNone];
	[taskTable setDataSource:self];  //设置数据源

	taskField = [[UITextField alloc] initWithFrame:fieldFrame];
	[taskField setBorderStyle:UITextBorderStyleRoundedRect];
	[taskField setPlaceHolder:@"Type a task,tap Insert"];

	insertButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
	[insertButton setFrame:buttonFrame];
	[insertButton addTarget:self action:@selector(addTask:) forControlEvents:UIControlEventTouchUpInside];
	[insertButton setTitle:@"Insert" forState:UIControlStateNormal];

	[[self window] addSubView:taskTable];
	[[self window] addSubView:taskField];
	[[self windwo] addSubView:insertButton];

	[[self window] setBackgroundColor:[UIColor whiteColor]];
	[[self window] makeKeyAndVisible];

	return YES;
}

-(void)applicationDidEnterBackground:(UIApplication *)application
{
	[tasks writeToFile:docPath() atomically:YES];
}

-(void)applicationWillTerminate:(UIApplication *)application
{
	[tasks writeToFile:docPath() atomically:YES];
}

#pragma mark --管理表格视图
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)numberOfRowsInSection
{
	//因为该表格视图只有一个表格段，所以忽略传入的表格段索引，直接返回任务数组个数
	return [tasks count];
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	UITableViewCell *c = [taskTable dequeueResuableCellWithIdentifier:@"Cell"];
	if(!c){
		c = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"Cell"];
	}

	NSString *item = [tasks objectAtIndex:[indexPath row]];
	[[c textLabel] setText:item];

	return c;
}

@end