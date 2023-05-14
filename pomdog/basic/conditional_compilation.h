// Copyright mogemimi. Distributed under the MIT license.

#pragma once

#if defined(_MSC_VER)
// NOTE: Visual C++
#define POMDOG_MSVC_SUPPRESS_WARNING_PUSH __pragma(warning(push))
#define POMDOG_MSVC_SUPPRESS_WARNING_POP __pragma(warning(pop))
#define POMDOG_MSVC_SUPPRESS_WARNING(w) __pragma(warning(disable \
                                                         : w))

#else
#define POMDOG_MSVC_SUPPRESS_WARNING_PUSH
#define POMDOG_MSVC_SUPPRESS_WARNING_POP
#define POMDOG_MSVC_SUPPRESS_WARNING(w)
#endif

#if defined(__clang__)
// NOTE: Clang
#define POMDOG_CLANG_PRAGMA_TO_STR(x) _Pragma(#x)
#define POMDOG_CLANG_SUPPRESS_WARNING_PUSH _Pragma("clang diagnostic push")
#define POMDOG_CLANG_SUPPRESS_WARNING_POP _Pragma("clang diagnostic pop")
#define POMDOG_CLANG_SUPPRESS_WARNING(w) POMDOG_CLANG_PRAGMA_TO_STR(clang diagnostic ignored w)
#else
#define POMDOG_CLANG_SUPPRESS_WARNING_PUSH
#define POMDOG_CLANG_SUPPRESS_WARNING_POP
#define POMDOG_CLANG_SUPPRESS_WARNING(w)
#endif

#if defined(__GNUC__) && !defined(__clang__)
// NOTE: GNU C compiler
#define POMDOG_GCC_PRAGMA_TO_STR(x) _Pragma(#x)
#define POMDOG_GCC_SUPPRESS_WARNING_PUSH _Pragma("GCC diagnostic push")
#define POMDOG_GCC_SUPPRESS_WARNING_POP _Pragma("GCC diagnostic pop")
#define POMDOG_GCC_SUPPRESS_WARNING(w) POMDOG_GCC_PRAGMA_TO_STR(GCC diagnostic ignored w)
#else
#define POMDOG_GCC_SUPPRESS_WARNING_PUSH
#define POMDOG_GCC_SUPPRESS_WARNING_POP
#define POMDOG_GCC_SUPPRESS_WARNING(w)
#endif

#define POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_BEGIN \
    POMDOG_CLANG_SUPPRESS_WARNING_PUSH \
    POMDOG_CLANG_SUPPRESS_WARNING("-Wdocumentation-unknown-command") \
    POMDOG_CLANG_SUPPRESS_WARNING("-Wunknown-warning-option") \
    POMDOG_CLANG_SUPPRESS_WARNING("-Wpadded") \
    POMDOG_CLANG_SUPPRESS_WARNING("-Wreserved-identifier") \
    POMDOG_CLANG_SUPPRESS_WARNING("-Wreserved-id-macro") \
    POMDOG_CLANG_SUPPRESS_WARNING("-Wweak-vtables") \
\
    POMDOG_GCC_SUPPRESS_WARNING_PUSH \
\
    POMDOG_MSVC_SUPPRESS_WARNING_PUSH \
    POMDOG_MSVC_SUPPRESS_WARNING(4242) \
    POMDOG_MSVC_SUPPRESS_WARNING(4265) \
    POMDOG_MSVC_SUPPRESS_WARNING(4324) \
    POMDOG_MSVC_SUPPRESS_WARNING(4355) \
    POMDOG_MSVC_SUPPRESS_WARNING(4365) \
    POMDOG_MSVC_SUPPRESS_WARNING(4514) \
    POMDOG_MSVC_SUPPRESS_WARNING(4668) \
    POMDOG_MSVC_SUPPRESS_WARNING(4625) \
    POMDOG_MSVC_SUPPRESS_WARNING(4626) \
    POMDOG_MSVC_SUPPRESS_WARNING(4710) \
    POMDOG_MSVC_SUPPRESS_WARNING(4711) \
    POMDOG_MSVC_SUPPRESS_WARNING(4820) \
    POMDOG_MSVC_SUPPRESS_WARNING(4986) \
    POMDOG_MSVC_SUPPRESS_WARNING(5026) \
    POMDOG_MSVC_SUPPRESS_WARNING(5027) \
    POMDOG_MSVC_SUPPRESS_WARNING(5039) \
    POMDOG_MSVC_SUPPRESS_WARNING(5204) \
    POMDOG_MSVC_SUPPRESS_WARNING(5219) \
    POMDOG_MSVC_SUPPRESS_WARNING(5220)

#define POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_END \
    POMDOG_CLANG_SUPPRESS_WARNING_POP \
    POMDOG_GCC_SUPPRESS_WARNING_POP \
    POMDOG_MSVC_SUPPRESS_WARNING_POP
