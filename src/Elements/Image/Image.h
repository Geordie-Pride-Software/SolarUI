#ifndef SOLARUI_IMAGE_H
#define SOLARUI_IMAGE_H

#include "../../../include/SolarUI_com.h"

#ifdef __cplusplus
extern "C" {
#endif


// **********************************************
// *              IMAGE STYLE                   *
// **********************************************

typedef struct
{
    solColour Tint;

    float Opacity;

} solImageStyle;


// **********************************************
// *              IMAGE STRUCT                  *
// **********************************************

typedef struct
{
    solElement Element;

    const char* FilePath;

    void* MediaHandle;

    unsigned int TextureID;

    bool Loaded;

    solImageStyle Style;

} solImage;


// **********************************************
// *              FUNCTIONS                     *
// **********************************************

void solImage_Init(
    solImage* image,
    const char* filePath,
    float x,
    float y,
    float width,
    float height
);


void solImage_Draw(
    solImage* image
);


void solImage_Load(
    solImage* image
);


void solImage_Unload(
    solImage* image
);


void solImage_SetTexture(
    solImage* image,
    unsigned int textureID
);


unsigned int solImage_GetTexture(
    solImage* image
);


void solImage_SetStyle(
    solImage* image,
    solImageStyle style
);


#ifdef __cplusplus
}
#endif

#endif