#include "Subnet.h"
#include <exception>
#include <iostream>

using namespace subcalc;

int main() {
	try {
		Subnet a("192.168.0.67", "255.255.255.0");
		Subnet b("10.10.10.10", "255.255.255.128");
		Subnet c("255.255.255.255", 14);
		Subnet d("255.255.255.255", 24);
		std::cout << a << std::endl << b << std::endl << c << std::endl << d << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}