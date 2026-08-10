#ifndef SOLARUI_LABEL_H
#define SOLARUI_LABEL_H

#include "../../../include/SolarUI_com.h"
#include "../../../include/SolarUI_exp.h"

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

SOLARUI_API void solLabel_Init(
    solLabel* label,
    const char* text,
    float x,
    float y
);


/* Drawing */

SOLARUI_API void solLabel_Draw(
    solLabel* label
);


/* Utility */

SOLARUI_API void solLabel_SetText(
    solLabel* label,
    const char* text
);

SOLARUI_API const char* solLabel_GetText(
    const solLabel* label
);

SOLARUI_API void solLabel_SetPosition(
    solLabel* label,
    float x,
    float y
);

SOLARUI_API void solLabel_SetColour(
    solLabel* label,
    solColour colour
);

SOLARUI_API void solLabel_SetFont(
    solLabel* label,
    solFont font
);

#ifdef __cplusplus
}
#endif

#endif