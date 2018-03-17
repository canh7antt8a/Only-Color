//
//  GameCenterAndGoolePlay.cpp
//  OnlyColor
//
//  Created by Nguyen Chi Hoang on 3/19/17.
//
//

#include "cocos2d.h"
#include "GameCenterAndGoolePlay.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "AdmobIOSWrapper.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "AdmodAndroid.h"
#endif


static GameCenterAndGoolePlay _sbManager;
GameCenterAndGoolePlay* GameCenterAndGoolePlay::getInstance()
{
    return &_sbManager;
}
void GameCenterAndGoolePlay::showAchievementsGoogleAndApple()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    AdmobIOSWrapper::getInstance()->showAchiment();
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    AdmodAndroid::showAchimentGoolgle();
#endif
}

void GameCenterAndGoolePlay::postAchievementGoogleAndApple( int levelGoogle){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    AdmodAndroid::unlockAchimentGoogle(levelGoogle);
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    if(levelGoogle == 5){
        AdmobIOSWrapper::getInstance()->unlockAchimnet("5", 5);
    }
    if(levelGoogle == 20){
        AdmobIOSWrapper::getInstance()->unlockAchimnet("20", 20);
    }
    if(levelGoogle == 40){
        AdmobIOSWrapper::getInstance()->unlockAchimnet("40", 40);
    }
    if(levelGoogle == 80){
        AdmobIOSWrapper::getInstance()->unlockAchimnet("80", 80);
    }
    if(levelGoogle == 100){
        AdmobIOSWrapper::getInstance()->unlockAchimnet("10", 100);
    }
#endif
}
