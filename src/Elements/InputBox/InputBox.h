#ifndef SOLARUI_INPUTBOX_H
#define SOLARUI_INPUTBOX_H

#include "../../../include/SolarUI_com.h"

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

void solInputBox_Init(
    solInputBox* input,
    const char* placeholder,
    char* buffer,
    int bufferSize,
    float x,
    float y,
    float width,
    float height
);



void solInputBox_Draw(
    solInputBox* input
);



void solInputBox_Update(
    solInputBox* input
);



void solInputBox_MouseUpdate(
    solInputBox* input,
    float mouseX,
    float mouseY,
    bool pressed
);



void solInputBox_KeyInput(
    solInputBox* input,
    char key
);



void solInputBox_Backspace(
    solInputBox* input
);



void solInputBox_Clear(
    solInputBox* input
);



const char* solInputBox_GetText(
    solInputBox* input
);



bool solInputBox_IsSubmitted(
    solInputBox* input
);



void solInputBox_SetCallback(
    solInputBox* input,
    void (*callback)(const char*)
);



void solInputBox_SetStyle(
    solInputBox* input,
    solInputBoxStyle style
);



#ifdef __cplusplus
}
#endif

#endif