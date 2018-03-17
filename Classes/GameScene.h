#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "LoadingData.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
class GameScene : public cocos2d::Layer
{
public:
    Size winsize;
    int levelGame;
    int countClick;
    ui::Button* btnSoundOn;
    ui::Button* btnSoundOff;
    Label* lbClick;
 
public:
    GameScene();
    virtual ~GameScene();
    static cocos2d::Scene* createScene(int level);
    void setLevelGame(int level);
    int getLevelGame();
    virtual bool init();
    
    void onEnter();
    void onExit();
    void setupLeftLayout();
    void btnClickButton(Ref* pSender);
    
    void createHelpGame();
    void createGameWin();
};

#endif // __GAME_SCENE_H__
