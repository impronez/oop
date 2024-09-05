#define CATCH_CONFIG_MAIN
#include "../Car/Car.h"
#include "../../../../catch/catch.hpp"

SCENARIO("Engine on")
{
	Car car;
	WHEN("Engine on")
	{
		car.TurnOnEngine();
		THEN("Engine on")
		{
			REQUIRE(car.IsTurnedOn());
		}
	}
	// TODO: Тестировать отдельные функции в разных сценариях
}

SCENARIO("Engine off")
{
	Car car;
	WHEN("Engine off")
	{
		car.TurnOffEngine();
		THEN("Engine off")
		{
			REQUIRE(!car.IsTurnedOn());
		}
	}

	WHEN("Gear is not zero")
	{
		car.TurnOnEngine();
		car.SetGear(1);
		car.TurnOffEngine();
		THEN("Engine on")
		{
			REQUIRE(car.IsTurnedOn());
		}
	}

	WHEN("Speed is not zero")
	{
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(15);
		car.SetGear(0);
		car.TurnOffEngine();
		THEN("Engine on")
		{
			REQUIRE(car.IsTurnedOn());
		}
	}
}

SCENARIO("Changing gear")
{
	Car car;
	car.TurnOnEngine();
	WHEN("Set gear = 1")
	{
		car.SetGear(1);
		THEN("Gear is 1")
		{
			REQUIRE(car.GetGear() == 1);
		}
	}

	WHEN("Set gear = -1")
	{
		car.SetGear(-1);
		THEN("Gear is -1")
		{
			REQUIRE(car.GetGear() == -1);
		}
	}

	WHEN("Set neutral gear")
	{
		car.SetGear(0);
		THEN("Gear is neutral")
		{
			REQUIRE(car.GetGear() == 0);
		}
	}

	WHEN("Set gear = 2")
	{
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);
		THEN("Gear is 2")
		{
			REQUIRE(car.GetGear() == 2);
		}
	}

	WHEN("Set gear = 3")
	{
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(3);
		THEN("Gear is 3")
		{
			REQUIRE(car.GetGear() == 3);
		}
	}

	WHEN("Set gear = 4")
	{
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(3);
		car.SetSpeed(40);
		car.SetGear(4);
		THEN("Gear is 4")
		{
			REQUIRE(car.GetGear() == 4);
		}
	}

	WHEN("Set gear = 5")
	{
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(3);
		car.SetSpeed(50);
		car.SetGear(5);
		THEN("Gear is 5")
		{
			REQUIRE(car.GetGear() == 5);
		}
	}

	WHEN("Set neutral gear when moving backwards")
	{
		car.SetGear(-1);
		car.SetSpeed(10);
		car.SetGear(0);
		THEN("Gear is neutral")
		{
			REQUIRE(car.GetGear() == 0);
		}
	}

	// TODO: проверка на exception
	// TODO: тестировать все значения передачи
	
	WHEN("Set not acceptable gear")
	{
		car.SetGear(1);
		car.SetSpeed(20);
		REQUIRE_THROWS(car.SetGear(5));
	}

	WHEN("Set first gear when moving backwards")
	{
		car.SetGear(-1);
		car.SetSpeed(10);
		car.SetGear(0);
		REQUIRE_THROWS(car.SetGear(1));
	}
	
	WHEN("Set rear gear when moving forwards")
	{
		car.SetGear(1);
		car.SetSpeed(10);
		car.SetGear(0);
		REQUIRE_THROWS(car.SetGear(-1));
	}
	
}

