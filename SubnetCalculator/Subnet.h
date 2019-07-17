#pragma once

#include <bitset>
#include <cstdint>
#include <ostream>
#include <string>

namespace subcalc {

	class Subnet
	{
	public:
		inline static std::bitset<32> const OCTET_MASKS[4] = {
			static_cast<std::uint32_t>(255<<24),
			static_cast<std::uint32_t>(255<<16),
			static_cast<std::uint32_t>(255<<8),
			static_cast<std::uint32_t>(255)
		};
		inline static std::uint_fast8_t const OCTET_MASK_BITSHIFTS[4] = {24, 16, 8, 0};

		Subnet(std::string ip, std::string mask);
		Subnet(std::string ip, std::uint_fast8_t maskCount);
		~Subnet();
		
		void SetIP(std::string ip);
		void SetMask(std::string mask);
		void SetMask(std::uint_fast8_t maskCount);
		void SetAddresses(std::string ip, std::string mask);
		void SetAddresses(std::string ip, std::uint_fast8_t maskCount);

		std::string GetIP() const;
		std::string GetMask() const;
		std::uint8_t GetMaskCount() const;
		std::string GetSubnet() const;
		std::bitset<32> GetBitsetIP() const;
		std::bitset<32> GetBitsetMask() const;
		std::bitset<32> GetBitsetSubnet() const;

		friend std::ostream& operator<<(std::ostream& stream, const Subnet& subnet);

	private:
		std::bitset<32> ip;
		std::bitset<32> mask;

		static std::bitset<32> ConvertStringToBitset(std::string address);
		static std::string ConvertBitsetToString(std::bitset<32> bitset);
		static std::bitset<32> ConvertMaskCountToBitset(std::uint_fast8_t count);
		static bool ValidateMask(std::bitset<32> const & mask);
	};
}