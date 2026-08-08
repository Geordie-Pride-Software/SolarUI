#include "Solar_UI_Input_Bridge.h"


#include "../internal/Solar_UI_Input.h"

#include <GL/freeglut.h>



// **********************************************
// *              INIT                          *
// **********************************************

void solInputBridge_Init(void)
{

}



// **********************************************
// *              MOUSE MOVE                    *
// **********************************************

void solInputBridge_MouseMove(
    int x,
    int y
)
{
    solInput_SetMousePosition(
        (float)x,
        (float)y
    );
}



// **********************************************
// *              MOUSE BUTTON                  *
// **********************************************

void solInputBridge_MouseButton(
    int button,
    int state,
    int x,
    int y
)
{

    solInput_SetMousePosition(
        (float)x,
        (float)y
    );



    if(button == GLUT_LEFT_BUTTON)
    {

        if(state == GLUT_DOWN)
        {
            solInput_SetMouseButton(
                SOL_MOUSE_LEFT,
                true
            );
        }


        else if(state == GLUT_UP)
        {
            solInput_SetMouseButton(
                SOL_MOUSE_LEFT,
                false
            );
        }

    }

}



// **********************************************
// *              KEY DOWN                      *
// **********************************************

void solInputBridge_KeyDown(
    unsigned char key,
    int x,
    int y
)
{
    solInput_SetKey(
        key,
        true
    );
}



// **********************************************
// *              KEY UP                        *
// **********************************************

void solInputBridge_KeyUp(
    unsigned char key,
    int x,
    int y
)
{
    solInput_SetKey(
        key,
        false
    );
}



// **********************************************
// *              SPECIAL KEYS                  *
// **********************************************

void solInputBridge_SpecialKey(
    int key,
    int x,
    int y
)
{
    solInput_SetSpecialKey(
        key,
        true
    );
}



// **********************************************
// *              SPECIAL KEY UP                *
// **********************************************

void solInputBridge_SpecialKeyUp(
    int key,
    int x,
    int y
)
{
    solInput_SetSpecialKey(
        key,
        false
    );
}