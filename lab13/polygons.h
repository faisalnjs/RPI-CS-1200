#ifndef POLYGONS_H
#define POLYGONS_H

#include "utilities.h"

class Polygon {
 public:
  Polygon(const std::string& name, const std::vector<Point>& points) : name(name), points(points) {}
  virtual ~Polygon() {}
  std::string name;
  std::vector<Point> points;
  std::string getName() const { return name; }
  bool HasAllEqualSides() const;
  bool HasAllEqualAngles() const;
  bool HasARightAngle() const;
};

bool Polygon::HasAllEqualSides() const {
  if (points.size() < 2) return true;
  double first_length = DistanceBetween(points[0], points[1]);
  for (size_t i = 1; i < points.size(); ++i) {
    double length = DistanceBetween(points[i], points[(i + 1) % points.size()]);
    if (std::abs(length - first_length) > DISTANCE_EPSILON) return false;
  }
  return true;
}

bool Polygon::HasAllEqualAngles() const {
  if (points.size() < 3) return true;
  double first_angle = Angle(points[points.size() - 1], points[0], points[1]);
  for (size_t i = 0; i < points.size(); ++i) {
    double angle = Angle(points[(i + points.size() - 1) % points.size()], points[i], points[(i + 1) % points.size()]);
    if (std::abs(angle - first_angle) > ANGLE_EPSILON) return false;
  }
  return true;
}

bool Polygon::HasARightAngle() const {
  for (size_t i = 0; i < 4; ++i) {
    const Point& a = points[(i + 3) % 4];
    const Point& b = points[i];
    const Point& c = points[(i + 1) % 4];
    double ang = Angle(a, b, c);
    if (RightAngle(ang)) return true;
  }
  return false;
};

class Triangle : public Polygon {
 public:
  Triangle(const std::string& name, const std::vector<Point>& points) : Polygon(name, points) {
    if (points.size() != 3) throw 1;
    double a0 = Angle(points[1], points[0], points[2]);
    double a1 = Angle(points[0], points[1], points[2]);
    double a2 = Angle(points[0], points[2], points[1]);
    if (a0 < ANGLE_EPSILON || a1 < ANGLE_EPSILON || a2 < ANGLE_EPSILON) throw 1;
  }
};

class IsoscelesTriangle : public Triangle {
 public:
  IsoscelesTriangle(const std::string& name, const std::vector<Point>& points) : Triangle(name, points) {
    double d0 = DistanceBetween(points[0], points[1]);
    double d1 = DistanceBetween(points[1], points[2]);
    double d2 = DistanceBetween(points[2], points[0]);
    if (!(EqualSides(d0, d1) || EqualSides(d1, d2) || EqualSides(d2, d0))) throw 1;
  }
};

class EquilateralTriangle : public IsoscelesTriangle {
 public:
  EquilateralTriangle(const std::string& name, const std::vector<Point>& points) : IsoscelesTriangle(name, points) {
    double d0 = DistanceBetween(points[0], points[1]);
    double d1 = DistanceBetween(points[1], points[2]);
    double d2 = DistanceBetween(points[2], points[0]);
    if (!(EqualSides(d0, d1) && EqualSides(d1, d2))) throw 1;
  }
};

class RightTriangle : public IsoscelesTriangle {
 public:
  RightTriangle(const std::string& name, const std::vector<Point>& points) : IsoscelesTriangle(name, points) {
    double a0 = Angle(points[1], points[0], points[2]);
    double a1 = Angle(points[0], points[1], points[2]);
    double a2 = Angle(points[0], points[2], points[1]);
    if (!RightAngle(a0) && !RightAngle(a1) && !RightAngle(a2)) throw 1;
  }
};

class IsoscelesRightTriangle : public RightTriangle {
 public:
  IsoscelesRightTriangle(const std::string& name, const std::vector<Point>& points) : RightTriangle(name, points) {
    double d0 = DistanceBetween(points[0], points[1]);
    double d1 = DistanceBetween(points[1], points[2]);
    double d2 = DistanceBetween(points[2], points[0]);
    if (!(EqualSides(d0, d1) || EqualSides(d1, d2) || EqualSides(d2, d0))) throw 1;
  }
};

