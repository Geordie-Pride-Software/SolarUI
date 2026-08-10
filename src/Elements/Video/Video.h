#ifndef SOLARUI_VIDEO_H
#define SOLARUI_VIDEO_H

#include "../../../include/SolarUI_com.h"
#include "../../../include/SolarUI_exp.h"

#ifdef __cplusplus
extern "C" {
#endif


// **********************************************
// *              VIDEO STYLE                   *
// **********************************************

typedef struct
{
    solColour Tint;

    float Opacity;

} solVideoStyle;


// **********************************************
// *              VIDEO STATE                   *
// **********************************************

typedef enum
{
    SOL_VIDEO_STOPPED = 0,
    SOL_VIDEO_PLAYING,
    SOL_VIDEO_PAUSED

} solVideoState;


// **********************************************
// *              VIDEO STRUCT                  *
// **********************************************

typedef struct
{
    solElement Element;

    const char* FilePath;

    void* MediaHandle;

    unsigned int TextureID;

    solVideoState State;

    bool Looping;

    float Volume;

    solVideoStyle Style;

} solVideo;


// **********************************************
// *              FUNCTIONS                     *
// **********************************************

SOLARUI_API void solVideo_Init(
    solVideo* video,
    const char* filePath,
    float x,
    float y,
    float width,
    float height
);


SOLARUI_API void solVideo_Draw(
    solVideo* video
);


SOLARUI_API void solVideo_Load(
    solVideo* video
);


SOLARUI_API void solVideo_Play(
    solVideo* video
);


SOLARUI_API void solVideo_Update(
    solVideo* video
);


SOLARUI_API void solVideo_Pause(
    solVideo* video
);


SOLARUI_API void solVideo_Stop(
    solVideo* video
);


SOLARUI_API void solVideo_SetLoop(
    solVideo* video,
    bool loop
);


SOLARUI_API void solVideo_SetVolume(
    solVideo* video,
    float volume
);


SOLARUI_API void solVideo_SetStyle(
    solVideo* video,
    solVideoStyle style
);


SOLARUI_API void solVideo_Unload(
    solVideo* video
);


#ifdef __cplusplus
}
#endif

#endif