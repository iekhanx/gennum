/*
 * ========================================================================
 *
 *       Filename:  InputSoundFile.cpp
 *
 *    Description:  InputSoundFile class Implementation 
 *
 *        Version:  1.0
 *        Created:  27/01/22 13:48:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//#include <SoundFileReader.hpp>
//#include <SoundFileFactory.hpp>
//#include <InputStream.hpp>
//#include <FileInputStream.hpp>
//#include <MemoryInputStream.hpp>

#include "InputSoundFile.hpp"
#include "Err.hpp"
#include <iostream>
#include <algorithm>
#include <cstdint>

namespace xwc
{
////////////////////////////////////////////////////////////
InputSoundFile::InputSoundFile() :
m_reader      (nullptr),
m_stream      (nullptr),
m_streamOwned (false),
m_sampleOffset   (0),
m_sampleCount (0),
m_channelCount(0),
m_sampleRate  (0)
{
}


////////////////////////////////////////////////////////////
InputSoundFile::~InputSoundFile()
{
    // Close the file in case it was open
    close();
}


////////////////////////////////////////////////////////////
bool InputSoundFile::openFromFile(const std::string& filename)
{
    // If the file is already open, first close it
    close();

    // Find a suitable reader for the file type
    m_reader = SoundFileFactory::createReaderFromFilename(filename);
    if (!m_reader)
        return false;

    // Wrap the file into a stream
    auto* file = new FileInputStream;
    m_stream = file;
    m_streamOwned = true;

    // Open it
    if (!file->open(filename))
    {
        close();
        return false;
    }

    // Pass the stream to the reader
    SoundFileReader::Info info;
    if (!m_reader->open(*file, info))
    {
        close();
        return false;
    }

    // Retrieve the attributes of the open sound file
    m_sampleCount = info.sampleCount;
    m_channelCount = info.channelCount;
    m_sampleRate = info.sampleRate;

    return true;
}


////////////////////////////////////////////////////////////
bool InputSoundFile::openFromMemory(const void* data, std::size_t sizeInBytes)
{
    // If the file is already open, first close it
    close();

    // Find a suitable reader for the file type
    m_reader = SoundFileFactory::createReaderFromMemory(data, sizeInBytes);
    if (!m_reader)
        return false;

    // Wrap the memory file into a stream
    auto* memory = new MemoryInputStream;
    m_stream = memory;
    m_streamOwned = true;

    // Open it
    memory->open(data, sizeInBytes);

    // Pass the stream to the reader
    SoundFileReader::Info info;
    if (!m_reader->open(*memory, info))
    {
        close();
        return false;
    }

    // Retrieve the attributes of the open sound file
    m_sampleCount = info.sampleCount;
    m_channelCount = info.channelCount;
    m_sampleRate = info.sampleRate;

    return true;
}


////////////////////////////////////////////////////////////
bool InputSoundFile::openFromStream(InputStream& stream)
{
    // If the file is already open, first close it
    close();

    // Find a suitable reader for the file type
    m_reader = SoundFileFactory::createReaderFromStream(stream);
    if (!m_reader)
        return false;

    // store the stream
    m_stream = &stream;
    m_streamOwned = false;

    // Don't forget to reset the stream to its beginning before re-opening it
    if (stream.seek(0) != 0)
    {
        err() << "Failed to open sound file from stream (cannot restart stream)" << std::endl;
        return false;
    }

    // Pass the stream to the reader
    SoundFileReader::Info info;
    if (!m_reader->open(stream, info))
    {
        close();
        return false;
    }

    // Retrieve the attributes of the open sound file
    m_sampleCount = info.sampleCount;
    m_channelCount = info.channelCount;
    m_sampleRate = info.sampleRate;

    return true;
}


////////////////////////////////////////////////////////////
uint64_t InputSoundFile::getSampleCount() const
{
    return m_sampleCount;
}


////////////////////////////////////////////////////////////
unsigned int InputSoundFile::getChannelCount() const
{
    return m_channelCount;
}


////////////////////////////////////////////////////////////
unsigned int InputSoundFile::getSampleRate() const
{
    return m_sampleRate;
}


////////////////////////////////////////////////////////////
Time InputSoundFile::getDuration() const
{
    // Make sure we don't divide by 0
    if (m_channelCount == 0 || m_sampleRate == 0)
        return Time::Zero;

    return seconds(static_cast<float>(m_sampleCount) / static_cast<float>(m_channelCount) / static_cast<float>(m_sampleRate));
}


////////////////////////////////////////////////////////////
Time InputSoundFile::getTimeOffset() const
{
    // Make sure we don't divide by 0
    if (m_channelCount == 0 || m_sampleRate == 0)
        return Time::Zero;

    return seconds(static_cast<float>(m_sampleOffset) / static_cast<float>(m_channelCount) / static_cast<float>(m_sampleRate));
}


////////////////////////////////////////////////////////////
uint64_t InputSoundFile::getSampleOffset() const
{
    return m_sampleOffset;
}


////////////////////////////////////////////////////////////
void InputSoundFile::seek(uint64_t sampleOffset)
{
    if (m_reader && m_channelCount != 0)
    {
        // The reader handles an overrun gracefully, but we
        // pre-check to keep our known position consistent
        m_sampleOffset = std::min(sampleOffset / m_channelCount * m_channelCount, m_sampleCount);
        m_reader->seek(m_sampleOffset);
    }
}


////////////////////////////////////////////////////////////
void InputSoundFile::seek(Time timeOffset)
{
    seek(static_cast<uint64_t>(timeOffset.asSeconds() * static_cast<float>(m_sampleRate)) * m_channelCount);
}


////////////////////////////////////////////////////////////
uint64_t InputSoundFile::read(int16_t* samples, uint64_t maxCount)
{
    uint64_t readSamples = 0;
    if (m_reader && samples && maxCount)
        readSamples = m_reader->read(samples, maxCount);
    m_sampleOffset += readSamples;
    return readSamples;
}


////////////////////////////////////////////////////////////
void InputSoundFile::close()
{
    // Destroy the reader
    delete m_reader;
    m_reader = nullptr;

    // Destroy the stream if we own it
    if (m_streamOwned)
    {
        delete m_stream;
        m_streamOwned = false;
    }
    m_stream = nullptr;
    m_sampleOffset = 0;

    // Reset the sound file attributes
    m_sampleCount = 0;
    m_channelCount = 0;
    m_sampleRate = 0;
}

} // namespace xwc

