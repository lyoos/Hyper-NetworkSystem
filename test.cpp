#include<iostream>
#include<sstream>
#include<regex>
#include <functional>
#include"hypns.hpp"

using namespace std;
using namespace hns;

void timeit(std::function<void()> func) {
	std::clock_t start = std::clock();
	func();
	int ms = (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000);
	std::cout << "# " << ms << "ms" << std::endl;
}

void test() {
	PackageHandler pvi("<PACKAGE pType=\"INITD\"FRM=\"P192:ssdfds:dfsdf:sdfdf:dsf\" TO=\"PR92:AFSD:AWFS\"><OBJECT oType=\"BIN\">Hallo Welt</OBJECT><OBJECT oType=\"BIN\">Hallo Welt</OBJECT><OBJECT oType=\"BIN\">Hallo Welt</OBJECT></PACKAGE>");
	if (pvi.coutpck() == true) {
		Package newPackage = pvi.GivePackage();
		cout << "Ist Package " << endl;
	}
}

int main() {




	timeit([] {
		test();
	});
	IDvString ts;
	ts = SelfID();


	getchar();
	
	return 0;
}
