#ifndef SOLARUI_DROPDOWN_H
#define SOLARUI_DROPDOWN_H

#include "../../../include/SUI/SolarUI_com.h"
#include "../../../include/SUI/SolarUI_exp.h"

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

SOLARUI_API void solDropdown_Init(
    solDropdown* dropdown,
    const char* label,
    const char** options,
    int optionCount,
    float x,
    float y,
    float width,
    float height
);



SOLARUI_API void solDropdown_Draw(
    solDropdown* dropdown
);



SOLARUI_API void solDropdown_Update(
    solDropdown* dropdown,
    float mouseX,
    float mouseY,
    bool mousePressed
);



SOLARUI_API bool solDropdown_Contains(
    solDropdown* dropdown,
    float x,
    float y
);



SOLARUI_API void solDropdown_Open(
    solDropdown* dropdown
);



SOLARUI_API void solDropdown_Close(
    solDropdown* dropdown
);



SOLARUI_API int solDropdown_GetIndex(
    solDropdown* dropdown
);



SOLARUI_API const char* solDropdown_GetValue(
    solDropdown* dropdown
);



SOLARUI_API void solDropdown_SetCallback(
    solDropdown* dropdown,
    solIntCallback callback
);



SOLARUI_API void solDropdown_SetStyle(
    solDropdown* dropdown,
    solDropdownStyle style
);



#ifdef __cplusplus
}
#endif

#endif