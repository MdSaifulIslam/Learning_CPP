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
	shared_ptr<Project> e_pName{};
public:
	void SetProject(const shared_ptr<Project>& prj) {
		e_pName = prj;
	}
	const shared_ptr<Project>& Getproject()const {
		return e_pName;
	}
};

void ShowInfo(shared_ptr<Employee>& emp) {
	cout << "Employee project details: ";
	emp->Getproject()->ShowProjectDetails();
}

class Printer {
	weak_ptr<int> m_pValue;
public:
	void setValue(weak_ptr<int> p) {
		m_pValue = p;
	}
	void Print() {
		cout << "Ref count: " << m_pValue.use_count() << endl;
		if (m_pValue.expired()) {
			cout << "Resource not available";
			return;
		}
		auto sp = m_pValue.lock();
		cout << "Value is: " << *sp << endl;
		cout << "Ref count: " << sp.use_count() << endl;
	}
};

int main() {

	Printer prn;
	int num{};
	cin >> num;
	shared_ptr<int> p{ new int{num} };

	prn.setValue(p);

	if (*p > 10) {
		p = nullptr;
	}
	prn.Print();

	////Operate(105);
	//shared_ptr<Project> prj{ new Project{} };
	//prj->SetName("Video decoder");

	//shared_ptr<Employee> e1{ new Employee{} };
	//e1->SetProject(prj);

	//shared_ptr<Employee> e2{ new Employee{} };
	//e2->SetProject(prj);

	//shared_ptr<Employee> e3{ new Employee{} };
	//e3->SetProject(prj);
	//e3 = nullptr; //ref count decreases by 1, also work: e3.reset();

	//cout << "project ref count: " << prj.use_count() << endl;

	//ShowInfo(e1);
	//ShowInfo(e2);

	//prj->ShowProjectDetails();

	return 0;
}
