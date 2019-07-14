#ifndef SUBNET_H
#define SUBNET_H
#include <string>
#include <ostream>
#include <bitset>
#define OUT

namespace subcalc {

	//TODO: Rewrite as functional programming instead of class based.
	class Subnet
	{
	public:
		Subnet(std::string ip, std::string mask);
		Subnet(std::string ip, size_t mask);
		~Subnet();
		friend std::ostream& operator<<(std::ostream& stream, const Subnet& subnet);
		void SetIP(std::string ip);
		void SetMask(std::string mask);
		void SetMask(size_t mask);
		void SetAddresses(std::string ip, std::string mask);
		void SetAddresses(std::string ip, size_t mask);
		std::string GetIP() const;
		std::string GetMask() const;
		size_t GetMaskCount() const;
		std::string GetSubnet() const;
		void GetBitsetIP(OUT std::bitset<8>(&bitset)[4]);
		void GetBitsetMask(OUT std::bitset<8>(&bitset)[4]);
		void GetBitsetSubnet(OUT std::bitset<8>(&bitset)[4]);

	private:
		std::bitset<8> ip[4];
		std::bitset<8> mask[4];

		void ConvertStringToBitset(std::string address, OUT std::bitset<8>(&bitset)[4]);
		std::string ConvertBitsetToString(const std::bitset<8>(&bitset)[4]) const;
		void ConvertMaskCountToBitset(size_t count, OUT std::bitset<8>(&bitset)[4]);
		bool ValidateMask(const std::bitset<8>(&mask)[4]) const;
	};

}
#endif