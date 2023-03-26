// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Stabilizer.hpp"

#include "core/Constants.hpp"

Stabilizer::Stabilizer()
	: m_PitchStabilizer(0.5f, 0.5f, 0.5f), m_RollStabilizer(0.5f, 0.5f, 0.5f), m_YawStabilizer(0.5f, 0.5f, 0.5f)
{
}

void Stabilizer::initialize()
{
	Serial.println("Initializing the Stabilizer.");

	// Initialize the sensor.
	m_Sensor.initialize();

	Serial.println("Stabilizer is initialized.");
}

void Stabilizer::update()
{
	m_Sensor.readData();
}

Vec3 Stabilizer::computeOutputs(float thrust, float pitch, float roll, float yaw)
{
	const auto angles = m_Sensor.getAcceleration();
	const auto rotationRate = m_Sensor.getGyration();

	const auto outputPitch = m_PitchStabilizer.calculate(angles.m_Pitch, pitch);
	const auto outputYaw = m_YawStabilizer.calculate(angles.m_Yaw, yaw);
	const auto outputRoll = m_RollStabilizer.calculate(angles.m_Roll, roll);

	return Vec3(outputPitch, outputYaw, outputRoll);
}