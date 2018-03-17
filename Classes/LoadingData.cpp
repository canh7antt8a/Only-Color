//
//  LoadingData.cpp
//  SmartRoad
//
//  Created by Harry Nguyen on 7/31/16.
//
//

#include "LoadingData.h"


LoadingData::LoadingData()
{
    if(!arrayPointGame.empty())
    {
        arrayPointGame.clear();
    }
    
}
LoadingData::~LoadingData()
{
    
}
std::vector<PointGame*> LoadingData::getArrayPoint()
{
    return arrayPointGame;
}
void LoadingData::loadingWithFileName(const char* fileName)
{

    XMLDocument* doc = new XMLDocument();
  
     std::string data = FileUtils::getInstance()->getStringFromFile(fileName);
     XMLError errorID = doc->Parse(data.c_str());
    if (errorID != 0) {
        CCLOG("Parse Error!");
        return;
    }
    
    XMLElement* root = doc->RootElement();
    for (XMLElement* elemetdata = root->FirstChildElement(); elemetdata; elemetdata = elemetdata->NextSiblingElement()) {
        XMLElement* child = elemetdata->FirstChildElement( "x" );
        if ( child )
        {
            int x = atoi(child->GetText());
            XMLElement* child2 = child->NextSiblingElement();
            if(child2) {
                int y = atoi(child2->GetText());
                XMLElement* child3 = child2->NextSiblingElement();
                if (child3)
                {
                    int z = atoi(child3->GetText());
                    PointGame* point = new PointGame(x,y,z);
                    arrayPointGame.push_back(point);
                }
            }
        }
    }
    delete doc;
}