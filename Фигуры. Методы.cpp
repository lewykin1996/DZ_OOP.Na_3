#include <iostream>
#include <string>

using namespace std;


class Figure {
protected:
	string name;
	int sides_count;

public:
	Figure(string n = "Фигура", int sides = 0)
		: name(n), sides_count(sides) {}

	virtual bool check() const {
		return sides_count == 0;
	}

	virtual void print_info() const {
		cout << name << ":\n";
		cout << (check() ? "Правильная" : "Неправильная") << "\n";
		cout << "Количество сторон: " << sides_count << "\n";
	}

	virtual ~Figure() {}
};

//ТРЕУГОЛЬНИК

class Triangle : public Figure {
protected:
	int a, b, c;
	int A, B, C;

public:
	Triangle(int a, int b, int c, int A, int B, int C)
		: Figure("Треугольник", 3),
		a(a), b(b), c(c),
		A(A), B(B), C(C) {}

	bool check() const override {
		return (a > 0 && b > 0 && c > 0) &&
			(A + B + C == 180);
	}

	void print_info() const override {
		Figure::print_info();
		cout << "Стороны: a=" << a << " b=" << b << " c=" << c << "\n";
		cout << "Углы: А=" << A << " B=" << B << " C=" << C << "\n";
	}
};

// Прямоугольный треугольник
class RightTriangle : public Triangle {
public:
	RightTriangle(int a, int b, int c, int A, int B)
		: Triangle(a, b, c, A, B, 90) {
		name = "Прямоугольный треугольник";
	}

	bool check() const override {
		return Triangle::check() &&
			(C == 90) &&
			(a * a + b * b == c * c);
	}
};

// Равнобедренный
class IsoscelesTriangle : public Triangle {
public:
	IsoscelesTriangle(int a, int b, int A, int B)
		: Triangle(a, b, a, A, B, A) {
		name = "Равнобедренный треугольник";
	}

	bool check() const override {
		return Triangle::check() &&
			(a == c && A == C);
	}
};

// Равносторонний
class EquilateralTriangle : public Triangle {
public:
	EquilateralTriangle(int a)
		: Triangle(a, a, a, 60, 60, 60) {
		name = "Равносторонний треугольник";
	}

	bool check() const override {
		return Triangle::check() &&
			(a == b && b == c &&
				A == 60 && B == 60 && C == 60);
	}
};

//ЧЕТЫРЁХУГОЛЬНИК

class Quadrangle : public Figure {
protected:
	int a, b, c, d;
	int A, B, C, D;

public:
	Quadrangle(int a, int b, int c, int d,
		int A, int B, int C, int D)
		: Figure("Четырёхугольник", 4),
		a(a), b(b), c(c), d(d),
		A(A), B(B), C(C), D(D) {}

	bool check() const override {
		return (a > 0 && b > 0 && c > 0 && d > 0) &&
			(A + B + C + D == 360);
	}

	void print_info() const override {
		Figure::print_info();
		cout << "Стороны: a=" << a << " b=" << b
			<< " c=" << c << " d=" << d << "\n";
		cout << "Углы: A=" << A << " B=" << B
			<< " C=" << C << " D=" << D << "\n";
	}
};

// Параллелограмм
class Parallelogram : public Quadrangle {
public:
	Parallelogram(int a, int b, int A, int B)
		: Quadrangle(a, b, a, b, A, B, A, B) {
		name = "Параллелограмм";
	}

	bool check() const override {
		return Quadrangle::check() &&
			(a == c && b == d &&
				A == C && B == D);
	}
};

// Прямоугольник
class Rectangle : public Parallelogram {
public:
	Rectangle(int a, int b)
		: Parallelogram(a, b, 90, 90) {
		name = "Прямоугольник";
	}

	bool check() const override {
		return Parallelogram::check() &&
			(A == 90 && B == 90 &&
				C == 90 && D == 90);
	}
};

// Ромб
class Rhombus : public Parallelogram {
public:
	Rhombus(int a, int A, int B)
		: Parallelogram(a, a, A, B) {
		name = "Ромб";
	}

	bool check() const override {
		return Parallelogram::check() &&
			(a == b && b == c && c == d);
	}
};

// Квадрат
class Square : public Rectangle {
public:
	Square(int a)
		: Rectangle(a, a) {
		name = "Квадрат";
	}

	bool check() const override {
		return Rectangle::check() &&
			(a == b && b == c && c == d);
	}
};


int main() {
	setlocale(LC_ALL, "Russian");

	Figure f;
	Triangle t(10, 20, 30, 50, 60, 70);
	RightTriangle rt1(10, 20, 30, 50, 60);
	RightTriangle rt2(10, 20, 30, 50, 40);
	IsoscelesTriangle it(10, 20, 50, 60);
	EquilateralTriangle et(30);

	Quadrangle q(10, 20, 30, 40, 50, 60, 70, 80);
	Rectangle r(10, 20);
	Square s(20);
	Parallelogram p(20, 30, 30, 40);
	Rhombus rh(30, 30, 40);

	Figure* figures[] = {
		&f, &t, &rt1, &rt2, &it, &et,
		&q, &r, &s, &p, &rh
	};

	for (Figure* fig : figures) {
		fig->print_info();
		cout << endl;
	}

	return 0;
}