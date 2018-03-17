//
//  GameBoard.cpp
//  OnlyColor
//
//  Created by Harry Nguyen on 8/10/16.
//
//

#include "GameBoard.h"
#include "Shape.h"
#include "DefineGame.h"
#include "SimpleAudioEngine.h"




Gameboard::Gameboard()
{
    if (!arrayShape.empty())
    {
        arrayShape.clear();
    }
}
void Gameboard::setMaxtrixWidthHeight(int width, int height)
{
    this->widthGameboard = width;
    this->heightGameboard = height;
}
Gameboard::~Gameboard()
{
    
}
Vec2 Gameboard::convertPosGameboard(const Vec2& pos)
{
    Vec2 vec2Result;
    Vec2 posConvert = Vec2(this->convertToWorldSpace(this->getPosition()).x + SHAPE_WIDTH /2,  this->convertToWorldSpace(this->getPosition()).y + SHAPE_HEIGHT/2);
    if(pos.x < posConvert.x || pos.y < posConvert.y || pos.x > posConvert.x + (widthGameboard) *SHAPE_WIDTH || pos.y > posConvert.y + (heightGameboard)* SHAPE_HEIGHT)
    {
        vec2Result = Vec2(-1, -1);
    }
    else
    {
        int realWidth = pos.x - posConvert.x;
        int realHeight = pos.y - posConvert.y;
        int cellPosX = realWidth/(SHAPE_WIDTH + 4.0f);
        int cellPosY = realHeight/(SHAPE_HEIGHT + 4.0f);
        vec2Result =  Vec2(cellPosX, cellPosY);
    }
    CCLOG("cell x %f, %f",vec2Result.x, vec2Result.y);
    return vec2Result;
    
}
Vec2 Gameboard::getPosstonScene(const Vec2& pos)
{
    if(pos.x < 0 || pos.y < 0 || pos.x > widthGameboard-1 || pos.y > heightGameboard-1)
    {
        return Vec2(-1,-1);
    }
    else
    {
        float pointX = pos.x * (SHAPE_WIDTH/2 + 2.0f) + this->getPositionX() + SHAPE_WIDTH/2;
        float pointY = pos.y * (SHAPE_HEIGHT/2 + 2.0f)+ this->getPositionY() + SHAPE_HEIGHT/2;
        return Vec2(pointX,pointY);
    }
}
void Gameboard::createStartGameBoard(std::vector<PointGame*> arrayPoint)
{
    sumTarget  = (int)arrayPoint.size();
    for (int i = 0 ; i < heightGameboard; i ++)
    {
        for (int j = 0; j < widthGameboard; j++) {
            Shape* shape = new Shape();
            shape->setPosition(this->getPosstonScene(Vec2(j, i)));
            shape->setValue(SHAPE_NOMARL);
            shape->createUIWithValue(0);
            shape->setPosmaxtrix(Vec2(j, i));
            this->addChild(shape);
            arrayShape.push_back(shape);
        }
    }
    
    for (int k = 0; k < arrayPoint.size(); k ++)
    {
        int index = arrayPoint.at(k)->x + arrayPoint.at(k)->y* widthGameboard;
        int valueOfIndex = arrayPoint.at(k)->value;
        
        arrayShape.at(index)->updateUIWithValue(valueOfIndex);
        arrayShape.at(index)->setValue(valueOfIndex);
    }
    
    CCLOG("sub target %d", sumTarget);
}
void Gameboard::getArrayShapeChange(const Vec2& posMaxtrixTouch)
{
    
}

