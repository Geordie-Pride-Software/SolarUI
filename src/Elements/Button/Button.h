#ifndef SOLARUI_BUTTON_H
#define SOLARUI_BUTTON_H

#include "../../../include/SolarUI_com.h"

#ifdef __cplusplus
extern "C" {
#endif


// **********************************************
// *              BUTTON STYLE                  *
// **********************************************

typedef struct
{
    solColour Background;
    solColour Hover;
    solColour Pressed;

    solColour Border;
    solColour Text;

} solButtonStyle;


// **********************************************
// *              BUTTON STATE                  *
// **********************************************

typedef enum
{
    SOL_BUTTON_NORMAL = 0,
    SOL_BUTTON_HOVERED,
    SOL_BUTTON_PRESSED

} solButtonState;


// **********************************************
// *              BUTTON STRUCT                 *
// **********************************************

typedef struct
{
    solElement Element;

    const char* Label;

    solButtonStyle Style;

    solButtonState State;

    solVoidCallback OnClick;

} solButton;


// **********************************************
// *              FUNCTIONS                     *
// **********************************************

void solButton_Init(
    solButton* button,
    const char* text,
    float x,
    float y,
    float width,
    float height
);


void solButton_Draw(
    solButton* button
);


void solButton_Update(
    solButton* button,
    float mouseX,
    float mouseY,
    bool mouseDown
);


bool solButton_Contains(
    solButton* button,
    float x,
    float y
);


void solButton_Click(
    solButton* button
);


void solButton_SetText(
    solButton* button,
    const char* text
);


void solButton_SetStyle(
    solButton* button,
    solButtonStyle style
);


void solButton_SetCallback(
    solButton* button,
    solVoidCallback callback
);


#ifdef __cplusplus
}
#endif

#endif