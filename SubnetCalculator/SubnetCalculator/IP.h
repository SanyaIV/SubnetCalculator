#ifndef IP_H
#define IP_H
#include <string>
#include <ostream>
#include <bitset>

namespace subcalc {

	class IP
	{
	public:
		IP(std::string address);
		IP(std::bitset<8>& oct1, std::bitset<8>& oct2, std::bitset<8>& oct3, std::bitset<8>& oct4);
		IP(std::bitset<8>(&octet)[4]);
		IP(const IP& other);
		~IP();
		friend std::ostream& operator<< (std::ostream& stream, const IP& ip);
		void getBitset(std::bitset<8>(&destination)[4]) const;

	protected:
		std::bitset<8> address[4];

	private:
		void convertStringToIP(std::string address);
	};

}

#endif