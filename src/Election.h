#pragma once
#include "TextUI.h"
#include "Candidate.h"
#include "ElectoralMap.h"
#include <map>
#include <vector>
class Election
{
public:
	Election(ElectoralMap* map_in);

	Candidate* RegisterCandidate(const Party c_party);
	//std::map<Party*, std::vector<Candidate*> > candidate_vectors() const { return candidate_vectors_; };
	std::vector<Candidate*> candidate_list() const{ return candidate_list_; }

	
	void RunElection();
	void RegisterCandidateCycle();
	void StartCampaignCycle();
	void SendCandidateCampaigning(Candidate& campaigning_candidate);

	virtual void TallyVotes();
	Candidate* DetermineWinner();
	Candidate* SelectCandidate(Party* cand_party);
	Candidate* SelectMajorityCandidate(Party* cand_party);


	ElectoralMap* map() const { return this->map_; };
	//std::map<Candidate*, unsigned int> candidate_vote_count() { return candidate_vote_count_; }
	std::map<Candidate*, unsigned int>& candidate_vote_count = candidate_vote_count_; //easier
private:
	ElectoralMap* map_;
	std::map<Party*, unsigned int> party_candidate_count_;
	std::map<Candidate*, unsigned int> candidate_vote_count_;
	//std::map<Party*, std::vector<Candidate*>* > candidate_vectors_ = {}; //A map of Party:candidates to make it easier for when we have multiple candidates of same party

	std::vector<Candidate*> candidate_list_;
	

	
};
