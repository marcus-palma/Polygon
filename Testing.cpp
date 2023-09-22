// Testing pointer-to-class-member-function. Unfortunately, parent and child pointers are not compatible with each other

/*

#include <functional>

//typedef  int (Fred::*FredMemFn)(char x, float y);  // Please do this!

class MyClass {
public:
	int TestFunction() { return 1 + 1; };
};

class MySubClass : public MyClass {
public:
	int TestSubFunction();
};

void Main() {
	MySubClass MySubClass_inst;
	MySubClass_inst.TestSubFunction();
};

int MySubClass::TestSubFunction() {
	typedef int (MyClass::*MyClassFuncP)();
	MyClassFuncP p = &MySubClass::TestSubFunction;
	MyClassFuncP p2 = &MyClass::TestFunction;
	int (MyClass::*MemberP)() = &MyClass::TestFunction;
	//int i = std::invoke(p);
	this->*p;

	int (MyClass::*p3)() = static_cast<int (MyClass::*)()>(&MySubClass::TestSubFunction);

	MySubClass MSC;
	MyClass* MCP = &MSC;
	(MCP->*p3)();
	
}

*/