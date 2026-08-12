#ifndef SOLAR_UI_RENDER_H
#define SOLAR_UI_RENDER_H

#include "../../include/SUI/SolarUI_com.h"

#include "../Elements/Label/Label.h"
#include "../Elements/Button/Button.h"
#include "../Elements/Slider/Slider.h"
#include "../Elements/Checkbox/Checkbox.h"
#include "../Elements/Image/Image.h"
#include "../Elements/Video/Video.h"
#include "../Elements/Dropdown/Dropdown.h"
#include "../Elements/InputBox/InputBox.h"


#ifdef __cplusplus
extern "C" {
#endif


// **********************************************
// *              RENDER SYSTEM                 *
// **********************************************

void solRender_Init(void);


void solRender_BeginFrame(void);


void solRender_EndFrame(void);



void solRender_SetLogicalSize(
    float width,
    float height
);


void solRender_GetLogicalSize(
    float* width,
    float* height
);



// **********************************************
// *              ELEMENT ROUTER                *
// **********************************************

void solRender_DrawElement(
    solElement* element
);



// **********************************************
// *              ELEMENT DRAWING               *
// **********************************************

void solRender_DrawLabel(
    solLabel* label
);


void solRender_DrawButton(
    solButton* button
);


void solRender_DrawSlider(
    solSlider* slider
);


void solRender_DrawCheckbox(
    solCheckbox* checkbox
);


void solRender_DrawImage(
    solImage* image
);


void solRender_DrawVideo(
    solVideo* video
);


void solRender_DrawDropdown(
    solDropdown* dropdown
);


void solRender_DrawInputBox(
    solInputBox* input
);



#ifdef __cplusplus
}
#endif

#endif