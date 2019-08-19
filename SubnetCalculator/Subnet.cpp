#include "Subnet.h"
#include <algorithm>
#include <exception>

namespace subcalc {

	Subnet::Subnet(std::string ip, std::string mask){
		SetAddresses(ip, mask);
		if (!ValidateMask(this->mask))
			throw std::invalid_argument("Malformed Subnet Mask");
	}

	Subnet::Subnet(std::string ip, std::uint8_t maskCount){
		SetAddresses(ip, maskCount);
	}

	std::bitset<32> Subnet::ConvertStringToBitset(std::string address){
		std::bitset<32> address2 = 0;
		size_t dotPos[3] = { 0,0,0 };
		
		for (int i = 0; i < 3; i++)
			dotPos[i] = address.find('.', (i > 0 ? dotPos[i - 1] + 1 : 0));

		if (dotPos[0] > 4 || dotPos[1] - dotPos[0] > 4 || dotPos[2] - dotPos[1] > 4 || address.size() - dotPos[2] > 4)
			throw std::invalid_argument("Malformed address");

		for (int i = 0; i < 4; i++) {
			try {
				int octet = -1;
				std::string octet_string = address.substr(((i > 0) ? dotPos[i - 1] + 1 : 0), (i < 3 ? dotPos[i] - (i > 0 ? dotPos[i - 1] : -1) - 1: address.size() - 1));
				if (std::all_of(octet_string.begin(), octet_string.end(), ::isdigit))
					octet = std::stoi(octet_string);

				if (octet >= 0 && octet <= 255)
					address2 |= std::bitset<32>(octet<<OCTET_MASK_BITSHIFTS[i]) & OCTET_MASKS[i];
				else 
					throw std::invalid_argument("Malformed address");
			}
			catch (std::exception&) {
				throw std::invalid_argument("Malformed address");
			}
		}

		return address2;
	}

	std::string Subnet::ConvertBitsetToString(std::bitset<32> bitset){
		std::string rvalue;
		for(int i = 0; i <= 3; i++){
			rvalue += std::to_string(((bitset & OCTET_MASKS[i]) >> OCTET_MASK_BITSHIFTS[i]).to_ulong());
			if(i != 3)
				rvalue += ".";
		}
		
		return rvalue;
	}

	std::bitset<32> Subnet::ConvertMaskCountToBitset(std::uint8_t count){
		std::bitset<32> bitset;

		if(count < 8 || count > 31)
			throw std::invalid_argument("Malformed Subnet Mask");
		
		for (int i = 31; i >= 32-count; i--)
			bitset.set(i, true);

		return bitset;
	}

	bool Subnet::ValidateMask(std::bitset<32> const & mask){
		for (int i = 31; i > 0; i--)
			if (!mask[i] && mask[i-1])
				return false;

		return true;
	}

	void Subnet::SetIP(std::string ip){
		this->ip = ConvertStringToBitset(ip);
	}

	void Subnet::SetMask(std::string mask){
		this->mask = ConvertStringToBitset(mask);
	}

	void Subnet::SetMask(std::uint_fast8_t mask){
		this->mask = ConvertMaskCountToBitset(mask);
	}

	void Subnet::SetAddresses(std::string ip, std::string mask){
		SetIP(ip);
		SetMask(mask);
	}

	void Subnet::SetAddresses(std::string ip, std::uint_fast8_t mask){
		SetIP(ip);
		SetMask(mask);
	}

	std::string Subnet::GetIP() const {
		return ConvertBitsetToString(ip);
	}

	std::string Subnet::GetMask() const {
		return ConvertBitsetToString(mask);
	}

	std::uint_fast8_t Subnet::GetMaskCount() const {
		return mask.count();
	}

	std::string Subnet::GetSubnet() const {
		std::bitset<32> subnet = ip & mask;
		return ConvertBitsetToString(subnet) + "/" + std::to_string(GetMaskCount());
	}

	std::bitset<32> Subnet::GetBitsetIP() const {
		return ip;
	}

	std::bitset<32> Subnet::GetBitsetMask() const {
		return mask;
	}

	std::bitset<32> Subnet::GetBitsetSubnet() const {
		return ip & mask;
	}

	std::ostream& operator<<(std::ostream& stream, const Subnet& subnet) {
		stream << "IP: " << subnet.GetIP() << std::endl << "Subnet Mask: " << subnet.GetMask() << std::endl << "Subnet: " << subnet.GetSubnet();
		return stream;
	}
}