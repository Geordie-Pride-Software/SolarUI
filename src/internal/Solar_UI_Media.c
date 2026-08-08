#include "Solar_UI_Media.h"


#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"


#define MINIAUDIO_IMPLEMENTATION
#include "../external/miniaudio.h"


#include "../external/libVLC/include/vlc.h"
#include "../external/libVLC/include/vlc/libvlc.h"



#include <stdlib.h>
#include <string.h>



#define SOL_MAX_MEDIA 1024



static solMedia MediaList[SOL_MAX_MEDIA];

static int MediaCount = 0;



static ma_engine AudioEngine;


static libvlc_instance_t* VLCInstance;



// **********************************************
// HELPERS
// **********************************************


/*
    Portable strdup — the caller's path may point at a
    temporary/stack buffer, so we own our own copy rather
    than storing the raw pointer.
*/
static char* solMedia_CopyPath(
    const char* path
)
{
    if(!path)
        return NULL;


    size_t length =
        strlen(path) + 1;


    char* copy =
        malloc(length);


    if(!copy)
        return NULL;


    memcpy(
        copy,
        path,
        length
    );


    return copy;
}



// **********************************************
// INITIALISATION
// **********************************************


void solMedia_Init(void)
{
    MediaCount = 0;


    memset(
        MediaList,
        0,
        sizeof(MediaList)
    );



    ma_engine_init(
        NULL,
        &AudioEngine
    );



    VLCInstance =
        libvlc_new(
            0,
            NULL
        );
}





void solMedia_Shutdown(void)
{

    for(int i = 0; i < MediaCount; i++)
    {
        solMedia_Unload(
            &MediaList[i]
        );
    }



    if(VLCInstance)
    {
        libvlc_release(
            VLCInstance
        );
    }



    ma_engine_uninit(
        &AudioEngine
    );

}




// **********************************************
// IMAGE
// **********************************************


solMedia* solMedia_LoadImage(
    const char* path
)
{

    if(!path)
        return NULL;


    if(MediaCount >= SOL_MAX_MEDIA)
        return NULL;



    solMedia* media =
        &MediaList[MediaCount++];



    media->Type =
        SOL_MEDIA_IMAGE;


    media->Path =
        solMedia_CopyPath(path);



    int width;
    int height;
    int channels;



    unsigned char* data =
        stbi_load(
            path,
            &width,
            &height,
            &channels,
            4
        );



    if(!data)
    {
        media->Loaded = false;

        return media;
    }



    /*
        Texture creation happens in
        the render bridge.

        Store raw data for now.
    */


    media->Handle =
        data;



    media->Loaded = true;



    return media;
}





// **********************************************
// AUDIO
// **********************************************


solMedia* solMedia_LoadAudio(
    const char* path
)
{

    if(!path)
        return NULL;


    if(MediaCount >= SOL_MAX_MEDIA)
        return NULL;



    solMedia* media =
        &MediaList[MediaCount++];


    media->Type =
        SOL_MEDIA_AUDIO;


    media->Path =
        solMedia_CopyPath(path);



    ma_sound* sound =
        malloc(
            sizeof(ma_sound)
        );


    if(!sound)
    {
        media->Loaded = false;

        return media;
    }



    ma_result result =
        ma_sound_init_from_file(
            &AudioEngine,
            path,
            0,
            NULL,
            NULL,
            sound
        );


    if(result != MA_SUCCESS)
    {
        free(sound);

        media->Handle = NULL;
        media->Loaded = false;

        return media;
    }



    media->Handle =
        sound;


    media->Loaded = true;



    return media;
}




void solMedia_PlayAudio(
    solMedia* media
)
{

    if(!media)
        return;



    ma_sound_start(
        media->Handle
    );

}



// **********************************************
// VIDEO
// **********************************************


solMedia* solMedia_LoadVideo(
    const char* path
)
{

    if(!path)
        return NULL;


    if(MediaCount >= SOL_MAX_MEDIA)
        return NULL;



    solMedia* media =
        &MediaList[MediaCount++];



    media->Type =
        SOL_MEDIA_VIDEO;


    media->Path =
        solMedia_CopyPath(path);



    libvlc_media_t* vlcMedia =
        libvlc_media_new_path(
            VLCInstance,
            path
        );


    if(!vlcMedia)
    {
        media->Handle = NULL;
        media->Loaded = false;

        return media;
    }



    libvlc_media_player_t* player =
        libvlc_media_player_new_from_media(
            vlcMedia
        );



    libvlc_media_release(
        vlcMedia
    );


    if(!player)
    {
        media->Handle = NULL;
        media->Loaded = false;

        return media;
    }



    media->Handle =
        player;


    media->Loaded = true;



    return media;

}





void solMedia_PlayVideo(
    solMedia* media
)
{
    if(!media)
        return;



    libvlc_media_player_play(
        media->Handle
    );

}





void solMedia_UpdateVideo(
    solMedia* media
)
{
    /*
        Frame callbacks will go here.

        libVLC will output frames into
        a buffer, then the render bridge
        uploads them as textures.
    */
}





// **********************************************
// CLEANUP
// **********************************************


void solMedia_Unload(
    solMedia* media
)
{

    if(!media)
        return;



    free(
        (void*)media->Path
    );

    media->Path = NULL;



    if(media->Handle)
    {

        if(media->Type == SOL_MEDIA_IMAGE)
        {
            stbi_image_free(
                media->Handle
            );
        }



        if(media->Type == SOL_MEDIA_AUDIO)
        {
            ma_sound_uninit(
                media->Handle
            );

            free(
                media->Handle
            );
        }



        if(media->Type == SOL_MEDIA_VIDEO)
        {
            libvlc_media_player_stop(
                media->Handle
            );


            libvlc_media_player_release(
                media->Handle
            );
        }


        media->Handle = NULL;

    }



    media->Loaded = false;

}