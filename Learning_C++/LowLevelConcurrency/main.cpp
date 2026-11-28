#include <iostream>
#include <list>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include <Windows.h>

using namespace std;

list<int> d_Data;
const int len = 100000;

class String {
public:
	//string f_Name;
	String() { cout << "String()" << endl; }
	//String(const string &name) : f_Name(name) { cout << "String(const String &name)" << endl; }
	String(const String&) { cout << "String(const String&)" << endl; }
	String& operator=(const String&) {
		cout << "operator=(const String&)" << endl;
		return *this;
	}
	friend ostream& operator<<(ostream& os, const String & str) { return os << "file"; }
	~String() { cout << "~String()" << endl; }
};

mutex d_Mutex;
void download() {

	for (int i = 0; i < len; i++) {
		lock_guard<mutex> mtx(d_Mutex);
		d_Data.push_back(i);
		if (i == 700) return;
	}
}

void download2() {

	for (int i = 0; i < len; i++) {
		lock_guard<mutex> mtx(d_Mutex);
		d_Data.push_back(i);
	}
}

int Add(int x, int y) { return x + y; }
int Square(int x) { return x * x; }

int Compute(const vector<int> &data) {
	int sum{};
	for (auto e : data) {
		sum += e;
		this_thread::sleep_for(chrono::seconds(1));
		cout << ".";
	}
	return sum;
}

void Process(){

	cout << "Thread ID: " << this_thread::get_id() << endl;
	for (int i = 0; i < 10; i++) {
		cout << i << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}

}

int main() {

	thread t1{ Process };
	HANDLE hndl = t1.native_handle();
	SetThreadDescription(hndl, L"T1-Peocess Thread");

	auto id = t1.get_id();
	cout << "Process ID: " << id << endl;

	int cores = thread::hardware_concurrency();
	cout << "Cores: " << cores << endl;
	cout << "Printing ... " << endl;

	t1.join();

	//thread thDownloader(download);
	//thread thDownloader2(download2);

	//thDownloader.join();
	//thDownloader2.join();

	//cout << d_Data.size() << endl;

	//String file;
	//cout << "[main] User Operation Started" << endl;
	//thread thDownloader(download, cref(file));
	////thDownloader.detach();

	//cout << "[main] User started another operation" << endl;
	//if (thDownloader.joinable()) { thDownloader.join(); }

	//system("Pause");

	//packaged_task<int(int, int)> taskAdd(Add);
	//future<int> ft = taskAdd.get_future();
	//taskAdd(3, 5);
	//auto result = ft.get();
	//cout << result << endl;

	//packaged_task<int(int)> taskSquare(Square);
	//future<int> fsq = taskSquare.get_future();
	//taskSquare(5);
	//result = fsq.get();
	//cout << result << endl;

	//packaged_task<int(const vector<int>&)> taskCompute(Compute);
	//future<int> fCompute = taskCompute.get_future();
	//vector<int> data{ 1, 2, 3, 4, 5 };
	////taskCompute(data);

	//thread threadCompute{ move(taskCompute), data };
	//cout << "Thread has started computing [ 1sec interval]" << endl;

	//result = fCompute.get();
	//cout << result << endl;

	//threadCompute.join();
	return 0;
}