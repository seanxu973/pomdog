//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_EVENTHANDLER_13D11737_31C0_49AC_8442_3A1F0A7C7CD7_HPP
#define POMDOG_EVENTHANDLER_13D11737_31C0_49AC_8442_3A1F0A7C7CD7_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include <memory>
#include <functional>
#include "../Config/Export.hpp"
#include "detail/FowardDeclarations.hpp"

namespace Pomdog {

class POMDOG_EXPORT EventHandler
{
public:
	EventHandler();
	EventHandler(EventHandler const&) = delete;
	EventHandler(EventHandler &&) = default;
	EventHandler& operator=(EventHandler const&) = delete;
	EventHandler& operator=(EventHandler &&) = default;
	
	~EventHandler() = default;
	
	EventConnection Connect(std::function<void(Event const&)> const& slot);

	EventConnection Connect(std::function<void(Event const&)> && slot);

	void Trigger(std::shared_ptr<Event const> const& event);

private:
	std::shared_ptr<Details::EventInternal::EventSlotCollection> slots;
};

}// namespace Pomdog

#endif // !defined(POMDOG_EVENTHANDLER_13D11737_31C0_49AC_8442_3A1F0A7C7CD7_HPP)
