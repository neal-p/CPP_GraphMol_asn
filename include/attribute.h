#include <iostream>

// Base class for attributes
class Attribute {
 public:
    virtual ~Attribute() = default;
    virtual void print() = 0;
};

// Template class for vertex and edge attributes
template <typename T>
class AttributeValue : public Attribute {
 public:
  T value;

  AttributeValue(const T& val) : value(val) {}

    void print() override {
        std::cout << value;
    }
};


