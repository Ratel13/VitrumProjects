//
//  ViewSingleLeaderboard.h
//  GooglePlayGameServices
//
//  Created by NSS on 4/7/14.
//
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <GooglePlayGames/GooglePlayGames.h>

@interface ViewSingleLeaderboard : UIViewController <GPGLeaderboardControllerDelegate>
{
    
}

-(void) showLeaderboard: (NSString *) leaderBoardID;

@end
