#include "Solar_UI_Input.h"


// **********************************************
// *              INTERNAL STATE                *
// **********************************************


static float MouseX = 0.0f;
static float MouseY = 0.0f;


static bool MouseDown = false;
static bool MousePressed = false;
static bool MouseReleased = false;


static bool Keys[256];
static bool SpecialKeys[256];


static solElement* FocusedElement = 0;


static solElement* CapturedElement = 0;



// **********************************************
// *              INITIALISATION                *
// **********************************************

void solInput_Init(void)
{
    MouseX = 0.0f;
    MouseY = 0.0f;


    MouseDown = false;
    MousePressed = false;
    MouseReleased = false;


    for(int i = 0; i < 256; i++)
    {
        Keys[i] = false;
        SpecialKeys[i] = false;
    }


    FocusedElement = 0;

    CapturedElement = 0;
}



// **********************************************
// *              UPDATE                        *
// **********************************************

void solInput_Update(void)
{
    /*
        Press/release events only last
        for one frame.
    */

    MousePressed = false;
    MouseReleased = false;
}



// **********************************************
// *              MOUSE                         *
// **********************************************

void solInput_SetMousePosition(
    float x,
    float y
)
{
    MouseX = x;
    MouseY = y;
}



float solInput_GetMouseX(void)
{
    return MouseX;
}



float solInput_GetMouseY(void)
{
    return MouseY;
}



void solInput_SetMouseButton(
    solMouseButton button,
    bool pressed
)
{
    /*
        Currently only storing left mouse.
        This can be expanded later.
    */

    if(button != SOL_MOUSE_LEFT)
        return;


    if(pressed && !MouseDown)
    {
        MousePressed = true;
    }


    if(!pressed && MouseDown)
    {
        MouseReleased = true;
    }


    MouseDown = pressed;
}



bool solInput_IsMouseDown(void)
{
    return MouseDown;
}



bool solInput_IsMousePressed(void)
{
    return MousePressed;
}



bool solInput_IsMouseReleased(void)
{
    return MouseReleased;
}



// **********************************************
// *              KEYBOARD                      *
// **********************************************

void solInput_SetKey(
    int key,
    bool pressed
)
{
    if(key < 0 || key >= 256)
        return;


    Keys[key] = pressed;
}



bool solInput_IsKeyDown(
    int key
)
{
    if(key < 0 || key >= 256)
        return false;


    return Keys[key];
}



void solInput_SetSpecialKey(
    int key,
    bool pressed
)
{
    if(key < 0 || key >= 256)
        return;


    SpecialKeys[key] = pressed;
}



bool solInput_IsSpecialKeyDown(
    int key
)
{
    if(key < 0 || key >= 256)
        return false;


    return SpecialKeys[key];
}



// **********************************************
// *              FOCUS                         *
// **********************************************

void solInput_SetFocus(
    solElement* element
)
{
    FocusedElement = element;
}



solElement* solInput_GetFocus(void)
{
    return FocusedElement;
}



void solInput_ClearFocus(void)
{
    FocusedElement = 0;
}



// **********************************************
// *              INPUT CAPTURE                 *
// **********************************************

void solInput_Capture(
    solElement* element
)
{
    CapturedElement = element;
}



void solInput_ReleaseCapture(void)
{
    CapturedElement = 0;
}



solElement* solInput_GetCapture(void)
{
    return CapturedElement;
}



// **********************************************
// *              ELEMENT ROUTER                *
// **********************************************

void solInput_SendToElement(
    solElement* element
)
{
    if(!element)
        return;


    float mouseX =
        solInput_GetMouseX();

    float mouseY =
        solInput_GetMouseY();

    bool mouseDown =
        solInput_IsMouseDown();

    bool mousePressed =
        solInput_IsMousePressed();


    switch(element->Type)
    {

        case SOL_ELEMENT_BUTTON:

            solButton_Update(
                (solButton*)element,
                mouseX,
                mouseY,
                mouseDown
            );

            break;



        case SOL_ELEMENT_SLIDER:

            solSlider_Update(
                (solSlider*)element,
                mouseX,
                mouseY,
                mouseDown
            );

            break;



        case SOL_ELEMENT_CHECKBOX:

            solCheckbox_Update(
                (solCheckbox*)element,
                mouseX,
                mouseY,
                mousePressed
            );

            break;



        case SOL_ELEMENT_DROPDOWN:

            solDropdown_Update(
                (solDropdown*)element,
                mouseX,
                mouseY,
                mousePressed
            );

            break;



        case SOL_ELEMENT_INPUTBOX:

            solInputBox_MouseUpdate(
                (solInputBox*)element,
                mouseX,
                mouseY,
                mousePressed
            );

            break;



        /*
            Labels, images and video are not
            interactive - nothing to route.
        */

        default:
            break;
    }
}