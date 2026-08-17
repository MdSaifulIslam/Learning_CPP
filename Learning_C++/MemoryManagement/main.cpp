#include<iostream>
#include "Integer.h"

using namespace std;

void Display(Integer* p) {
	if (!p) {
		return;
	}
	cout << p->getValue() << endl;
}

Integer* GetPointer(int value) {
	Integer* p = new Integer{value};
	return p;
}

void copyData(unique_ptr<Integer> &ptr) { // NO '&' HERE!
	cout << "Copying value in a file: " << ptr->getValue() << endl;
}

void Store(unique_ptr<Integer> &p) {
	cout << "Storing value in a file: " << p->getValue() << endl;
	p->setValue(77);
	*p = 700;
	/*
	What the compiler actually generates for *p = 700:
	Integer temp(700);        // ① implicit construction — "Integr(int value)"
	*p = temp;                // ② copy assignment operator runs
	temp.~Integer();          // ③ temp destroyed — "~Integr()"

	This is the reason, there is extra initialization like following:
	Integr(int value)
	~Integr()
	*/
	copyData(p);
}

void Operate(int value) {
	//Integer* p = GetPointer(value);
	unique_ptr<Integer> p{ GetPointer(value) };
	if (p == nullptr) {
		p.reset(new Integer{ value });
	}

	p->setValue(100);
	Display(p.get());
	//delete p;
	//p = nullptr;

	//p = new Integer{};
	p.reset(new Integer{});
	*p = __LINE__;
	Display(p.get());
	Store(p);
	*p = 200;
	Display(p.get());
	//delete p;
}

class Project {
	string p_Name;
public:
	void SetName(const string& name) {
		p_Name = name;
	}
	void ShowProjectDetails()const {
		cout << "[Project Name]: " << p_Name << endl;
	}
};

class Employee {
	Project *e_pName{};
public:
	void SetProject(Project* prj) {
		e_pName = prj;
	}
	const Project* Getproject()const {
		return e_pName;
	}
};

void ShowInfo(Employee* emp) {
	cout << "Employee project details: ";
	emp->Getproject()->ShowProjectDetails();
}

int main() {

	//Operate(105);
	Project* prj = new Project{};
	prj->SetName("Video decoder");

	Employee* e1 = new Employee{};
	e1->SetProject(prj);

	Employee* e2 = new Employee{};
	e2->SetProject(prj);

	Employee* e3 = new Employee{};
	e3->SetProject(prj);

	ShowInfo(e1);
	ShowInfo(e2);

	prj->ShowProjectDetails();

	delete prj;
	delete e1;
	delete e2;
	delete e3;

	return 0;
}
