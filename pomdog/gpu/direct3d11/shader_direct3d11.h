// Copyright mogemimi. Distributed under the MIT license.

#pragma once

#include "pomdog/basic/conditional_compilation.h"
#include "pomdog/gpu/direct3d11/prerequisites_direct3d11.h"
#include "pomdog/gpu/shader.h"
#include "pomdog/memory/unsafe_ptr.h"
#include "pomdog/utility/errors.h"

POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_BEGIN
#include <wrl/client.h>
#include <cstdint>
#include <vector>
POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_END

namespace pomdog::gpu::detail {
class ShaderBytecode;
struct ShaderCompileOptions;
} // namespace pomdog::gpu::detail

namespace pomdog::gpu::detail::direct3d11 {

template <class NativeShaderType>
class ShaderDirect3D11 final : public Shader {
private:
    Microsoft::WRL::ComPtr<NativeShaderType> shader_;
    std::vector<std::uint8_t> codeBlob_;

public:
    [[nodiscard]] std::unique_ptr<Error>
    initialize(
        unsafe_ptr<ID3D11Device> device,
        const ShaderBytecode& shaderBytecode,
        const ShaderCompileOptions& compileOptions) noexcept;

    /// Gets the pointer of the native shader object.
    [[nodiscard]] Microsoft::WRL::ComPtr<NativeShaderType>
    getShader() const noexcept;

    /// Gets the pointer of the shader bytecode.
    [[nodiscard]] ShaderBytecode
    getShaderBytecode() const noexcept;
};

using VertexShaderDirect3D11 = ShaderDirect3D11<ID3D11VertexShader>;
using PixelShaderDirect3D11 = ShaderDirect3D11<ID3D11PixelShader>;

} // namespace pomdog::gpu::detail::direct3d11
