//
//  Shape.cpp
//  GameTest
//
//  Created by Harry Nguyen on 6/10/16.
//
//

#include "Shape.h"
#define ZorderSprite 124
#define ZorderText 126
static  char sValue[100] = {0};
Shape::Shape()
{
}
void Shape::createUIWithValue(int value)
{
    countRotation = 0;
    char bufferSprite[256] = {0};
    sprintf(bufferSprite, "shape%d.png", value);
    
    mSprite = Sprite::create(bufferSprite);
    mSprite->setPosition(this->getPosition());
    mSprite->setVisible(true);
    this->addChild(mSprite,ZorderSprite);
    
    
    sprintf(sValue, "%d",mValue);
    mtext = Label::createWithTTF(sValue, "BRLNSB.TTF", 40);
    mtext->setPosition(this->getPosition());
    mtext->setVisible(false);
    this->addChild(mtext,ZorderText);
}
Shape::~Shape()
{
    
}
void Shape::updateUIWithValue(int value)
{
    this->mValue = value;
    char newStrValue[512] = {0};
    sprintf(newStrValue, "shape%d.png", value);
    mSprite->setTexture(newStrValue);
    
    char bufferLabel[128] = {0};
    sprintf(bufferLabel, "%d", value);
    mtext->setString(bufferLabel);
    mtext->setVisible(false);
}
void Shape::onEnter()
{
    Node::onEnter();
    this->scheduleUpdate();
}
void Shape::onExit()
{
    Node::onExit();
    this->unscheduleUpdate();
}
void Shape::update(float dt)
{
}
int Shape::getValue()
{
    return mValue;
}
void Shape::setValue(int value)
{
    this->mValue = value;
}
void Shape::setPosmaxtrix(const Vec2& posMaxtrix)
{
    this->posMaxtrix = posMaxtrix;
}
Vec2 Shape::getPosmaxtrix()
{
    return posMaxtrix;
}
bool Shape::runActionShape()
{
    if(mSprite)
    {
        countRotation++;
        RotateTo* action1 = RotateTo::create(0.26f, mSprite->getRotation() + 90.0f);
       
        auto action2 = CallFunc::create([=](){
            mSprite->setRotation(0.0f);
        });
        auto sequence = Sequence::create(action1,action2, NULL);
        mSprite->runAction(sequence);
    }
    return false;
}
