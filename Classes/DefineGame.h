
//
//  DefineGame.h
//  OnlyColor
//
//  Created by Harry Nguyen on 8/10/16.
//
//

#ifndef DefineGame_h
#define DefineGame_h

#define SHAPE_WIDTH 64
#define SHAPE_HEIGHT 64

#define TAG_BTN_SOUND_ON 122
#define TAG_BTN_SOUND_OFF 123

#define TAG_BTN_MENU 124
#define TAG_BTN_REPLAY 125
#define TAG_BTN_ARCHIMENT 126
#define WIDTH_MATRIX 12
#define HEIGHT_MATRIX 8

enum{
    SHAPE_NOMARL = 0,
    SHAPE_TYPE_ONE = 1,
    SHAPE_TYPE_TWO = 2,
};

enum STATUS_LOADING {
    IDLE_PROGRESS = 1,
    PAUSE_PROGRESS = 2,
    ADDTIME_PROGRESS = 3,
    DELETIME_PROGRESS = 4,
    END_GAME = 5
};

#endif /* DefineGame_h */
