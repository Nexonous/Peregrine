// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "core/IDataLink.hpp"

#include <cstddef>
#include <IBusBM.h>

/**
 * @brief FS-i6 input channel enum.
 * This contains all the supported input channels of the receiver.
 */
enum class FSi6InputChannel : uint8_t
{
	Throttle = 2,
	Pitch = 1,
	Roll = 0,
	Yaw = 3,

	Aux1 = 4, // This is used to switch between FlyModes.
	Aux2 = 5,

	Thrust = Throttle
};

constexpr auto g_ChannelMinimum = 1000;
constexpr auto g_ChannelMaximum = 2000;

/**
 * @brief FS-i6 6 channel radio data link class.
 * This class handles input for the FS-i6 controller using the iBus interface.
 *
 * This data link uses the RX2 pin (GPIO16).
 */
class FSi6DataLink final : public IDataLink
{
public:
	/**
	 * @brief Construct a new FSi6DataLink object.
	 */
	FSi6DataLink() = default;

	/**
	 * @brief On initialize method.
	 * This method is intended to be used to initialize the data link.
	 */
	void onInitialize() override;

	/**
	 * @brief On update method.
	 * This method is intended to be used to update the data link and to poll the latest information.
	 */
	void onUpdate() override;

	/**
	 * @brief On get thrust method.
	 * Return the required thrust.
	 *
	 * @return The thrust value.
	 */
	[[nodiscard]] float onGetThrust() override { return m_Throttle; }

	/**
	 * @brief On get pitch method.
	 * Required pitch value.
	 *
	 * @return The pitch value.
	 */
	[[nodiscard]] float onGetPitch() override { return m_Pitch; }

	/**
	 * @brief On get roll method.
	 * Required roll value.
	 *
	 * @return The roll value.
	 */
	[[nodiscard]] float onGetRoll() override { return m_Roll; }

	/**
	 * @brief On get yaw method.
	 * Return the required yaw value.
	 *
	 * @return The yaw value.
	 */
	[[nodiscard]] float onGetYaw() override { return m_Yaw; }

private:
	/**
	 * @brief Read data from the iBus interface.
	 * This returns the value transmitted by the receiver of a given channel.
	 *
	 * @param channel The channel to read.
	 * @param minimum The channel's minimum value.
	 * @param maximum The channel's maximum value.
	 * @param defaultValue The channel's default value. It's set to 0 by default.
	 * @return The incoming value.
	 */
	[[nodiscard]] int readChannel(FSi6InputChannel channel, int minimum, int maximum, int defaultValue = 0);

	/**
	 * @brief Read boolean data from the iBus interface.
	 * This returns teh boolean value transmitted by a swich (of the transmitter) by the receiver of a given channel.
	 *
	 * @param channel The channel to read.
	 * @param defaultValue The channel's default value. it's set to false by default.
	 * @return true If the switch is on.
	 * @return false If the switch is off.
	 */
	[[nodiscard]] bool readChannelBool(FSi6InputChannel channel, bool defaultValue = false);

private:
	IBusBM m_Connection;

	float m_Throttle = 0;
	float m_Pitch = 0;
	float m_Roll = 0;
	float m_Yaw = 0;
};