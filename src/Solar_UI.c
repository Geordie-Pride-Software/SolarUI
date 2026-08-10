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
    /*
        Press/release are one-frame edge flags,
        set asynchronously by GLUT's mouse
        callback whenever it fires (between
        frames). They must stay readable for
        this ENTIRE frame's dispatch below -
        clearing them here at the top would wipe
        out a press event before anything ever
        got to read it. Cleared at the end
        instead, once dispatch is done with them.
    */



    /*
        Videos need to keep playing/advancing
        regardless of mouse hover or capture,
        so they get ticked every frame here
        rather than through input dispatch.
    */

    for(int i = 0; i < ElementCount; i++)
    {
        if(Elements[i] && Elements[i]->Type == SOL_ELEMENT_VIDEO)
        {
            solVideo_Update(
                (solVideo*)Elements[i]
            );
        }
    }



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



    solInput_Update();
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



// **********************************************
// *              VIEWPORT                      *
// **********************************************


static int ScreenWidth  = 800;
static int ScreenHeight = 600;


void solUI_SetLogicalSize(
    float width,
    float height
)
{
    solRender_SetLogicalSize(
        width,
        height
    );
}



void solUI_UpdateViewport(
    int width,
    int height
)
{
    if(width <= 0 || height <= 0)
        return;


    ScreenWidth  = width;
    ScreenHeight = height;
}



void solUI_ScreenToLogical(
    int screenX,
    int screenY,
    float* logicalX,
    float* logicalY
)
{
    float logicalWidth  = 0.0f;
    float logicalHeight = 0.0f;

    solRender_GetLogicalSize(
        &logicalWidth,
        &logicalHeight
    );


    if(logicalX)
    {
        *logicalX =
            (float)screenX *
            (logicalWidth / (float)ScreenWidth);
    }


    if(logicalY)
    {
        *logicalY =
            (float)screenY *
            (logicalHeight / (float)ScreenHeight);
    }
}



// **********************************************
// *              FONT SYSTEM                   *
// **********************************************


static solFont DefaultFont = { NULL, 12.0f };


void solUI_SetFont(
    solFont font
)
{
    DefaultFont = font;
}