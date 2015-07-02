//  RMISDK.h
//  Confidential and Protected Property of Rivus Media Inc

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

//------------------------------------------------
//  Error Codes:
//------------------------------------------------
typedef enum {
    RMIErrorCodeOK = 0,
    RMIErrorCodeNetworkUnreachable = 1,
    RMIErrorCodeNotReadyWithEnoughChoices,
    RMIErrorCodeSystemError,
    RMIErrorCodeUnsupportedIosVersion //version 5.0 or earlier
} RMIErrorCode;

//------------------------------------------------
//  Optional: Background Transition Style
//------------------------------------------------
typedef enum {
    RMIBackgroundTransitionStyleFadeTransition = 1, //Fades the current background of the App. This is the default and is recommended!
    RMIBackgroundTransitionStyleSoftTransition, //Transitions from the background of the App to Custom Image.
    RMIBackgroundTransitionStyleHardTransition, //Uses Custom Image w/o any Transition.
} RMIBackgroundTransitionStyle;

//------------------------------------------------
//  Optional: Log Level
//------------------------------------------------
typedef enum {
    RMISDKLogLevelOff       = 0, //default
    RMISDKLogLevelError     = 1,
    RMISDKLogLevelBasic     = 2,
    RMISDKLogLevelDetail    = 3,
} RMISDKLogLevel;

//------------------------------------------------
//  Required: Delegate Methods:
//------------------------------------------------
@class RMISDK;

@protocol RMISDKDelegate <NSObject>
-(void)rivusUserIsSponsoredWithTag:(NSString *)tag;
-(void)rivusUserDidCancelWithTag:(NSString *)tag;
-(void)rivusDidFailWithTag:(NSString *)tag withError:(NSError *)error;
@optional
-(void)rivusDidDisplayWithTag:(NSString *)tag;

@end

@interface RMISDK : NSObject
//------------------------------------------------
//  Required: Initialization and Display
//------------------------------------------------
+(instancetype)sdkWithPublisherID:(NSString *)pubID
                       andAppName:(NSString *)appName
                 andTargetingData:(NSDictionary *)targetingData;

-(void)displayFromViewController:(UIViewController *)appViewController
                    withDelegate:(id<RMISDKDelegate>)delegate
                  withTag:(NSString *)tag
                         askUser:(BOOL)askUser;
//------------------------------------------------
//  Optional: Properties of RMIViewController
//------------------------------------------------
@property (nonatomic, readonly, strong) NSString *pubID; //provided by your Rivus Mobile Account Manager
@property (nonatomic, readonly, strong) NSString *appName; //your unique name for your app
@property (nonatomic, weak) id<RMISDKDelegate> delegate;
@property (nonatomic, readonly) NSString *sdkVersion; //returns current SDK version
@property (nonatomic) RMISDKLogLevel logLevel;
@property (nonatomic, readonly, strong) NSDictionary *targetingData; //can change it after initialization
@property (nonatomic, readonly, strong) NSString *adTag;
@property (nonatomic) BOOL adInProgress;

//------------------------------------------------
//  Optional: Customising the Background
//------------------------------------------------
-(void)setBackgroundTranstionStyle:(RMIBackgroundTransitionStyle)style;
-(void)setCustomBackgroundAsView:(UIView *)view;
-(void)setCustomBackgroundToImageNamed:(NSString *)imageName; //do place image file in bundle

//------------------------------------------------
//  Optional: Utility Methods:
//------------------------------------------------
+(BOOL)isInited;
+(instancetype)sdk; //returns the singleton instance of RivusViewController
-(BOOL)isReady; //checks if enough choices are availble for a good user experience
-(BOOL)isSupportedIosVersion; //checks if version if iOS6 or later
-(void)stop; //to force SDK to stop

@end

