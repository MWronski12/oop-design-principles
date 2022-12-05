#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Cmd;
using PCmd = shared_ptr<Cmd>;

class Cmd
{
public:
    virtual ~Cmd() {}
    void operator()() { execute(); } // wzorzec komendy
    virtual PCmd clone() = 0;
    virtual void add(PCmd c){}; // dodaje komendÄ do kolekcji

private:
    virtual void execute() = 0; // implementacja akcji dla konkretnej komendy
};

class CmdDrawLine : public Cmd
{
public:
    virtual PCmd clone() { return PCmd(new CmdDrawLine(*this)); }

private:
    virtual void execute() { cout << "CmdDrawLine" << endl; } // implementacja jest nieistotna w tym zadaniu
};

class CmdPrintText : public Cmd
{
public:
    virtual PCmd clone() { return PCmd(new CmdPrintText(*this)); }

private:
    virtual void execute() { cout << "CmdPrintText" << endl; } // implementacja jest nieistotna w tym zadaniu
};

class CmdMacro : public Cmd
{
public:
    virtual ~CmdMacro() {}
    void operator()() { execute(); } // wzorzec komendy
    virtual PCmd clone() { return PCmd(new CmdMacro(*this)); };
    virtual void add(PCmd c)
    {
        commands_.push_back(c);
    }; // dodaje komendÄ do kolekcji

private:
    virtual void execute()
    {
        for (PCmd c : commands_)
        {
            (*c)();
        }
    }; // implementacja akcji dla konkretnej komendy
    vector<PCmd> commands_;
};

int main()
{
    // CmdDrawLine m0;
    // PCmd m0_clone = m0.clone();

    // PCmd m1(new CmdMacro);
    // m1->add(m0_clone);

    PCmd m1(new CmdMacro);
    m1->add(PCmd(new CmdDrawLine));
    m1->add(PCmd(new CmdPrintText));
    m1->add(PCmd(new CmdPrintText));
    PCmd m2(new CmdMacro);
    m2->add(m1);
    m2->add(m1);

    (*m2)();

    return 0;
}

/*

Polecenia:

    Dostarcz kod klasy CmdMacro. Twój kod nie musi siÄ kompilowaÄ, ale powinno w nim byÄ widaÄ rozwiÄzanie.


    Klasa ta pozwala wykonywaÄ komendy w kolejnoĹci ich dodania. Jakiego wzorca projektowego uĹźyĹeĹ do dostarczenia tego udogodnienia?


    Co robi metoda 'clone'?


    Nie zapomnij dostarczyÄ metodÄ 'clone' dla klasy CmdMacro

*/
