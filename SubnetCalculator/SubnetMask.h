#ifndef SUBNETMASK_H
#define SUBNETMASK_H
#include "IP.h"
#include <string>

namespace subcalc {

	class SubnetMask : public IP
	{
	public:
		SubnetMask(std::string address);
		~SubnetMask();
		int count() const;
	private:
		bool validate();
	};

}
#endif