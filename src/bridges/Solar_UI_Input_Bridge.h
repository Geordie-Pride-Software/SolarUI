#ifndef SOLAR_UI_INPUT_BRIDGE_H
#define SOLAR_UI_INPUT_BRIDGE_H


#include "../../include/SolarUI_com.h"
#include "../../include/SolarUI_exp.h"


#ifdef __cplusplus
extern "C" {
#endif



// **********************************************
// *              INITIALISATION                *
// **********************************************

SOLARUI_API void solInputBridge_Init(void);



// **********************************************
// *              MOUSE                         *
// **********************************************

SOLARUI_API void solInputBridge_MouseMove(
    int x,
    int y
);



SOLARUI_API void solInputBridge_MouseButton(
    int button,
    int state,
    int x,
    int y
);



// **********************************************
// *              KEYBOARD                      *
// **********************************************

SOLARUI_API void solInputBridge_KeyDown(
    unsigned char key,
    int x,
    int y
);



SOLARUI_API void solInputBridge_KeyUp(
    unsigned char key,
    int x,
    int y
);



SOLARUI_API void solInputBridge_SpecialKey(
    int key,
    int x,
    int y
);


SOLARUI_API void solInputBridge_SpecialKeyUp(
    int key,
    int x,
    int y
);



#ifdef __cplusplus
}
#endif


#endif