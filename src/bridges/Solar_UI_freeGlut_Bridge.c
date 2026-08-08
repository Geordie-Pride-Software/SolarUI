#include "Solar_UI_freeGlut_Bridge.h"


#include <GL/freeglut.h>



void solFreeGLUT_Render_Init(void)
{

}



void solFreeGLUT_BeginFrame(void)
{
    glPushMatrix();

}



void solFreeGLUT_EndFrame(void)
{
    glPopMatrix();

    glutSwapBuffers();
}



// **********************************************
// *              RECTANGLE                     *
// **********************************************

void solFreeGLUT_DrawRectangle(
    float x,
    float y,
    float width,
    float height,
    solColour colour
)
{
    glColor4f(
        colour.r,
        colour.g,
        colour.b,
        colour.a
    );


    glBegin(GL_QUADS);

        glVertex2f(
            x,
            y
        );


        glVertex2f(
            x + width,
            y
        );


        glVertex2f(
            x + width,
            y + height
        );


        glVertex2f(
            x,
            y + height
        );

    glEnd();
}



// **********************************************
// *              BORDER                        *
// **********************************************

void solFreeGLUT_DrawBorder(
    float x,
    float y,
    float width,
    float height,
    solColour colour
)
{
    glColor4f(
        colour.r,
        colour.g,
        colour.b,
        colour.a
    );


    glBegin(GL_LINE_LOOP);

        glVertex2f(
            x,
            y
        );


        glVertex2f(
            x + width,
            y
        );


        glVertex2f(
            x + width,
            y + height
        );


        glVertex2f(
            x,
            y + height
        );

    glEnd();
}



// **********************************************
// *              TEXT                          *
// **********************************************

void solFreeGLUT_DrawText(
    float x,
    float y,
    const char* text,
    solColour colour
)
{
    if(!text)
        return;


    glColor4f(
        colour.r,
        colour.g,
        colour.b,
        colour.a
    );


    glRasterPos2f(
        x,
        y
    );


    while(*text)
    {
        glutBitmapCharacter(
            GLUT_BITMAP_HELVETICA_18,
            *text
        );

        text++;
    }
}



// **********************************************
// *              TEXTURE                       *
// **********************************************

void solFreeGLUT_DrawTexture(
    unsigned int textureID,
    float x,
    float y,
    float width,
    float height
)
{
    if(textureID == 0)
        return;


    glEnable(
        GL_TEXTURE_2D
    );


    glBindTexture(
        GL_TEXTURE_2D,
        textureID
    );


    glBegin(GL_QUADS);


        glTexCoord2f(
            0.0f,
            0.0f
        );

        glVertex2f(
            x,
            y
        );


        glTexCoord2f(
            1.0f,
            0.0f
        );

        glVertex2f(
            x + width,
            y
        );


        glTexCoord2f(
            1.0f,
            1.0f
        );

        glVertex2f(
            x + width,
            y + height
        );


        glTexCoord2f(
            0.0f,
            1.0f
        );

        glVertex2f(
            x,
            y + height
        );


    glEnd();


    glDisable(
        GL_TEXTURE_2D
    );
}