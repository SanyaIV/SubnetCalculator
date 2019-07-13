#ifndef SUBNET_H
#define SUBNET_H
#include <string>
#include <ostream>
#include <bitset>
#define OUT

namespace subcalc {

	class Subnet
	{
	public:
		Subnet(std::string ip, std::string mask);
		Subnet(std::string ip, unsigned int mask);
		~Subnet();
		friend std::ostream& operator<<(std::ostream& stream, const Subnet& subnet);
		std::string GetIP() const;
		std::string GetMask() const;
		size_t GetMaskCount() const;
		std::string GetSubnet() const;

	private:
		std::bitset<8> ip[4];
		std::bitset<8> mask[4];

		void ConvertStringToBitset(std::string address, OUT std::bitset<8>(&bitset)[4]);
		bool ValidateMask(const std::bitset<8>(&mask)[4]) const;
	};

}
#endif