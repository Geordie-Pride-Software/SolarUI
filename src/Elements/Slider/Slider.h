#ifndef SOLARUI_SLIDER_H
#define SOLARUI_SLIDER_H

#include "../../../include/SolarUI_com.h"

#ifdef __cplusplus
extern "C" {
#endif


// **********************************************
// *              SLIDER STYLE                  *
// **********************************************

typedef struct
{
    solColour Track;
    solColour Fill;
    solColour Thumb;

    solColour Text;

} solSliderStyle;


// **********************************************
// *              SLIDER STRUCT                 *
// **********************************************

typedef struct
{
    solElement Element;

    const char* Label;

    solSliderStyle Style;

    float MinValue;
    float MaxValue;
    float CurrentValue;

    bool Dragging;

    solFloatCallback OnValueChanged;

} solSlider;


// **********************************************
// *              FUNCTIONS                     *
// **********************************************

void solSlider_Init(
    solSlider* slider,
    const char* label,
    float x,
    float y,
    float width,
    float height,
    float minValue,
    float maxValue,
    float startValue
);


void solSlider_Draw(
    solSlider* slider
);


void solSlider_Update(
    solSlider* slider,
    float mouseX,
    float mouseY,
    bool mouseDown
);


bool solSlider_Contains(
    solSlider* slider,
    float x,
    float y
);


void solSlider_SetValue(
    solSlider* slider,
    float value
);


float solSlider_GetValue(
    solSlider* slider
);


void solSlider_SetCallback(
    solSlider* slider,
    solFloatCallback callback
);


void solSlider_SetStyle(
    solSlider* slider,
    solSliderStyle style
);


#ifdef __cplusplus
}
#endif

#endif