#pragma once
#pragma once
#include <map>
#include <utility>
#include <vector>
#include "Enums.h"
#include "District.h"
#include "Candidate.h"

//Because of templating issues with vectors and enums I had to include the source code in this header

//Make sure this header is included first in main
class ElectoralMap
{
public:
	//ElectoralMap(Party parties, unsigned int district_count);
	void AddParty(Party party_in);
	District* CreateDistrict();
	void SetUpDistricts(unsigned int district_count);

private:
	ElectoralMap();
	ElectoralMap(ElectoralMap const&);
	static std::vector<Party> parties_;
	std::vector<District*> districts_; //Better performance than map

};