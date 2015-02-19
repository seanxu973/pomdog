﻿//
//  Copyright (C) 2013-2015 mogemimi.
//  Distributed under the MIT License. See LICENSE.md or
//  http://enginetrouble.net/pomdog/license for details.
//

#ifndef POMDOG_BUTTONSTATE_092E7B2B_0243_46C2_B46E_43B330ED0F44_HPP
#define POMDOG_BUTTONSTATE_092E7B2B_0243_46C2_B46E_43B330ED0F44_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <cstdint>

namespace Pomdog {

///@~Japanese
/// @brief ボタンが押されているかどうかの状態を表します。
enum class ButtonState: bool {
	///@~Japanese
	/// @brief ボタンが離されている状態を表します。
	Released = false,

	///@~Japanese
	/// @brief ボタンが押されている状態を表します。
	Pressed = true
};

}// namespace Pomdog

#endif // !defined(POMDOG_BUTTONSTATE_092E7B2B_0243_46C2_B46E_43B330ED0F44_HPP)
