#include "IP.h"
#include <algorithm>
#include <exception>

namespace subcalc {

	IP::IP(std::string address)
	{
		convertStringToIP(address);
	}

	IP::IP(std::bitset<8>& oct1, std::bitset<8>& oct2, std::bitset<8>& oct3, std::bitset<8>& oct4){
		address[0] = oct1;
		address[1] = oct2;
		address[2] = oct3;
		address[3] = oct4;
	}

	IP::IP(std::bitset<8>(&octet)[4]) {
		for (int i = 0; i < 3; i++)
			address[i] = octet[i];
	}

	IP::IP(const IP& other) {
		for(int i = 0; i < 3; i++)
			address[i] = other.address[i];
	}

	IP::~IP()
	{
	}

	std::ostream& operator<<(std::ostream& stream, const IP& ip) {
		stream << ip.address[0].to_ulong() << "." << ip.address[1].to_ulong() << "." << ip.address[2].to_ulong() << "." << ip.address[3].to_ulong();
		return stream;
	}

	void IP::getBitset(std::bitset<8>(&destination)[4]) const {
		for(int i = 0; i < 3; i++)
			destination[i] = address[i];
	}

	void IP::convertStringToIP(std::string address) {
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
					this->address[i] = tmp;
				else
					throw std::invalid_argument("Malformed address");
			}
			catch (std::exception&) {
				throw std::invalid_argument("Malformed address");
			}
		}
	}

}