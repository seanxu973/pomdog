// Copyright (c) 2013-2020 mogemimi. Distributed under the MIT license.

#include "AudioEngineAL.hpp"
#include "ErrorCheckerAL.hpp"
#include "Pomdog/Utility/Assert.hpp"

namespace Pomdog::Detail::SoundSystem::OpenAL {

AudioEngineAL::AudioEngineAL()
{
}

AudioEngineAL::~AudioEngineAL() = default;

float AudioEngineAL::GetMainVolume() const
{
    float volume = 0.0f;
    alGetListenerf(AL_GAIN, &volume);
    return volume;
}

void AudioEngineAL::SetMainVolume(float volume)
{
    POMDOG_ASSERT(volume >= 0.0f);
    alListenerf(AL_GAIN, volume);
}

} // namespace Pomdog::Detail::SoundSystem::OpenAL
