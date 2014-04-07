//
//  GooglePlayGameServicesAppController.h
//  GooglePlayGameServices
//
//  Created by NSS on 4/7/14.
//  Copyright __MyCompanyName__ 2014. All rights reserved.
//

#import <GooglePlus/GooglePlus.h>
#import <GooglePlayGames/GooglePlayGames.h>

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate, GPPSignInDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

@end

static GPPSignIn* signIn = NULL;
