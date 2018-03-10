#include "Subnet.h"

namespace subcalc {

	Subnet::Subnet(const IP& ip, const SubnetMask& mask) : IP(ip), mask(mask){
		updateSubnet();
	}

	std::ostream& operator<<(std::ostream& stream, const Subnet& subnet) {
		stream << (IP)subnet << "/" << subnet.mask.count();
		return stream;
	}

	void Subnet::updateSubnet() {

		std::bitset<8> tmp[4];
		mask.getBitset(tmp);

		for (int i = 0; i < 3; i++)
			address[i] &= tmp[i];
	}


	Subnet::~Subnet()
	{
	}

}