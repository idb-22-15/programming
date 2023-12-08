#include <cmath>
#include <iostream>
#include <limits>
// #include <numbers>

// Создать класс, описывающий окружность. Определить площадь круга.
// Определить площадь кольца, образованного двумя концентрическими окружностями.
// Создать класс-наследник, описывающий цилиндр.
// Найти сторону квадрата, имеющего площадь, совпадающую с площадью полной
// поверхности полого цилиндра.
class IAreaComputable {
 public:
  virtual float get_area() = 0;
};

class WrongArgumentException : public std::exception {
 private:
  std::string message;

 public:
  WrongArgumentException(std::string message) { this->message = message; }

  const char* what() const throw() { return message.c_str(); }
};

class Circle : public IAreaComputable {
 private:
  float radius;

  float compute_area() { return M_PI * radius * radius; }

 public:
  Circle(float radius) {
    if (radius <= 0)
      throw WrongArgumentException("Radius must be positive number");
    this->radius = radius;
  }

  float get_radius() { return radius; }
  float get_area() { return compute_area(); }
};

class Ring : public IAreaComputable {
 protected:
  Circle* outer_circle;
  Circle* inner_circle;

 public:
  Ring(float outer_radius, float inner_radius) {
    this->outer_circle = new Circle(outer_radius);
    this->inner_circle = new Circle(inner_radius);

    if (outer_circle->get_radius() <= inner_circle->get_radius())
      throw WrongArgumentException(
          "Outer radius must be greater than inner radius");
  }

  ~Ring() {
    delete outer_circle;
    delete inner_circle;
  }

  float get_area() {
    return outer_circle->get_area() - inner_circle->get_area();
  }
};

class Cylinder : public Circle {
 private:
  float height;

  float compute_area() { return 2 * Circle::get_area() + compute_side_area(); }
  float compute_side_area() { return 2 * M_PI * get_radius() * height; }

 public:
  Cylinder(float radius, float height) : Circle(radius) {
    this->height = height;

    if (height <= 0)
      throw WrongArgumentException("Height must be positive number");
  }

  float get_height() { return height; }
  float get_area() { return compute_area(); }
};

class HollowCylinder : public Cylinder {
 private:
  Circle* inner_circle;

  float compute_outer_side_area() {
    return 2 * M_PI * get_outer_radius() * get_height();
  }

  float compute_inner_side_area() {
    return 2 * M_PI * get_inner_radius() * get_height();
  }

  float compute_area() {
    return 2 * (Circle::get_area() - inner_circle->get_area()) +
           compute_outer_side_area() + compute_inner_side_area();
  }

 public:
  HollowCylinder(float outer_radius, float inner_radius, float height)
      : Cylinder(outer_radius, height) {
    inner_circle = new Circle(inner_radius);
    if (get_inner_radius() >= get_outer_radius())
      throw WrongArgumentException(
          "Outer radius must be greater than inner radius");
  }
  ~HollowCylinder() { delete inner_circle; }

  float get_area() { return compute_area(); }
  float get_inner_radius() { return inner_circle->get_radius(); }
  float get_outer_radius() { return Circle::get_radius(); }
};

class HollowCylinderLegacy : public Ring {
 private:
  float heigth;

  float compute_outer_side_area() {
    return 2 * M_PI * outer_circle->get_radius() * heigth;
  }

  float compute_inner_side_area() {
    return 2 * M_PI * inner_circle->get_radius() * heigth;
  }

  float compute_area() {
    return 2 * Ring::get_area() + compute_outer_side_area() +
           compute_inner_side_area();
  }

 public:
  HollowCylinderLegacy(float outer_radius, float inner_radius, float heigth)
      : Ring(outer_radius, inner_radius) {
    if (heigth <= 0)
      throw WrongArgumentException("Height must be positive number");
    this->heigth = heigth;
  }

  float get_area() { return compute_area(); };

  float get_inner_radius() { return inner_circle->get_radius(); }
  float get_outer_radius() { return outer_circle->get_radius(); }
  float get_height() { return heigth; }
};

class Square : public IAreaComputable {
 private:
  float side;

  float compute_area() { return side * side; }

 public:
  Square(float side) { this->side = side; }

  static Square from_area(float area) { return Square(sqrt(area)); }

  float get_side() { return side; }

  float get_area() { return compute_area(); }
};

void input_number(std::string message, float& number) {
  while (std::cout << message && !(std::cin >> number)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input; please re-enter\n";
  }
}

int main() {
  bool params_correct = true;

  do {
    float circle_radius;
    input_number("Enter circle radius: ", circle_radius);

    try {
      Circle circle = Circle(circle_radius);
      params_correct = true;
      std::cout << "Circle area: " << circle.get_area() << std::endl;
    } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      params_correct = false;
    }
  } while (!params_correct);

  std::cout << "==========" << std::endl;

  do {
    std::cout << "Enter ring params" << std::endl;

    float outer_radius;
    float inner_radius;

    input_number("Enter outer radius: ", outer_radius);
    input_number("Enter inner radius: ", inner_radius);

    try {
      Ring ring = Ring(outer_radius, inner_radius);
      params_correct = true;
      std::cout << "Ring area: " << ring.get_area() << std::endl;
    } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      params_correct = false;
    }
  } while (!params_correct);

  params_correct = true;

  std::cout << "==========" << std::endl;

  do {
    std::cout << "Enter hollow cylinder params" << std::endl;

    float outer_radius;
    float inner_radius;
    float height;

    input_number("Enter outer radius: ", outer_radius);
    input_number("Enter inner radius: ", inner_radius);
    input_number("Enter height: ", height);

    try {
      HollowCylinder cylinder =
          HollowCylinder(outer_radius, inner_radius, height);

      std::cout << "Cylinder area: " << cylinder.get_area() << std::endl;

      Square square = Square::from_area(cylinder.get_area());
      std::cout << "Square area: " << square.get_area() << std::endl;
      std::cout << "Square side: " << square.get_side() << std::endl;

    } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      params_correct = false;
    };
  } while (!params_correct);
}