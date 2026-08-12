#ifndef SOLAR_UI_MEDIA_H
#define SOLAR_UI_MEDIA_H

#include <stdbool.h>
#include "SUI/SolarUI_com.h"


#ifdef __cplusplus
extern "C" {
#endif



// **********************************************
// *              MEDIA TYPES                   *
// **********************************************

typedef enum
{
    SOL_MEDIA_NONE = 0,

    SOL_MEDIA_IMAGE,
    SOL_MEDIA_AUDIO,
    SOL_MEDIA_VIDEO

} solMediaType;



typedef struct
{
    int id;

    solMediaType Type;

    const char* Path;


    bool Loaded;


    // Image texture / backend handle
    unsigned int TextureID;


    // Audio/video backend data
    void* Handle;


    // Video-only: whether playback should
    // restart automatically when it ends.
    bool Looping;


} solMedia;



// **********************************************
// *              SYSTEM                        *
// **********************************************

void solMedia_Init(void);

void solMedia_Shutdown(void);



// **********************************************
// *              IMAGE                         *
// **********************************************


solMedia* solMedia_LoadImage(
    const char* path
);



void solMedia_Unload(
    solMedia* media
);



// **********************************************
// *              AUDIO                         *
// **********************************************


solMedia* solMedia_LoadAudio(
    const char* path
);



void solMedia_PlayAudio(
    solMedia* media
);



// **********************************************
// *              VIDEO                         *
// **********************************************


solMedia* solMedia_LoadVideo(
    const char* path
);



void solMedia_PlayVideo(
    solMedia* media
);



void solMedia_PauseVideo(
    solMedia* media
);



void solMedia_StopVideo(
    solMedia* media
);



void solMedia_SetVideoLoop(
    solMedia* media,
    bool loop
);



void solMedia_SetVideoVolume(
    solMedia* media,
    float volume
);



void solMedia_UnloadVideo(
    solMedia* media
);



void solMedia_UpdateVideo(
    solMedia* media
);



#ifdef __cplusplus
}
#endif


#endif