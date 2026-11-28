#include <iostream>
#include <list>
#include <thread>

using namespace std;

list<int> d_Data;
const int SIZE = 9000000;

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

void download(const String &file) {

	cout << "[Downloader] Started download the file: " << file << endl;
	for (int i = 0; i < SIZE; i++) {
		d_Data.push_back(i);
	}
	cout << "[Downloader] Finished download" << endl;
}

int main() {

	String file;
	cout << "[main] User Operation Started" << endl;
	thread thDownloader(download, cref(file));
	//thDownloader.detach();

	cout << "[main] User started another operation" << endl;
	if (thDownloader.joinable()) { thDownloader.join(); }

	//system("Pause");
	return 0;
}