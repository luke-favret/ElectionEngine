
#include "RepresentativeElection.h"

void RepresentativeElection::TallyVotes()
{
	std::cout << "REP VOTE TALLY" << std::endl;

	this->CalculateTotalConstituents();


	const auto& districts = this->map()->districts();
	auto winning_party = districts.begin()++;
	int max_cand_votes = 0;

	for (std::vector<District>::const_iterator it = districts.begin(); it != districts.end(); it++) {//districts
		max_cand_votes = 0;
		const std::map<Party*, unsigned int>& votes = it->party_constituents();
		const auto maj_party = it->FindMajorityParty();
		auto major_it = votes.find(maj_party);
		if (major_it == votes.end()) {
			throw("Couldn't find majority party");
		}
		
		auto major_cand = this->SelectMajorityCandidate(maj_party);
		this->candidate_vote_count.at(major_cand) += this->CalculateDistrictRepresentatives(it->id());
		//std::cout << "Should be vote count" << this->CalculateDistrictRepresentatives(it->id())<< std::endl;

	}
	return;
}

/*Static function that creates a new election. Asks for type of election, then creates either election or representative election
and returns pointer. */
Election* RepresentativeElection::CreateElection(ElectoralMap* map_in)
{
	Election* new_election = NULL;

	int election_type = TextUI::AskElectionType();
	switch (election_type) {
	case 1:	 new_election = new Election(map_in); break;	//direct election
	case 2:  new_election = new RepresentativeElection(map_in);  break;
	case 0: return NULL;
	}

	map_in->SetElection(new_election);



	return new_election;
}

int RepresentativeElection::CalculateDistrictRepresentatives(int district_id)
{
	const auto& dist = this->map()->GetDistrictById(district_id);
	double dist_const = static_cast<double> (dist->total_constituents());
	double tot_const = static_cast<double> (this->total_constituents_);

	int district_votes = static_cast<int> ((dist_const / tot_const) * static_cast<double>(this->total_votes_));


	return district_votes;
}

int RepresentativeElection::CalculateTotalConstituents()
{
	int total_const = 0;
	const auto& districts = this->map()->districts();
	for (auto it = districts.begin(); it != districts.end(); it++) {
		const auto& party_ct = it->party_constituents();
		for (auto it2 = party_ct.begin(); it2 != party_ct.end(); it2++) {
			total_const += it2->second;
		}
	}
	this->total_constituents_ = total_const;
	this->total_votes_ = 5 * districts.size();

	return total_const;
}
