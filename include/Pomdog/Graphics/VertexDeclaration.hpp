﻿//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_VERTEXDECLARATION_5FD2E1E3_E19B_4C29_BE93_D10685FCEB02_HPP
#define POMDOG_VERTEXDECLARATION_5FD2E1E3_E19B_4C29_BE93_D10685FCEB02_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include <cstdint>
#include <vector>
#include "../Config/Export.hpp"
#include "VertexElement.hpp"

namespace Pomdog {

/// @addtogroup Framework
/// @{
/// @addtogroup Graphics
/// @{

///@~Japanese 
/// @brief 頂点を定義します。
class POMDOG_EXPORT VertexDeclaration {
public:
	VertexDeclaration(std::initializer_list<VertexElement> vertexElements);

	explicit VertexDeclaration(std::vector<VertexElement> const& vertexElements);

	explicit VertexDeclaration(std::vector<VertexElement> && vertexElements);
	
	VertexDeclaration(VertexElement const* vertexElements, std::size_t elementCount);

	///@~Japanese
	/// @brief 頂点データ 1 つ分のサイズをバイト単位で取得します。
	/// @remarks 1 つの頂点の先頭から次の頂点までのバイト数です。
	/// @return 頂点データ 1 つ分のサイズ（バイト単位）を返却します。
	std::uint32_t StrideBytes() const;

	///@~Japanese
	/// @brief 頂点宣言の要素のリストを取得します。
	std::vector<VertexElement> const& VertexElements() const;

private:
	///@~Japanese
	/// @brief 頂点宣言の要素のリストです。
	std::vector<VertexElement> elements;

	///@~Japanese
	/// @brief 1 つの頂点の先頭から次の頂点までのバイト数です。
	std::uint32_t strideBytes;
};

/// @}
/// @}

}// namespace Pomdog

#endif // !defined(POMDOG_VERTEXDECLARATION_5FD2E1E3_E19B_4C29_BE93_D10685FCEB02_HPP)
