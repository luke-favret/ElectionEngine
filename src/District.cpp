#include "District.h"

unsigned int District::current_id_ = 0;



void District::RunCampaign(Party& candidate_party)
{
	double p_success = 0;

	
	int max_other_const = -1;


	auto biggest_other_party = this->party_constituents_.begin();
	auto none = this->party_constituents_.begin();
	auto cand_party = this->party_constituents_.begin();
	//finding and assigning party iterators
	for (auto it = this->party_constituents_.begin(); it != this->party_constituents_.end(); it++) {
		if (*it->first == Party::None) { none = it; }
		else if (*it->first == candidate_party) { cand_party = it; }
		else if (it->second > max_other_const) {
			biggest_other_party = it;
			max_other_const = it->second;
		}
	}

	//casting iterator ints to doubles
	double constituents_none = static_cast<double> (none->second);
	double cand_party_constituents = static_cast<double> (cand_party->second); //this is inefficient, fix later
	double ftotal_constituents = static_cast<double> (total_constituents_);


	p_success = 10.0 * ( ((cand_party_constituents + 1.0) * 2.0) / (ftotal_constituents - constituents_none - cand_party_constituents) ) * (((cand_party_constituents + 1.0) * 2.0) / square_miles_);
	if (p_success > 100.0) { p_success = 100.0; } //probability of converting a constituent affiliated with Party::None
	double p_extra_success = p_success * 0.1; //probability of converting a constituent affiliated with next biggest party
	std::cout << std::endl;
	std::cout << "||XX||XX||XX||XX||XX||XX||XX||XX||XX||XX||XX||XX||" << std::endl;
	std::cout << "Chances to convert: " << p_success << std::endl;
	std::cout << "Chances to convert from another party: " << p_extra_success << std::endl;

	int iroll = std::rand() % 10001;
	double froll = (static_cast<double>(iroll)) / 100.0;

	if (froll <= p_success and none->second > 0) { //Convert from none
		//std::cout << none->second << std::endl;
		
		//std::cout << none->second << std::endl;
		//std::cout << *this << std::endl;
		none->second = none->second - 1;
		cand_party->second = cand_party->second + 1;

		std::cout << "Congrats, you have converted someone from none to "<< candidate_party <<"!" << std::endl;
	}
	if (froll <= p_extra_success and biggest_other_party->second > 0) { //Convert from second biggest party
		biggest_other_party->second--;
		cand_party->second++;

		std::cout << "Congrats, you have converted someone from " << *biggest_other_party->first<<" to " << candidate_party << "!" << std::endl;
	}
	std::cout << "||XX||XX||XX||XX||XX||XX||XX||XX||XX||XX||XX||XX||" << std::endl;
	std::cout << std::endl;
	return;
}

Party* District::FindMajorityParty() const
{
	int highest_candidates = 0;
	Party* ret_party = nullptr;
	for (auto it = (party_constituents_.begin()++); it != party_constituents_.end(); it++) {
		if (it->second > highest_candidates) {
			highest_candidates = it->second;
			ret_party = it->first;
		}
	}
	return ret_party;
}


std::ostream& operator<<(std::ostream& os, District& dt)
{
	os << "District " << dt.id_ + 1 << ": \n" << "Square miles: " << dt.square_miles_ << "\n";
	for (std::map<Party*, unsigned int>::iterator it = dt.party_constituents_.begin(); it != dt.party_constituents_.end(); it++) {
		os << *it->first << ": " << it->second << "\t";
	}
	os << "\n";
	return os;
}

std::ostream& operator<<(std::ostream& os, const District& dt)
{
	os << "District " << dt.id_ + 1 << ": \n" << "Square miles: " << dt.square_miles_ << "\n";
	for (std::map<Party*, unsigned int>::const_iterator it = dt.party_constituents_.begin(); it != dt.party_constituents_.end(); it++) {
		os << *it->first << ": " << it->second << "\t";
	}
	os << "\n";
	return os;
}