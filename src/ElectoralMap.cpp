#pragma once
#include "ElectoralMap.h"
#include <random>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
//#include "Election.h"



//std::vector<Party> ElectoralMap::parties_;
/*Creates input number of districts*/
ElectoralMap* ElectoralMap::instance_;
void ElectoralMap::SetUpDistricts(unsigned int district_count)
{
	for (unsigned int i = 0; i < district_count; i++) {
		this->CreateDistrict();
	}
}

ElectoralMap* ElectoralMap::InitiateMap()
{
	ElectoralMap* new_map = new ElectoralMap();
	ElectoralMap::instance_ = new_map;
	return new_map;
}

ElectoralMap::ElectoralMap()
{
	this->current_election_ = NULL;
	//this->parties_ = {};
	//this->districts_ = {};

}

void ElectoralMap::AddParty(Party party_in)
{
	parties_.push_back(party_in);

}

/* Creates a district and generates the values for its fields.
Also adds it to district vector of electoralmap.
The values are not generated in the district constructor in case we want to make them manual later on*/
District* ElectoralMap::CreateDistrict()
{
	std::map<Party*, unsigned int> party_constituents;
	unsigned int tot_constituents = 0;

	//creates party:constituent count map
	for (auto it = this->parties_.begin(); it != this->parties_.end(); ++it) {
		unsigned int constituent_count = (rand() % 10);// random number 0 - 9
		tot_constituents += constituent_count;

		party_constituents.insert({ &*it , constituent_count }); //Party:int
	}

	unsigned int size = (rand() % 25) + 5; //random btwn 5-29

	District* new_district = new District(size, party_constituents, tot_constituents);

	this->districts_.push_back(*new_district);
	return new_district;
}

