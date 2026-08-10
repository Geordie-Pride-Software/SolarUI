#ifndef SOLARUI_INPUTBOX_H
#define SOLARUI_INPUTBOX_H

#include "../../../include/SolarUI_com.h"
#include "../../../include/SolarUI_exp.h"

#ifdef __cplusplus
extern "C" {
#endif


// **********************************************
// *             INPUTBOX STYLE                *
// **********************************************

typedef struct
{
    solColour Background;
    solColour Border;

    solColour Text;
    solColour Placeholder;

    solColour Cursor;

} solInputBoxStyle;



// **********************************************
// *             INPUTBOX STRUCT                *
// **********************************************

typedef struct
{
    solElement Element;


    const char* Placeholder;


    char* Buffer;

    int BufferSize;

    int Length;


    int CursorPosition;


    bool Focused;

    bool Submitted;


    solInputBoxStyle Style;


    void (*OnSubmit)(const char* text);


} solInputBox;



// **********************************************
// *              FUNCTIONS                    *
// **********************************************

SOLARUI_API void solInputBox_Init(
    solInputBox* input,
    const char* placeholder,
    char* buffer,
    int bufferSize,
    float x,
    float y,
    float width,
    float height
);



SOLARUI_API void solInputBox_Draw(
    solInputBox* input
);



SOLARUI_API void solInputBox_Update(
    solInputBox* input
);



SOLARUI_API void solInputBox_MouseUpdate(
    solInputBox* input,
    float mouseX,
    float mouseY,
    bool pressed
);



SOLARUI_API void solInputBox_KeyInput(
    solInputBox* input,
    char key
);



SOLARUI_API void solInputBox_Backspace(
    solInputBox* input
);



SOLARUI_API void solInputBox_Clear(
    solInputBox* input
);



SOLARUI_API const char* solInputBox_GetText(
    solInputBox* input
);



SOLARUI_API bool solInputBox_IsSubmitted(
    solInputBox* input
);



SOLARUI_API void solInputBox_SetCallback(
    solInputBox* input,
    void (*callback)(const char*)
);



SOLARUI_API void solInputBox_SetStyle(
    solInputBox* input,
    solInputBoxStyle style
);



#ifdef __cplusplus
}
#endif

#endif