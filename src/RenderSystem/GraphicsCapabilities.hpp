﻿//
//  Copyright (C) 2013-2015 mogemimi.
//  Distributed under the MIT License. See LICENSE.md or
//  http://enginetrouble.net/pomdog/license for details.
//

#ifndef POMDOG_GRAPHICSCAPABILITIES_17FEAA5D_4BF2_4EEB_8D34_77B032B1534B_HPP
#define POMDOG_GRAPHICSCAPABILITIES_17FEAA5D_4BF2_4EEB_8D34_77B032B1534B_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <cstddef>

namespace Pomdog {
namespace Details {
namespace RenderSystem {

class GraphicsCapabilities {
public:
	std::size_t SamplerSlotCount;
};

}// namespace RenderSystems
}// namespace Details
}// namespace Pomdog

#endif // !defined(POMDOG_GRAPHICSCAPABILITIES_17FEAA5D_4BF2_4EEB_8D34_77B032B1534B_HPP)
