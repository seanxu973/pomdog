// Copyright (c) 2013-2020 mogemimi. Distributed under the MIT license.

#include "AudioHelper.hpp"
#include "Pomdog/Audio/AudioChannels.hpp"
#include "Pomdog/Utility/Assert.hpp"

namespace Pomdog::Detail::AudioHelper {

[[nodiscard]] std::size_t
GetSamples(std::size_t sizeInBytes, int bitsPerSample, AudioChannels channels) noexcept
{
    POMDOG_ASSERT(bitsPerSample >= 8);
    POMDOG_ASSERT(bitsPerSample == 8 || bitsPerSample == 16 || bitsPerSample == 24 || bitsPerSample == 32);

    static_assert(static_cast<int>(AudioChannels::Mono) == 1, "");
    static_assert(static_cast<int>(AudioChannels::Stereo) == 2, "");

    auto channelCount = static_cast<int>(channels);
    POMDOG_ASSERT(channelCount > 0);
    POMDOG_ASSERT(channelCount <= 2);

    auto divisior = (bitsPerSample / 8) * channelCount;
    POMDOG_ASSERT(divisior > 0);

    return sizeInBytes / divisior;
}

[[nodiscard]] Duration
GetSampleDuration(std::size_t samples, int sampleRate) noexcept
{
    POMDOG_ASSERT(sampleRate > 0);
    POMDOG_ASSERT(sampleRate >= 8000);
    POMDOG_ASSERT(sampleRate <= 48000);
    return std::chrono::seconds(samples / sampleRate);
}

} // namespace Pomdog::Detail::AudioHelper