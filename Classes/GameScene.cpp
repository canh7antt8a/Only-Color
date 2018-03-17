#include "GameScene.h"
#include "GameBoard.h"
#include "DefineGame.h"
#include "SimpleAudioEngine.h"
#include "LevelGameScene.h"
#include "AdmodAndroid.h"
#include "Admob.h"
#include "GameCenterAndGoolePlay.h"
#define X_COORDI 80
#define COLOR Color4B(8,2,4,200)
USING_NS_CC;
#define TAG_LAYER_HELP_GAME 1234
#define TAG_LAYER_WIN_GAME 1235
#define TAG_BTN_HELP_GAME 178



GameScene::GameScene()
{
    
}
GameScene::~GameScene()
{
    
}
Scene* GameScene::createScene(int level)
{
    auto scene = Scene::create();
    auto layer = new GameScene();
    layer->setLevelGame(level);
    layer->init();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    
#if  CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    Admob::getInstance()->showBanner(AdmobPosition::TopCenter);
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    AdmodAndroid::showBanner();
#endif
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bensound-littleidea.mp3");
    }
    countClick = 0;
    winsize = Director::getInstance()->getWinSize();
    auto bg = Sprite::create("bgSceneSelect.png");
    bg->setPosition(Vec2(winsize.width/2, winsize.height/2));
    this->addChild(bg);
    
    auto titleLevel = Sprite::create("banner_level.png");
    titleLevel->setPosition(Vec2(winsize.width/2, winsize.height - titleLevel->getContentSize().height/2));
    this->addChild(titleLevel,1);
    
    auto titleBg = Sprite::create("bg_ingame.png");
    titleBg->setPosition(Vec2(winsize.width*0.44,winsize.height*0.46));
    this->addChild(titleBg,1);
    
    
    
    char bufferLabelLevel[512] ={0};
    sprintf(bufferLabelLevel, "Level %d", levelGame);
    Label* lbLevel = Label::createWithTTF(bufferLabelLevel, "BRLNSDB.TTF", 36);
    lbLevel->setPosition(Vec2(titleLevel->getPositionX(), titleLevel->getPositionY() + 10.0f));
    lbLevel->setTextColor(Color4B(77.0f/255.0f, 41.0f/255.0f , 17.0f/255.0f, 180));
    this->addChild(lbLevel,2);
    
    lbClick = Label::createWithTTF("Touch : 0", "BRLNSDB.TTF", 32.0f);
    lbClick->setAnchorPoint(Vec2(0, 0.5f));
    lbClick->setPosition(Vec2(20,titleLevel->getPositionY()));
    this->addChild(lbClick,2);
    
    /*minTouch*/
    char bufferbestTouch[512] = {0};
    sprintf(bufferbestTouch, "MIN_TOUCH_%d",levelGame);
    int bestTouch = UserDefault::getInstance()->getIntegerForKey(bufferbestTouch, 1000);
    
    
    if(bestTouch == 1000)
    {
        Label* bestClick = Label::createWithTTF("Best touch : --", "BRLNSDB.TTF", 32.0f);
        bestClick->setAnchorPoint(Vec2(1, 0.5f));
        bestClick->setPosition(Vec2(winsize.width,titleLevel->getPositionY()));
        this->addChild(bestClick,2);
    }
    else
    {
        char tempBest[512] = {0};
        sprintf(tempBest, "Best touch : %d",bestTouch);
        Label* bestClick = Label::createWithTTF(tempBest, "BRLNSDB.TTF", 32.0f);
        bestClick->setAnchorPoint(Vec2(1, 0.5f));
        bestClick->setPosition(Vec2(winsize.width - 20,titleLevel->getPositionY()));
        this->addChild(bestClick,2);
    }
    
    
    
    /*level*/
    char bufferLevel[512] = {0};
    sprintf(bufferLevel, "level%d.xml", levelGame);
    LoadingData* loading = new LoadingData();
    loading->loadingWithFileName(bufferLevel);
    
    this->setupLeftLayout();
    if(levelGame == 1)
    {
        this->createHelpGame();
    }
    
    
    
    Gameboard* gameboard = new Gameboard();
    gameboard->setMaxtrixWidthHeight(WIDTH_MATRIX, HEIGHT_MATRIX);
    gameboard->setPosition(Vec2(-5, -2.5));
    gameboard->createStartGameBoard(loading->getArrayPoint());
    this->addChild(gameboard,4);
    
    auto touch = EventListenerTouchOneByOne::create();
    touch->setSwallowTouches(true);
    
    touch->onTouchBegan = [=](Touch* mTouch , Event* pEvent){
        std::vector<Shape*> arrayCheck;
        Vec2 pos =  gameboard->convertPosGameboard(mTouch->getLocation());
        
        if(pos.x >= 0 && pos.y >= 0 && pos.x < WIDTH_MATRIX && pos.y < HEIGHT_MATRIX)
        {
            
#if  CC_TARGET_PLATFORM == CC_PLATFORM_IOS
            Admob::getInstance()->hideBanner();
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
            AdmodAndroid::hideBanner();
#endif
            countClick ++;
            static char bufferCountTouch[512] = {0};
            sprintf(bufferCountTouch, "Touch : %d", countClick);
            lbClick->setString(bufferCountTouch);
            gameboard->checkSumOfColumAndRow(gameboard->getShapeWithPosition(pos), arrayCheck);
            gameboard->rotationAndChangeValue(arrayCheck);
            if(gameboard->checkWinArray() == true)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
                static char buffetMinTouch[512] = {0};
                sprintf(buffetMinTouch, "MIN_TOUCH_%d",levelGame);
                int minTouch = UserDefault::getInstance()->getIntegerForKey(buffetMinTouch, 10000);
                if(countClick < minTouch)
                {
                    UserDefault::getInstance()->setIntegerForKey(buffetMinTouch, countClick);
                }
                auto actionDelay = DelayTime::create(0.6f);
                auto action2 = CallFunc::create([=](){
                    this->createGameWin();
                });
                this->runAction(Sequence::create(actionDelay,action2, NULL));
            }
        }
        
        return  true;
    };
    touch->onTouchMoved = [=](Touch* mTouch, Event* pEvent){
    };
    touch->onTouchEnded = [=](Touch* mTouch, Event* pEvent){
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, this);
    
    
    GameCenterAndGoolePlay::getInstance()->postAchievementGoogleAndApple(levelGame);
    return true;
}
void GameScene::setLevelGame(int level)
{
    this->levelGame = level;
}
int GameScene::getLevelGame()
{
    return levelGame;
}

