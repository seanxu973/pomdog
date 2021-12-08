// Copyright mogemimi. Distributed under the MIT license.

#pragma once

#include "pomdog/basic/conditional_compilation.hpp"
#include "pomdog/graphics/forward_declarations.hpp"
#include "pomdog/math/forward_declarations.hpp"

POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_BEGIN
#include <cstddef>
#include <memory>
#include <vector>
POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_END

namespace pomdog::detail {

class GraphicsCommandListImmediate;
struct GraphicsCapabilities;

class NativeGraphicsContext {
public:
    NativeGraphicsContext() = default;
    NativeGraphicsContext(const NativeGraphicsContext&) = delete;
    NativeGraphicsContext& operator=(const NativeGraphicsContext&) = delete;

    virtual ~NativeGraphicsContext();

    /// Retrieves the capabilities of a GraphicsContext.
    virtual GraphicsCapabilities GetCapabilities() const = 0;

    virtual void ExecuteCommandLists(
        const std::vector<std::shared_ptr<GraphicsCommandListImmediate>>& commandLists) = 0;

    virtual void Present() = 0;

    virtual void Draw(
        std::size_t vertexCount,
        std::size_t startVertexLocation) = 0;

    virtual void DrawIndexed(
        std::size_t indexCount,
        std::size_t startIndexLocation) = 0;

    virtual void DrawInstanced(
        std::size_t vertexCountPerInstance,
        std::size_t instanceCount,
        std::size_t startVertexLocation,
        std::size_t startInstanceLocation) = 0;

    virtual void DrawIndexedInstanced(
        std::size_t indexCountPerInstance,
        std::size_t instanceCount,
        std::size_t startIndexLocation,
        std::size_t startInstanceLocation) = 0;

    virtual void SetRenderPass(const RenderPass& renderPass) = 0;

    virtual void SetViewport(const Viewport& viewport) = 0;

    virtual void SetScissorRect(const Rectangle& scissorRect) = 0;

    virtual void SetBlendFactor(const Vector4& blendFactor) = 0;

    virtual void SetVertexBuffer(
        int index,
        const std::shared_ptr<VertexBuffer>& vertexBuffer,
        std::size_t offset) = 0;

    virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

    virtual void SetPipelineState(const std::shared_ptr<PipelineState>& pipelineState) = 0;

    virtual void SetConstantBuffer(
        int index,
        const std::shared_ptr<NativeBuffer>& constantBuffer,
        std::size_t offset,
        std::size_t sizeInBytes) = 0;

    virtual void SetSampler(int index, const std::shared_ptr<SamplerState>& sampler) = 0;

    virtual void SetTexture(int index) = 0;

    virtual void SetTexture(int index, const std::shared_ptr<Texture2D>& texture) = 0;

    virtual void SetTexture(int index, const std::shared_ptr<RenderTarget2D>& texture) = 0;
};

} // namespace pomdog::detail
