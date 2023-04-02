// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "WiFiSystem.hpp"

#include "core/Logging.hpp"

#include <WiFi.h>

void WiFiSystem::initialize()
{
	PEREGRINE_PRINTLN("Initializing the WiFi system.");

	// If the required WiFi exists, attempt to connect.
	if (exists())
	{
		PEREGRINE_PRINT("Attempting to connect to the WiFi...");

		// Begin the wifi connection.
		WiFi.begin(g_SSID, g_Password);

		// Try to connect.
		uint8_t tries = 2 /* minutes */ * 60 /* seconds */ * 2 /* 500 ms */;
		while (WiFi.status() != WL_CONNECTED && tries > 0)
		{
			delay(500);
			PEREGRINE_PRINT(".");

			--tries;
		}

		PEREGRINE_PRINTLN();
		if (tries == 0)
			PEREGRINE_PRINTLN("Failed to connect to the WiFi!");

		else
			PEREGRINE_PRINTLN("Successfully connected to the WiFi!");
	}
	else
	{
		PEREGRINE_PRINTLN("The required WiFi does not exist.");
	}
}

void WiFiSystem::update()
{
}

bool WiFiSystem::exists() const
{
	WiFi.mode(WIFI_STA);
	WiFi.disconnect();

	// Scan through all the networks.
	const auto networkCount = WiFi.scanNetworks();
	PEREGRINE_PRINT("Number of available WiFi networks: ");
	PEREGRINE_PRINTLN(networkCount);

	bool isAvailable = false;
	for (int i = 0; i < networkCount; i++)
	{
		const auto SSID = WiFi.SSID(i);

		PEREGRINE_PRINT("Available network: ");
		PEREGRINE_PRINTLN(SSID);

		// If the required WiFi exists, return true.
		if (WiFi.SSID(i) == g_SSID)
			isAvailable = true;
	}

	// Else return false.
	return isAvailable;
}