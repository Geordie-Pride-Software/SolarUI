#include "SolarUI.h"

#include "internal/Solar_UI_Render.h"
#include "internal/Solar_UI_Input.h"
#include "internal/Solar_UI_Media.h"


#include <stdlib.h>
#include <stdbool.h>



#define SOL_MAX_ELEMENTS 2048



// **********************************************
// *              ELEMENT STORAGE               *
// **********************************************


static solElement* Elements[SOL_MAX_ELEMENTS];

static int ElementCount = 0;



static solElement* InputCapture = NULL;



// **********************************************
// *              INTERNAL FUNCTIONS             *
// **********************************************


static void solUI_SortLayers(void)
{
    for(int i = 0; i < ElementCount - 1; i++)
    {
        for(int j = i + 1; j < ElementCount; j++)
        {
            if(
                Elements[i]->Layer >
                Elements[j]->Layer
            )
            {
                solElement* temp =
                    Elements[i];

                Elements[i] =
                    Elements[j];

                Elements[j] =
                    temp;
            }
        }
    }
}





static bool solUI_PointInside(
    solElement* element,
    float x,
    float y
)
{
    if(!element)
        return false;


    return
        x >= element->Bounds.Position.X &&
        x <= element->Bounds.Position.X +
             element->Bounds.Size.Width &&

        y >= element->Bounds.Position.Y &&
        y <= element->Bounds.Position.Y +
             element->Bounds.Size.Height;
}





static solElement* solUI_GetElementAt(
    float x,
    float y
)
{
    solElement* result = NULL;


    int highestLayer = -999999;



    for(int i = 0; i < ElementCount; i++)
    {
        solElement* element =
            Elements[i];


        if(!element)
            continue;



        if(element->Visibility != SOL_VISIBLE)
            continue;



        if(element->State != SOL_ENABLED)
            continue;



        if(!solUI_PointInside(
            element,
            x,
            y
        ))
            continue;



        if(
            element->Layer >= highestLayer
        )
        {
            result = element;

            highestLayer =
                element->Layer;
        }
    }


    return result;
}



// **********************************************
// *              INITIALISATION                *
// **********************************************


int solUI_Init(void)
{
    ElementCount = 0;

    InputCapture = NULL;


    solRender_Init();

    solInput_Init();

    solMedia_Init();



    return 1;
}



// **********************************************
// *              SHUTDOWN                      *
// **********************************************


void solUI_Shutdown(void)
{
    solMedia_Shutdown();


    ElementCount = 0;

    InputCapture = NULL;
}



// **********************************************
// *              ELEMENT MANAGEMENT             *
// **********************************************


bool solUI_AddElement(
    solElement* element
)
{
    if(!element)
        return false;


    if(ElementCount >= SOL_MAX_ELEMENTS)
        return false;



    Elements[
        ElementCount++
    ] = element;



    solUI_SortLayers();



    return true;
}





bool solUI_RemoveElement(
    solElement* element
)
{
    if(!element)
        return false;



    for(int i = 0; i < ElementCount; i++)
    {
        if(Elements[i] == element)
        {

            for(
                int j = i;
                j < ElementCount - 1;
                j++
            )
            {
                Elements[j] =
                    Elements[j + 1];
            }


            ElementCount--;


            return true;
        }
    }


    return false;
}



// **********************************************
// *              UPDATE                        *
// **********************************************


void solUI_Update(void)
{
    solInput_Update();



    /*
        If an element has captured input,
        it receives everything.
    */

    if(InputCapture)
    {
        solInput_SendToElement(
            InputCapture
        );
    }

    else
    {
        solElement* target =
            solUI_GetElementAt(
                solInput_GetMouseX(),
                solInput_GetMouseY()
            );


        if(target)
        {
            solInput_SendToElement(
                target
            );
        }
    }
}



// **********************************************
// *              DRAW                          *
// **********************************************


void solUI_Draw(void)
{
    solRender_BeginFrame();



    /*
        Draw from lowest layer
        to highest layer.
    */

    for(int i = 0; i < ElementCount; i++)
    {
        solRender_DrawElement(
            Elements[i]
        );
    }



    solRender_EndFrame();
}



// **********************************************
// *              INPUT CAPTURE                 *
// **********************************************


void solUI_CaptureInput(
    solElement* element
)
{
    InputCapture =
        element;
}



void solUI_ReleaseInput(void)
{
    InputCapture =
        NULL;
}