﻿//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_INPUTLAYOUT_B0E2CBE1_3C0D_4D11_8260_CF62EE25D392_HPP
#define POMDOG_INPUTLAYOUT_B0E2CBE1_3C0D_4D11_8260_CF62EE25D392_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include <memory>
#include <vector>
#include "../Config/Export.hpp"
#include "../Config/FundamentalTypes.hpp"
#include "../Utility/Noncopyable.hpp"
#include "detail/ForwardDeclarations.hpp"

namespace Pomdog {
namespace Details {
namespace RenderSystem {

class NativeInputLayout;

}// namespace RenderSystem
}// namespace Details

/// @addtogroup Framework
/// @{
/// @addtogroup Graphics
/// @{

///@~Japanese
/// @brief 入力レイアウトを記述します。
class POMDOG_EXPORT InputLayout: Noncopyable
{
public:
	InputLayout() = delete;
	InputLayout(InputLayout const&) = delete;
	InputLayout(InputLayout &&) = default;
	
	InputLayout(std::shared_ptr<GraphicsDevice> const& graphicsDevice,
		std::shared_ptr<EffectPass> const& effectPass);
	
	InputLayout(std::shared_ptr<GraphicsDevice> const& graphicsDevice,
		std::shared_ptr<EffectPass> const& effectPass,
		std::vector<VertexBufferBinding> const& vertexBindings);
	
	~InputLayout();

public:
	Details::RenderSystem::NativeInputLayout* GetNativeInputLayout();

private:
	std::unique_ptr<Details::RenderSystem::NativeInputLayout> nativeInputLayout;
};

/// @}
/// @}

}// namespace Pomdog

#endif // !defined(POMDOG_INPUTLAYOUT_B0E2CBE1_3C0D_4D11_8260_CF62EE25D392_HPP)
