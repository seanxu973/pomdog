// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#include "Pomdog/Content/AssetBuilders/PipelineStateBuilder.hpp"
#include "Pomdog/Content/detail/AssetLoaderContext.hpp"
#include "Pomdog/Graphics/GraphicsDevice.hpp"
#include "Pomdog/Graphics/PipelineState.hpp"
#include "Pomdog/Graphics/PipelineStateDescription.hpp"
#include "Pomdog/Graphics/Shader.hpp"
#include "Pomdog/Utility/Assert.hpp"
#include "Pomdog/Utility/Exception.hpp"
#include <utility>

namespace Pomdog {
namespace AssetBuilders {
//-----------------------------------------------------------------------
class Builder<PipelineState>::Impl final {
public:
    PipelineStateDescription description;
    Detail::AssetLoaderContext loaderContext;
    std::shared_ptr<GraphicsDevice> graphicsDevice;
    bool hasBlendState = false;
    bool hasRasterizerState = false;
    bool hasDepthStencilState = false;

public:
    std::shared_ptr<PipelineState> Load();
};
//-----------------------------------------------------------------------
std::shared_ptr<PipelineState> Builder<PipelineState>::Impl::Load()
{
    POMDOG_ASSERT(!description.InputLayout.InputElements.empty());

    if (!hasBlendState) {
        description.BlendState = BlendDescription::CreateDefault();
        hasBlendState = true;
    }

    if (!hasRasterizerState) {
        description.RasterizerState = RasterizerDescription::CreateDefault();
        hasRasterizerState = true;
    }

    if (!hasDepthStencilState) {
        description.DepthStencilState = DepthStencilDescription::CreateDefault();
        hasDepthStencilState = true;
    }

    auto pipelineState = std::make_shared<PipelineState>(graphicsDevice, description);
    return std::move(pipelineState);
}
//-----------------------------------------------------------------------
// explicit instantiations
template class Builder<PipelineState>;
//-----------------------------------------------------------------------
Builder<PipelineState>::Builder(Detail::AssetLoaderContext const& contextIn)
    : impl(std::make_unique<Impl>())
{
    POMDOG_ASSERT(impl);
    impl->loaderContext = contextIn;
    impl->graphicsDevice = contextIn.GraphicsDevice.lock();
    POMDOG_ASSERT(impl->graphicsDevice);
}
//-----------------------------------------------------------------------
Builder<PipelineState>::Builder(Builder<PipelineState> &&) = default;
Builder<PipelineState> & Builder<PipelineState>::operator=(Builder<PipelineState> &&) = default;
Builder<PipelineState>::~Builder() = default;
//-----------------------------------------------------------------------
Builder<PipelineState> & Builder<PipelineState>::SetVertexShader(
    std::unique_ptr<Shader> && vertexShader)
{
    POMDOG_ASSERT(impl);
    POMDOG_ASSERT(vertexShader);
    impl->description.VertexShader = std::move(vertexShader);
    return *this;
}
//-----------------------------------------------------------------------
Builder<PipelineState> & Builder<PipelineState>::SetPixelShader(
    std::unique_ptr<Shader> && pixelShader)
{
    POMDOG_ASSERT(impl);
    POMDOG_ASSERT(pixelShader);
    impl->description.PixelShader = std::move(pixelShader);
    return *this;
}
//-----------------------------------------------------------------------
Builder<PipelineState> & Builder<PipelineState>::SetInputLayout(
    InputLayoutDescription const& inputLayout)
{
    POMDOG_ASSERT(impl);
    POMDOG_ASSERT(!inputLayout.InputElements.empty());
    impl->description.InputLayout = inputLayout;
    return *this;
}
//-----------------------------------------------------------------------
Builder<PipelineState> & Builder<PipelineState>::SetInputLayout(
    InputLayoutDescription && inputLayout)
{
    POMDOG_ASSERT(impl);
    POMDOG_ASSERT(!inputLayout.InputElements.empty());
    impl->description.InputLayout = std::move(inputLayout);
    return *this;
}
//-----------------------------------------------------------------------
Builder<PipelineState> & Builder<PipelineState>::SetBlendState(
    BlendDescription const& blendState)
{
    POMDOG_ASSERT(impl);
    impl->description.BlendState = blendState;
    impl->hasBlendState = true;
    return *this;
}
//-----------------------------------------------------------------------
Builder<PipelineState> & Builder<PipelineState>::SetRasterizerState(
    RasterizerDescription const& rasterizerState)
{
    POMDOG_ASSERT(impl);
    impl->description.RasterizerState = rasterizerState;
    impl->hasRasterizerState = true;
    return *this;
}
//-----------------------------------------------------------------------
Builder<PipelineState> & Builder<PipelineState>::SetDepthStencilState(
    DepthStencilDescription const& depthStencilState)
{
    POMDOG_ASSERT(impl);
    impl->description.DepthStencilState = depthStencilState;
    impl->hasDepthStencilState = true;
    return *this;
}
//-----------------------------------------------------------------------
std::shared_ptr<PipelineState> Builder<PipelineState>::Build()
{
    POMDOG_ASSERT(impl);
    return impl->Load();
}
//-----------------------------------------------------------------------
} // namespace AssetBuilders
} // namespace Pomdog