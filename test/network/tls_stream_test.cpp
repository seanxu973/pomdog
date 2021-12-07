// Copyright mogemimi. Distributed under the MIT license.

#include "pomdog/network/tls_stream.hpp"
#include "Executor.hpp"
#include "pomdog/application/game_clock.hpp"
#include "pomdog/network/array_view.hpp"
#include "pomdog/network/io_service.hpp"
#include "pomdog/signals/connection_list.hpp"
#include "pomdog/utility/errors.hpp"
#include "pomdog/utility/string_helper.hpp"
#include "catch_amalgamated.hpp"
#include <cstring>
#include <sstream>
#include <thread>
#include <unordered_map>

using namespace Pomdog;

TEST_CASE("TLS connection for HTTPS client", "[Network]")
{
    Executor executor;
    ConnectionList conn;

    const auto hostName = "www.google.com";
    const auto path = "/";
    const auto port = "443";

    std::unordered_map<std::string, std::string> fields;
    fields.emplace("Host", hostName);
    fields.emplace("Connection", "close");

    auto [streamResult, err] = TLSStream::Connect(executor.GetService(), std::string{hostName} + ":" + port);
    if (err != nullptr) {
        WARN(err->ToString());
        return;
    }

    // NOTE: According to C++ Standard Core issue 2313, structured bindings are
    // never capturable because they are never names of variables. The following
    // code is a workaround that makes structured bindings captuable.
    auto stream = std::move(streamResult);

    stream.SetTimeout(std::chrono::seconds{5});

    conn += stream.OnConnected([&](const std::unique_ptr<Error>& err) {
        if (err != nullptr) {
            WARN("Unable to connect server");
            executor.ExitLoop();
            return;
        }

        REQUIRE(stream.IsConnected());

        // NOTE: Write the GET request
        std::ostringstream ss;
        ss << "GET " << path;
        ss << " HTTP/1.1"
           << "\n";
        for (const auto& field : fields) {
            ss << field.first << ": " << field.second << "\n";
        }
        ss << "\n";

        std::string header = ss.str();

        auto writeErr = stream.Write(ArrayView<char const>{header.data(), header.size()}.ViewAs<std::uint8_t const>());
        REQUIRE(writeErr == nullptr);
    });
    conn += stream.OnDisconnect([&] {
        REQUIRE_FALSE(stream.IsConnected());
    });
    conn += stream.OnRead([&](const ArrayView<uint8_t>& view, const std::unique_ptr<Error>& err) {
        if (err != nullptr) {
            WARN("Unable to connect server");
            stream.Disconnect();
            executor.ExitLoop();
            return;
        }

        std::string_view text(reinterpret_cast<const char*>(view.GetData()), view.GetSize());

        constexpr auto html = "HTTP/1.1 200 OK\r\n";
        REQUIRE(StringHelper::HasPrefix(text, html));

        REQUIRE(stream.IsConnected());
        stream.Disconnect();
        REQUIRE_FALSE(stream.IsConnected());

        executor.ExitLoop();
    });

    executor.RunLoop();

    REQUIRE_FALSE(stream.IsConnected());
}