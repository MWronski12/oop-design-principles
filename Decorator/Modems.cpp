#include <iostream>

// Interface
class Modem
{
public:
    virtual void dial() = 0;
    virtual void setVolume(int volume) = 0;
    virtual int getVolume() = 0;
};

// Extends abstract class Modem and overrides dial function
class MyModem : public Modem
{
public:
    void dial() override { std::cout << "Dialing from MyModem...\n"; };

    void setVolume(int volume) override
    {
        this->itsVolume = volume;
    };
    int getVolume() override
    {
        return this->itsVolume;
    };

private:
    int itsVolume;
};

class ModemDecorator : public Modem
{
public:
    ModemDecorator(Modem &m) : itsModem(m){};
    Modem &getModem() { return this->itsModem; };

    virtual void dial() override
    {
        getModem().dial();
    };
    virtual void setVolume(int volume) override
    {
        getModem().setVolume(volume);
    }
    virtual int getVolume() override
    {
        return getModem().getVolume();
    }

private:
    Modem &itsModem;
};

// Extends ModemDecorator and overrides dial function
class LoudDialModem : public ModemDecorator
{
public:
    LoudDialModem(Modem &m) : ModemDecorator(m){};
    void dial() override
    {
        this->getModem().setVolume(10);
        this->getModem().dial();
    }
};

int main()
{
    MyModem m;
    LoudDialModem l(m);
    l.dial();
    std::cout << l.getVolume() << "\n";
    return 0;
}
