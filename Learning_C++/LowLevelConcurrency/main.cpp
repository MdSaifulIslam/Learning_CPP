#include <iostream>
#include <list>
#include <thread>

using namespace std;

list<int> d_Data;
const int SIZE = 9000000;

void download() {

	cout << "[Downloader] Started download" << endl;
	for (int i = 0; i < SIZE; i++) {
		d_Data.push_back(i);
	}
	cout << "[Downloader] Finished download" << endl;
}

int main() {

	cout << "[main] User Operation Started" << endl;
	thread thDownloader(download);
	thDownloader.detach();

	cout << "[main] User started another operation" << endl;
	if (thDownloader.joinable()) { thDownloader.join(); }

	system("Pause");
	return 0;
}