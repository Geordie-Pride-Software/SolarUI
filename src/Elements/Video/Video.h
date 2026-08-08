#ifndef SOLARUI_VIDEO_H
#define SOLARUI_VIDEO_H

#include "../../../include/SolarUI_com.h"

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

void solVideo_Init(
    solVideo* video,
    const char* filePath,
    float x,
    float y,
    float width,
    float height
);


void solVideo_Draw(
    solVideo* video
);


void solVideo_Load(
    solVideo* video
);


void solVideo_Play(
    solVideo* video
);


void solVideo_Pause(
    solVideo* video
);


void solVideo_Stop(
    solVideo* video
);


void solVideo_SetLoop(
    solVideo* video,
    bool loop
);


void solVideo_SetVolume(
    solVideo* video,
    float volume
);


void solVideo_SetStyle(
    solVideo* video,
    solVideoStyle style
);


void solVideo_Unload(
    solVideo* video
);


#ifdef __cplusplus
}
#endif

#endif