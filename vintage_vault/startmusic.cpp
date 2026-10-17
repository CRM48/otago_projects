#include "startmusic.h"

#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#endif

void startBackgroundMusic(const char* audioFile) {
#ifdef _WIN32
    PlaySoundA(audioFile, nullptr, SND_FILENAME | SND_ASYNC | SND_LOOP);
#endif
}

void stopBackgroundMusic() {
#ifdef _WIN32
    PlaySoundA(nullptr, nullptr, 0);
#endif
}