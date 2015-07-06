#import <UIKit/UIKit.h>

NSString *docPath(void);

@interface BNRAppDelegate: UIResponder
<UIApplicationDelegate,UITableViewDataSource>
{
	UITableView *taskTable;
	UITextField *taskField;
	UIButton *insertButton;

	NSMutableArray *tasks;	
}

-(void)addTask:(id)sender;

@property(strong,nonatomic)UIWindow *window;

@end