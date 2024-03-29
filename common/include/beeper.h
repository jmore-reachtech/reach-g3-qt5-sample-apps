// Copyright 2020 Reach Technology

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#ifndef BEEPER_H
#define BEEPER_H

#include <QObject>
#include <qqml.h>

#include <alsa/asoundlib.h>
#include <alsa/control.h>

class Beeper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString soundFile READ soundFile WRITE setSoundFile NOTIFY soundFileChanged)
    QML_ELEMENT

public:
    explicit Beeper(QObject *parent = nullptr);
    ~Beeper();

    QString soundFile(void);

signals:
    void soundFileChanged();

public slots:
    void beep(void);
    void setSoundFile(const QString &path);
    void setVolume(int);

private:
    snd_pcm_t           *m_playbackHandle;
    uint8_t             *m_wavePtr;
    snd_pcm_sframes_t   m_waveFrames;
    QString             currentSoundFile;
};

#endif // BEEPER_H
