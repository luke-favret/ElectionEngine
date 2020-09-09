// ElectionEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Enums.h"
#include "ElectoralMap.h"
#include "TextUI.h"
#include "RepresentativeElection.h"
#include "Election.h"

class District;
//#include <vector>

/*Luke Favret
This program allows one to simulate an election between multiple user-defined parties and candidates. 
*/
int main()
{
	ElectoralMap* emap = ElectoralMap::InitiateMap();
	emap->AddParty(Party::None); emap->AddParty(Party::Posadist); emap->AddParty(Party::AlsoPosadist); emap->AddParty(Party::MeowMeow);//None must be added first
	emap->SetUpDistricts(4);

	//TextUI::PrintDistricts(emap->districts());

	Election* c_election = RepresentativeElection::CreateElection(emap);
	if (c_election == NULL) { TextUI::ExitProgram(); return 0; }

	c_election->RunElection();
}

