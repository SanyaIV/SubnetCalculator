#include "IP.h"
#include "SubnetMask.h"
#include "Subnet.h"
#include <exception>
#include <iostream>

using namespace subcalc;

int main() {
	try {
		IP ip("192.168.0.10");
		SubnetMask mask("255.255.255.0");
		Subnet subnet(ip, mask);
		std::cout << ip << std::endl << mask << std::endl << subnet << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}