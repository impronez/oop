#pragma once
enum class Direction
{
	Forward, Backward, Stand
};

class Car
{
public: 
	bool IsTurnedOn() const; // Properties
	Direction GetDirection() const;
	int GetSpeed() const;
	int GetGear() const;

	bool TurnOnEngine(); // Actions
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
private:
	bool m_isOn = false;
	int m_speed = 0;
	int m_gear = 0;
	Direction m_direction = Direction::Stand;
};