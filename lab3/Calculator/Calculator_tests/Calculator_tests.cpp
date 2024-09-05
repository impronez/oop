#define CATCH_CONFIG_MAIN
#include "../Calculator/Calculator.h"
#include "../Calculator/Function.h"
#include "../Calculator/Var.h"
#include "../Calculator/Menu.h"
#include "../../../../catch/catch.hpp"
#include <cmath>

TEST_CASE("Checking var")
{
	/*
	WHEN("Value is not initialisated")
	{
		Var var(name);
		double nan = NAN;
		THEN("Value is NaN")
		{
			REQUIRE(var.GetVar().second == nan);
		}
	}
	*/
	WHEN("Value is initialisated")
	{
		double value = 9.00;
		Var var(value);
		THEN("Value is 9.00")
		{
			REQUIRE(var.GetValue() == value);
		}
	}
}

TEST_CASE("Checking function")
{
	GIVEN("Checking constructor")
	{
		WHEN("Constructor with 1 param(double)")
		{
			Var x(9.0);
			Function func(&x);
			THEN("Value is 9.0")
			{
				REQUIRE(func.GetValue() == x.GetValue());
			}
		}
		WHEN("Constructor with 1 param(function)")
		{
			Var x(9.0);
			Function func1(&x);
			Function func2(&func1);
			THEN("Value is 9.0")
			{
				REQUIRE(func1.GetValue() == func2.GetValue());
			}
		}
		WHEN("Constructor with 2 param(double, double)")
		{
			Var x1(9.0);
			Var x2(2.0);
			Operation oper = Operation::Addition;
			Function func(&x1, &x2, oper);
			THEN("Value is 18.0")
			{
				REQUIRE(func.GetValue() == x1.GetValue() + x2.GetValue());
			}
		}
		WHEN("Constructor with 2 param(func, double)")
		{
			Var x(9.0);
			Var x2(10);
			Operation oper = Operation::Addition;
			Function func1(&x2);
			Function func2(&func1, &x, oper);
			THEN("Value is 9.0")
			{
				REQUIRE(func2.GetValue() == x2.GetValue() + x.GetValue());
			}
		}
		WHEN("Constructor with 2 param(func, func)")
		{
			Var x1(9.0);
			Var x2(3);
			Operation oper = Operation::Addition;
			Function func1(&x1);
			Function func2(&x2);
			Function func3(&func1, &func2, oper);
			THEN("Value is 9.0")
			{
				REQUIRE(func3.GetValue() == func1.GetValue() + func2.GetValue());
			}
		}
	}

	GIVEN("Checking operations")
	{
		Var x(10), y(3);

		WHEN("Check addition")
		{
			Operation oper = Operation::Addition;
			Function func(&x, &y, oper);
			THEN("True")
			{
				REQUIRE(func.GetValue() == x.GetValue() + y.GetValue());
			}
		}
		WHEN("Check subtraction")
		{
			Operation oper = Operation::Subtraction;
			Function func(&y, &x, oper);
			THEN("True")
			{
				REQUIRE(func.GetValue() == y.GetValue() - x.GetValue());
			}
		}
		WHEN("Check multiplication")
		{
			Operation oper = Operation::Multiplication;
			Function func(&y, &x, oper);
			THEN("True")
			{
				REQUIRE(func.GetValue() == x.GetValue() * y.GetValue());
			}
		}
		WHEN("Check division")
		{
			Operation oper = Operation::Division;
			Function func(&x, &y, oper);
			THEN("True")
			{
				REQUIRE(func.GetValue() == x.GetValue() / y.GetValue());
			}
		}
	}

	GIVEN("Checking function with editing of variable")
	{
		Var x(5), y(5);
		WHEN("Function from 2 variables")
		{
			Operation oper = Operation::Multiplication;
			Function func(&x, &y, oper);
			THEN("True")
			{
				REQUIRE(func.GetValue() == (x.GetValue() * y.GetValue()));
			}
		}
		WHEN("Function from function")
		{
			Operation oper = Operation::Multiplication;
			Function func1(&x, &y, oper);
			Function func2(&func1);
			THEN("func1 == func2 == x*y")
			{
				REQUIRE(func1.GetValue() == func2.GetValue());
				REQUIRE(func1.GetValue() == x.GetValue() * y.GetValue());
			}
		}
		WHEN("var is not inited, then init")
		{
			Var x(5);
			Function func1(&x);
			Function func2(&func1);
			THEN("func1 == func2 == 5")
			{
				REQUIRE(func1.GetValue() == x.GetValue());
				REQUIRE(func1.GetValue() == func2.GetValue());
			}
		}
	}
}

