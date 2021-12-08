// Copyright mogemimi. Distributed under the MIT license.

#pragma once

#include "pomdog/basic/platform.hpp"

#if defined(POMDOG_PLATFORM_MACOSX) || defined(POMDOG_PLATFORM_APPLE_IOS)
#include "pomdog/platform/apple/time_source_apple.hpp"
#elif defined(POMDOG_PLATFORM_WIN32)
#include "pomdog/platform/win32/time_source_win32.hpp"
#elif defined(POMDOG_PLATFORM_LINUX) || defined(POMDOG_PLATFORM_ANDROID)
#include "pomdog/platform/linux/time_source_linux.hpp"
#elif defined(POMDOG_PLATFORM_EMSCRIPTEN)
#include "pomdog/platform/emscripten/time_source_emscripten.hpp"
#else
#error "Platform undefined or not supported."
#endif

namespace pomdog::detail {

#if defined(POMDOG_PLATFORM_MACOSX) || defined(POMDOG_PLATFORM_APPLE_IOS)
using TimeSource = detail::apple::TimeSourceApple;
#elif defined(POMDOG_PLATFORM_WIN32)
using TimeSource = detail::win32::TimeSourceWin32;
#elif defined(POMDOG_PLATFORM_LINUX) || defined(POMDOG_PLATFORM_ANDROID)
using TimeSource = detail::linux::TimeSourceLinux;
#elif defined(POMDOG_PLATFORM_EMSCRIPTEN)
using TimeSource = detail::emscripten::TimeSourceEmscripten;
#else
#error "Platform undefined or not supported."
#endif

} // namespace pomdog::detail
