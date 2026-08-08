#ifndef SOLAR_UI_MANAGER_H
#define SOLAR_UI_MANAGER_H

#include "../../include/SolarUI_com.h"

#ifdef __cplusplus
extern "C" {
#endif


// **********************************************
// *              INITIALISATION                *
// **********************************************

void solUI_Manager_Init(void);


// **********************************************
// *              ELEMENT MANAGEMENT             *
// **********************************************

void solUI_Manager_Add(
    solElement* element
);


void solUI_Manager_Remove(
    solElement* element
);


void solUI_Manager_Clear(void);


// **********************************************
// *              FRAME UPDATE                  *
// **********************************************

void solUI_Manager_Update(void);


void solUI_Manager_Draw(void);


// **********************************************
// *              LAYERING                      *
// **********************************************

void solUI_Manager_SetLayer(
    solElement* element,
    int layer
);


int solUI_Manager_GetLayer(
    solElement* element
);


// **********************************************
// *              INPUT                        *
// **********************************************

solElement* solUI_Manager_GetElementAt(
    float x,
    float y
);


void solUI_Manager_ProcessInput(void);


// **********************************************
// *              INPUT BLOCKING                *
// **********************************************
// Used by overlay-style elements (e.g. an open
// dropdown) to stop input reaching elements
// underneath. Backed by the Input module's
// existing capture mechanism.

void solUI_Manager_BlockInputBelow(
    solElement* element
);


void solUI_Manager_UnblockInput(void);



#ifdef __cplusplus
}
#endif

#endif