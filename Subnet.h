#pragma once

#include <bitset>
#include <cstddef>
#include <string>

class Subnet
{
public:
	inline static std::uint_fast8_t constexpr OCTET_MASK_BITSHIFTS[4] = {24, 16, 8, 0};
	inline static std::bitset<32> constexpr OCTET_MASKS[4] = {
		static_cast<std::uint32_t>(255<<OCTET_MASK_BITSHIFTS[0]),
		static_cast<std::uint32_t>(255<<OCTET_MASK_BITSHIFTS[1]),
		static_cast<std::uint32_t>(255<<OCTET_MASK_BITSHIFTS[2]),
		static_cast<std::uint32_t>(255<<OCTET_MASK_BITSHIFTS[3])
	};
	
	//Delete default generations
	Subnet() 							= delete;
	Subnet(const Subnet&) 				= delete;
	Subnet& operator=(const Subnet&) 	= delete;
	Subnet(Subnet&&) 					= delete;
	Subnet& operator=(Subnet&&) 		= delete;
	~Subnet() 							= delete;

	static std::bitset<32> StringToIP(const std::string& address);
	static std::bitset<32> StringToMask(const std::string& mask);
	static std::string BitsetToString(const std::bitset<32>& bitset);

	static std::bitset<32> MaskCountToMask(std::size_t count);
	static std::size_t MaskToMaskCount(const std::bitset<32>& mask);
	static std::bitset<32> GetMaskFromHostCount(std::size_t count);
	static bool ValidateMask(const std::bitset<32>& mask);

	static std::bitset<32> GetSubnet(const std::bitset<32>& ip, const std::bitset<32>& mask);
	static std::bitset<32> GetSubnet(const std::bitset<32>& ip, std::size_t maskCount);
	static std::bitset<32> GetSubnet(const std::string& ip, const std::string& mask);
	static std::bitset<32> GetSubnet(const std::string& ip, std::size_t maskCount);

	static std::bitset<32> GetMinHost(const std::bitset<32>& ip, const std::bitset<32>& mask);
	static std::bitset<32> GetMaxHost(const std::bitset<32>& ip, const std::bitset<32>& mask);
	static void GetHostRange(const std::bitset<32>& ip, const std::bitset<32>& mask, std::bitset<32>& minimumHost, std::bitset<32>& maximumHost);
	static std::bitset<32> GetBroadcast(const std::bitset<32>& ip, const std::bitset<32>& mask);
};
