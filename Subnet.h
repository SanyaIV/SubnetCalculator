#pragma once

#include <bitset>
#include <cstddef>
#include <ostream>
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

	static auto StringToIP(std::string address) -> std::bitset<32>;
	static auto StringToMask(std::string mask) -> std::bitset<32>;
	static auto BitsetToString(const std::bitset<32>& bitset) -> std::string;

	static auto MaskCountToMask(std::size_t count) -> std::bitset<32>;
	static auto MaskToMaskCount(const std::bitset<32>& mask) -> std::size_t;
	static auto ValidateMask(const std::bitset<32>& mask) -> bool;

	static auto GetSubnet(const std::bitset<32>& ip, const std::bitset<32>& mask) -> std::bitset<32>;
	static auto GetSubnet(const std::bitset<32>& ip, std::size_t maskCount) -> std::bitset<32>;
	static auto GetSubnet(std::string ip, std::string mask) -> std::bitset<32>;
	static auto GetSubnet(std::string ip, std::size_t maskCount) -> std::bitset<32>;

	static auto GetMinHost(const std::bitset<32>& ip, const std::bitset<32>& mask) -> std::bitset<32>;
	static auto GetMaxHost(const std::bitset<32>& ip, const std::bitset<32>& mask) -> std::bitset<32>;
	static void GetHostRange(const std::bitset<32>& ip, const std::bitset<32>& mask, std::bitset<32>& minimumHost, std::bitset<32>& maximumHost);
	static auto GetBroadcast(const std::bitset<32>& ip, const std::bitset<32>& mask) -> std::bitset<32>;
};
