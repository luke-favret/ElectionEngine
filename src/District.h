#pragma once
#include "Enums.h"
//#include <vector>
#pragma once
#include <map>
#include <iostream>

class District
{
public:

	District(const unsigned int& miles_in, std::map<Party*, unsigned int>& party_constituents_in, const unsigned int& tot_constituents_in)
		: id_(District::current_id_), square_miles_(miles_in), party_constituents_(party_constituents_in), total_constituents_(tot_constituents_in)
	{
		District::current_id_++;
	};

	void RunCampaign(Party& candidate_party); //probability of converting a constituent affiliated with Party::None
	Party* FindMajorityParty() const;

	//getter functions
	unsigned int id() const { return id_; };
	unsigned int square_miles() const { return square_miles_; };
	unsigned int total_constituents() const { return total_constituents_; };
	std::map<Party*, unsigned int> party_constituents() const { return party_constituents_; };

	static unsigned int current_id() { return current_id_; };

	//setter functions
	static void increase_current_id() { District::current_id_++;}

	friend std::ostream& operator<<(std::ostream& os, District& dt);
	friend std::ostream& operator<<(std::ostream& os, const District& dt);

private:
	const unsigned int id_;
	static unsigned int current_id_;

	const unsigned int square_miles_;
	const unsigned int total_constituents_;
	std::map<Party*, unsigned int> party_constituents_;
};