void GameScene::createGameWin()
{
    if(levelGame % 5 == 0)
    {
#if  CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        Admob::getInstance()->loadInterstitial();
        Admob::getInstance()->showInterstitial();
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        AdmodAndroid::showFullAdvertiment();
#endif
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("win.mp3",false);
    Layer* winLayer= Layer::create();
    winLayer->setPosition(Vec2::ZERO);
    winLayer->setContentSize(Size(Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height));
    winLayer->setTag(TAG_LAYER_WIN_GAME);
    this->addChild(winLayer,TAG_LAYER_WIN_GAME);
    
    auto touch = EventListenerTouchOneByOne::create();
    touch->setSwallowTouches(true);
    touch->onTouchBegan = [&](Touch* ptouch, Event* mEvent){
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, winLayer);
    
    LayerColor* layerColorWin = LayerColor::create(COLOR, winsize.width, winsize.height);
    layerColorWin->setPosition(Vec2(0,0));
    winLayer->addChild(layerColorWin);
    
    /*Prepari*/
    Sprite* monsterDown;
    Sprite* monsterUp;
    monsterDown = Sprite::create("monster_down.png");
    monsterDown->setPosition(Vec2(winsize.width/2, -winsize.height*0.5));
    layerColorWin->addChild(monsterDown,1234);
    
    monsterUp = Sprite::create("monster_up.png");
    monsterUp->setPosition(Vec2(winsize.width/2, winsize.height*1.5));
    layerColorWin->addChild(monsterUp,1234);
    
    monsterUp->runAction(MoveTo::create(0.5f,Vec2(winsize.width/2, winsize.height*0.8)));
    monsterDown->runAction(MoveTo::create(0.5f,Vec2(winsize.width/2, winsize.height*0.2)));
    
    
    int hightLevel =  UserDefault::getInstance()->getIntegerForKey("HightLevel", 1);
    if (levelGame >= hightLevel)
    {
        UserDefault::getInstance()->setIntegerForKey("HightLevel", levelGame + 1);
    }
    this->scheduleOnce([=](float dt){
        Director::getInstance()->replaceScene(GameScene::createScene(levelGame + 1));
    }, 2.0f, "NextLevel");
    
}

void GameScene::onEnter(){
    Layer::onEnter();
    EventListenerKeyboard *keyboardEvent = EventListenerKeyboard::create();
    keyboardEvent->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event*){
        if(keyCode == EventKeyboard::KeyCode::KEY_BACK){
            Director::getInstance()->replaceScene(LevelGameScene::createLevelGameScene());
        }
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardEvent, this);
}
void GameScene::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
}

