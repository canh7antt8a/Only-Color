//
//  GameCenterIOS.h
//  OnlyColor
//
//  Created by Nguyen Chi Hoang on 3/19/17.
//
//

#ifndef GameCenterIOS_h
#define GameCenterIOS_h

@interface GameCenterIos : NSObject
{
}

+ (GameCenterIos*)shared;

- (void)login;

- (BOOL)showAchievements;
- (void)postAchievement:(const char*)idName percent:(NSNumber*)percentComplete;
- (void)clearAllAchivements;

- (BOOL)showScores;
- (void)postScore:(const char*)idName score:(NSNumber*)score;
- (void)clearAllScores;
@end
#endif /* GameCenterIOS_h */
