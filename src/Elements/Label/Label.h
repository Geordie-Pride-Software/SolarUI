#ifndef SOLARUI_LABEL_H
#define SOLARUI_LABEL_H

#include "../../../include/SolarUI_com.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    solElement Element;

    const char* Text;

    solFont Font;

    solLabelStyle Style;

} solLabel;


/* Creation */

void solLabel_Init(
    solLabel* label,
    const char* text,
    float x,
    float y
);


/* Drawing */

void solLabel_Draw(
    solLabel* label
);


/* Utility */

void solLabel_SetText(
    solLabel* label,
    const char* text
);

const char* solLabel_GetText(
    const solLabel* label
);

void solLabel_SetPosition(
    solLabel* label,
    float x,
    float y
);

void solLabel_SetColour(
    solLabel* label,
    solColour colour
);

void solLabel_SetFont(
    solLabel* label,
    solFont font
);

#ifdef __cplusplus
}
#endif

#endif