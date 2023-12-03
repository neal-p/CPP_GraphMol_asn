#pragma once

#include <iostream>

// Base class for attributes
class Attribute {
 public:
  virtual ~Attribute() = default;
  virtual Attribute* clone() = 0;
  virtual void print() = 0;
};

// Template class for vertex and edge attributes
template <typename T>
class AttributeValue : public Attribute {
 public:
  T value;

  AttributeValue(const T& val) : value(val) {}
  AttributeValue() : value() {}

  void print() override { std::cout << value; }

  AttributeValue<T>* clone() override { return new AttributeValue<T>(); }
};
