#include "Button.h"

#include "../../internal/Solar_UI_Render.h"


static solButtonStyle DefaultButtonStyle()
{
    solButtonStyle style;

    style.Background = (solColour)
    {
        0.25f,
        0.25f,
        0.25f,
        1.0f
    };

    style.Hover = (solColour)
    {
        0.35f,
        0.35f,
        0.35f,
        1.0f
    };

    style.Pressed = (solColour)
    {
        0.15f,
        0.15f,
        0.15f,
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


void solButton_Init(
    solButton* button,
    const char* text,
    float x,
    float y,
    float width,
    float height
)
{
    if (!button)
        return;


    button->Element.Bounds.Position.X = x;
    button->Element.Bounds.Position.Y = y;

    button->Element.Bounds.Size.Width = width;
    button->Element.Bounds.Size.Height = height;


    button->Element.Type = SOL_ELEMENT_BUTTON;

    button->Element.Layer = 0;
    button->Element.Visibility = SOL_VISIBLE;
    button->Element.State = SOL_ENABLED;


    button->Label = text;

    button->Style = DefaultButtonStyle();

    button->State = SOL_BUTTON_NORMAL;

    button->OnClick = 0;
}


void solButton_Draw(
    solButton* button
)
{
    if (!button)
        return;


    if (button->Element.Visibility != SOL_VISIBLE)
        return;


    solRender_DrawButton(button);
}


bool solButton_Contains(
    solButton* button,
    float x,
    float y
)
{
    if (!button)
        return false;


    return (
        x >= button->Element.Bounds.Position.X &&
        x <= button->Element.Bounds.Position.X +
             button->Element.Bounds.Size.Width &&

        y >= button->Element.Bounds.Position.Y &&
        y <= button->Element.Bounds.Position.Y +
             button->Element.Bounds.Size.Height
    );
}


void solButton_Update(
    solButton* button,
    float mouseX,
    float mouseY,
    bool mouseDown
)
{
    if (!button)
        return;


    bool wasPressed =
        (button->State == SOL_BUTTON_PRESSED);


    if (solButton_Contains(button, mouseX, mouseY))
    {
        if (mouseDown)
        {
            button->State = SOL_BUTTON_PRESSED;
        }
        else
        {
            /*
                Mouse released while still over
                the button, after having been
                pressed on it - that's a click.
                Moving off before releasing
                doesn't count (button->State
                would already be NORMAL by then).
            */

            if (wasPressed)
            {
                solButton_Click(
                    button
                );
            }


            button->State = SOL_BUTTON_HOVERED;
        }
    }
    else
    {
        button->State = SOL_BUTTON_NORMAL;
    }
}


void solButton_Click(
    solButton* button
)
{
    if (!button)
        return;


    if (button->OnClick)
        button->OnClick();
}


void solButton_SetText(
    solButton* button,
    const char* text
)
{
    if (!button)
        return;

    button->Label = text;
}


void solButton_SetStyle(
    solButton* button,
    solButtonStyle style
)
{
    if (!button)
        return;

    button->Style = style;
}


void solButton_SetCallback(
    solButton* button,
    solVoidCallback callback
)
{
    if (!button)
        return;

    button->OnClick = callback;
}