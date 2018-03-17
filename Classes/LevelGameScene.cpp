//
//  LevelGameScene.cpp
//  CleverMoving
//
//  Created by Harry Nguyen on 7/15/16.
//
//

#include "LevelGameScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "DefineGame.h"
#include "AdmodAndroid.h"
#include "Admob.h"
#define BUFFER 20.0f
#define COLOR4B Color4B(15,15,15,0)
#define TOTAL_PAGE 5
#define TOTAL_ROW 7
#define TOTAL_COLUMN 3
#define MAX_LEVEL 100

LevelGameScene::~LevelGameScene()
{
    
}
Scene* LevelGameScene::createLevelGameScene()
{
    auto scene = Scene::create();
    auto layer = LevelGameScene::create();
    scene->addChild(layer);
    return scene;
}
bool LevelGameScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bensound-littleidea.mp3");
    int adLevel = UserDefault::getInstance()->getIntegerForKey("ADFULLLEVELSCENE", 0);
    UserDefault::getInstance()->setIntegerForKey("ADFULLLEVELSCENE", adLevel + 1);
    
    if(adLevel % 4 == 0)
    {
#if  CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        Admob::getInstance()->loadInterstitial();
        Admob::getInstance()->showInterstitial();
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        AdmodAndroid::showFullAdvertiment();
#endif
    }
    else
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        Admob::getInstance()->showBanner(AdmobPosition::BottomCenter);
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        AdmodAndroid::showBanner();
#endif
    }
    
    winsize = Director::getInstance()->getWinSize();
    /*Create Layerleft*/
    this->createNavigationBarWith();
    
    auto pageView = cocos2d::ui::PageView::create();
    pageView->setTouchEnabled(true);
    pageView->setContentSize(Size(winsize.width, winsize.height));
    for (int i = 0; i < TOTAL_PAGE; i++) {
        auto layout = cocos2d::ui::Layout::create();
        layout->setContentSize(Size(winsize.width, winsize.height));
        LayerColor* color = LayerColor::create(COLOR4B, winsize.width, winsize.height);
        color->setAnchorPoint(Vec2::ZERO);
        color->setPosition(Vec2::ZERO);
        layout->addChild(color);
        for (int j = 0 ; j < TOTAL_COLUMN; j++)
        {
            for (int k = 0 ; k < TOTAL_ROW; k++)
            {
                int index = i*TOTAL_ROW*TOTAL_COLUMN + (k + j*TOTAL_ROW) + 1;
                
                auto button = ui::Button::create();
                if (index > UserDefault::getInstance()->getIntegerForKey("HightLevel",1))
                {
                    button->loadTextures("level_lock.png","","",ui::Widget::TextureResType::LOCAL);
                }
                else
                {
                    button->loadTextures("level_open.png","","",ui::Widget::TextureResType::LOCAL);
                }
                float height = winsize.height/2 + button->getContentSize().height*0.8 - j*(button->getContentSize().height + BUFFER);
                
                button->setPosition(Vec2(button->getContentSize().width*1.5 + (button->getContentSize().width + BUFFER)*k,height ));
                button->setTag(index);
                button->addClickEventListener(CC_CALLBACK_1(LevelGameScene::btnClickButton,this));
                button->setZoomScale(0.3f);
                
                
                auto label = Label::createWithTTF("", "BRLNSDB.TTF", 42);
                char str[512] = {0};
                sprintf(str, "%d",index);
                label->setString(str);
                label->setPosition(Vec2(button->getContentSize().width/2, button->getContentSize().height/2));
                button->addChild(label,100);
                
                if (index > UserDefault::getInstance()->getIntegerForKey("HightLevel",1))
                {
                    
                    auto splock = Sprite::create("lock.png");
                    splock->setPosition(Vec2(button->getContentSize().width/2, button->getContentSize().height/2));
                    button->addChild(splock);
                    button->setEnabled(false);
                    label->setVisible(false);
                    label->setColor(Color3B(Color3B::WHITE));
                }
                layout->addChild(button);
            }
        }
        
        pageView->addPage(layout);
    }
    int currentIndex =  UserDefault::getInstance()->getIntegerForKey("HightLevel", 1)/(TOTAL_ROW* TOTAL_COLUMN);
    pageView->setCurrentPageIndex(currentIndex);
    this->addChild(pageView,100);
    
    this->scheduleUpdate();
    return true;
}
void LevelGameScene::pageviewCallBack(Ref* sender, cocos2d::ui::PageViewEventType type)
{
    if(type == cocos2d::ui::PAGEVIEW_EVENT_TURNING){
      
    }
}
void LevelGameScene::btnClickButton(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("click.mp3");
    int  tag =  ((ui::Button*)pSender)->getTag();
    Director::getInstance()->replaceScene(GameScene::createScene(tag));
}


void LevelGameScene::onEnter(){
    Layer::onEnter();
    EventListenerKeyboard *keyboardEvent = EventListenerKeyboard::create();
    keyboardEvent->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event*){
        if(keyCode == EventKeyboard::KeyCode::KEY_BACK){
            Director::getInstance()->end();
        }
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardEvent, this);
}
void LevelGameScene::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
}

void LevelGameScene::createNavigationBarWith()
{
    auto bg = Sprite::create("bgSceneSelect.png");
    bg->setPosition(Vec2(winsize.width/2, winsize.height/2));
    this->addChild(bg);
    
    auto spNameGame = Sprite::create("text_onlycolor.png");
    spNameGame->setPosition(Vec2(winsize.width/2, winsize.height - spNameGame->getContentSize().height/2));
    this->addChild(spNameGame,1);
    
    auto layerLevel = Sprite::create("bgLayerSelect.png");
    layerLevel->setPosition(Vec2(winsize.width/2, winsize.height*0.4));
    this->addChild(layerLevel,1);
    
    btnSoundOn = ui::Button::create("button_turnon.png","","",ui::Widget::TextureResType::LOCAL);
    btnSoundOn->setPosition(Vec2(winsize.width - btnSoundOn->getContentSize().width*0.6, winsize.height- btnSoundOn->getContentSize().height*0.6));
    btnSoundOn->setTag(TAG_BTN_SOUND_ON);
    btnSoundOn->setSwallowTouches(true);
    btnSoundOn->addClickEventListener(CC_CALLBACK_1(LevelGameScene::btnClickSoundOnOff,this));
    btnSoundOn->setZoomScale(0.1f);
    this->addChild(btnSoundOn,102);
    
    btnSoundOff = ui::Button::create("button_turnoff.png","","",ui::Widget::TextureResType::LOCAL);
    btnSoundOff->setPosition(btnSoundOn->getPosition());
    btnSoundOff->setSwallowTouches(true);
    btnSoundOff->setTag(TAG_BTN_SOUND_OFF);
    btnSoundOff->addClickEventListener(CC_CALLBACK_1(LevelGameScene::btnClickSoundOnOff,this));
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
    
}


void LevelGameScene::btnClickSoundOnOff(Ref* pSender)
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
}
void LevelGameScene::update(float dt)
{
    
}


