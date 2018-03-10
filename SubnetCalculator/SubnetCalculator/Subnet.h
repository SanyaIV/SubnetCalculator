#ifndef SUBNET_H
#define SUBNET_H
#include "SubnetMask.h"
#include "IP.h"

namespace subcalc {

	class Subnet : public IP
	{
	public:
		Subnet(const IP& ip, const SubnetMask& mask);
		~Subnet();
		friend std::ostream& operator<<(std::ostream& stream, const Subnet& subnet);

	private:
		void updateSubnet();

		SubnetMask mask;
	};

}
#endif