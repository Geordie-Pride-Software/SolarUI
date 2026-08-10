// ==================================================
//  SolarUI smoke test
//
//  Uses ONLY "SolarUI.h" - it now pulls in every
//  element type (Button, Label, Slider, Checkbox,
//  etc.) and the input feed functions itself, and
//  the DLL actually exports all of it.
// ==================================================

#include <GL/freeglut.h>
#include <cstdio>

#include "../include/SolarUI.h"


static const int WINDOW_WIDTH  = 800;
static const int WINDOW_HEIGHT = 600;


static solButton    g_Button;
static solLabel     g_Label;
static solLabel     g_ValueLabel;
static solSlider    g_Slider;
static solCheckbox  g_Checkbox;

static char g_ValueText[64];


// **************************************************
//              ELEMENT CALLBACKS
// **************************************************

static void OnButtonClicked(void)
{
    printf("[test] Button clicked!\n");

    solLabel_SetText(
        &g_Label,
        "Button was clicked!"
    );
}


static void OnSliderChanged(float value)
{
    snprintf(
        g_ValueText,
        sizeof(g_ValueText),
        "Slider value: %.2f",
        value
    );

    solLabel_SetText(
        &g_ValueLabel,
        g_ValueText
    );
}


static void OnCheckboxChanged(bool checked)
{
    printf(
        "[test] Checkbox is now %s\n",
        checked ? "checked" : "unchecked"
    );
}


// **************************************************
//              GLUT CALLBACKS
// **************************************************

static void Display(void)
{
    solUI_Update();
    solUI_Draw();
}


static void Timer(int value)
{
    glutPostRedisplay();

    // ~60fps. glutIdleFunc redraws in an
    // uncapped busy-loop, which on Windows
    // fights with the compositor and shows up
    // as flicker/tearing - a timer keeps it to
    // a fixed, stable rate instead.
    glutTimerFunc(16, Timer, 0);
}


static void Reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    solUI_UpdateViewport(width, height);
}


static void MouseMove(int x, int y)
{
    solInputBridge_MouseMove(x, y);
}


static void MouseButton(int button, int state, int x, int y)
{
    solInputBridge_MouseButton(button, state, x, y);
}


static void KeyDown(unsigned char key, int x, int y)
{
    solInputBridge_KeyDown(key, x, y);

    // Esc to quit, for convenience.
    if(key == 27)
    {
        solUI_Shutdown();
        exit(0);
    }
}


static void KeyUp(unsigned char key, int x, int y)
{
    solInputBridge_KeyUp(key, x, y);
}


static void SpecialKeyDown(int key, int x, int y)
{
    solInputBridge_SpecialKey(key, x, y);
}


static void SpecialKeyUp(int key, int x, int y)
{
    solInputBridge_SpecialKeyUp(key, x, y);
}


// **************************************************
//              SETUP
// **************************************************

static void BuildTestUI(void)
{
    solUI_SetLogicalSize(
        (float)WINDOW_WIDTH,
        (float)WINDOW_HEIGHT
    );


    solButton_Init(
        &g_Button,
        "Click Me",
        50, 50,
        160, 40
    );

    solButton_SetCallback(
        &g_Button,
        OnButtonClicked
    );

    solUI_AddElement(
        &g_Button.Element
    );



    solLabel_Init(
        &g_Label,
        "Press the button above",
        50, 110
    );

    solUI_AddElement(
        &g_Label.Element
    );



    solSlider_Init(
        &g_Slider,
        "Test Slider",
        50, 160,
        200, 24,
        0.0f, 100.0f,
        25.0f
    );

    solSlider_SetCallback(
        &g_Slider,
        OnSliderChanged
    );

    solUI_AddElement(
        &g_Slider.Element
    );



    snprintf(
        g_ValueText,
        sizeof(g_ValueText),
        "Slider value: %.2f",
        g_Slider.CurrentValue
    );

    solLabel_Init(
        &g_ValueLabel,
        g_ValueText,
        50, 210
    );

    solUI_AddElement(
        &g_ValueLabel.Element
    );



    solCheckbox_Init(
        &g_Checkbox,
        "Toggle me",
        50, 260,
        24, 24
    );

    solCheckbox_SetCallback(
        &g_Checkbox,
        OnCheckboxChanged
    );

    solUI_AddElement(
        &g_Checkbox.Element
    );
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("SolarUI Test");


    if(!solUI_Init())
    {
        fprintf(stderr, "[test] solUI_Init failed\n");
        return 1;
    }


    BuildTestUI();


    glutDisplayFunc(Display);
    glutTimerFunc(16, Timer, 0);
    glutReshapeFunc(Reshape);

    glutMotionFunc(MouseMove);
    glutPassiveMotionFunc(MouseMove);
    glutMouseFunc(MouseButton);

    glutKeyboardFunc(KeyDown);
    glutKeyboardUpFunc(KeyUp);
    glutSpecialFunc(SpecialKeyDown);
    glutSpecialUpFunc(SpecialKeyUp);


    printf("[test] SolarUI test running - Esc to quit.\n");

    glutMainLoop();


    solUI_Shutdown();

    return 0;
}
