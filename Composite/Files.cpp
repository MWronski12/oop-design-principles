#include <iostream>
#include <vector>

class File
{
public:
    virtual std::string getName() const = 0;
    virtual int getSize() const = 0;
};

class SingleFile : public File
{
public:
    SingleFile(std::string n, int s) : name_(n), size_(s) {}
    std::string getName() const { return name_; }
    int getSize() const { return size_; }
    ~SingleFile() {}

private:
    std::string name_;
    int size_;
};

class Dir : public File
{
    using Child = File *;
    using Children = std::vector<Child>;

public:
    Dir(const std::string &n) : name_(n) {}
    ~Dir()
    {
        for (Child c : ch_)
            delete c;
    }
    std::string getName() const { return name_; }
    int getSize() const
    {
        int s = 0;
        for (Child c : ch_)
            s += c->getSize();
        return s;
    }
    void add(Child el) { ch_.push_back(el); }

private:
    std::string name_;
    Children ch_;
};

int main()
{
    Dir root("root");

    // Level 1
    Dir dir_1("dir_1");
    SingleFile file_1("file_1", 100);
    root.add(dynamic_cast<File *>(&dir_1));
    root.add(dynamic_cast<File *>(&file_1));

    // Level 2
    Dir dir_2("dir_2");
    SingleFile file_2("file_2", 150);
    dir_1.add(dynamic_cast<File *>(&dir_2));
    dir_1.add(dynamic_cast<File *>(&file_2));

    std::cout << root.getName() << "size is: " << root.getSize() << std::endl;
    std::cout << dir_1.getName() << "size is: " << dir_1.getSize() << std::endl;
}