#include "Subnet.h"
#include <algorithm>
#include <exception>
#include <iostream>

namespace subcalc {

	Subnet::Subnet(std::string ip, std::string mask){
		SetAddresses(ip, mask);
		if (!ValidateMask(this->mask))
			throw std::invalid_argument("Malformed Subnet Mask");
	}

	Subnet::Subnet(std::string ip, size_t mask){
		SetAddresses(ip, mask);
	}

	void Subnet::ConvertStringToBitset(std::string address, OUT std::bitset<8>(&bitset)[4]){
		size_t dotPos[3] = { 0,0,0 };
		
		for (int i = 0; i < 3; i++)
			dotPos[i] = address.find('.', (i > 0 ? dotPos[i - 1] + 1 : 0));

		if (dotPos[0] > 4 || dotPos[1] - dotPos[0] > 4 || dotPos[2] - dotPos[1] > 4 || address.size() - dotPos[2] > 4)
			throw std::invalid_argument("Malformed address");

		for (int i = 0; i < 4; i++) {
			try {
				int tmp = -1;
				std::string tmps = address.substr(((i > 0) ? dotPos[i - 1] + 1 : 0), (i < 3 ? dotPos[i] - (i > 0 ? dotPos[i - 1] : -1) - 1: address.size() - 1));
				if (std::all_of(tmps.begin(), tmps.end(), ::isdigit))
					tmp = std::stoi(tmps);

				if (tmp >= 0 && tmp <= 255)
					bitset[i] = tmp;
				else
					throw std::invalid_argument("Malformed address");
			}
			catch (std::exception&) {
				throw std::invalid_argument("Malformed address");
			}
		}
	}

	std::string Subnet::ConvertBitsetToString(const std::bitset<8>(&bitset)[4]) const{
		return std::to_string(bitset[0].to_ulong()) + "." 
		+ std::to_string(bitset[1].to_ulong()) + "." 
		+ std::to_string(bitset[2].to_ulong()) + "." 
		+ std::to_string(bitset[3].to_ulong());
	}

	void Subnet::ConvertMaskCountToBitset(size_t count, std::bitset<8>(&bitset)[4]){
		if(count < 8 || count > 31)
			throw std::invalid_argument("Malformed Subnet Mask");
		
		for (int i = 0; i <= 3; i++){
			if(count >= 8){
				bitset[i].set();
				count -= 8;
			}
			else if(count > 0){
				for (int j = 7; j >= 8-count; j--){
					bitset[i].set(j, true);
				}
				break;
			}

		}
	}

	bool Subnet::ValidateMask(const std::bitset<8>(&mask)[4]) const{
		for (int i = 0; i < 3; i++)
			if (!mask[i].all() && mask[i + 1].any())
				return false;
		
		for (int i = 0; i < 3; i++) 
			for (int j = 7; j > 0; j--) 
				if (!mask[i][j] && mask[i][j-1])
					return false;

		return true;
	}

	void Subnet::SetIP(std::string ip){
		ConvertStringToBitset(ip, this->ip);
	}

	void Subnet::SetMask(std::string mask){
		ConvertStringToBitset(mask, this->mask);
	}

	void Subnet::SetMask(size_t mask){
		ConvertMaskCountToBitset(mask, this->mask);
	}

	void Subnet::SetAddresses(std::string ip, std::string mask){
		SetIP(ip);
		SetMask(mask);
	}

	void Subnet::SetAddresses(std::string ip, size_t mask){
		SetIP(ip);
		SetMask(mask);
	}

	std::string Subnet::GetIP() const {
		return ConvertBitsetToString(ip);
	}

	std::string Subnet::GetMask() const {
		return ConvertBitsetToString(mask);
	}

	size_t Subnet::GetMaskCount() const {
		size_t tmp = 0;
		for (int i = 0; i <= 3; i++)
			tmp += mask[i].count();

		return tmp;
	}

	std::string Subnet::GetSubnet() const {
		std::bitset<8> subnet[4];
		
		for (int i = 0; i <= 3; i++)
			subnet[i] = ip[i] & mask[i];

		return ConvertBitsetToString(subnet) + "/" + std::to_string((int)GetMaskCount());
	}

	void Subnet::GetBitsetIP(OUT std::bitset<8>(&bitset)[4]){
		for(int i = 0; i <= 3; i++)
			bitset[i] = ip[i];
	}

	void Subnet::GetBitsetMask(OUT std::bitset<8>(&bitset)[4]){
		for(int i = 0; i <= 3; i++)
			bitset[i] = mask[i];
	}

	void Subnet::GetBitsetSubnet(OUT std::bitset<8>(&bitset)[4]){
		
		for(int i = 0; i <= 3; i++)
			bitset[i] = ip[i] & mask[i];
	}

	std::ostream& operator<<(std::ostream& stream, const Subnet& subnet) {
		stream << "IP: " << subnet.GetIP() << std::endl << "Subnet Mask: " << subnet.GetMask() << std::endl << "Subnet: " << subnet.GetSubnet();
		return stream;
	}

	Subnet::~Subnet()
	{
	}

}