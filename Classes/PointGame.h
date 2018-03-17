//
//  PointGame.h
//  SmartRoad
//
//  Created by Harry Nguyen on 7/31/16.
//
//

#ifndef PointGame_h
#define PointGame_h

#include <stdio.h>

class PointGame {
public:
    int x;
    int y;
    int value;
public:
    PointGame(int x, int y , int z);
    virtual ~PointGame();
};

#endif /* PointGame_h */
