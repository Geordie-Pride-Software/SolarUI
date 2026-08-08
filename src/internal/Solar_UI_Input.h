#ifndef SOLAR_UI_INPUT_H
#define SOLAR_UI_INPUT_H

#include "../../include/SolarUI_com.h"

#ifdef __cplusplus
extern "C" {
#endif


// **********************************************
// *              INITIALISATION                *
// **********************************************

void solInput_Init(void);


// **********************************************
// *              UPDATE                        *
// **********************************************

void solInput_Update(void);


// **********************************************
// *              MOUSE                         *
// **********************************************

void solInput_SetMousePosition(
    float x,
    float y
);


float solInput_GetMouseX(void);


float solInput_GetMouseY(void);



void solInput_SetMouseButton(
    solMouseButton button,
    bool pressed
);


bool solInput_IsMouseDown(void);


bool solInput_IsMousePressed(void);


bool solInput_IsMouseReleased(void);


// **********************************************
// *              KEYBOARD                      *
// **********************************************

void solInput_SetKey(
    int key,
    bool pressed
);


bool solInput_IsKeyDown(
    int key
);


void solInput_SetSpecialKey(
    int key,
    bool pressed
);


bool solInput_IsSpecialKeyDown(
    int key
);


// **********************************************
// *              FOCUS                         *
// **********************************************

void solInput_SetFocus(
    solElement* element
);


solElement* solInput_GetFocus(void);



void solInput_ClearFocus(void);


// **********************************************
// *              INPUT CAPTURE                 *
// **********************************************
// Used by things like Dropdown menus.
// When captured, elements underneath cannot
// receive input.

void solInput_Capture(
    solElement* element
);


void solInput_ReleaseCapture(void);


solElement* solInput_GetCapture(void);



#ifdef __cplusplus
}
#endif

#endif