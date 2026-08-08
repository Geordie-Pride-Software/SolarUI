#ifndef SOLARUI_H
#define SOLARUI_H


#include "SolarUI_exp.h"
#include "SolarUI_com.h"


#ifdef __cplusplus
extern "C" {
#endif



// **********************************************
// *              VERSION INFORMATION            *
// **********************************************

#define SOLARUI_VERSION_MAJOR 1
#define SOLARUI_VERSION_MINOR 0
#define SOLARUI_VERSION_PATCH 0



// **********************************************
// *              CORE LIFECYCLE                 *
// **********************************************


SOLARUI_API int solUI_Init(void);


SOLARUI_API void solUI_Shutdown(void);



SOLARUI_API void solUI_Update(void);


SOLARUI_API void solUI_Draw(void);



// **********************************************
// *              ELEMENT MANAGEMENT             *
// **********************************************


SOLARUI_API bool solUI_AddElement(
    solElement* element
);



SOLARUI_API bool solUI_RemoveElement(
    solElement* element
);



// **********************************************
// *              LAYER / INPUT CONTROL          *
// **********************************************


SOLARUI_API void solUI_CaptureInput(
    solElement* element
);



SOLARUI_API void solUI_ReleaseInput(void);



SOLARUI_API void solUI_SetElementLayer(
    solElement* element,
    int layer
);



SOLARUI_API int solUI_GetElementLayer(
    solElement* element
);



// **********************************************
// *              VIEWPORT                      *
// **********************************************


SOLARUI_API void solUI_SetLogicalSize(
    float width,
    float height
);



SOLARUI_API void solUI_UpdateViewport(
    int width,
    int height
);



SOLARUI_API void solUI_ScreenToLogical(
    int screenX,
    int screenY,
    float* logicalX,
    float* logicalY
);



// **********************************************
// *              FONT SYSTEM                   *
// **********************************************


SOLARUI_API void solUI_SetFont(
    solFont font
);



#ifdef __cplusplus
}
#endif


#endif