SCENARIO("Checking calculator")
{
	Var x(10), y(5);
	Operation oper = Operation::Multiplication;
	Function func1(&x, &y, oper);
	Calculator calc;
	std::string name = "x";
	GIVEN("Adding variable")
	{
		WHEN("Check adding var")
		{
			THEN("True")
			{
				REQUIRE(calc.NewVar(name));
			}
		}
		WHEN("Var already exist")
		{
			calc.NewVar(name);
			THEN("Exception")
			{
				REQUIRE_THROWS(calc.NewVar(name));
			}
		}
		WHEN("Checking of setting value for exisiting variable")
		{
			calc.NewVar(name);
			std::string val = "10";
			THEN("True")
			{
				REQUIRE(calc.VarIdentification(name, val));
			}

		}
		WHEN("Add var with value")
		{
			std::string val = "10";
			THEN("True")
			{
				REQUIRE(calc.VarIdentification(name, val));
			}

		}
		WHEN("Add var with incorrect value")
		{
			std::string val = ".10";
			THEN("False")
			{
				REQUIRE(calc.VarIdentification(name, val));
			}
		}
	}

	GIVEN("Function")
	{
		std::string funcName = "x1Mulx2";
		std::string firstVar = "x1";
		std::string secondVar = "x2";
		std::string firstVal = "10", secondVal = "20";
		WHEN("Adding new function")
		{
			calc.VarIdentification(firstVar, firstVal);
			calc.VarIdentification(secondVar, secondVal);
			THEN("True")
			{
				REQUIRE(calc.NewFunction(funcName, firstVar, secondVar, oper));
			}
		}
		WHEN("Adding existing function")
		{
			calc.VarIdentification(firstVar, firstVal);
			calc.VarIdentification(secondVar, secondVal);
			calc.NewFunction(funcName, firstVar, secondVar, oper);
			THEN("False")
			{
				REQUIRE_THROWS(calc.NewFunction(funcName, secondVar, secondVar, oper));
			}
		}
		WHEN("Add functional function")
		{
			calc.VarIdentification(firstVar, firstVal);
			calc.VarIdentification(secondVar, secondVal);
			calc.NewFunction(funcName, firstVar, secondVar, oper);
			firstVar = funcName;
			std::string funcName = "ss";
			secondVar = "";
			THEN("TRUE")
			{
				REQUIRE(calc.NewFunction(funcName, firstVar, secondVar, oper));
			}
		}
	}
}

TEST_CASE("Calculating Fibonachi number")
{
	Var v0(0);
	Var v1(1);
	Operation operation = Operation::Addition;
	Function fib0(&v0);
	Function fib1(&v1);
	Function fib2(&fib1, &fib0, operation);
	Function fib3(&fib2, &fib1, operation);
	Function fib4(&fib3, &fib2, operation);
	Function fib5(&fib4, &fib3, operation);
	Function fib6(&fib5, &fib4, operation);
	Function fib7(&fib6, &fib5, operation);
	Function fib8(&fib7, &fib6, operation);
	Function fib9(&fib8, &fib7, operation);
	Function fib10(&fib9, &fib8, operation);
	Function fib11(&fib10, &fib9, operation);
	Function fib12(&fib11, &fib10, operation);
	Function fib13(&fib12, &fib11, operation);
	Function fib14(&fib13, &fib12, operation);
	Function fib15(&fib14, &fib13, operation);
	Function fib16(&fib15, &fib14, operation);
	Function fib17(&fib16, &fib15, operation);
	Function fib18(&fib17, &fib16, operation);
	Function fib19(&fib18, &fib17, operation);
	Function fib20(&fib19, &fib18, operation);
	Function fib21(&fib20, &fib19, operation);
	Function fib22(&fib21, &fib20, operation);
	Function fib23(&fib22, &fib21, operation);
	Function fib24(&fib23, &fib22, operation);
	Function fib25(&fib24, &fib23, operation);
	Function fib26(&fib25, &fib24, operation);
	Function fib27(&fib26, &fib25, operation);
	Function fib28(&fib27, &fib26, operation);
	Function fib29(&fib28, &fib27, operation);
	Function fib30(&fib29, &fib28, operation);
	Function fib31(&fib30, &fib29, operation);
	Function fib32(&fib31, &fib30, operation);
	Function fib33(&fib32, &fib31, operation);
	Function fib34(&fib33, &fib32, operation);
	Function fib35(&fib34, &fib33, operation);
	Function fib36(&fib35, &fib34, operation);
	Function fib37(&fib36, &fib35, operation);
	Function fib38(&fib37, &fib36, operation);
	Function fib39(&fib38, &fib37, operation);
	Function fib40(&fib39, &fib38, operation);
	Function fib41(&fib40, &fib39, operation);
	Function fib42(&fib41, &fib40, operation);
	Function fib43(&fib42, &fib41, operation);
	Function fib44(&fib43, &fib42, operation);
	Function fib45(&fib44, &fib43, operation);
	Function fib46(&fib45, &fib44, operation);
	Function fib47(&fib46, &fib45, operation);
	Function fib48(&fib47, &fib46, operation);
	Function fib49(&fib48, &fib47, operation);
	Function fib50(&fib49, &fib48, operation);
	v0.SetValue(1);
}
