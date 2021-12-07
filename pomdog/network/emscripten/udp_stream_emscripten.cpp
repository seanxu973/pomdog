// Copyright (c) 2013-2021 mogemimi. Distributed under the MIT license.

#include "pomdog/network/emscripten/udp_stream_emscripten.hpp"
#include "pomdog/network/array_view.hpp"
#include "pomdog/network/io_service.hpp"
#include "pomdog/utility/assert.hpp"

POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_BEGIN
#include <utility>
POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_END

namespace Pomdog::Detail {

UDPStreamEmscripten::UDPStreamEmscripten([[maybe_unused]] IOService* serviceIn)
{
}

UDPStreamEmscripten::~UDPStreamEmscripten()
{
}

std::unique_ptr<Error>
UDPStreamEmscripten::Connect(
    [[maybe_unused]] std::string_view host,
    [[maybe_unused]] std::string_view port,
    [[maybe_unused]] const Duration& connectTimeout)
{
    // FIXME: Not implemented yet.
    return Errors::New("not implemented yet");
}

std::unique_ptr<Error>
UDPStreamEmscripten::Listen(
    [[maybe_unused]] std::string_view host,
    [[maybe_unused]] std::string_view port)
{
    // FIXME: Not implemented yet.
    return Errors::New("not implemented yet");
}

void UDPStreamEmscripten::Close()
{
    // FIXME: Not implemented yet.
}

std::unique_ptr<Error>
UDPStreamEmscripten::Write([[maybe_unused]] const ArrayView<std::uint8_t const>& data)
{
    // FIXME: Not implemented yet.
    return Errors::New("not implemented yet");
}

std::unique_ptr<Error>
UDPStreamEmscripten::WriteTo(
    [[maybe_unused]] const ArrayView<std::uint8_t const>& data,
    [[maybe_unused]] std::string_view address)
{
    // FIXME: Not implemented yet.
    return Errors::New("not implemented yet");
}

} // namespace Pomdog::Detail