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

#ifndef SOUND_H
#define SOUND_H

#include "stdint.h"

#define CHAN_1 1
#define HZ_44100 44100
#define BITS_PER_SAMPLE_16 16

// WAVE file header format
struct wav_header {
    /* RIFF descriptor */
    uint8_t     riff[4];            // RIFF string
    uint32_t    chunk_size;         // overall size of file in bytes
    uint8_t     wave[4];            // WAVE string
    /* fmt chunk */
    uint8_t     fmt[4];             // fmt string with trailing null char
    uint32_t    chunk_1_size;       // length of the format data
    uint16_t    format_type;        // format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
    uint16_t    channels;           // no.of channels
    uint32_t    sample_per_sec;     // sampling rate (blocks per second)
    uint32_t    bytes_per_sec;      // SampleRate * NumChannels * BitsPerSample/8
    uint16_t    block_align;        // NumChannels * BitsPerSample/8
    uint16_t    bits_per_sample;    // bits per sample, 8- 8bits, 16- 16 bits etc
    /* data chunk */
    uint8_t     data [4];           // DATA string
    uint32_t    data_size;          // NumSamples * NumChannels * BitsPerSample/8 - size of the next chunk that will be read
};

// For WAVE file loading
static const unsigned char RiffTag[4]	= { 'R', 'I', 'F', 'F' };
static const unsigned char WaveTag[4] = { 'W', 'A', 'V', 'E' };
static const unsigned char FmtTag[4] = { 'f', 'm', 't', ' ' };
static const unsigned char DataTag[4] = { 'd', 'a', 't', 'a' };

#endif // SOUND_H
