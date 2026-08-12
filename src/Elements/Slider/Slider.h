#ifndef SOLARUI_SLIDER_H
#define SOLARUI_SLIDER_H

#include "../../../include/SUI/SolarUI_com.h"
#include "../../../include/SUI/SolarUI_exp.h"

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

SOLARUI_API void solSlider_Init(
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


SOLARUI_API void solSlider_Draw(
    solSlider* slider
);


SOLARUI_API void solSlider_Update(
    solSlider* slider,
    float mouseX,
    float mouseY,
    bool mouseDown
);


SOLARUI_API bool solSlider_Contains(
    solSlider* slider,
    float x,
    float y
);


SOLARUI_API void solSlider_SetValue(
    solSlider* slider,
    float value
);


SOLARUI_API float solSlider_GetValue(
    solSlider* slider
);


SOLARUI_API void solSlider_SetCallback(
    solSlider* slider,
    solFloatCallback callback
);


SOLARUI_API void solSlider_SetStyle(
    solSlider* slider,
    solSliderStyle style
);


#ifdef __cplusplus
}
#endif

#endif