
#include "TextUI.h"
//#include "Election.h"
#include <iostream>             
#include <locale>         // std::locale, std::tolower
#include <map>
#include <vector>


/*Gets cin input, converts to lowercase, and returns it. 
Conversion to lowercase learned from http://www.cplusplus.com/reference/locale/tolower/ */
std::string TextUI::GetInput()
{
	std::string input;
	std::locale loc;
	std::cin >> input;

	for (std::string::size_type i = 0; i < input.length(); ++i)
		input[i] = std::tolower(input[i], loc); //converts to lowercase
	std::cin.clear();
	return input;
}

int TextUI::AskElectionType()
{
	std::cout << "What kind of election should we have (direct or representative, 0 to stop)\?" << std::endl;
	int choice = -1;
	std::string input = TextUI::GetInput();
	if (input == "direct") { choice = 1; }
	else if (input == "representative") { choice = 2; }
	else if (input == "0") { choice = 0; }
	else if (choice == -1) {
		std::cout << "Invalid input. Please try again." << std::endl;
		choice = TextUI::AskElectionType();
	}

	return choice;
}

int TextUI::AskRegisterCandidate(Party& party_in)
{
	std::cout << "Register a candidate for the " << party_in << " party\? (y/n)" << std::endl;
	int choice = -1;
	std::string input = TextUI::GetInput();
	if (input == "y") { choice = 1; }
	else if (input == "n") { choice = 2; }
	else if (input == "0") { choice = 0; }
	else if (choice == -1) {
		std::cout << "Invalid input. Please try again." << std::endl;
		choice = TextUI::AskRegisterCandidate(party_in);
	}

	return choice;
}

std::string TextUI::AskCandidateName()
{
	std::cout << "What would you like the candidate's name to be\?" << std::endl;
	return TextUI::GetInput();
}

int TextUI::AskCampaignCandidateID()
{
	std::cout << "Which candidate is campaigning (id) (0 to stop) \?" << std::endl;
	std::string input = TextUI::GetInput();
	int ret_val = 0;
	try {
		ret_val = std::stoi(input);
	}
	catch(...){
		std::cout << "Invalid Input. Please try again." << std::endl;
		ret_val = TextUI::AskCampaignCandidateID();
	}
	if (ret_val < 0) {
		std::cout << "Invalid Input. Please try again." << std::endl;
		ret_val = TextUI::AskCampaignCandidateID();
	}

	return ret_val - 1;
}

int TextUI::AskCampaignDistrictID()
{
	std::cout << "Where is this candidate campaigning (id) (0 to stop) \?" << std::endl;
	std::string input = TextUI::GetInput();
	int ret_val = 0;
	try {
		ret_val = std::stoi(input);
	}
	catch (...) {
		std::cout << "Invalid Input. Please try again." << std::endl;
		ret_val = TextUI::AskCampaignDistrictID();
	}
	if (ret_val < 0) {
		std::cout << "Invalid Input. Please try again." << std::endl;
		ret_val = TextUI::AskCampaignDistrictID();
	}

	return ret_val - 1;
}


void TextUI::PrintCandidates(const std::vector<Candidate*>& candidate_vec)
{
	for (auto it = candidate_vec.begin(); it != candidate_vec.end(); it++) {
		std::cout << **it << std::endl;
	}

}

void TextUI::PrintDistricts(const std::vector<District>& districts)
{	
	std::cout << std::endl;
	std::cout << "____________________________________" << std::endl;
	std::cout << std::endl;
	for (std::vector<District>::const_iterator it = districts.begin(); it != districts.end(); it++) {
		std::cout << *it << std::endl;
	}
	std::cout << "____________________________________" << std::endl;
	std::cout << std::endl;
}

void TextUI::ExitProgram()
{
	std::cout << "You have chosen to exit the program. Now Exiting..." << std::endl;
}
