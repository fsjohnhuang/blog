#pragma once
#include <iostream>
using namespace std;

class Complex {
public:
	// 构造函数
	Complex(string version, double r, double i = 0) // Default arguments(默认实参)
		: re (r), im (i) // Initialization list(初始列/初值列)
	{}
	// Overloading(重载)构造函数
	Complex() : re(1), im(1) {}

	// 静态方法，使用方式`类名::方法()`
	static Complex& getInstance() {
		return * new Complex();
	}

	// 静态数据，必须在类外部初始化
	static int version;
	// 静态方法可以通过 `类名::方法()` 或 `对象.方法()` 调用，且静态方法内仅能访问静态属性。
	static int set_version(int value) { version = value; }

	// 定义inline(内联)函数，编译器会根据函数内部逻辑决定是否最后编译为inline函数
	// getter函数。const标识该方法不会改变对象的属性。
	// 创建对象时若标识该对象为const `const Complex constComplex`, 那么constComplex仅能调用const标识的方法。
	// 成员函数，编译器会自动将 Complex* this 注入，因此可以通过`this->re`获取属性，或直接 `re` 获取属性。
	double real() const { return this->re; }	
	void real(double r) { re = r; } // setter函数

	// 仅声明方法，要在外部定义方法
	double imag() const;
	void imag(double);

	// 操作符重载
	// 其中 `const Complex&` 为 pass by reference (to const)，那么在方法中无法修改该实参的属性值
	// 而`Complex&` pass by reference，则可以在方法中修改实参的属性值
	// inline方式定义的操作符重载，默认自动添加`Complex* this`作为第一个形参，所以函数形参列表中不用添加 `Complex* this`。
	// 使用语法为 Complex c1; Complex c2(2,3); c1 += c2; 此时函数返回值并没有作用，而是表达式的left handside的实参的属性被更新了。
	// 操作符连用`c1 += c2 += c3`，从右到左计算。且此时函数返回值将作为下一轮计算的实参。
	Complex& operator += (const Complex& c) {
		re += c.re; // 由于形参c的类型和当前函数所属对象的类型的一致的，因此c和当前函数所属对象互为friend，即符合友元函数的规则。
		im += c.imag();

		// 随函数弹栈而销毁的数据不能返回该数据的引用或指针，即只能return by value。
		// 其它情况优先选择返回引用或指针，即return by reference。
		return *this;
	}

	Complex& operator -= (const Complex& c) {
		// 通过friend函数将实现延迟
		return __doaminus(this, c);
	}

	// conversion function(类型转换函数)
	// 将当前类型转为函数名指定的数据类型，且形参列表为空，返回类型为空。
	// 使用形式为 
	// 1. double(new Complex)
	// 2. double d = 4 + new Complex。
	// 注意：第二个使用形式，会先搜索函数签名为 double operator + (double a, const Complex& b) 的全局函数，若搜索失败再尝试将b转换为double。
	operator double() const {
		return 1000 * re + im;
	}

	// non-explicit-one-argument ctor
	// 将double转换为Complex
	// 使用形式为
	// Complex c = Complex(2,3) + 4; 将4转换为Complex(4)
	// 由于conversion function 和 non-explicit-one-argument ctor 并存，因此在调用 Complex c = Complex(3,4) + 4;时会出现到底是将Complex转double还是4转Complex的冲突。
	// 通过将non-explicit-one-argument ctor改写为explicit-one-argument ctor，禁止隐式将4转换为Complex，解决冲突。
	// explicit Complex(double r, double i = 0) : re(r), im(i) {}
	// 然后要显式指定转换方式：Complex c = Complex(3,4) + Complex(4)
	Complex(double r, double i = 0) : re(r), im(i) {}
	// 操作符重载，使用形式为 `Complex() + Complex()`
	Complex operator + (const Complex& c) {
		return Complex(this->re + c.re, this->im + c.im);
	}

	// 析构函数，在对象被销毁前执行。若内部没有使用指针(pointer free)，那么一般不用写析构函数。
	// 若对象被分配在栈中，那么出栈时会自动被执行；
	// 若对象被分配在堆中，则需要通过delete触发对象的销毁。
	~Complex() {
		std::cout << "~" << im << std::endl;
	}
private:
	// 类的对象属性
	double re, im;

	// friend(友元)函数
	// 类中仅能包含友元函数的声明时, 则必须由外部实现友元函数的定义，并且可以在友元函数内部获取对象的protected,private的属性和方法。
	// 注意：相同class的各个object互为friend(友元)
	friend double __realPlusImag(Complex*);

	// 类中定义友元函数，则外部无法重新定义该友元函数
	friend Complex& __doaminus(Complex* c, const Complex& o) {
		c->re -= o.re;
		c->im -= o.im;
		return *c;
	}
};

// 外部定义类实例方法
double Complex::imag() const {
	return im;
}

// 外部定义类实例方法,并标识为inline函数，但编译器会根据函数内部逻辑决定是否最后编译为inline函数
inline void Complex::imag(double i) {
	im = i;
}

// 非成员函数的方式，实现操作符重载
// 这里采用return by value
// 若表达式的left handside不是当前定义类型，而right handside为当前定义的类型，则只能通过非成员函数方式实现操作符重载
Complex operator + (const Complex& x, const Complex& y) {
	// temp object(临时对象)，没有名称且其生命周期到下一行即结束
	// 语法 `typename()`
	return Complex(x.real() + y.real(), x.imag() + y.imag());
}

// <<操作符运算顺序为从左到右
ostream& operator << (ostream& os, const Complex& c){
	return os << '(' << c.real() << ',' << c.imag() << ')';
}

int Complex::version = 1;
