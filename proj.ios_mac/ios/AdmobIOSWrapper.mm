//
//  AdmobIOSWrapper.m
//  PikachuSpace
//
//  Created by Hoang Nguyen on 1/27/17.
//
//

#import "AdmobIOSWrapper.h"
#import "AdmobIOS.h"
#import "GameCenterIOS.h"

static AdmobIOSWrapper _sAdmobIOSWrapper;

AdmobIOSWrapper* AdmobIOSWrapper::getInstance() {
    return &_sAdmobIOSWrapper;
}

void AdmobIOSWrapper::init(const std::string &bannerId, const std::string &interstitialId) {
    NSString *banner = [NSString stringWithUTF8String:bannerId.data()];
    NSString* interstitial = [NSString stringWithUTF8String:interstitialId.data()];
    [[AdmobIOS sharedAdmob] setBannerId:banner];
    [[AdmobIOS sharedAdmob] setInterstitialId:interstitial];
}

void AdmobIOSWrapper::showBanner(int position) {
    [[AdmobIOS sharedAdmob] showBannerInPostion:position];
}

void AdmobIOSWrapper::hideBanner() {
    [[AdmobIOS sharedAdmob] hideBanner];
}

void AdmobIOSWrapper::loadInterstitial() {
    [[AdmobIOS sharedAdmob] loadInterstitial];
}

void AdmobIOSWrapper::showInterstitial() {
    [[AdmobIOS sharedAdmob] showInterstitial];
}
bool AdmobIOSWrapper::getShowFullVideo(){
    return  [[AdmobIOS sharedAdmob] getStatusShowAdmod];
}



void AdmobIOSWrapper::showAchiment()
{
    [[GameCenterIos shared] login];
    [[GameCenterIos shared] showAchievements];
}
void AdmobIOSWrapper::unlockAchimnet(const char* idName, int numberPerCen)
{
    [[GameCenterIos shared] postScore:idName score:[NSNumber numberWithInt:numberPerCen]];
}
