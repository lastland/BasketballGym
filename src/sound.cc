#include <string>
#include "sound.hh"

using namespace std;

#define SOUNDS_LOCATION "resources/sounds/"

Sound::Sound()
    : QObject()
{
    char srcs[][256] = {SOUNDS_LOCATION "basketball_here.wav",
                        SOUNDS_LOCATION "basketball_near.wav",
                        SOUNDS_LOCATION "basketball_middle.wav",
                        SOUNDS_LOCATION "basketball_far.wav",
                        SOUNDS_LOCATION "basketball_veryfar.wav"};
    for (int i = 0; i < SOUNDLEVEL_CNT; i++)
    {
        m_basketballSound[i] = new SoundObject(srcs[i]);
    }
}

Sound::~Sound()
{
    for (int i = 0; i < SOUNDLEVEL_CNT; i++)
    {
        delete m_basketballSound[i];
    }
}

void Sound::basketballSound(SoundLevel soundLevel)
{
    m_basketballSound[soundLevel]->play();
}