/*check Shape at row*/
void Gameboard::checkRow(Shape* shape, std::vector<Shape*> &array)
{
    if(shape != NULL && shape->getValue() != SHAPE_NOMARL)
    {
        array.push_back(shape);
        int indexNeighbour = shape->getPosmaxtrix().x + 1;
        while (indexNeighbour < widthGameboard) {
            Shape* shapeNeighbour = arrayShape.at(indexNeighbour + shape->getPosmaxtrix().y * widthGameboard);
            if(shapeNeighbour != NULL)
            {
                if(shapeNeighbour->getValue() !=  SHAPE_NOMARL){
                    array.push_back(shapeNeighbour);
                    indexNeighbour ++;
                }else{
                    break;
                }
            }
        }
        indexNeighbour = shape->getPosmaxtrix().x - 1;
        while (indexNeighbour >= 0) {
            Shape* shapeNeighbour = arrayShape.at(indexNeighbour + shape->getPosmaxtrix().y * widthGameboard);
            
            if(shapeNeighbour != NULL)
            {
                if(shapeNeighbour->getValue() != SHAPE_NOMARL){
                    array.push_back(shapeNeighbour);
                    indexNeighbour --;
                }else{
                    break;
                }
            }
        }
    }
}
/*check Shape at Column*/
void Gameboard::checkColum( Shape* shape, std::vector<Shape*> &array)
{
    if(shape != NULL && shape->getValue() != SHAPE_NOMARL)
    {
        array.push_back(shape);
        int indexNeighbour = shape->getPosmaxtrix().y + 1;
        while (indexNeighbour < heightGameboard) {
            Shape* shapeNeighbour = arrayShape.at(shape->getPosmaxtrix().x + indexNeighbour* widthGameboard);
            if(shapeNeighbour != NULL)
            {
                if(shapeNeighbour->getValue() != SHAPE_NOMARL){
                    array.push_back(shapeNeighbour);
                    indexNeighbour ++;
                }else{
                    break;
                }
            }
        }
        indexNeighbour = shape->getPosmaxtrix().y - 1;
        while (indexNeighbour >= 0) {
            Shape* shapeNeighbour = arrayShape.at(shape->getPosmaxtrix().x + indexNeighbour* widthGameboard);
            if(shapeNeighbour != NULL)
            {
                if(shapeNeighbour->getValue() != SHAPE_NOMARL){
                    array.push_back(shapeNeighbour);
                    indexNeighbour --;
                }else{
                    break;
                }
            }
        }
        
    }
}

/*check Shape at colum and row (sum of colum and row)*/

void Gameboard::checkSumOfColumAndRow(Shape* shape, std::vector<Shape*> &array)
{
    std::vector<Shape*> arrayShapeRow;
    checkRow(shape,arrayShapeRow);
    std::vector<Shape*> arrayShapeColumn;
    checkColum(shape, arrayShapeColumn);
    
    
    for (int i = 0 ; i < arrayShapeRow.size(); i++) {
        array.push_back(arrayShapeRow.at(i));
    }
    
    for (int j = 1 ; j < arrayShapeColumn.size(); j++) {
        array.push_back(arrayShapeColumn.at(j));
    }
    
}

/*Get shape of position*/

Shape* Gameboard::getShapeWithPosition(const Vec2& pos)
{
    Shape* shape = new Shape();
    shape= arrayShape.at(pos.x + pos.y*widthGameboard);
    return shape;
}

/*Rotation and change*/

void  Gameboard::rotationAndChangeValue(std::vector<Shape*> &array)
{
    if(array.size() > 0)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("buttonLevel.mp3");
    }
    for (int j = 0 ; j < array.size(); j++) {
        int index = array.at(j)->getPosmaxtrix().x + array.at(j)->getPosmaxtrix().y* widthGameboard;
        int value = array.at(j)->getValue();
        if (value == SHAPE_TYPE_ONE)
        {
            arrayShape.at(index)->setValue(SHAPE_TYPE_TWO);
            arrayShape.at(index)->updateUIWithValue(SHAPE_TYPE_TWO);
            array.at(j)->setValue(SHAPE_TYPE_TWO);
        }
        if (value == SHAPE_TYPE_TWO)
        {
            arrayShape.at(index)->setValue(SHAPE_TYPE_ONE);
            arrayShape.at(index)->updateUIWithValue(SHAPE_TYPE_ONE);
            array.at(j)->setValue(SHAPE_TYPE_ONE);
        }
        arrayShape.at(index)->runActionShape();
    }
}
bool Gameboard::checkWinArray()
{
    int item1  = 0 ;
    int item2 = 0;
    for (int i = 0 ; i < arrayShape.size(); i++) {
        if(arrayShape.at(i)->getValue() != SHAPE_NOMARL)
        {
            if(arrayShape.at(i)->getValue() == SHAPE_TYPE_ONE)
            {
                item1 += 1;
            }
            else
            {
                item2 += 1;
            }
        }
    }
    if(item1 == sumTarget || item2 == sumTarget)
    {
        return true;
    }
    return  false;
}
