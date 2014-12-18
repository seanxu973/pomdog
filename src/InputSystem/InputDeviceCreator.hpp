﻿//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_INPUTDEVICECREATOR_D5540F16_00DB_404F_BD2F_C24E6819474A_HPP
#define POMDOG_INPUTDEVICECREATOR_D5540F16_00DB_404F_BD2F_C24E6819474A_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include <memory>

namespace Pomdog {
namespace Details {
namespace InputSystem {

template <class T>
class InputDeviceCreator {
public:
	virtual ~InputDeviceCreator() = default;

	virtual std::shared_ptr<T> Create() = 0;
};

}// namespace InputSystem
}// namespace Details
}// namespace Pomdog

#endif // !defined(POMDOG_INPUTDEVICECREATOR_D5540F16_00DB_404F_BD2F_C24E6819474A_HPP)