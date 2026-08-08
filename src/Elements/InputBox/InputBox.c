#include "InputBox.h"

#include "../../internal/Solar_UI_Input.h"
#include "../../internal/Solar_UI_Render.h"



static solInputBoxStyle DefaultInputStyle()
{
    solInputBoxStyle style;


    style.Background =
    (solColour)
    {
        0.15f,
        0.15f,
        0.15f,
        1.0f
    };


    style.Border =
    (solColour)
    {
        1.0f,
        1.0f,
        1.0f,
        1.0f
    };


    style.Text =
    (solColour)
    {
        1.0f,
        1.0f,
        1.0f,
        1.0f
    };


    style.Placeholder =
    (solColour)
    {
        0.6f,
        0.6f,
        0.6f,
        1.0f
    };


    style.Cursor =
    (solColour)
    {
        1.0f,
        1.0f,
        1.0f,
        1.0f
    };


    return style;
}



void solInputBox_Init(
    solInputBox* input,
    const char* placeholder,
    char* buffer,
    int bufferSize,
    float x,
    float y,
    float width,
    float height
)
{
    if(!input)
        return;


    input->Element.Bounds.Position.X = x;
    input->Element.Bounds.Position.Y = y;


    input->Element.Bounds.Size.Width = width;
    input->Element.Bounds.Size.Height = height;


    input->Element.Layer = 0;

    input->Element.Visibility = SOL_VISIBLE;
    input->Element.State = SOL_ENABLED;


    input->Placeholder = placeholder;


    input->Buffer = buffer;

    input->BufferSize = bufferSize;


    input->Length = 0;

    input->CursorPosition = 0;


    input->Focused = false;

    input->Submitted = false;


    if(buffer)
        buffer[0] = '\0';


    input->Style = DefaultInputStyle();


    input->OnSubmit = 0;
}



void solInputBox_Draw(
    solInputBox* input
)
{
    if(!input)
        return;


    solRender_DrawInputBox(input);
}



void solInputBox_MouseUpdate(
    solInputBox* input,
    float mouseX,
    float mouseY,
    bool pressed
)
{
    if(!input)
        return;


    if(!pressed)
        return;



    bool inside =
    (
        mouseX >= input->Element.Bounds.Position.X &&
        mouseX <= input->Element.Bounds.Position.X +
                  input->Element.Bounds.Size.Width &&

        mouseY >= input->Element.Bounds.Position.Y &&
        mouseY <= input->Element.Bounds.Position.Y +
                  input->Element.Bounds.Size.Height
    );


    if(inside)
    {
        input->Focused = true;


        solInput_SetFocus(
            (solElement*)input
        );
    }
    else
    {
        input->Focused = false;


        if(solInput_GetFocus()
            ==
            (solElement*)input)
        {
            solInput_ClearFocus();
        }
    }
}



void solInputBox_KeyInput(
    solInputBox* input,
    char key
)
{
    if(!input)
        return;


    if(!input->Focused)
        return;



    if(key == '\n')
    {
        input->Submitted = true;


        if(input->OnSubmit)
        {
            input->OnSubmit(
                input->Buffer
            );
        }

        return;
    }



    if(input->Length >= input->BufferSize - 1)
        return;



    input->Buffer[
        input->CursorPosition
    ] = key;



    input->CursorPosition++;

    input->Length++;


    input->Buffer[
        input->Length
    ] = '\0';
}



void solInputBox_Backspace(
    solInputBox* input
)
{
    if(!input)
        return;


    if(!input->Focused)
        return;


    if(input->Length <= 0)
        return;



    input->Length--;

    input->CursorPosition--;


    input->Buffer[
        input->Length
    ] = '\0';
}



void solInputBox_Clear(
    solInputBox* input
)
{
    if(!input)
        return;


    input->Length = 0;

    input->CursorPosition = 0;


    if(input->Buffer)
        input->Buffer[0] = '\0';
}



const char* solInputBox_GetText(
    solInputBox* input
)
{
    if(!input)
        return 0;


    return input->Buffer;
}



bool solInputBox_IsSubmitted(
    solInputBox* input
)
{
    if(!input)
        return false;


    bool value =
        input->Submitted;


    input->Submitted = false;


    return value;
}



void solInputBox_SetCallback(
    solInputBox* input,
    void (*callback)(const char*)
)
{
    if(!input)
        return;


    input->OnSubmit = callback;
}



void solInputBox_SetStyle(
    solInputBox* input,
    solInputBoxStyle style
)
{
    if(!input)
        return;


    input->Style = style;
}