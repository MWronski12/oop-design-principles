#include <exception>
#include <iostream>
#include <string>

class Exception;
class PermissionException;
class NetworkException;

class Visitor
{
public:
    virtual void visit(const PermissionException &e) = 0;
    virtual void visit(const NetworkException &e) = 0;
};

// klasa bazowa dla bledow
class Exception : public std::runtime_error
{
public:
    Exception() : runtime_error("Error!"){};
    virtual void accept(Visitor &v) const = 0;
};

// wyjatek - brak uprawnien
class PermissionException : public Exception
{
public:
    PermissionException(int user_id = 0) : userId(user_id) {}
    void accept(Visitor &v) const override { v.visit(*this); }
    int getUserId() const { return userId; }

private:
    int userId; // identyfikator uzytkownika, ktory nie mial uprawnien
};

// wyjatek - blad wewnetrzny serwera
class NetworkException : public Exception
{
public:
    void accept(Visitor &v) const override { v.visit(*this); }
};

using Translator = Visitor;

class PolishTranslator : public Translator
{
public:
    virtual void visit(const PermissionException &e)
    {
        std::cerr << u8"Użytkownik " << std::to_string(e.getUserId()) << u8" nie ma uprawnień!" << std::endl;
    };
    virtual void visit(const NetworkException &e)
    {
        std::cerr << u8"Błąd połączenia sieciowego!" << std::endl;
    };
};

class EnglishTranslator : public Translator
{
public:
    virtual void visit(const PermissionException &e)
    {
        std::cerr << "User " << std::to_string(e.getUserId()) << " has no permission!" << std::endl;
    };
    virtual void visit(const NetworkException &e)
    {
        std::cerr << "Network error!" << std::endl;
    };
};

class Settings
{
public:
    static Settings &getInstance()
    {
        if (!instance)
            instance = new Settings;
        return *instance;
    }
    void setLanguage(const std::string &l) { lang = l; }

    // kod tej metody nie jest poprawny, powinna byc fabryka, prosze nie poprawiac
    Translator &getTranslator()
    {
        if (lang == "PL")
            return *polishTranslator_;
        else
            return *englishTranslator_;
    }

private:
    inline static Settings *instance;
    Settings(const Settings &) = delete;
    Settings &operator=(const Settings &) = delete;
    Settings() {}
    ~Settings()
    {
        delete englishTranslator_;
        delete polishTranslator_;
    }
    std::string lang = "EN";

    // przechowywanie obiektow do translacji tak jak nizej to blad, prosze nie poprawiac
    Translator *englishTranslator_ = new EnglishTranslator;
    Translator *polishTranslator_ = new PolishTranslator;
};

void printError(const Exception &e)
{
    Translator &t = Settings::getInstance().getTranslator();
    e.accept(t);
}

int main()
{
    try
    {
        throw PermissionException(13);
    }
    catch (Exception &e)
    {
        printError(e);
    }
    try
    {
        throw NetworkException();
    }
    catch (Exception &e)
    {
        printError(e);
    }

    Settings::getInstance().setLanguage("PL");

    try
    {
        throw PermissionException(13);
    }
    catch (Exception &e)
    {
        printError(e);
    }
    try
    {
        throw NetworkException();
    }
    catch (Exception &e)
    {
        printError(e);
    }

    return 0;
}
