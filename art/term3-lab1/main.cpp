#include <iostream>
#include "Circle.cpp"

int main() {
  Circle circle = Circle(10);

  std::cout << "Circle area: " << circle.get_area() << std::endl;

  Cylinder cylinder = Cylinder(4, 5, 10);

  std::cout << "Cylinder area: " << cylinder.get_area() << std::endl;

  Square square = Square::from_area(cylinder.get_area());

  std::cout << "Square area: " << square.get_area() << std::endl;
  std::cout << "Square side: " << square.get_side() << std::endl;
}