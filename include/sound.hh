#ifndef _SOUND_H_
#define _SOUND_H_

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <phonon/MediaObject>
#include "soundobject.hh"

typedef enum _sound_level {
    HERE,
    NEAR,
    MIDDLE,
    FAR,
    VERYFAR,
    SOUNDLEVEL_CNT
} SoundLevel;

class Sound : public QObject
{
    Q_OBJECT
public:
    Sound();
    virtual ~Sound();

public slots:
    void basketballSound(SoundLevel soundLevel);

private:
    SoundObject *m_basketballSound[SOUNDLEVEL_CNT];
};

#endif /* _SOUND_H_ */
