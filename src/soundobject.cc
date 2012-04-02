#include <iostream>
#include <QtCore/QCoreApplication>
#include <QtGui/QSound>
#include "soundobject.hh"

using namespace std;

SoundObject::SoundObject(char* src)
    : QObject(), m_src(src)
{
#ifdef USE_PHONON
#endif
}

SoundObject::~SoundObject()
{
#ifdef USE_PHONON
    delete m_phononMedia;
#endif
}

void SoundObject::play(void)
{
#ifdef USE_PHONON
    m_phononMedia = Phonon::createPlayer(Phonon::MusicCategory,
                                         Phonon::MediaSource(m_src));
    m_phononMedia->play();
#endif
#ifdef USE_QSOUND
    QSound::play(m_src);
#endif
}
