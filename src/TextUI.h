#pragma once
#include <string>
#include "Enums.h"
#include "Candidate.h"
#include "District.h"
#include <map>
#include <vector>
//class Election;
//class Candidate;


class TextUI
{
public:
	static std::string GetInput();
	static int AskElectionType();
	static int AskRegisterCandidate(Party& party_in);
	static std::string AskCandidateName();

	static int AskCampaignCandidateID();
	static int AskCampaignDistrictID();

	static void PrintCandidates(const std::vector<Candidate*>& candidate_vec);
	static void PrintDistricts(const std::vector<District>& districts);

	static void ExitProgram();

private:
	TextUI();
	TextUI(TextUI const&);
	//TextUI& operator=(TextUI const&);
	//~TextUI(); 
};
