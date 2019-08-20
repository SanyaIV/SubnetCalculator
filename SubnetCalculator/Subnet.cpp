#include "Subnet.h"
#include <algorithm>
#include <exception>

auto Subnet::StringToIP(std::string address) -> std::bitset<32>
{
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
auto Subnet::StringToMask(std::string mask) -> std::bitset<32>
{
	auto bitsetMask = StringToIP(mask);
	if(ValidateMask(bitsetMask))
		return bitsetMask;
	else
		throw std::invalid_argument("Malformed subnet mask");
}
auto Subnet::BitsetToString(const std::bitset<32>& bitset) -> std::string
{
	std::string rvalue;
	for(int i = 0; i <= 3; i++){
		rvalue += std::to_string(((bitset & OCTET_MASKS[i]) >> OCTET_MASK_BITSHIFTS[i]).to_ulong());
		if(i != 3)
			rvalue += ".";
	}
	
	return rvalue;
}

auto Subnet::MaskCountToMask(std::size_t count) -> std::bitset<32>
{
	std::bitset<32> bitset;

	if(count < 8 || count > 31)
		throw std::invalid_argument("Malformed Subnet Mask");
	
	for (int i = 31; i >= 32-count; i--)
		bitset.set(i, true);

	return bitset;
}
auto MaskToMaskCount(const std::bitset<32>& mask) { return mask.count(); }
auto Subnet::ValidateMask(const std::bitset<32>& mask) -> bool 
{
	for (int i = 31; i > 0; i--)
		if (!mask[i] && mask[i-1])
			return false;

	return true;
}

auto Subnet::GetSubnet(const std::bitset<32>& ip, const std::bitset<32>& mask)	-> std::bitset<32> { return ip & mask; }
auto Subnet::GetSubnet(const std::bitset<32>& ip, std::size_t maskCount) 		-> std::bitset<32> { return ip & MaskCountToMask(maskCount); }
auto Subnet::GetSubnet(std::string ip, std::string mask) 						-> std::bitset<32> { return StringToIP(ip) & StringToMask(mask); }
auto Subnet::GetSubnet(std::string ip, std::size_t maskCount) 					-> std::bitset<32> { return StringToIP(ip) & MaskCountToMask(maskCount); }


auto Subnet::GetMinHost(const std::bitset<32>& ip, const std::bitset<32>& mask) -> std::bitset<32>{ return (ip & mask).set(0, true); }
auto Subnet::GetMaxHost(const std::bitset<32>& ip, const std::bitset<32>& mask) -> std::bitset<32>{ return ((ip & mask) | std::bitset<32>(mask).flip()).set(0, false); }
void Subnet::GetHostRange(const std::bitset<32>& ip, const std::bitset<32>& mask, std::bitset<32>& minimumHost, std::bitset<32>& maximumHost)
{
	minimumHost = GetMinHost(ip, mask);
	maximumHost = GetMaxHost(ip, mask);
}
auto Subnet::GetBroadcast(const std::bitset<32>& ip, const std::bitset<32>& mask) 		-> std::bitset<32> { return (ip & mask) | std::bitset<32>(mask).flip(); }