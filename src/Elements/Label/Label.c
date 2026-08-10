#include "Label.h"

/* The renderer is responsible for actually drawing text */
#include "../../internal/Solar_UI_Render.h"

void solLabel_Init(
    solLabel* label,
    const char* text,
    float x,
    float y
)
{
    if (!label)
        return;

    label->Element.Bounds.Position.X = x;
    label->Element.Bounds.Position.Y = y;

    label->Element.Bounds.Size.Width = 0.0f;
    label->Element.Bounds.Size.Height = 0.0f;

    label->Element.Visibility = SOL_VISIBLE;
    label->Element.State = SOL_ENABLED;
    label->Element.Type = SOL_ELEMENT_LABEL;

    label->Element.Layer = 0;

    label->Text = text;

    label->Style.Text = (solColour)
    {
        1.0f,
        1.0f,
        1.0f,
        1.0f
    };

    label->Font.Handle = 0;
}

void solLabel_Draw(
    solLabel* label
)
{
    if (!label)
        return;

    if (label->Element.Visibility != SOL_VISIBLE)
        return;

    solRender_DrawLabel(label);
}

void solLabel_SetText(
    solLabel* label,
    const char* text
)
{
    if (!label)
        return;

    label->Text = text;
}

const char* solLabel_GetText(
    const solLabel* label
)
{
    if (!label)
        return 0;

    return label->Text;
}

void solLabel_SetPosition(
    solLabel* label,
    float x,
    float y
)
{
    if (!label)
        return;

    label->Element.Bounds.Position.X = x;
    label->Element.Bounds.Position.Y = y;
}

void solLabel_SetColour(
    solLabel* label,
    solColour colour
)
{
    if (!label)
        return;

    label->Style.Text = colour;
}

void solLabel_SetFont(
    solLabel* label,
    solFont font
)
{
    if (!label)
        return;

    label->Font = font;
}