SCENARIO("Changing speed")
{
	Car car;
	car.TurnOnEngine();
	WHEN("Starting")
	{
		car.SetGear(1);
		car.SetSpeed(10);
		THEN("Speed is 10")
		{
			REQUIRE(car.GetSpeed() == 10);
		}
	}

	GIVEN("Gear is 1")
	{
		car.SetGear(1);
		WHEN("Min speed")
		{
			car.SetSpeed(0);
			THEN("Speed is 0")
			{
				REQUIRE(car.GetSpeed() == 0);
			}
		}

		WHEN("Max speed")
		{
			car.SetSpeed(30);
			THEN("Speed is 30")
			{
				REQUIRE(car.GetSpeed() == 30);
			}
		}

		WHEN("Min speed - 1")
		{
			car.SetSpeed(0);
			REQUIRE_THROWS(car.SetSpeed(-1));
		}

		WHEN("Max speed + 1")
		{
			car.SetSpeed(30);
			REQUIRE_THROWS(car.SetSpeed(31));
			
		}
	}

	GIVEN("Gear is 2")
	{
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);
		WHEN("Min speed")
		{
			car.SetSpeed(20);
			THEN("Speed is 20")
			{
				REQUIRE(car.GetSpeed() == 20);
			}
		}

		WHEN("Max speed")
		{
			car.SetSpeed(50);
			THEN("Speed is 50")
			{
				REQUIRE(car.GetSpeed() == 50);
			}
		}

		WHEN("Min speed - 1")
		{
			car.SetSpeed(20);
			REQUIRE_THROWS(car.SetSpeed(19));
		}

		WHEN("Max speed + 1")
		{
			car.SetSpeed(50);
			REQUIRE_THROWS(car.SetSpeed(51));
		}
	}

	GIVEN("Gear is 3")
	{
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(3);
		WHEN("Min speed")
		{
			car.SetSpeed(30);
			THEN("Speed is 30")
			{
				REQUIRE(car.GetSpeed() == 30);
			}
		}

		WHEN("Max speed")
		{
			car.SetSpeed(60);
			THEN("Speed is 60")
			{
				REQUIRE(car.GetSpeed() == 60);
			}
		}

		WHEN("Min speed - 1")
		{
			car.SetSpeed(30);
			REQUIRE_THROWS(car.SetSpeed(29));
		}

		WHEN("Max speed + 1")
		{
			car.SetSpeed(60);
			REQUIRE_THROWS(car.SetSpeed(61));
		}
	}

	GIVEN("Gear is 4")
	{
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(3);
		car.SetSpeed(40);
		car.SetGear(4);
		WHEN("Min speed")
		{
			car.SetSpeed(40);
			THEN("Speed is 40")
			{
				REQUIRE(car.GetSpeed() == 40);
			}
		}

		WHEN("Max speed")
		{
			car.SetSpeed(90);
			THEN("Speed is 90")
			{
				REQUIRE(car.GetSpeed() == 90);
			}
		}

		WHEN("Min speed - 1")
		{
			car.SetSpeed(40);
			REQUIRE_THROWS(car.SetSpeed(39));
		}

		WHEN("Max speed + 1")
		{
			car.SetSpeed(90);
			REQUIRE_THROWS(car.SetSpeed(91));
		}
	}

	GIVEN("Gear is 5")
	{
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(3);
		car.SetSpeed(50);
		car.SetGear(5);
		WHEN("Min speed")
		{
			car.SetSpeed(50);
			THEN("Speed is 50")
			{
				REQUIRE(car.GetSpeed() == 50);
			}
		}

		WHEN("Max speed")
		{
			car.SetSpeed(150);
			THEN("Speed is 150")
			{
				REQUIRE(car.GetSpeed() == 150);
			}
		}

		WHEN("Min speed - 1")
		{
			car.SetSpeed(50);
			REQUIRE_THROWS(car.SetSpeed(49));
		}

		WHEN("Max speed + 1")
		{
			car.SetSpeed(150);
			REQUIRE_THROWS(car.SetSpeed(151));
		}
	}

	GIVEN("Gear is -1")
	{
		car.SetGear(-1);
		WHEN("Min speed")
		{
			car.SetSpeed(0);
			THEN("Speed is 0")
			{
				REQUIRE(car.GetSpeed() == 0);
			}
		}

		WHEN("Max speed")
		{
			car.SetSpeed(20);
			THEN("Speed is 20")
			{
				REQUIRE(car.GetSpeed() == 20);
			}
		}

		WHEN("Min speed - 1")
		{
			REQUIRE_THROWS(car.SetSpeed(-1));
		}

		WHEN("Max speed + 1")
		{
			REQUIRE_THROWS(car.SetSpeed(21));
		}
	}

	
	WHEN("Incorrect value of speed")
	{
		car.SetGear(1);
		REQUIRE_THROWS(car.SetSpeed(1000));
	}

	WHEN("Speed is not acceptable")
	{
		car.SetGear(1);
		REQUIRE_THROWS(car.SetSpeed(100));
	}
	// TODO: тестировать все пограничные значения скоростей и недопустимые
}

SCENARIO("Check direction of movement")
{
	Car car;
	car.TurnOnEngine();
	WHEN("Initially")
	{
		REQUIRE(car.GetDirection() == Direction::Stand);
	}

	WHEN("Forward movement")
	{
		car.SetGear(1);
		car.SetSpeed(10);
		THEN("Direction is forward")
		{
			REQUIRE(car.GetDirection() == Direction::Forward);
		}
	}

	WHEN("Backward movement")
	{
		car.SetGear(-1);
		car.SetSpeed(10);
		THEN("Direction is backward")
		{
			REQUIRE(car.GetDirection() == Direction::Backward);
		}
	}

	WHEN("Stopping")
	{
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(0);
		car.SetSpeed(0);
		THEN("Direction is standing still")
		{
			REQUIRE(car.GetDirection() == Direction::Stand);
		}
	}
}