#ifndef SOLARUI_DROPDOWN_H
#define SOLARUI_DROPDOWN_H

#include "../../../include/SolarUI_com.h"

#ifdef __cplusplus
extern "C" {
#endif


// **********************************************
// *            DROPDOWN STYLE                 *
// **********************************************

typedef struct
{
    solColour Background;
    solColour Hover;

    solColour Border;

    solColour Text;

} solDropdownStyle;


// **********************************************
// *            DROPDOWN STRUCT                 *
// **********************************************

typedef struct
{
    solElement Element;


    const char* Label;


    const char** Options;

    int OptionCount;

    int SelectedIndex;


    bool Open;

    int HoverIndex;


    /*
        When open, this becomes a temporary
        overlay element.
    */
    int PopupLayer;


    solDropdownStyle Style;


    solIntCallback OnSelectionChanged;


} solDropdown;



// **********************************************
// *              FUNCTIONS                     *
// **********************************************

void solDropdown_Init(
    solDropdown* dropdown,
    const char* label,
    const char** options,
    int optionCount,
    float x,
    float y,
    float width,
    float height
);



void solDropdown_Draw(
    solDropdown* dropdown
);



void solDropdown_Update(
    solDropdown* dropdown,
    float mouseX,
    float mouseY,
    bool mousePressed
);



bool solDropdown_Contains(
    solDropdown* dropdown,
    float x,
    float y
);



void solDropdown_Open(
    solDropdown* dropdown
);



void solDropdown_Close(
    solDropdown* dropdown
);



int solDropdown_GetIndex(
    solDropdown* dropdown
);



const char* solDropdown_GetValue(
    solDropdown* dropdown
);



void solDropdown_SetCallback(
    solDropdown* dropdown,
    solIntCallback callback
);



void solDropdown_SetStyle(
    solDropdown* dropdown,
    solDropdownStyle style
);



#ifdef __cplusplus
}
#endif

#endif