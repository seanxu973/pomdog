﻿//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#include <iutest/gtest/iutest_switch.hpp>
#include <Pomdog/Logging/LogChannel.hpp>
#include <Pomdog/Logging/LogEntry.hpp>
#include <Pomdog/Event/EventConnection.hpp>
#include <Pomdog/Event/ScopedConnection.hpp>

using Pomdog::LogChannel;
using Pomdog::LogEntry;
using Pomdog::LoggingLevel;
using Pomdog::ScopedConnection;

TEST(LogChannel, LoggingLevel)
{
	static_assert(LoggingLevel::Critical < LoggingLevel::Warning, "TEST(LogChannel, LoggingLevel)");
	static_assert(LoggingLevel::Critical < LoggingLevel::Info, "TEST(LogChannel, LoggingLevel)");
	static_assert(LoggingLevel::Critical < LoggingLevel::Verbose, "TEST(LogChannel, LoggingLevel)");
	static_assert(LoggingLevel::Critical < LoggingLevel::Internal, "TEST(LogChannel, LoggingLevel)");
	static_assert(LoggingLevel::Warning < LoggingLevel::Info, "TEST(LogChannel, LoggingLevel)");
	static_assert(LoggingLevel::Warning < LoggingLevel::Verbose, "TEST(LogChannel, LoggingLevel)");
	static_assert(LoggingLevel::Warning < LoggingLevel::Internal, "TEST(LogChannel, LoggingLevel)");
	static_assert(LoggingLevel::Info < LoggingLevel::Verbose, "TEST(LogChannel, LoggingLevel)");
	static_assert(LoggingLevel::Info < LoggingLevel::Internal, "TEST(LogChannel, LoggingLevel)");
	static_assert(LoggingLevel::Verbose < LoggingLevel::Internal, "TEST(LogChannel, LoggingLevel)");
}

TEST(LogChannel, LogMessage)
{
	LogChannel channel("test");
	std::string message;
	
	channel.Connect([&message](Pomdog::LogEntry const& entry){
		message = entry.message;
	});
	
	channel.LogMessage("Chuck Norris can split the atom.", LoggingLevel::Critical);
	EXPECT_EQ(message, "Chuck Norris can split the atom.");
	
	channel.LogMessage("With his bare hands.", LoggingLevel::Critical);
	EXPECT_EQ(message, "With his bare hands.");
}

TEST(LogChannel, Disconnect)
{
	LogChannel channel("test");
	std::string message;
	
	auto connection = channel.Connect([&message](Pomdog::LogEntry const& entry){
		message = entry.message;
	});
	
	channel.LogMessage("Chuck Norris can split the atom.", LoggingLevel::Critical);
	EXPECT_EQ(message, "Chuck Norris can split the atom.");
	
	message.clear();
	connection.Disconnect();
	
	channel.LogMessage("With his bare hands.", LoggingLevel::Critical);
	EXPECT_TRUE(message.empty());
}

TEST(LogChannel, Connection)
{
	LogChannel channel("test");
	std::string message;
	
	auto connectionA = channel.Connect([&message](Pomdog::LogEntry const& entry){
		message += "connection(A): ";
		message += entry.message;
		message += ", ";
	});
	
	channel.Connect([&message](Pomdog::LogEntry const& entry){
		message += "connection(B): ";
		message += entry.message;
	});
	
	channel.LogMessage("Hi", LoggingLevel::Critical);
	EXPECT_EQ(message, "connection(A): Hi, connection(B): Hi");
	
	message.clear();
	connectionA.Disconnect();
	
	channel.LogMessage("A disconnect", LoggingLevel::Critical);
	EXPECT_EQ(message, "connection(B): A disconnect");
}

TEST(LogChannel, GetName)
{
	{
		LogChannel channel("test");
		EXPECT_EQ("test", channel.GetName());
	}
	{
		LogChannel channel("Chuck Norris");
		EXPECT_EQ("Chuck Norris", channel.GetName());
	}
}

