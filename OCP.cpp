#include <iostream>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <string.h>

using namespace std;

class Shape
{
public:
    virtual void Draw() const = 0;
    bool Preceeds(const Shape &) const;
    bool operator<(const Shape &s) { return Preceeds(s); };

private:
    static const char *typeOrderTable[];
};

class Square : public Shape
{
public:
    virtual void Draw() const
    {
        cout << "Square!\n";
    }
};

class Circle : public Shape
{
public:
    virtual void Draw() const
    {
        cout << "Circle!\n";
    }
};

const char *Shape::typeOrderTable[] = {
    typeid(Circle).name(),
    typeid(Square).name(),
    0,
};

bool Shape::Preceeds(const Shape &s) const
{
    const char *thisType = typeid(*this).name();
    const char *argType = typeid(s).name();
    int thisOrd = -1;
    int argOrd = -1;
    bool done = false;

    for (int i = 0; !done; i++)
    {
        const char *tableEntry = typeOrderTable[i];
        if (tableEntry != 0)
        {
            if (strcmp(tableEntry, thisType) == 0)
                thisOrd = i;
            if (strcmp(tableEntry, argType) == 0)
                argOrd = i;
            if (thisOrd >= 0 && argOrd >= 0)
                done = true;
        }
        else
        {
            done = true;
        }
    }
    return thisOrd < argOrd;
}

template <typename P>
class Lessp // utility for sorting containers of pointers.
{
public:
    bool operator()(const P p, const P q) { return (*p) < (*q); }
};

void DrawAllShapes(vector<Shape *> &list)
{
    vector<Shape *> &orderedList = list;
    sort(orderedList.begin(), orderedList.end(), Lessp<Shape *>());

    vector<Shape *>::const_iterator i;
    for (i = orderedList.begin(); i != orderedList.end(); i++)
        (*i)->Draw();
}

int main()
{
    Square s;
    Circle c;

    vector<Shape *> list{&s, &c};
    DrawAllShapes(list);

    return 1;
}
