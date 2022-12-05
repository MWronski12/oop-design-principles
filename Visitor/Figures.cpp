#include <iostream>
#include <vector>
#include <memory>
#include <typeinfo>

using namespace std;

class Visitor;

class Figure
{
public:
    Figure() {}
    virtual void accept(Visitor &v) = 0;
    virtual double getArea() const = 0;
};

class Rectangle;
class Triangle;

class Visitor
{
public:
    virtual ~Visitor() {}
    virtual void visit(Rectangle &) = 0;
    virtual void visit(Triangle &) = 0;
};

class Rectangle : public Figure
{
public:
    Rectangle(double site_a, double site_b) : Figure(), a(site_a), b(site_b) {}
    virtual void accept(Visitor &v) { v.visit(*this); }
    virtual double getArea() const { return a * b; }

private:
    double a;
    double b;
};

class Triangle : public Figure
{
public:
    Triangle(double base, double height) : Figure(), b(base), h(height) {}
    virtual void accept(Visitor &v) { v.visit(*this); }
    virtual double getArea() const { return 0.5 * b * h; }

private:
    double b;
    double h;
};

class NamesContainer : public Visitor
{
public:
    virtual ~NamesContainer(){};
    virtual void visit(Rectangle &)
    {
        names += "Rectangle ";
    };
    virtual void visit(Triangle &)
    {
        names += "Triangle ";
    };

    string names = "";
};

class RectanglesCounter : public Visitor
{
public:
    virtual ~RectanglesCounter(){};

    virtual void visit(Rectangle &)
    {
        rectanglesCount++;
    };
    virtual void visit(Triangle &){};

    int rectanglesCount = 0;
};

using PFigure = shared_ptr<Figure>;
using Figures = vector<PFigure>;

// suma pĂłl figur w kolekcji
double sumArea(const Figures &figures)
{
    double sum = 0.0;
    for (PFigure f : figures)
        sum += f->getArea();
    return sum;
}

// nazwy figur rozdzielone spacjÄ, nazwa dla Rectangle to "Rectangle", nazwa dla Triangle to "Traingle"
string names(const Figures &figures)
{
    NamesContainer v;
    for (PFigure f : figures)
    {
        (*f).accept(v);
    }
    return v.names;
}

// liczba prostokatow w kolekcji
int numRectangles(const Figures &figures)
{
    RectanglesCounter v;
    for (PFigure f : figures)
    {
        (*f).accept(v);
    }
    return v.rectanglesCount;
}

int main()
{
    Figures figures;
    figures.push_back(PFigure(new Rectangle(1.0, 1.0)));
    figures.push_back(PFigure(new Triangle(2.0, 2.0)));
    figures.push_back(PFigure(new Rectangle(2.0, 2.0)));

    cout << "numFigures:" << figures.size() << endl;
    cout << "numRectangles:" << numRectangles(figures) << endl;
    cout << "names:" << names(figures) << endl;
    cout << "sumArea:" << sumArea(figures) << endl;

    return 0;
}