#include <QDebug>

#include "sound.h"
#include "beeper.h"

Beeper::Beeper(QObject *parent): QObject(parent), m_playbackHandle(nullptr), m_wavePtr(nullptr)
{
    /*Open sound card */
    int err;
    if ((err = snd_pcm_open(&m_playbackHandle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0)
    {
        qDebug("Can't open sound card default: %s\n", snd_strerror(err));
    }
    else
    {
        qDebug() << "Sound card is open";
    }
}

Beeper::~Beeper()
{
    qDebug() << "Closing sound card";
    snd_pcm_close(m_playbackHandle);

    if (m_wavePtr != nullptr)
    {
        free(m_wavePtr);
    }
}

QString Beeper::soundFile()
{
    return "";
}

void Beeper::setSoundFile(const QString &path)
{
    FILE *file = nullptr;
    struct wav_header header;
    int ret;

    qDebug() << "Opening sound file: " << path;

    memset(&header, 0, sizeof(struct wav_header));

    file = fopen(path.toUtf8().data(), "r");
    if (file == nullptr)
    {
        qDebug() << "Failed to open wav file: ";
        return;
    }

    if (m_wavePtr != nullptr)
    {
        free(m_wavePtr);
    }

    ret = fread(&header, 1, sizeof(wav_header), file);
    m_waveFrames = (header.data_size *8) / header.bits_per_sample;

    /*We only support a Signed 16 bit little endian, rate 44100 Hz, Mono */
    if ((header.sample_per_sec != HZ_44100) && (header.bits_per_sample != BITS_PER_SAMPLE_16) &&
        (header.channels != 2))
    {
        qDebug() << "Invalid wav file format, required format is: "
        "Signed 16 bit Little Endian, Rate 44100 Hz, Mono";
        return;
    }

    m_wavePtr = (uint8_t*) malloc(header.data_size);
    ret = fread(m_wavePtr, 1, header.data_size, file);
    if (ret != (int) header.data_size)
    {
        qDebug() << "Wav data read failed: expected " << header.data_size << " read " << ret;
    }

    /*Set the audio card's hardware parameters (sample rate, bit resolution, etc) */
    if ((ret = snd_pcm_set_params(m_playbackHandle,
            SND_PCM_FORMAT_S16,
            SND_PCM_ACCESS_RW_INTERLEAVED,
            CHAN_1,
            header.sample_per_sec,
            1,
            50000)) < 0)
    {
        qDebug("Can't set sound parameters: %s \n", snd_strerror(ret));
        return;
    }

    /*Prepare for first write */
    if ((ret = snd_pcm_prepare(m_playbackHandle)) < 0)
    {
        qDebug("Error preparing sound card: %s \n", snd_strerror(ret));
        return;
    }

    fclose(file);

    emit soundFileChanged();
}

void Beeper::beep()
{
    snd_pcm_sframes_t frames = 0;
    int ret = 0;

    qDebug("Beep - starting the sound file");

    if (m_wavePtr == nullptr)
    {
        return;
    }

    frames = snd_pcm_writei(m_playbackHandle, m_wavePtr, m_waveFrames);
    if (frames < 0)
    {
        qDebug("Error playing wave: %s \n", snd_strerror(frames));
        frames = snd_pcm_recover(m_playbackHandle, frames, 0);
    }

    /*Wait for playback to completely finish */
    snd_pcm_drain(m_playbackHandle);

    /*Prepare for next write */
    if ((ret = snd_pcm_prepare(m_playbackHandle)) < 0)
    {
        qDebug("Error preparing sound card: %s \n", snd_strerror(ret));
    }

    qDebug("Beep - end");

}
