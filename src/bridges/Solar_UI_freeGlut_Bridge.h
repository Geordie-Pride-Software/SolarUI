#ifndef SOLAR_UI_FREEGLUT_BRIDGE_H
#define SOLAR_UI_FREEGLUT_BRIDGE_H


#include "../../include/SolarUI_com.h"


#ifdef __cplusplus
extern "C" {
#endif



// **********************************************
// *              INITIALISATION                *
// **********************************************

void solFreeGLUT_Render_Init(void);



// **********************************************
// *              FRAME CONTROL                 *
// **********************************************

void solFreeGLUT_BeginFrame(void);

void solFreeGLUT_EndFrame(void);



// **********************************************
// *              BASIC DRAWING                 *
// **********************************************

void solFreeGLUT_DrawRectangle(
    float x,
    float y,
    float width,
    float height,
    solColour colour
);



void solFreeGLUT_DrawBorder(
    float x,
    float y,
    float width,
    float height,
    solColour colour
);



void solFreeGLUT_DrawText(
    float x,
    float y,
    const char* text,
    solColour colour
);



// **********************************************
// *              TEXTURES                      *
// **********************************************

void solFreeGLUT_DrawTexture(
    unsigned int textureID,
    float x,
    float y,
    float width,
    float height
);



#ifdef __cplusplus
}
#endif


#endif