//
//  ViewController.m
//  RivusSDKSampleNativeApp
//
//  Created by Olivier Boucher on 2015-07-19.
//  Copyright (c) 2015 Rivus Media Inc. All rights reserved.
//

#import "ViewController.h"
#import "RivusSDK/RMISDK.h"

@interface ViewController ()
@property (strong, nonatomic) IBOutlet UIButton *launchButton;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}
- (IBAction)lauchButtonClick:(id)sender {
    if([[RMISDK sdk] isReady]){
        [[RMISDK sdk] displayFromViewController:self withDelegate:nil withTag:nil askUser:NO];
    }
    else {
        NSString *message = @"RivusSDK is currently loading...";
        UIAlertView *toast = [[UIAlertView alloc] initWithTitle:nil
                                                        message:message
                                                       delegate:nil
                                              cancelButtonTitle:nil
                                              otherButtonTitles:nil, nil];
        [toast show];
        
        int duration = 3; // duration in seconds
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, duration * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
            [toast dismissWithClickedButtonIndex:0 animated:YES];
        });
    }
}

@end
