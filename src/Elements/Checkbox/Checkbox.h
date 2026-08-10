#ifndef SOLARUI_CHECKBOX_H
#define SOLARUI_CHECKBOX_H

#include "../../../include/SolarUI_com.h"
#include "../../../include/SolarUI_exp.h"

#ifdef __cplusplus
extern "C" {
#endif


// **********************************************
// *             CHECKBOX STYLE                 *
// **********************************************

typedef struct
{
    solColour Background;
    solColour Checked;

    solColour Hover;
    solColour Border;

    solColour Text;

} solCheckboxStyle;


// **********************************************
// *             CHECKBOX STRUCT                *
// **********************************************

typedef struct
{
    solElement Element;

    const char* Label;

    solCheckboxStyle Style;

    bool Checked;

    bool Hovered;

    solBoolCallback OnCheckedChanged;

} solCheckbox;


// **********************************************
// *              FUNCTIONS                     *
// **********************************************

SOLARUI_API void solCheckbox_Init(
    solCheckbox* checkbox,
    const char* label,
    float x,
    float y,
    float width,
    float height
);


SOLARUI_API void solCheckbox_Draw(
    solCheckbox* checkbox
);


SOLARUI_API void solCheckbox_Update(
    solCheckbox* checkbox,
    float mouseX,
    float mouseY,
    bool mousePressed
);


SOLARUI_API bool solCheckbox_Contains(
    solCheckbox* checkbox,
    float x,
    float y
);


SOLARUI_API void solCheckbox_SetChecked(
    solCheckbox* checkbox,
    bool state
);


SOLARUI_API bool solCheckbox_IsChecked(
    solCheckbox* checkbox
);


SOLARUI_API void solCheckbox_SetCallback(
    solCheckbox* checkbox,
    solBoolCallback callback
);


SOLARUI_API void solCheckbox_SetStyle(
    solCheckbox* checkbox,
    solCheckboxStyle style
);


#ifdef __cplusplus
}
#endif

#endif