class Quadrilateral : public Polygon {
 public:
  Quadrilateral(const std::string& name, const std::vector<Point>& points) : Polygon(name, points) {
    if (points.size() != 4) throw 1;
    for (size_t i = 0; i < 4; ++i) {
      const Point& a = points[(i + 3) % 4];
      const Point& b = points[i];
      const Point& c = points[(i + 1) % 4];
      double ang = Angle(a, b, c);
      if (ang < ANGLE_EPSILON || fabs(ang - 180.0) < ANGLE_EPSILON) throw 1;
    }
  }
};

class Rectangle : public Quadrilateral {
 public:
  Rectangle(const std::string& name, const std::vector<Point>& points) : Quadrilateral(name, points) {
    Vector v0(points[0], points[1]);
    Vector v1(points[1], points[2]);
    Vector v2(points[2], points[3]);
    Vector v3(points[3], points[0]);
    if (!Parallel(v0, v2) || !Parallel(v1, v3)) throw 1;
    for (size_t i = 0; i < 4; ++i) {
      const Point& a = points[(i + 3) % 4];
      const Point& b = points[i];
      const Point& c = points[(i + 1) % 4];
      double ang = Angle(a, b, c);
      if (!RightAngle(ang)) throw 1;
    }
  }
};

class Square : public Rectangle {
 public:
  Square(const std::string& name, const std::vector<Point>& points) : Rectangle(name, points) {
    double d0 = DistanceBetween(points[0], points[1]);
    double d1 = DistanceBetween(points[1], points[2]);
    double d2 = DistanceBetween(points[2], points[3]);
    double d3 = DistanceBetween(points[3], points[0]);
    if (!(EqualSides(d0, d1) && EqualSides(d1, d2) && EqualSides(d2, d3))) throw 1;
  }
};

class Rhombus : public Quadrilateral {
 public:
  Rhombus(const std::string& name, const std::vector<Point>& points) : Quadrilateral(name, points) {
    double d0 = DistanceBetween(points[0], points[1]);
    double d1 = DistanceBetween(points[1], points[2]);
    double d2 = DistanceBetween(points[2], points[3]);
    double d3 = DistanceBetween(points[3], points[0]);
    if (!(EqualSides(d0, d1) && EqualSides(d1, d2) && EqualSides(d2, d3))) throw 1;
  }
};

class Parallelogram : public Quadrilateral {
 public:
  Parallelogram(const std::string& name, const std::vector<Point>& points) : Quadrilateral(name, points) {
    Vector v0(points[0], points[1]);
    Vector v1(points[1], points[2]);
    Vector v2(points[2], points[3]);
    Vector v3(points[3], points[0]);
    if (!Parallel(v0, v2) || !Parallel(v1, v3)) throw 1;
  }
};

class Kite : public Quadrilateral {
 public:
  Kite(const std::string& name, const std::vector<Point>& points) : Quadrilateral(name, points) {
    double d0 = DistanceBetween(points[0], points[1]);
    double d1 = DistanceBetween(points[1], points[2]);
    double d2 = DistanceBetween(points[2], points[3]);
    double d3 = DistanceBetween(points[3], points[0]);
    if (!((EqualSides(d0, d1) && EqualSides(d2, d3)) || (EqualSides(d1, d2) && EqualSides(d3, d0)))) throw 1;
  }
};

class Trapezoid : public Quadrilateral {
 public:
  Trapezoid(const std::string& name, const std::vector<Point>& points) : Quadrilateral(name, points) {
    Vector v0(points[0], points[1]);
    Vector v1(points[1], points[2]);
    Vector v2(points[2], points[3]);
    Vector v3(points[3], points[0]);
    if (!Parallel(v0, v2) && !Parallel(v1, v3)) throw 1;
  }
};

#endif