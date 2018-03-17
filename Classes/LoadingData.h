//
//  LoadingData.h
//  SmartRoad
//
//  Created by Harry Nguyen on 7/31/16.
//
//

#ifndef LoadingData_h
#define LoadingData_h

#include <stdio.h>
#include "tinyxml2/tinyxml2.h"
#include "cocos2d.h"
#include "PointGame.h"
using namespace tinyxml2;
USING_NS_CC;

class LoadingData {
public:
    std::vector<PointGame*> arrayPointGame;
    LoadingData();
    virtual ~LoadingData();
    void loadingWithFileName(const char* fileName);
    std::vector<PointGame*> getArrayPoint();
    
};

#endif /* LoadingData_h */
