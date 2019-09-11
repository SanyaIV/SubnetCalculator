#include "Subnet.h"
#include <algorithm>
#include <cmath>
#include <exception>
#include <ostream>

std::bitset<32> Subnet::StringToIP(const std::string& address)
{
	std::bitset<32> address2 = 0;
	std::size_t dotPos[3] = { 0,0,0 };
	
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
std::bitset<32> Subnet::StringToMask(const std::string& mask)
{
	auto bitsetMask = StringToIP(mask);
	if(ValidateMask(bitsetMask))
		return bitsetMask;
	else
		throw std::invalid_argument("Malformed subnet mask");
}
std::string Subnet::BitsetToString(const std::bitset<32>& bitset)
{
	std::string rvalue("");
	for(int i = 0; i <= 3; i++){
		rvalue += std::to_string(((bitset & OCTET_MASKS[i]) >> OCTET_MASK_BITSHIFTS[i]).to_ulong());
		if(i != 3)
			rvalue += ".";
	}
	
	return rvalue;
}

std::bitset<32> Subnet::MaskCountToMask(std::size_t count)
{
	std::bitset<32> bitset(0);

	if(count < 8 || count > 31)
		throw std::invalid_argument("Malformed subnet mask");
	
	for (int i = 31; i >= 32-count; i--)
		bitset.set(i, true);

	return bitset;
}
std::size_t Subnet::MaskToMaskCount(const std::bitset<32>& mask) { return mask.count(); }
std::bitset<32> Subnet::GetMaskFromHostCount(std::size_t count)
{
	static constexpr int ADDITIONAL_REQUIRED_HOSTS = 2;
	std::size_t exponent = static_cast<std::size_t>(std::ceil(std::log2(count + ADDITIONAL_REQUIRED_HOSTS)));

	if(exponent >= 32)
		throw std::invalid_argument("Too many hosts");
	else if (exponent <= 1)
		throw std::invalid_argument("Too few hosts");

	exponent = ~((1 << exponent) - 1); //inverted bit shift of 2^exponent - 1
	std::bitset<32> mask(exponent);

	if(ValidateMask(mask))
		return mask;
	else
		throw std::invalid_argument("Mask failed validation");
}
bool Subnet::ValidateMask(const std::bitset<32>& mask)
{
	for (int i = 31; i > 0; i--)
		if (!mask[i] && mask[i-1])
			return false;

	return true;
}

std::bitset<32> Subnet::GetSubnet(const std::bitset<32>& ip, const std::bitset<32>& mask)	{ return ip & mask; }
std::bitset<32> Subnet::GetSubnet(const std::bitset<32>& ip, std::size_t maskCount) 	 	{ return ip & MaskCountToMask(maskCount); }
std::bitset<32> Subnet::GetSubnet(const std::string& ip, const std::string& mask) 			{ return StringToIP(ip) & StringToMask(mask); }
std::bitset<32> Subnet::GetSubnet(const std::string& ip, std::size_t maskCount) 			{ return StringToIP(ip) & MaskCountToMask(maskCount); }

std::bitset<32> Subnet::GetMinHost(const std::bitset<32>& ip, const std::bitset<32>& mask) 	{ return (ip & mask).set(0, true); }
std::bitset<32> Subnet::GetMaxHost(const std::bitset<32>& ip, const std::bitset<32>& mask) 	{ return ((ip & mask) | std::bitset<32>(mask).flip()).set(0, false); }
void Subnet::GetHostRange(const std::bitset<32>& ip, const std::bitset<32>& mask, std::bitset<32>& minimumHost, std::bitset<32>& maximumHost)
{
	minimumHost = GetMinHost(ip, mask);
	maximumHost = GetMaxHost(ip, mask);
}
std::bitset<32> Subnet::GetBroadcast(const std::bitset<32>& ip, const std::bitset<32>& mask) { return (ip & mask) | std::bitset<32>(mask).flip(); }