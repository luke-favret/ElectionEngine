
#pragma once
#include "Election.h"
#include "Candidate.h"
#include "TextUI.h"
Election::Election(ElectoralMap* map_in) : map_(map_in) {
	
	/*std::vector<Party>& parties = map_->parties(); //Initializes party votes map
	for (auto it = parties.begin(); it != parties.end(); it++) {
		this->party_votes.insert({ &*it, 0 });
		std::vector<Candidate*>* new_vec = new std::vector<Candidate*>;
		this->candidate_vectors_.insert({ &*it, new_vec }); //initalizes party -> candidates vectors
	}*/

	//build party:candidate count
	std::vector<Party>& parties = map_in->parties();
	for (auto it = parties.begin() + 1; it != parties.end(); it++) {
		this->party_candidate_count_.insert({ &*it, 0 });
	}
}



/* Retrieves candidate name from TextUI. Next,creates candidate with that name and with poarty = input party. Lastly, adds candidate 
to candidate vector and returns address to candidate.*/
Candidate* Election::RegisterCandidate(const Party c_party)
{
	std::string c_name = TextUI::AskCandidateName();
	Candidate* new_candidate = new Candidate(c_party, c_name);
	candidate_list_.push_back(new_candidate);
	candidate_vote_count_.insert({ new_candidate, 0 });

	for (auto it = this->party_candidate_count_.begin(); it != this->party_candidate_count_.end(); it++) {
		if (*it->first == c_party) {
			it->second++; //increase party:candidate count 
		}
	}

	return new_candidate;
	//legacy map of vectors code
	/*auto party_vec = candidate_vectors_.begin();
	for (auto it = candidate_vectors_.begin(); it != candidate_vectors_.end(); it++) {
		if (*(it->first) == *c_party) {
			party_vec = it;
		}
	}
	std::vector<Candidate*>& this_party_vec = *party_vec->second;
	this_party_vec.push_back(new_candidate);*/
	
}



/* Runs all functions needed for an election process*/
void Election::RunElection()
{
	this->RegisterCandidateCycle();
	this->StartCampaignCycle();
	this->TallyVotes();
	auto winner = this->DetermineWinner();
	std::cout << "\n" << "Congratulations, " << winner->name() << ", you've won!" << std::endl;
	return;
}


/* Cycles through all parties, asking if a candidate should be registered for each. Doesn't move to next party until
noone is registered for that party for a step*/
void Election::RegisterCandidateCycle()
{
	std::vector<Party> parties = map_->parties(); //cycles through maps
	for (auto it = parties.begin() + 1; it != parties.end(); it++) { // skips party::none
		if (TextUI::AskRegisterCandidate(*it) == 1) {
			this->RegisterCandidate(*it);
			--it; //Makes it so we ask again for same party
		}
	}
	//TextUI::PrintCandidates(candidate_list_);
	return;
}


/*Starts&runs the campaign cycle, which asks which candidate should go campaigning and in what district. Doesn't exit until 0 is entered.*/
void Election::StartCampaignCycle()
{
	int campaigned_candidates = 0;
	int total_candidates = Candidate::current_id();
	int cand_id;
	bool campaigns_over = false;

	while (!campaigns_over) {
		std::cout << "_________________________" << std::endl;
		TextUI::PrintCandidates(candidate_list_);
		cand_id = TextUI::AskCampaignCandidateID();
		if (cand_id < -1 || cand_id >= total_candidates) {
			std::cout << "Candidate not found. " << std::endl;
		}
		else if(cand_id != -1){
			SendCandidateCampaigning(*candidate_list_[cand_id]);
			if (candidate_list_[cand_id]->has_campaigned == false) {
				candidate_list_[cand_id]->has_campaigned = true;
				campaigned_candidates++;
			}
		}
		else {
			campaigns_over = true;
		}
	}
	return;
	
}

/*Starts*/
void Election::SendCandidateCampaigning(Candidate& campaigning_candidate)
{
	int num_of_districts = District::current_id();
	bool done_campaigning = false;
	int district_id;
	Party cand_party = campaigning_candidate.aligned_party();
	while (!done_campaigning) {
		const std::vector<District>& districts = map_->districts();
		TextUI::PrintDistricts(districts);
		district_id = TextUI::AskCampaignDistrictID();
		if ((district_id > -1) && (district_id < num_of_districts)) {
			District& temp_district = *(map_->GetDistrictById(district_id));
			temp_district.RunCampaign(cand_party);
		}
		else if(district_id != -1){
			std::cout << "ID not found. " << std::endl;
			std::cout << district_id << " " << num_of_districts << " "<< (district_id > -2) << " " << (district_id < num_of_districts)<< std::endl;
			district_id = TextUI::AskCampaignDistrictID();
		}
		else{
			done_campaigning = true;
			campaigning_candidate.has_campaigned = true; 
		}
	}

	return;
}

void Election::TallyVotes()
{
	const auto& districts = map_->districts();
	for (auto it = districts.begin(); it != districts.end(); it++) {//districts
		std::map<Party*, unsigned int> votes = it->party_constituents(); //clones votes

		int loose_votes = 0;
		//for giving none votes to majority party
		const auto maj_party = it->FindMajorityParty();
		auto major_it = votes.find(maj_party);
		if (major_it == votes.end()) {
			throw("Couldn't find majority party");
		}



		for (auto it2 = votes.begin(); it2 != votes.end(); it2++) {//party:votes
			auto chosen_candidate = this->SelectCandidate(it2->first);
			if (chosen_candidate == nullptr || it2 == major_it) { //if there is no registered candidate or it is the majority party
				loose_votes += it2->second;
			}
			else {
				this->candidate_vote_count_.at(chosen_candidate) += it2->second; //add votes to chosen candidate's totals
			}
		}
		//loose & majority party votes handling
		auto major_candidate = this->SelectMajorityCandidate(major_it->first);
		this->candidate_vote_count_.at(major_candidate) += loose_votes;

	}
	return;
}

Candidate* Election::DetermineWinner()
{
	std::cout << "Final Vote Totals: " << std::endl;
	int highest_votes = 0;
	auto hv_entry = candidate_vote_count_.begin();
	for (auto it = candidate_vote_count_.begin(); it != candidate_vote_count_.end(); it++) {
		if (it->second > highest_votes) {
			highest_votes = it->second;
			hv_entry = it;
		}
		if (it->second >= 0) {
			std::cout << it->first->name() << ": " << it->second << std::endl;
		}
	}
	return hv_entry->first;
}

Candidate* Election::SelectCandidate(Party* cand_party)
{
	int party_candidates = 0;
	int candidate_index;
	int previous_candidates = 0;
	
	for (auto it = party_candidate_count_.begin(); it != party_candidate_count_.end(); it++) {

		if (*cand_party == *it->first) {
			party_candidates = it->second;
			break;
		}
		else {
			previous_candidates += it->second;
		}
	}
		
	if (party_candidates <= 0) { return nullptr; } //if party has no candidates 
	else{ candidate_index = (rand() % party_candidates) + previous_candidates; }
	
	

	
	return candidate_list_[candidate_index];
}

Candidate* Election::SelectMajorityCandidate(Party* cand_party)
{
	auto major_candidate = this->SelectCandidate(cand_party);
	if (major_candidate == nullptr) {
		major_candidate = candidate_list_[rand() % candidate_list_.size()]; //picks random candidate
	}
	return major_candidate;
}

