#include "Car.h"
#include <utility>
#include <stdexcept>
#include <map>

namespace {

	const std::map<int, std::pair<int, int>> RANGES =
	{
		{ -1, { 0, 20 } },
		{ 0, { 0, 150 } },
		{ 1, { 0, 30 } },
		{ 2, { 20, 50 } },
		{ 3, { 30, 60 } },
		{ 4, { 40, 90 } },
		{ 5, { 50, 150 } }
	};

	Direction SetDirection(int gear, int speed, Direction currentDirection)
	{
		Direction direction = currentDirection;
		if (speed == 0)
		{
			direction = Direction::Stand;
		}
		else if (gear == -1 && speed > 0)
		{
			direction = Direction::Backward;
		}
		else if (gear > 0 && speed > 0)
		{
			direction = Direction::Forward;
		}
		return direction;
	}

	void CheckSpeedChanging(int currentSpeed, int newSpeed, int gear)
	{
		if (newSpeed < 0 || newSpeed > 150)
		{
			throw std::logic_error("Incorrect value of speed!");
		}

		if (gear == 0 && newSpeed > currentSpeed)
		{
			throw std::logic_error("Trying to increase speed while gear is neutral!");
		}
	}

	bool MatchingGearWithSpeed(int speed, int gear)
	{
		std::pair<int, int> rangeOfSpeed = GetSpeedRangeOfGear(gear);
		if (speed >= rangeOfSpeed.first && speed <= rangeOfSpeed.second)
		{
			return true;
		}
		return false;
	}

	void CheckGearSwitching(bool isOn, int currentGear, int newGear, int speed, Direction direction)
	{
		if (!isOn && newGear != 0)
		{
			throw std::logic_error("Trying to switch gear while engine is off!");
		}

		if (newGear < -1 || newGear > 5)
		{
			throw std::out_of_range("Incorrect value of gear!");
		}

		if (newGear == -1 && direction == Direction::Forward)
		{
			throw std::logic_error("Trying to switch into rear gear while moving forward!");
		}
		// TODO: >= 1 передачи
		if (newGear > 0 && direction == Direction::Backward)
		{
			throw std::logic_error("Trying to switch into forward gear while moving backward!");
		}

		if (currentGear == 0 && newGear == -1 && speed > 0)
		{
			throw std::logic_error("Trying to switch into backward gear while car is moving");
		}
	}

	std::pair<int, int> GetSpeedRangeOfGear(int gear)
	{
		std::pair<int, int> range = RANGES.at(gear);
		return range;
		// TODO: switch to map
	}
}

bool Car::IsTurnedOn() const
{
	return m_isOn;
}

Direction Car::GetDirection() const
{
	return m_direction;
}

int Car::GetGear() const
{
	return m_gear;
}

int Car::GetSpeed() const
{
	return m_speed;
}

bool Car::TurnOnEngine()
{
	m_isOn = true;
	return true;
}

bool Car::TurnOffEngine()
{
	if (m_gear != 0 || m_speed != 0)
	{
		return false;
	}
	m_isOn = false;
	return true;
}

bool Car::SetGear(int gear)
{
	CheckGearSwitching(m_isOn, m_gear, gear, m_speed, m_direction);

	bool isMatching = MatchingGearWithSpeed(m_speed, gear);

	if (isMatching)
	{
		m_gear = gear;
	}
	else
	{
		throw std::out_of_range("This gear is not matching for acceptable range current speed!");
	}
	return isMatching;
}


bool Car::SetSpeed(int speed)
{
	CheckSpeedChanging(m_speed, speed, m_gear);

	bool isMatching = MatchingGearWithSpeed(speed, m_gear);
	
	if (isMatching)
	{
		m_speed = speed;
		m_direction = SetDirection(m_gear, m_speed, m_direction);
	}
	else
	{
		throw std::out_of_range("This speed isn't matching for acceptable speed range for current gear!");
	}

	return isMatching;
}