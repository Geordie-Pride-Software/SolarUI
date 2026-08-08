#include "Solar_UI_Render.h"


#include "../bridges/Solar_UI_freeGlut_Bridge.h"



// **********************************************
// *              INITIALISATION                *
// **********************************************

void solRender_Init(void)
{
    solFreeGLUT_Render_Init();
}



void solRender_BeginFrame(void)
{
    solFreeGLUT_BeginFrame();
}



void solRender_EndFrame(void)
{
    solFreeGLUT_EndFrame();
}



// **********************************************
// *              ELEMENT ROUTER                *
// **********************************************

void solRender_DrawElement(
    solElement* element
)
{
    if(!element)
        return;


    switch(element->Type)
    {

        case SOL_ELEMENT_LABEL:

            solRender_DrawLabel(
                (solLabel*)element
            );

            break;



        case SOL_ELEMENT_BUTTON:

            solRender_DrawButton(
                (solButton*)element
            );

            break;



        case SOL_ELEMENT_SLIDER:

            solRender_DrawSlider(
                (solSlider*)element
            );

            break;



        case SOL_ELEMENT_CHECKBOX:

            solRender_DrawCheckbox(
                (solCheckbox*)element
            );

            break;



        case SOL_ELEMENT_IMAGE:

            solRender_DrawImage(
                (solImage*)element
            );

            break;



        case SOL_ELEMENT_VIDEO:

            solRender_DrawVideo(
                (solVideo*)element
            );

            break;



        case SOL_ELEMENT_DROPDOWN:

            solRender_DrawDropdown(
                (solDropdown*)element
            );

            break;



        case SOL_ELEMENT_INPUTBOX:

            solRender_DrawInputBox(
                (solInputBox*)element
            );

            break;



        default:
            break;
    }
}



// **********************************************
// *              LABEL                         *
// **********************************************

void solRender_DrawLabel(
    solLabel* label
)
{
    if(!label)
        return;


    solFreeGLUT_DrawText(
        label->Element.Bounds.Position.X,
        label->Element.Bounds.Position.Y,
        label->Text,
        label->Style.Text
    );
}



// **********************************************
// *              BUTTON                        *
// **********************************************

void solRender_DrawButton(
    solButton* button
)
{
    if(!button)
        return;



    solFreeGLUT_DrawRectangle(
        button->Element.Bounds.Position.X,
        button->Element.Bounds.Position.Y,

        button->Element.Bounds.Size.Width,
        button->Element.Bounds.Size.Height,

        button->Style.Background
    );



    solFreeGLUT_DrawBorder(
        button->Element.Bounds.Position.X,
        button->Element.Bounds.Position.Y,

        button->Element.Bounds.Size.Width,
        button->Element.Bounds.Size.Height,

        button->Style.Border
    );



    solFreeGLUT_DrawText(
        button->Element.Bounds.Position.X,
        button->Element.Bounds.Position.Y,

        button->Label,

        button->Style.Text
    );
}



// **********************************************
// *              SLIDER                        *
// **********************************************

void solRender_DrawSlider(
    solSlider* slider
)
{
    if(!slider)
        return;



    float percent =
        (
            slider->CurrentValue -
            slider->MinValue
        )
        /
        (
            slider->MaxValue -
            slider->MinValue
        );



    solFreeGLUT_DrawRectangle(
        slider->Element.Bounds.Position.X,
        slider->Element.Bounds.Position.Y,

        slider->Element.Bounds.Size.Width,
        slider->Element.Bounds.Size.Height,

        slider->Style.Track
    );



    solFreeGLUT_DrawRectangle(
        slider->Element.Bounds.Position.X,
        slider->Element.Bounds.Position.Y,

        slider->Element.Bounds.Size.Width * percent,
        slider->Element.Bounds.Size.Height,

        slider->Style.Fill
    );
}



// **********************************************
// *              CHECKBOX                      *
// **********************************************

void solRender_DrawCheckbox(
    solCheckbox* checkbox
)
{
    if(!checkbox)
        return;



    solColour colour;


    if(checkbox->Checked)
        colour = checkbox->Style.Checked;
    else
        colour = checkbox->Style.Background;



    solFreeGLUT_DrawRectangle(
        checkbox->Element.Bounds.Position.X,
        checkbox->Element.Bounds.Position.Y,

        checkbox->Element.Bounds.Size.Width,
        checkbox->Element.Bounds.Size.Height,

        colour
    );
}



// **********************************************
// *              IMAGE                         *
// **********************************************

void solRender_DrawImage(
    solImage* image
)
{
    if(!image)
        return;



    solFreeGLUT_DrawTexture(
        image->TextureID,

        image->Element.Bounds.Position.X,
        image->Element.Bounds.Position.Y,

        image->Element.Bounds.Size.Width,
        image->Element.Bounds.Size.Height
    );
}



// **********************************************
// *              VIDEO                         *
// **********************************************

void solRender_DrawVideo(
    solVideo* video
)
{
    if(!video)
        return;



    solFreeGLUT_DrawTexture(
        video->TextureID,

        video->Element.Bounds.Position.X,
        video->Element.Bounds.Position.Y,

        video->Element.Bounds.Size.Width,
        video->Element.Bounds.Size.Height
    );
}



// **********************************************
// *              DROPDOWN                      *
// **********************************************

void solRender_DrawDropdown(
    solDropdown* dropdown
)
{
    if(!dropdown)
        return;



    solFreeGLUT_DrawRectangle(
        dropdown->Element.Bounds.Position.X,
        dropdown->Element.Bounds.Position.Y,

        dropdown->Element.Bounds.Size.Width,
        dropdown->Element.Bounds.Size.Height,

        dropdown->Style.Background
    );



    if(!dropdown->Open)
        return;



    for(int i = 0; i < dropdown->OptionCount; i++)
    {

        solFreeGLUT_DrawRectangle(
            dropdown->Element.Bounds.Position.X,

            dropdown->Element.Bounds.Position.Y +
            (
                dropdown->Element.Bounds.Size.Height *
                (i + 1)
            ),

            dropdown->Element.Bounds.Size.Width,

            dropdown->Element.Bounds.Size.Height,

            dropdown->Style.Background
        );


        solFreeGLUT_DrawText(
            dropdown->Element.Bounds.Position.X,

            dropdown->Element.Bounds.Position.Y +
            (
                dropdown->Element.Bounds.Size.Height *
                (i + 1)
            ),

            dropdown->Options[i],

            dropdown->Style.Text
        );
    }
}



// **********************************************
// *              INPUT BOX                     *
// **********************************************

void solRender_DrawInputBox(
    solInputBox* input
)
{
    if(!input)
        return;



    solFreeGLUT_DrawRectangle(
        input->Element.Bounds.Position.X,
        input->Element.Bounds.Position.Y,

        input->Element.Bounds.Size.Width,
        input->Element.Bounds.Size.Height,

        input->Style.Background
    );



    if(input->Buffer[0] != '\0')
    {
        solFreeGLUT_DrawText(
            input->Element.Bounds.Position.X,
            input->Element.Bounds.Position.Y,

            input->Buffer,

            input->Style.Text
        );
    }
    else
    {
        solFreeGLUT_DrawText(
            input->Element.Bounds.Position.X,
            input->Element.Bounds.Position.Y,

            input->Placeholder,

            input->Style.Placeholder
        );
    }
}