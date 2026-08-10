#include "Checkbox.h"

#include "../../internal/Solar_UI_Render.h"


static solCheckboxStyle DefaultCheckboxStyle()
{
    solCheckboxStyle style;


    style.Background = (solColour)
    {
        0.2f,
        0.2f,
        0.2f,
        1.0f
    };


    style.Checked = (solColour)
    {
        0.2f,
        0.8f,
        0.2f,
        1.0f
    };


    style.Hover = (solColour)
    {
        0.35f,
        0.35f,
        0.35f,
        1.0f
    };


    style.Border = (solColour)
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



void solCheckbox_Init(
    solCheckbox* checkbox,
    const char* label,
    float x,
    float y,
    float width,
    float height
)
{
    if (!checkbox)
        return;


    checkbox->Element.Bounds.Position.X = x;
    checkbox->Element.Bounds.Position.Y = y;

    checkbox->Element.Bounds.Size.Width = width;
    checkbox->Element.Bounds.Size.Height = height;


    checkbox->Element.Type = SOL_ELEMENT_CHECKBOX;

    checkbox->Element.Layer = 0;
    checkbox->Element.Visibility = SOL_VISIBLE;
    checkbox->Element.State = SOL_ENABLED;


    checkbox->Label = label;


    checkbox->Style = DefaultCheckboxStyle();


    checkbox->Checked = false;

    checkbox->Hovered = false;


    checkbox->OnCheckedChanged = 0;
}



void solCheckbox_Draw(
    solCheckbox* checkbox
)
{
    if (!checkbox)
        return;


    if (checkbox->Element.Visibility != SOL_VISIBLE)
        return;


    solRender_DrawCheckbox(checkbox);
}



bool solCheckbox_Contains(
    solCheckbox* checkbox,
    float x,
    float y
)
{
    if (!checkbox)
        return false;


    return
    (
        x >= checkbox->Element.Bounds.Position.X &&
        x <= checkbox->Element.Bounds.Position.X +
             checkbox->Element.Bounds.Size.Width &&

        y >= checkbox->Element.Bounds.Position.Y &&
        y <= checkbox->Element.Bounds.Position.Y +
             checkbox->Element.Bounds.Size.Height
    );
}



void solCheckbox_Update(
    solCheckbox* checkbox,
    float mouseX,
    float mouseY,
    bool mousePressed
)
{
    if (!checkbox)
        return;


    checkbox->Hovered =
        solCheckbox_Contains(
            checkbox,
            mouseX,
            mouseY
        );


    if (checkbox->Hovered && mousePressed)
    {
        solCheckbox_SetChecked(
            checkbox,
            !checkbox->Checked
        );
    }
}



void solCheckbox_SetChecked(
    solCheckbox* checkbox,
    bool state
)
{
    if (!checkbox)
        return;


    if (checkbox->Checked != state)
    {
        checkbox->Checked = state;


        if (checkbox->OnCheckedChanged)
        {
            checkbox->OnCheckedChanged(state);
        }
    }
}



bool solCheckbox_IsChecked(
    solCheckbox* checkbox
)
{
    if (!checkbox)
        return false;


    return checkbox->Checked;
}



void solCheckbox_SetCallback(
    solCheckbox* checkbox,
    solBoolCallback callback
)
{
    if (!checkbox)
        return;


    checkbox->OnCheckedChanged = callback;
}



void solCheckbox_SetStyle(
    solCheckbox* checkbox,
    solCheckboxStyle style
)
{
    if (!checkbox)
        return;


    checkbox->Style = style;
}