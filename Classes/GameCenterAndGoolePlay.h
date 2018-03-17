//
//  GameCenterAndGoolePlay.h
//  OnlyColor
//
//  Created by Nguyen Chi Hoang on 3/19/17.
//
//

#ifndef GameCenterAndGoolePlay_h
#define GameCenterAndGoolePlay_h

#include <stdio.h>

class GameCenterAndGoolePlay
{
public:
    static GameCenterAndGoolePlay* getInstance();
    void showAchievementsGoogleAndApple();
    void postAchievementGoogleAndApple( int levelGoogle);
};
#endif /* GameCenterAndGoolePlay_h */
