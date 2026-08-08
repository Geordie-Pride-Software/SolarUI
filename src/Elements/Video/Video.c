#include "Video.h"

#include "../../internal/Solar_UI_Render.h"
#include "../../internal/Solar_UI_Media.h"



static solVideoStyle DefaultVideoStyle()
{
    solVideoStyle style;


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



void solVideo_Init(
    solVideo* video,
    const char* filePath,
    float x,
    float y,
    float width,
    float height
)
{
    if (!video)
        return;


    video->Element.Bounds.Position.X = x;
    video->Element.Bounds.Position.Y = y;


    video->Element.Bounds.Size.Width = width;
    video->Element.Bounds.Size.Height = height;


    video->Element.Layer = 0;

    video->Element.Visibility = SOL_VISIBLE;
    video->Element.State = SOL_ENABLED;


    video->FilePath = filePath;


    video->MediaHandle = 0;

    video->TextureID = 0;


    video->State = SOL_VIDEO_STOPPED;


    video->Looping = false;


    video->Volume = 100.0f;


    video->Style = DefaultVideoStyle();
}



void solVideo_Draw(
    solVideo* video
)
{
    if (!video)
        return;


    if (video->Element.Visibility != SOL_VISIBLE)
        return;


    solRender_DrawVideo(video);
}



void solVideo_Load(
    solVideo* video
)
{
    if (!video)
        return;


    if (!video->FilePath)
        return;


    video->MediaHandle =
        solMedia_LoadVideo(
            video->FilePath
        );
}



void solVideo_Play(
    solVideo* video
)
{
    if (!video)
        return;


    if (!video->MediaHandle)
        return;


    solMedia_PlayVideo(
        video->MediaHandle
    );


    video->State = SOL_VIDEO_PLAYING;
}



void solVideo_Pause(
    solVideo* video
)
{
    if (!video)
        return;


    if (!video->MediaHandle)
        return;


    solMedia_PauseVideo(
        video->MediaHandle
    );


    video->State = SOL_VIDEO_PAUSED;
}



void solVideo_Stop(
    solVideo* video
)
{
    if (!video)
        return;


    if (!video->MediaHandle)
        return;


    solMedia_StopVideo(
        video->MediaHandle
    );


    video->State = SOL_VIDEO_STOPPED;
}



void solVideo_SetLoop(
    solVideo* video,
    bool loop
)
{
    if (!video)
        return;


    video->Looping = loop;


    solMedia_SetVideoLoop(
        video->MediaHandle,
        loop
    );
}



void solVideo_SetVolume(
    solVideo* video,
    float volume
)
{
    if (!video)
        return;


    if (volume < 0)
        volume = 0;


    if (volume > 100)
        volume = 100;


    video->Volume = volume;


    solMedia_SetVideoVolume(
        video->MediaHandle,
        volume
    );
}



void solVideo_SetStyle(
    solVideo* video,
    solVideoStyle style
)
{
    if (!video)
        return;


    video->Style = style;
}



void solVideo_Unload(
    solVideo* video
)
{
    if (!video)
        return;


    if (!video->MediaHandle)
        return;


    solMedia_UnloadVideo(
        video->MediaHandle
    );


    video->MediaHandle = 0;

    video->State = SOL_VIDEO_STOPPED;
}