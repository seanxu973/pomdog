// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#include "Pomdog/Graphics/EffectReflection.hpp"
#include "../RenderSystem/NativeEffectReflection.hpp"
#include "../RenderSystem/NativeGraphicsDevice.hpp"
#include "Pomdog/Graphics/GraphicsDevice.hpp"
#include "Pomdog/Graphics/PipelineState.hpp"
#include "Pomdog/Utility/Assert.hpp"

namespace Pomdog {
//-----------------------------------------------------------------------
EffectReflection::EffectReflection(
    std::shared_ptr<GraphicsDevice> const& graphicsDevice,
    std::shared_ptr<PipelineState> const& pipelineState)
{
    POMDOG_ASSERT(graphicsDevice && graphicsDevice->NativeGraphicsDevice());
    POMDOG_ASSERT(pipelineState && pipelineState->NativePipelineState());

    auto nativeDevice = graphicsDevice->NativeGraphicsDevice();

    nativeEffectReflection = nativeDevice->CreateEffectReflection(
        *pipelineState->NativePipelineState());
}
//-----------------------------------------------------------------------
EffectReflection::~EffectReflection() = default;
//-----------------------------------------------------------------------
std::vector<EffectConstantDescription> EffectReflection::GetConstantBuffers() const
{
    POMDOG_ASSERT(nativeEffectReflection);
    return nativeEffectReflection->GetConstantBuffers();
}
//-----------------------------------------------------------------------
} // namespace Pomdog
