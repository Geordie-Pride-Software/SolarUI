#ifndef SOLARUI_IMAGE_H
#define SOLARUI_IMAGE_H

#include "../../../include/SUI/SolarUI_com.h"
#include "../../../include/SUI/SolarUI_exp.h"

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

SOLARUI_API void solImage_Init(
    solImage* image,
    const char* filePath,
    float x,
    float y,
    float width,
    float height
);


SOLARUI_API void solImage_Draw(
    solImage* image
);


SOLARUI_API void solImage_Load(
    solImage* image
);


SOLARUI_API void solImage_Unload(
    solImage* image
);


SOLARUI_API void solImage_SetTexture(
    solImage* image,
    unsigned int textureID
);


SOLARUI_API unsigned int solImage_GetTexture(
    solImage* image
);


SOLARUI_API void solImage_SetStyle(
    solImage* image,
    solImageStyle style
);


#ifdef __cplusplus
}
#endif

#endif