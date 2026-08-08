#include "Image.h"

#include "../../internal/Solar_UI_Render.h"
#include "../../internal/Solar_UI_Media.h"


static solImageStyle DefaultImageStyle()
{
    solImageStyle style;


    style.Tint = (solColour)
    {
        1.0f,
        1.0f,
        1.0f,
        1.0f
    };


    style.Opacity = 1.0f;


    return style;
}



void solImage_Init(
    solImage* image,
    const char* filePath,
    float x,
    float y,
    float width,
    float height
)
{
    if (!image)
        return;


    image->Element.Bounds.Position.X = x;
    image->Element.Bounds.Position.Y = y;


    image->Element.Bounds.Size.Width = width;
    image->Element.Bounds.Size.Height = height;


    image->Element.Layer = 0;

    image->Element.Visibility = SOL_VISIBLE;
    image->Element.State = SOL_ENABLED;


    image->FilePath = filePath;


    image->TextureID = 0;

    image->Loaded = false;


    image->Style = DefaultImageStyle();
}



void solImage_Draw(
    solImage* image
)
{
    if (!image)
        return;


    if (image->Element.Visibility != SOL_VISIBLE)
        return;


    if (!image->Loaded)
        return;


    solRender_DrawImage(image);
}



void solImage_Load(
    solImage* image
)
{
    if (!image)
        return;


    if (!image->FilePath)
        return;


    image->TextureID =
        solMedia_LoadImage(
            image->FilePath
        );


    if (image->TextureID != 0)
    {
        image->Loaded = true;
    }
}



void solImage_Unload(
    solImage* image
)
{
    if (!image)
        return;


    if (!image->Loaded)
        return;


    solMedia_UnloadImage(
        image->TextureID
    );


    image->TextureID = 0;

    image->Loaded = false;
}



void solImage_SetTexture(
    solImage* image,
    unsigned int textureID
)
{
    if (!image)
        return;


    image->TextureID = textureID;

    image->Loaded = true;
}



unsigned int solImage_GetTexture(
    solImage* image
)
{
    if (!image)
        return 0;


    return image->TextureID;
}



void solImage_SetStyle(
    solImage* image,
    solImageStyle style
)
{
    if (!image)
        return;


    image->Style = style;
}