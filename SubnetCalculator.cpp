#include "Subnet.h"
#include <exception>
#include <iostream>

auto QueryUserInput(std::string question){
	std::string userInput = "";

	while(userInput == ""){
		std::cout << question;
		std::getline(std::cin, userInput);
	}

	return userInput;
}

auto QueryIP(){
	while(true){
		try{
			return Subnet::StringToIP(QueryUserInput("IP: "));
		}catch (std::invalid_argument& e){
			std::cout << e.what() << std::endl;
		}
	}
}

auto QueryMask(){
	while(true){
		try{
			return Subnet::StringToMask(QueryUserInput("Mask: "));
		}catch (std::invalid_argument& e){
			std::cout << e.what() << std::endl;
		}
	}
}

void PrintResult(const std::bitset<32>& ip, const std::bitset<32>& mask){
	auto minimumHost = std::bitset<32>();
	auto maximumHost = std::bitset<32>();
	Subnet::GetHostRange(ip, mask, minimumHost, maximumHost);

	std::cout << std::endl << "|Results|" << std::endl
		<< "|IP:		" 		<< Subnet::BitsetToString(ip) << std::endl 
		<< "|Mask:		" 		<< Subnet::BitsetToString(mask) << std::endl 
		<< "|Subnet:	" 		<< Subnet::BitsetToString(Subnet::GetSubnet(ip, mask)) << std::endl 
		<< "|Minimum Host:	"	<< Subnet::BitsetToString(Subnet::GetMinHost(ip, mask)) << std::endl 
		<< "|Maximum Host:	"	<< Subnet::BitsetToString(Subnet::GetMaxHost(ip, mask)) << std::endl
		<< "|Broadcast:	" 		<< Subnet::BitsetToString(Subnet::GetBroadcast(ip, mask)) << std::endl;
}

int main() {
	bool loop = true;
	
	std::cout << "!Subnet Calculator!" << std::endl << std::endl;

	do{
		auto ip = QueryIP();
		auto mask = QueryMask();
		PrintResult(ip, mask);

		auto answer = QueryUserInput("\nContinue?: ");
		if(answer[0] != 'Y' && answer[0] != 'y') loop = false;

	}while(loop);
}