TEST(LogChannel, SetLoggingLevel)
{
	LogChannel channel("test");
	
	channel.SetLevel(LoggingLevel::Critical);
	EXPECT_EQ(channel.GetLevel(), LoggingLevel::Critical);
	
	channel.SetLevel(LoggingLevel::Warning);
	EXPECT_EQ(channel.GetLevel(), LoggingLevel::Warning);
	
	channel.SetLevel(LoggingLevel::Info);
	EXPECT_EQ(channel.GetLevel(), LoggingLevel::Info);
	
	channel.SetLevel(LoggingLevel::Verbose);
	EXPECT_EQ(channel.GetLevel(), LoggingLevel::Verbose);
	
	channel.SetLevel(LoggingLevel::Internal);
	EXPECT_EQ(channel.GetLevel(), LoggingLevel::Internal);
}

TEST(LogChannel, VerbosityLevelThreshold)
{
	LogChannel channel("test");
	std::string message;
		
	channel.Connect([&message](Pomdog::LogEntry const& entry){
		message = entry.message;
	});
	
	constexpr auto facts = "Chuck Norris's keyboard has an F13 key";
	
	auto ResetMessageAndSendLog = [&](Pomdog::LoggingLevel verbosity){
		message.clear();
		channel.LogMessage(facts, verbosity);
	};
	
	channel.SetLevel(LoggingLevel::Critical);
	ResetMessageAndSendLog(LoggingLevel::Critical);
	EXPECT_EQ(message, facts);
	ResetMessageAndSendLog(LoggingLevel::Warning);
	EXPECT_TRUE(message.empty());
	ResetMessageAndSendLog(LoggingLevel::Info);
	EXPECT_TRUE(message.empty());
	ResetMessageAndSendLog(LoggingLevel::Verbose);
	EXPECT_TRUE(message.empty());
	ResetMessageAndSendLog(LoggingLevel::Internal);
	EXPECT_TRUE(message.empty());
	
	channel.SetLevel(LoggingLevel::Warning);
	ResetMessageAndSendLog(LoggingLevel::Critical);
	EXPECT_EQ(message, facts);
	ResetMessageAndSendLog(LoggingLevel::Warning);
	EXPECT_EQ(message, facts);
	ResetMessageAndSendLog(LoggingLevel::Info);
	EXPECT_TRUE(message.empty());
	ResetMessageAndSendLog(LoggingLevel::Verbose);
	EXPECT_TRUE(message.empty());
	ResetMessageAndSendLog(LoggingLevel::Internal);
	EXPECT_TRUE(message.empty());
	
	channel.SetLevel(LoggingLevel::Info);
	ResetMessageAndSendLog(LoggingLevel::Critical);
	EXPECT_EQ(message, facts);
	ResetMessageAndSendLog(LoggingLevel::Warning);
	EXPECT_EQ(message, facts);
	ResetMessageAndSendLog(LoggingLevel::Info);
	EXPECT_EQ(message, facts);
	ResetMessageAndSendLog(LoggingLevel::Verbose);
	EXPECT_TRUE(message.empty());
	ResetMessageAndSendLog(LoggingLevel::Internal);
	EXPECT_TRUE(message.empty());
	
	channel.SetLevel(LoggingLevel::Verbose);
	ResetMessageAndSendLog(LoggingLevel::Critical);
	EXPECT_EQ(message, facts);
	ResetMessageAndSendLog(LoggingLevel::Warning);
	EXPECT_EQ(message, facts);
	ResetMessageAndSendLog(LoggingLevel::Info);
	EXPECT_EQ(message, facts);
	ResetMessageAndSendLog(LoggingLevel::Verbose);
	EXPECT_EQ(message, facts);
	ResetMessageAndSendLog(LoggingLevel::Internal);
	EXPECT_TRUE(message.empty());
	
	channel.SetLevel(LoggingLevel::Internal);
	ResetMessageAndSendLog(LoggingLevel::Critical);
	EXPECT_EQ(message, facts);
	ResetMessageAndSendLog(LoggingLevel::Warning);
	EXPECT_EQ(message, facts);
	ResetMessageAndSendLog(LoggingLevel::Info);
	EXPECT_EQ(message, facts);
	ResetMessageAndSendLog(LoggingLevel::Verbose);
	EXPECT_EQ(message, facts);
	ResetMessageAndSendLog(LoggingLevel::Internal);
	EXPECT_EQ(message, facts);
}
