#ifndef _SOUNDOBJECT_H_
#define _SOUNDOBJECT_H_

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <phonon/MediaObject>

#define USE_PHONON
//#define USE_QSOUND


class SoundObject : public QObject
{
    Q_OBJECT
public:
    SoundObject(char* src);
    virtual ~SoundObject();
public slots:
    void play(void);
private:
    QString m_src;
#ifdef USE_PHONON
    Phonon::MediaObject *m_phononMedia;
#endif
};

#endif /* _SOUNDOBJECT_H_ */
