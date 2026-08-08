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
            solInput_SetMouseDown(
                true
            );


            solInput_SetMousePressed(
                true
            );
        }


        else if(state == GLUT_UP)
        {
            solInput_SetMouseDown(
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
        key
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
        key
    );
}