#include "SubnetMask.h"
#include <exception>
#include <iostream>

namespace subcalc {

	SubnetMask::SubnetMask(std::string address) : IP(address){
		if (!validate())
			throw std::invalid_argument("Malformed Subnet Mask");
	}

	int SubnetMask::count() const {
		int tmp = 0;
		for (int i = 0; i < 3; i++)
			tmp += (int)address[i].count();

		return tmp;
	}

	bool SubnetMask::validate() {
		for (int i = 0; i < 3; i++)
			if (!address[i].all() && address[i + 1].any())
				return false;
		
		for (int i = 0; i < 3; i++) 
			for (int j = 7; j > 0; j--) 
				if (!address[i][j] && address[i][j-1])
					return false;

		return true;
	}

	SubnetMask::~SubnetMask()
	{
	}
}