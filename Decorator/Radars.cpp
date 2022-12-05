#include <iostream>

class Vehicle
{
public:
    virtual void move() = 0;
};

class NormalVehicle : public Vehicle
{
public:
    virtual void move()
    {
        std::cout << "Moving forward!\n";
    }
};

class VehicleDecorator : public Vehicle
{
public:
    VehicleDecorator(Vehicle &v) : itsVehicle(v){};

    virtual void move()
    {
        itsVehicle.move();
    }

    Vehicle &itsVehicle;
};

class Lidar : public VehicleDecorator
{
public:
    Lidar(Vehicle &v) : VehicleDecorator(v) {}
    virtual void move() override
    {
        std::cout << "Lidar did not detect any obstacles!\n";
        obstacleDetected = false;
        if (!obstacleDetected)
            itsVehicle.move();
    }

private:
    bool obstacleDetected;
};

class Radar : public VehicleDecorator
{
public:
    Radar(Vehicle &v) : VehicleDecorator(v) {}
    virtual void move() override
    {
        std::cout << "Radar did not detect any obstacles!\n";
        obstacleDetected = false;
        if (!obstacleDetected)
            itsVehicle.move();
    }

private:
    bool obstacleDetected;
};

class Camera : public VehicleDecorator
{
public:
    Camera(Vehicle &v) : VehicleDecorator(v) {}
    virtual void move() override
    {
        std::cout << "Camera did not detect any obstacles!\n";
        obstacleDetected = false;
        if (!obstacleDetected)
            itsVehicle.move();
    }

private:
    bool obstacleDetected;
};

int main()
{
    NormalVehicle v;
    Camera c(v);
    Lidar lc(c);
    Radar rlc(lc);

    rlc.move();
}