void GameScene::setupLeftLayout()
{
    ui::Button* btnMenu = ui::Button::create("button_menu_normal.png","button_menu_pressed.png","",ui::Widget::TextureResType::LOCAL);
    btnMenu->setPosition(Vec2(winsize.width - btnMenu->getContentSize().width*0.6,btnMenu->getContentSize().height*0.86));
    btnMenu->setTag(TAG_BTN_MENU);
    btnMenu->setSwallowTouches(true);
    btnMenu->addClickEventListener(CC_CALLBACK_1(GameScene::btnClickButton,this));
    btnMenu->setZoomScale(0.1f);
    this->addChild(btnMenu,102);
    
    
    ui::Button* btnReplay = ui::Button::create("button_replay_normal.png","button_replay_pressed.png","",ui::Widget::TextureResType::LOCAL);
    btnReplay->setPosition(Vec2(btnMenu->getPositionX(), btnMenu->getPositionY() + btnReplay->getContentSize().height*1.2));
    btnReplay->setTag(TAG_BTN_REPLAY);
    btnReplay->setSwallowTouches(true);
    btnReplay->addClickEventListener(CC_CALLBACK_1(GameScene::btnClickButton,this));
    btnReplay->setZoomScale(0.1f);
    this->addChild(btnReplay,102);
    
    
    btnSoundOn = ui::Button::create("button_turnon.png","","",ui::Widget::TextureResType::LOCAL);
    btnSoundOn->setPosition(Vec2(btnMenu->getPositionX(), btnReplay->getPositionY() + btnSoundOn->getContentSize().height*1.2));
    btnSoundOn->setTag(TAG_BTN_SOUND_ON);
    btnSoundOn->setSwallowTouches(true);
    btnSoundOn->addClickEventListener(CC_CALLBACK_1(GameScene::btnClickButton,this));
    btnSoundOn->setZoomScale(0.1f);
    this->addChild(btnSoundOn,102);
    
    
    btnSoundOff = ui::Button::create("button_turnoff.png","","",ui::Widget::TextureResType::LOCAL);
    btnSoundOff->setPosition(btnSoundOn->getPosition());
    btnSoundOff->setTag(TAG_BTN_SOUND_OFF);
    btnSoundOff->setSwallowTouches(true);
    btnSoundOff->addClickEventListener(CC_CALLBACK_1(GameScene::btnClickButton,this));
    btnSoundOff->setZoomScale(0.1f);
    this->addChild(btnSoundOff,102);
    
    if(UserDefault::getInstance()->getBoolForKey("sound", true))
    {
        btnSoundOn->setVisible(true);
        btnSoundOff->setVisible(false);
    }
    else
    {
        btnSoundOn->setVisible(false);
        btnSoundOff->setVisible(true);
    }
    
    
    /*btnAchiment*/
    ui::Button* btnAchiment = ui::Button::create("button_chart_normal.png","button_chart_pressed.png","",ui::Widget::TextureResType::LOCAL);
    btnAchiment->setPosition(Vec2(btnMenu->getPositionX(), btnSoundOff->getPositionY() + btnAchiment->getContentSize().height*1.2));
    btnAchiment->setTag(TAG_BTN_ARCHIMENT);
    btnAchiment->setSwallowTouches(true);
    btnAchiment->addClickEventListener(CC_CALLBACK_1(GameScene::btnClickButton,this));
    btnAchiment->setZoomScale(0.1f);
    this->addChild(btnAchiment,102);
    
}

