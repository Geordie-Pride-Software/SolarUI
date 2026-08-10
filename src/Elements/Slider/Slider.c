#include "Slider.h"

#include "../../internal/Solar_UI_Render.h"


static solSliderStyle DefaultSliderStyle()
{
    solSliderStyle style;


    style.Track = (solColour)
    {
        0.25f,
        0.25f,
        0.25f,
        1.0f
    };


    style.Fill = (solColour)
    {
        0.2f,
        0.6f,
        1.0f,
        1.0f
    };


    style.Thumb = (solColour)
    {
        1.0f,
        1.0f,
        1.0f,
        1.0f
    };


    style.Text = (solColour)
    {
        1.0f,
        1.0f,
        1.0f,
        1.0f
    };


    return style;
}



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
)
{
    if (!slider)
        return;


    slider->Element.Bounds.Position.X = x;
    slider->Element.Bounds.Position.Y = y;

    slider->Element.Bounds.Size.Width = width;
    slider->Element.Bounds.Size.Height = height;


    slider->Element.Type = SOL_ELEMENT_SLIDER;

    slider->Element.Layer = 0;
    slider->Element.Visibility = SOL_VISIBLE;
    slider->Element.State = SOL_ENABLED;


    slider->Label = label;


    slider->MinValue = minValue;
    slider->MaxValue = maxValue;

    slider->CurrentValue = startValue;


    slider->Dragging = false;


    slider->Style = DefaultSliderStyle();


    slider->OnValueChanged = 0;
}



void solSlider_Draw(
    solSlider* slider
)
{
    if (!slider)
        return;


    if (slider->Element.Visibility != SOL_VISIBLE)
        return;


    solRender_DrawSlider(slider);
}



bool solSlider_Contains(
    solSlider* slider,
    float x,
    float y
)
{
    if (!slider)
        return false;


    return
    (
        x >= slider->Element.Bounds.Position.X &&
        x <= slider->Element.Bounds.Position.X +
             slider->Element.Bounds.Size.Width &&

        y >= slider->Element.Bounds.Position.Y &&
        y <= slider->Element.Bounds.Position.Y +
             slider->Element.Bounds.Size.Height
    );
}



void solSlider_Update(
    solSlider* slider,
    float mouseX,
    float mouseY,
    bool mouseDown
)
{
    if (!slider)
        return;


    if (mouseDown)
    {
        if (solSlider_Contains(slider, mouseX, mouseY))
        {
            slider->Dragging = true;
        }
    }
    else
    {
        slider->Dragging = false;
    }


    if (slider->Dragging)
    {
        float percentage;


        percentage =
            (mouseX - slider->Element.Bounds.Position.X)
            /
            slider->Element.Bounds.Size.Width;


        if (percentage < 0.0f)
            percentage = 0.0f;


        if (percentage > 1.0f)
            percentage = 1.0f;


        float newValue =
            slider->MinValue +
            (
                percentage *
                (
                    slider->MaxValue -
                    slider->MinValue
                )
            );


        solSlider_SetValue(
            slider,
            newValue
        );
    }
}



void solSlider_SetValue(
    solSlider* slider,
    float value
)
{
    if (!slider)
        return;


    if (value < slider->MinValue)
        value = slider->MinValue;


    if (value > slider->MaxValue)
        value = slider->MaxValue;


    if (slider->CurrentValue != value)
    {
        slider->CurrentValue = value;


        if (slider->OnValueChanged)
            slider->OnValueChanged(value);
    }
}



float solSlider_GetValue(
    solSlider* slider
)
{
    if (!slider)
        return 0.0f;


    return slider->CurrentValue;
}



void solSlider_SetCallback(
    solSlider* slider,
    solFloatCallback callback
)
{
    if (!slider)
        return;


    slider->OnValueChanged = callback;
}



void solSlider_SetStyle(
    solSlider* slider,
    solSliderStyle style
)
{
    if (!slider)
        return;


    slider->Style = style;
}