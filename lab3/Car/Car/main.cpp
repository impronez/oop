#include <iostream>
#include <string>
#include "Car.h"
#include <map>

const std::string INFO = "info";
const std::string ENGINE_ON = "engineon";
const std::string ENGINE_OFF = "engineoff";
const std::string SET_GEAR = "setgear";
const std::string SET_SPEED = "setspeed";
const std::string EXIT = "exit";

const std::map<Direction, std::string> DIRECTIONS =
{
    { Direction::Forward, "Forward" },
    { Direction::Backward, "Backward" },
    { Direction::Stand, "Standing still" }
};

void GetInfoAboutCar(Car& car)
{
    int gear = car.GetGear();
    int speed = car.GetSpeed();
    std::string direction = DIRECTIONS.at(car.GetDirection());
    bool isTurnedOn = car.IsTurnedOn();

    std::cout << "Engine: " << (isTurnedOn ? "On" : "Off") << std::endl;
    std::cout << "Gear: " << gear << std::endl;
    std::cout << "Speed: " << speed << std::endl;
    std::cout << "Direction: " << direction << std::endl;
    // TODO: direction-switch to map
    // TODO: писать код вывода каждого поля с новой строки 
}

bool IsNumber(const std::string& str)
{
    bool isFirstSymbol = true;
    for (char const& c : str) {
        if (isFirstSymbol && c == '-')
        {
            isFirstSymbol = false;
            continue;
        }
        if (std::isdigit(c) == 0)
        {
            return false;
        }
    }
    return true;
}

void StringToLowerCase(std::string& str)
{
    for (char &ch : str)
    {
        ch = tolower(ch);
    }
}

void SetGear(Car& car)
{
    int gear = 0;
    bool isSwitched = false;
    std::string line;
    std::cout << "Enter the set gear: ";
    while (1)
    {
        std::getline(std::cin, line);
        if (!IsNumber(line))
        {
            std::cout << "Incorrect value! Enter correct value of set gear: ";
            continue;
        }
        gear = std::stoi(line);
        try
        {
            isSwitched = car.SetGear(gear);
        }
        catch (const std::exception& err)
        {
            std::cout << err.what() << std::endl;
        }
        break;
    }  
    if (isSwitched)
    {
        std::cout << "Gear is switched to " << gear << std::endl;
    }
}

void SetSpeed(Car& car)
{
    int speed = 0;
    bool isChanged = false;
    std::string line;
    std::cout << "Enter the set speed: ";
    while (1)
    {
        std::getline(std::cin, line);
        if (!IsNumber(line))
        {
            std::cout << "Incorrect value! Enter correct value of set gear: ";
            continue;
        }
        speed = std::stoi(line);
        try
        {
            isChanged = car.SetSpeed(speed);
        }
        catch (const std::exception& err)
        {
            std::cout << err.what() << std::endl;
        }
        break;
    }
    if (isChanged)
    {
        std::cout << "Speed is changed to " << speed << std::endl;
    }
}

void EngineOn(Car& car)
{
    bool isOn = car.IsTurnedOn();
    if (isOn)
    {
        std::cout << "Engine is already on!\n";
        return;
    }

    car.TurnOnEngine();
    std::cout << "Engine on!\n";
}

void EngineOff(Car& car)
{
    bool isOn = car.IsTurnedOn();
    if (!isOn)
    {
        std::cout << "Engine is already off!\n";
        return;
    }
    bool isOff = car.TurnOffEngine();
    if (!isOff)
    {
        int gear = car.GetGear();
        int speed = car.GetSpeed();
        if (gear != 0)
        {
            std::cout << "Impossible. Gear is not neutral!\n";
        }
        else if (speed != 0)
        {
            std::cout << "Impossible. Speed is not neautral!\n";
        }
        return;
    }
    std::cout << "Engine off!\n";
}

void Menu(Car& car)
{
    std::string line;
    while (1)
    {
        std::getline(std::cin, line);
        StringToLowerCase(line);
        if (line == INFO)
        {
            GetInfoAboutCar(car);
        }
        else if (line == ENGINE_ON)
        {
            EngineOn(car);
        }
        else if (line == ENGINE_OFF)
        {
            EngineOff(car);
        }
        else if (line == SET_GEAR)
        {
            SetGear(car);
        }
        else if (line == SET_SPEED)
        {
            SetSpeed(car);
        }
        else if (line == EXIT || line.empty())
        {
            break;
        }
    }
}

int main()
{
    std::cout << "Menu: 'EngineOn', 'EngineOff', 'SetGear', 'SetSpeed'.\n";
    Car car;
    Menu(car);
}