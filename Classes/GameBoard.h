//
//  GameBoard.h
//  OnlyColor
//
//  Created by Harry Nguyen on 8/10/16.
//
//

#ifndef GameBoard_h
#define GameBoard_h

#include <stdio.h>
#include "cocos2d.h"
#include "PointGame.h"
#include "Shape.h"
USING_NS_CC;

class Gameboard: public Layer
{
public:
    Vec2 posGameboard;
    int widthGameboard;
    int heightGameboard;
    std::vector<Shape*> arrayShape;
    int sumTarget;
public:
    Gameboard();
    void setMaxtrixWidthHeight(int width, int height);
    virtual ~Gameboard();
    Vec2 convertPosGameboard(const Vec2& pos);
    Vec2 getPosstonScene(const Vec2& pos);
    void createStartGameBoard(std::vector<PointGame*> arrayPoint);
    
    void getArrayShapeChange(const Vec2& posMaxtrixTouch);
    
    void checkColum( Shape* shape, std::vector<Shape*> &array);
    void checkRow(Shape* shape, std::vector<Shape*> &array);
    
    void checkSumOfColumAndRow(Shape* shape,std::vector<Shape*> &array);
    
    Shape* getShapeWithPosition(const Vec2& pos);
    
    void  rotationAndChangeValue(std::vector<Shape*> &array);
    
    bool checkWinArray();
};


#endif /* GameBoard_h */
