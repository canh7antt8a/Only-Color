//
//  LevelGameScene.h
//  CleverMoving
//
//  Created by Harry Nguyen on 7/15/16.
//
//

#ifndef LevelGameScene_h
#define LevelGameScene_h

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;
class LevelGameScene : public Layer {
public:
    Size winsize;
    ui::Button* btnSoundOn;
    ui::Button* btnSoundOff;
    
public:
    virtual bool init();
    virtual ~LevelGameScene();
    static Scene* createLevelGameScene();
    CREATE_FUNC(LevelGameScene);
    void btnClickButton(Ref* pSender);
    void pageviewCallBack(cocos2d::Ref * psender, cocos2d::ui::PageViewEventType type);
    void createNavigationBarWith();
    void onEnter();
    void onExit();
    void btnClickSoundOnOff(Ref* pSender);
    void update(float dt);
};

#endif /* LevelGameScene_hpp */
