#include <iostream>
#include <vector>

using namespace std;

// Klasa pomocnicza, jej nie zmieniamy
class File
{
public:
    File(const std::string &file_name);
    void write(const std::string &msg);
};

// Klasa pomocnicza, jej nie zmieniamy
class Mail
{
public:
    Mail(const std::string &address) {}
    void send(const std::string &msg) {}
};

class Observer
{
public:
    virtual void notify(const string &msg) = 0;
};

class FileObs : public Observer
{
public:
    FileObs(const string &file_name) : f_(file_name) {}
    virtual void notify(const string &msg) { f_.write(msg); }

private:
    File f_;
};

class MailObs : public Observer
{
public:
    MailObs(const string &address) : m_(address) {}
    virtual void notify(const string &msg) { m_.send(msg); }

private:
    Mail m_;
};

class LoggerBetter
{
public:
    typedef vector<Observer *> Observers;

    LoggerBetter() {}

    void reg(Observer *o) { obs_.push_back(o); }

    int msg(const string &msg) const
    {
        for (Observers::const_iterator it = obs_.begin(); it != obs_.end(); ++it)
            (*it)->notify(msg);
    }

private:
    Observers obs_;
};

int main()
{
    LoggerBetter l;
    return 0;
}