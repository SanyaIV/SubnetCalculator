#include "Subnet.h"
#include <exception>
#include <iostream>
#include <string>

auto QueryUserInput(std::string question){
	std::string userInput = "";

	while(userInput == ""){
		std::cout << question;
		std::getline(std::cin, userInput);
	}

	return userInput;
}

auto QueryIntegerUserInput(std::string question){
	while(true){
		try{
			return std::stoul(QueryUserInput(question));
		}catch (std::invalid_argument& e){
			std::cout << e.what() << std::endl;
		}
	}
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

auto QueryMaskFromHostCount(){
	while(true){
		try{
			return Subnet::GetMaskFromHostCount(QueryIntegerUserInput("Amount of hosts: "));
		}catch (std::invalid_argument& e){
			std::cout << e.what() << std::endl;
		}
	}
}

void PrintSubnet(const std::bitset<32>& ip, const std::bitset<32>& mask){
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

void CalculateSubnet(){
	auto ip = QueryIP();
	auto mask = QueryMask();
	PrintSubnet(ip, mask);
}

void CalculateSubnetFromHostCount(){
	auto ip = QueryIP();
	auto mask = QueryMaskFromHostCount();
	PrintSubnet(ip, mask);
}

void PrintMenu(){
	std::cout << "1. Calculate Subnet from IP and Mask" << std::endl;
	std::cout << "2. Calculate Subnet from IP and desired amount of hosts" << std::endl;
	std::cout << "0. Exit" << std::endl << std::endl;
}

int main() {
	bool loop = true;
	char input;
	
	std::cout << "!Subnet Calculator!" << std::endl << std::endl;

	do{
		PrintMenu();
		input = QueryIntegerUserInput("Choice: ");

		switch(input){
			case 0:
				loop = false;
				return 0;
				break;
			case 1:
				CalculateSubnet();
				break;
			case 2:
				CalculateSubnetFromHostCount();
				break;
			default:
				std::cout << "Invalid choice" << std::endl;
				break;
		}

		std::cout << std::endl << "Press [ENTER] to continue . . .";
		std::cin.get();
		std::cout << std::endl;
		
	}while(loop);
}

