#include "Solar_UI_Manager.h"

#include "Solar_UI_Input.h"


#define SOL_MAX_ELEMENTS 512


static solElement* Elements[SOL_MAX_ELEMENTS];

static int ElementCount = 0;



// **********************************************
// *              INITIALISATION                *
// **********************************************

void solUI_Manager_Init(void)
{
    ElementCount = 0;


    for(int i = 0; i < SOL_MAX_ELEMENTS; i++)
    {
        Elements[i] = NULL;
    }
}



// **********************************************
// *              ADD / REMOVE                  *
// **********************************************

void solUI_Manager_Add(
    solElement* element
)
{
    if(!element)
        return;


    if(ElementCount >= SOL_MAX_ELEMENTS)
        return;


    Elements[ElementCount] = element;

    ElementCount++;
}



void solUI_Manager_Remove(
    solElement* element
)
{
    if(!element)
        return;


    for(int i = 0; i < ElementCount; i++)
    {
        if(Elements[i] == element)
        {
            for(int j = i; j < ElementCount - 1; j++)
            {
                Elements[j] = Elements[j + 1];
            }


            ElementCount--;

            break;
        }
    }
}



void solUI_Manager_Clear(void)
{
    ElementCount = 0;
}



// **********************************************
// *              LAYERING                      *
// **********************************************

void solUI_Manager_SetLayer(
    solElement* element,
    int layer
)
{
    if(!element)
        return;


    element->Layer = layer;
}



int solUI_Manager_GetLayer(
    solElement* element
)
{
    if(!element)
        return -1;


    return element->Layer;
}



// **********************************************
// *              FIND ELEMENT                  *
// **********************************************

solElement* solUI_Manager_GetElementAt(
    float x,
    float y
)
{
    solElement* found = NULL;


    int highestLayer = -2147483647;


    for(int i = 0; i < ElementCount; i++)
    {
        solElement* element = Elements[i];


        if(!element)
            continue;


        if(element->Visibility != SOL_VISIBLE)
            continue;


        if(element->Layer < highestLayer)
            continue;


        if(
            x >= element->Bounds.Position.X &&
            x <= element->Bounds.Position.X +
                 element->Bounds.Size.Width &&

            y >= element->Bounds.Position.Y &&
            y <= element->Bounds.Position.Y +
                 element->Bounds.Size.Height
        )
        {
            found = element;

            highestLayer = element->Layer;
        }
    }


    return found;
}



// **********************************************
// *              INPUT PROCESSING              *
// **********************************************

void solUI_Manager_ProcessInput(void)
{
    float x =
        solInput_GetMouseX();


    float y =
        solInput_GetMouseY();



    solElement* target = NULL;



    /*
        Captured elements always win.

        Example:
        Dropdown open -> nothing underneath
        receives input.
    */

    target =
        solInput_GetCapture();



    if(!target)
    {
        target =
            solUI_Manager_GetElementAt(
                x,
                y
            );
    }



    if(!target)
        return;



    /*
        Individual elements handle their
        own behaviour.

        Later this will call element-specific
        update functions.
    */
}



// **********************************************
// *              FRAME                         *
// **********************************************

void solUI_Manager_Update(void)
{
    solUI_Manager_ProcessInput();
}



// **********************************************
// *              INPUT BLOCKING                *
// **********************************************

void solUI_Manager_BlockInputBelow(
    solElement* element
)
{
    if(!element)
        return;


    solInput_Capture(
        element
    );
}



void solUI_Manager_UnblockInput(void)
{
    solInput_ReleaseCapture();
}



void solUI_Manager_Draw(void)
{
    /*
        Drawing will later be sorted by layer.
    */


    for(int i = 0; i < ElementCount; i++)
    {
        if(Elements[i])
        {
            /*
                Actual drawing is delegated
                to each element.
            */
        }
    }
}