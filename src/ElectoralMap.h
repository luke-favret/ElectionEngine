#pragma once
#include <map>
#include <utility>
#include <vector>
//#include "Election.h"
#include "Enums.h"
#include "TextUI.h"
#include "District.h"
#include "Candidate.h"

class Election; //Forwards declaration

//Because of templating issues with vectors and enums I had to include the source code in this header

//Make sure this header is included first in main
class ElectoralMap
{
public:
	//ElectoralMap(Party parties, unsigned int district_count);
	void AddParty(Party party_in);
	District* CreateDistrict();
	void SetUpDistricts(unsigned int district_count);

	static ElectoralMap* InitiateMap();

	std::vector<Party>& parties()  { return parties_; }; //had to un-const for correct pointers in election party map
	std::vector<District> districts() const { return districts_; }

	District* GetDistrictById(unsigned int dist_id)  { return &(this->districts_[dist_id]); }
	District* SetDistrictById(unsigned int dist_id) { return &(this->districts_[dist_id]); }

	void SetElection(Election* election_in) { current_election_ = election_in; return; }
private:
	ElectoralMap();
	ElectoralMap(ElectoralMap const&);
	static ElectoralMap* instance_;

	std::vector<Party> parties_;
	std::vector<District> districts_; //Better performance than map

	Election* current_election_;

};

//#include "ElectoralMap.cpp"