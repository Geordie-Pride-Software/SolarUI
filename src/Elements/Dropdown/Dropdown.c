#include "Dropdown.h"

#include "../../internal/Solar_UI_Render.h"
#include "../../internal/Solar_UI_Manager.h"



static solDropdownStyle DefaultDropdownStyle()
{
    solDropdownStyle style;


    style.Background = (solColour)
    {
        0.2f,
        0.2f,
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



void solDropdown_Init(
    solDropdown* dropdown,
    const char* label,
    const char** options,
    int optionCount,
    float x,
    float y,
    float width,
    float height
)
{
    if (!dropdown)
        return;


    dropdown->Element.Bounds.Position.X = x;
    dropdown->Element.Bounds.Position.Y = y;


    dropdown->Element.Bounds.Size.Width = width;
    dropdown->Element.Bounds.Size.Height = height;


    dropdown->Element.Layer = 0;


    dropdown->Element.Visibility = SOL_VISIBLE;
    dropdown->Element.State = SOL_ENABLED;


    dropdown->Label = label;


    dropdown->Options = options;

    dropdown->OptionCount = optionCount;


    dropdown->SelectedIndex = 0;


    dropdown->Open = false;


    dropdown->HoverIndex = -1;


    dropdown->PopupLayer = 10000;


    dropdown->Style = DefaultDropdownStyle();


    dropdown->OnSelectionChanged = 0;
}



void solDropdown_Draw(
    solDropdown* dropdown
)
{
    if (!dropdown)
        return;


    if (dropdown->Element.Visibility != SOL_VISIBLE)
        return;


    solRender_DrawDropdown(dropdown);
}



bool solDropdown_Contains(
    solDropdown* dropdown,
    float x,
    float y
)
{
    if (!dropdown)
        return false;


    float height =
        dropdown->Element.Bounds.Size.Height;


    if (dropdown->Open)
    {
        height *= dropdown->OptionCount + 1;
    }


    return
    (
        x >= dropdown->Element.Bounds.Position.X &&
        x <= dropdown->Element.Bounds.Position.X +
             dropdown->Element.Bounds.Size.Width &&

        y >= dropdown->Element.Bounds.Position.Y &&
        y <= dropdown->Element.Bounds.Position.Y +
             height
    );
}



void solDropdown_Open(
    solDropdown* dropdown
)
{
    if (!dropdown)
        return;


    dropdown->Open = true;


    /*
        This is important:
        the dropdown becomes an overlay.
    */

    dropdown->Element.Layer =
        dropdown->PopupLayer;


    solUI_Manager_BlockInputBelow(
        (solElement*)dropdown
    );
}



void solDropdown_Close(
    solDropdown* dropdown
)
{
    if (!dropdown)
        return;


    dropdown->Open = false;


    dropdown->Element.Layer = 0;


    solUI_Manager_UnblockInput();
}



void solDropdown_Update(
    solDropdown* dropdown,
    float mouseX,
    float mouseY,
    bool mousePressed
)
{
    if (!dropdown)
        return;


    if (!mousePressed)
        return;


    if (!dropdown->Open)
    {
        if (solDropdown_Contains(
            dropdown,
            mouseX,
            mouseY))
        {
            solDropdown_Open(dropdown);
        }

        return;
    }



    int index =
        (
            mouseY -
            dropdown->Element.Bounds.Position.Y
        )
        /
        dropdown->Element.Bounds.Size.Height;



    if(index > 0 &&
       index <= dropdown->OptionCount)
    {
        dropdown->SelectedIndex =
            index - 1;


        if(dropdown->OnSelectionChanged)
        {
            dropdown->OnSelectionChanged(
                dropdown->SelectedIndex
            );
        }


        solDropdown_Close(dropdown);
    }
}



int solDropdown_GetIndex(
    solDropdown* dropdown
)
{
    if (!dropdown)
        return -1;


    return dropdown->SelectedIndex;
}



const char* solDropdown_GetValue(
    solDropdown* dropdown
)
{
    if (!dropdown)
        return 0;


    return dropdown->Options[
        dropdown->SelectedIndex
    ];
}



void solDropdown_SetCallback(
    solDropdown* dropdown,
    solIntCallback callback
)
{
    if (!dropdown)
        return;


    dropdown->OnSelectionChanged = callback;
}



void solDropdown_SetStyle(
    solDropdown* dropdown,
    solDropdownStyle style
)
{
    if (!dropdown)
        return;


    dropdown->Style = style;
}