void GameScene::createHelpGame()
{
    Layer* helpLayer= Layer::create();
    helpLayer->setAnchorPoint(Vec2::ZERO);
    helpLayer->setPosition(Vec2::ZERO);
    helpLayer->setContentSize(Size(Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height));
    helpLayer->setTag(TAG_LAYER_HELP_GAME);
    this->addChild(helpLayer,TAG_LAYER_HELP_GAME);
    
    auto touch = EventListenerTouchOneByOne::create();
    touch->setSwallowTouches(true);
    touch->onTouchBegan = [&](Touch* ptouch, Event* mEvent){
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, helpLayer);
    
    LayerColor* layerColor = LayerColor::create(COLOR, winsize.width, winsize.height);
    layerColor->setPosition(Vec2(0,0));
    helpLayer->addChild(layerColor);
    
    auto spHelpGame = Sprite::create("help.png");
    spHelpGame->setPosition(Vec2(winsize.width/2, winsize.height/2));
    layerColor->addChild(spHelpGame,1);
    
    ui::Button* btnHelpToLearn  = ui::Button::create("button_help_normal.png","button_help_pressed.png","",ui::Widget::TextureResType::LOCAL);
    btnHelpToLearn->setPosition(Vec2(spHelpGame->getPositionX(), spHelpGame->getPositionY() - spHelpGame->getContentSize().height*0.46));
    btnHelpToLearn->setTag(TAG_BTN_HELP_GAME);
    btnHelpToLearn->setSwallowTouches(true);
    btnHelpToLearn->addClickEventListener(CC_CALLBACK_1(GameScene::btnClickButton,this));
    btnHelpToLearn->setZoomScale(0.1f);
    layerColor->addChild(btnHelpToLearn,2);
    
    
}
void GameScene::btnClickButton(Ref* pSender)
{
    int  tag =  ((ui::Button*)pSender)->getTag();
    
    if(tag == TAG_BTN_SOUND_ON)
    {
        
        
        btnSoundOn->setVisible(false);
        btnSoundOff->setVisible(true);
        UserDefault::getInstance()->setBoolForKey("sound", false);
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
        
    }
    if(tag == TAG_BTN_SOUND_OFF)
    {
        btnSoundOn->setVisible(true);
        btnSoundOff->setVisible(false);
        UserDefault::getInstance()->setBoolForKey("sound", true);
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
    }
    if(tag == TAG_BTN_MENU)
    {
        Director::getInstance()->replaceScene(LevelGameScene::createLevelGameScene());
    }
    if(tag == TAG_BTN_REPLAY)
    {
        Director::getInstance()->replaceScene(GameScene::createScene(levelGame));
    }
    if(tag == TAG_BTN_HELP_GAME)
    {
        if(this->getChildByTag(TAG_LAYER_HELP_GAME))
        {
            this->removeChildByTag(TAG_LAYER_HELP_GAME);
        }
    }
    if(tag == TAG_BTN_ARCHIMENT)
    {
        GameCenterAndGoolePlay::getInstance()->showAchievementsGoogleAndApple();
    }
}






