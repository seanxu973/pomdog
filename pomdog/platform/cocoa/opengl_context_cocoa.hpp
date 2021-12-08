// Copyright mogemimi. Distributed under the MIT license.

#pragma once

#include "pomdog/graphics/forward_declarations.hpp"
#include "pomdog/graphics/gl4/opengl_context.hpp"
#import <Cocoa/Cocoa.h>
#include <memory>

@class NSOpenGLContext;

namespace pomdog {
class Error;
} // namespace pomdog

namespace pomdog::detail::cocoa {

class OpenGLContextCocoa final : public gl4::OpenGLContext {
public:
    OpenGLContextCocoa() noexcept;
    OpenGLContextCocoa(const OpenGLContextCocoa&) = delete;
    OpenGLContextCocoa& operator=(const OpenGLContextCocoa&) = delete;

    ~OpenGLContextCocoa() noexcept override;

    [[nodiscard]] std::unique_ptr<Error>
    Initialize(const PresentationParameters& presentationParameters) noexcept;

    void MakeCurrent() override;

    void ClearCurrent() override;

    void SwapBuffers() override;

    void Lock() noexcept;

    void Unlock() noexcept;

    void SetView(NSView* view) noexcept;

    void SetView() noexcept;

    [[nodiscard]] NSOpenGLContext*
    GetNativeOpenGLContext() noexcept;

private:
    __strong NSOpenGLContext* openGLContext = nil;
};

} // namespace pomdog::detail::cocoa
