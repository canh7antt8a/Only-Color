//
//  Shape.hpp
//  GameTest
//
//  Created by Harry Nguyen on 6/10/16.
//
//

#ifndef Shape_h
#define Shape_h

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class Shape  :public Node
{
private:
    Sprite* mSprite;
    Label* mtext;
    int mValue;
    Vec2 posMaxtrix;
    bool doneAction;
    int countRotation;
public:
    Shape();
    void createUIWithValue(int value);
    virtual ~Shape();
    void updateUIWithValue(int value);
    void update(float dt);
    void onEnter();
    void onExit();
    int getValue();
    void setValue(int value);
    void setPosmaxtrix(const Vec2& posMaxtrix);
    Vec2 getPosmaxtrix();
    
    bool runActionShape();
};

#endif /* Shape_h */
