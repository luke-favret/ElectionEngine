
#include "Election.h"

/*WINNER TAKES ALL representative election*/
class RepresentativeElection :
	public Election
{
public:
	RepresentativeElection(ElectoralMap* (map_in))
		: Election(map_in) {};
	virtual void TallyVotes();
	static Election* CreateElection(ElectoralMap* map_in);
	int CalculateDistrictRepresentatives(int district_id);
	int CalculateTotalConstituents();
private:
	int total_constituents_ = 0;
	int total_votes_ = 0;
};
