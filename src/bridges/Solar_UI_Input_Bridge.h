#ifndef SOLAR_UI_INPUT_BRIDGE_H
#define SOLAR_UI_INPUT_BRIDGE_H


#include "../../include/SolarUI_com.h"


#ifdef __cplusplus
extern "C" {
#endif



// **********************************************
// *              INITIALISATION                *
// **********************************************

void solInputBridge_Init(void);



// **********************************************
// *              MOUSE                         *
// **********************************************

void solInputBridge_MouseMove(
    int x,
    int y
);



void solInputBridge_MouseButton(
    int button,
    int state,
    int x,
    int y
);



// **********************************************
// *              KEYBOARD                      *
// **********************************************

void solInputBridge_KeyDown(
    unsigned char key,
    int x,
    int y
);



void solInputBridge_KeyUp(
    unsigned char key,
    int x,
    int y
);



void solInputBridge_SpecialKey(
    int key,
    int x,
    int y
);


void solInputBridge_SpecialKeyUp(
    int key,
    int x,
    int y
);



#ifdef __cplusplus
}
#endif


#endif