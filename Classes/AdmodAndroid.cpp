//
//  AdmodAndroid.cpp

#include "AdmodAndroid.h"
#include "cocos2d.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "jni/JniHelper.h"
extern "C"{
    void AdmodAndroid::showBanner(){

        JniMethodInfo methodInfo;
        bool b = JniHelper::getStaticMethodInfo(methodInfo,"org.cocos2dx.cpp.AppActivity","showAd","()V");
        if(b){
        	 log("aaaaaaaaaaaaaaaaaaaaaaaaaaa");
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
            
        }else{
            log("Error");
        }
    }
    void AdmodAndroid::hideBanner(){
        JniMethodInfo methodInfo;
        bool b = JniHelper::getStaticMethodInfo(methodInfo,"org.cocos2dx.cpp.AppActivity","hideAd","()V");
        if(b){
       	 log("bbbbbbbbbbbbbbbbbbbbbbbbbb");
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }else{
            log("Error");
        }
    }
    void AdmodAndroid::showFullAdvertiment(){
        JniMethodInfo methodInfo;
        bool b = JniHelper::getStaticMethodInfo(methodInfo,"org.cocos2dx.cpp.AppActivity","showInterstitialAd","()V");
        if(b)
        {
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
        else{
            log("Error");
        }

    }
    
    void AdmodAndroid::unlockAchimentGoogle(int levelUnlock)
    {
        JniMethodInfo methodInfo;
        jint p = (jint)levelUnlock;
        bool b = JniHelper::getStaticMethodInfo(methodInfo,"com.nguyenhoang.game.GoogleLeaderboards","jniUnlock","(I)V");
        log("sssssssssssssssssssssssssssssssssss");
        if(b)
        {
            log("44444444444444444444444444");
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,p);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
        else
        {
            log("5555555555555555555555555555555555555");
        }
    }
    void AdmodAndroid::showAchimentGoolgle() {
        JniMethodInfo methodInfo;
        bool b = JniHelper::getStaticMethodInfo(methodInfo,"com.nguyenhoang.game.GoogleLeaderboards","jniShowAchiment","()V");
        if(b){
            log("dddddd");
            
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }else{
            log("Error");
        }
    }
    
}
#endif
