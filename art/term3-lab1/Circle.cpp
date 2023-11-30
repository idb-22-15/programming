#include <cmath>
#include <iostream>

class AreaComputable {
 public:
  virtual float get_area() = 0;
};

class Circle : public AreaComputable {
 private:
  float radius;

 public:
  Circle(float radius) { this->radius = radius; }

  float get_radius() { return radius; }
  float get_area() { return M_PI * radius * radius; }
};

class RingException : public std::exception {
  const char* what() {
    return "Ring exception: outer radius"
           "must be greater than inner radius";
  };
};

class Ring : public AreaComputable {
 protected:
  Circle* outer_circle;
  Circle* inner_circle;

 public:
  Ring(float outer_radius, float inner_radius) {
    this->outer_circle = new Circle(outer_radius);
    this->inner_circle = new Circle(inner_radius);
    if (outer_circle->get_radius() <= inner_circle->get_radius()) {
      throw RingException();
    }
  }

  ~Ring() {
    delete outer_circle;
    delete inner_circle;
  }

  float get_area() {
    return outer_circle->get_area() - inner_circle->get_area();
  }
};

class Cylinder : public Ring {
 private:
  float heigth;

 public:
  Cylinder(float outer_radius, float inner_radius, float heigth)
      : Ring(outer_radius, inner_radius) {
    this->heigth = heigth;
  }

  float get_outer_side_area() {
    return 2 * M_PI * outer_circle->get_radius() * heigth;
  }

  float get_inner_side_area() {
    return 2 * M_PI * inner_circle->get_radius() * heigth;
  }

  float get_area() {
    return 2 * Ring::get_area() + get_outer_side_area() + get_inner_side_area();
  };

  float get_height() { return heigth; }
};

class Square : public AreaComputable {
 private:
  float side;

 public:
  Square(float side) { this->side = side; }

  static Square from_area(float area) { return Square(sqrt(area)); }

  float get_side() { return side; }

  float get_area() { return side * side; }
};