#pragma once
#include "Enums.h"
#include <string> 

class Candidate
{

public:
	Candidate(const Party party_in, const std::string name_in) 
		: aligned_party_(party_in), id_(Candidate::current_id_), name_(name_in) {
		Candidate::current_id_++;
		std::cout << "Registered " << aligned_party_ << std::endl;
	};


	unsigned int id() const { return id_; };
	std::string name() const { return name_; };
	const Party aligned_party() const { return aligned_party_; };

	static unsigned int current_id() { return current_id_; };

	friend std::ostream& operator<<(std::ostream& os, Candidate& cd);

	bool has_campaigned = false;
private:
	const std::string name_;

	const Party aligned_party_; //used to be a pointer
	const unsigned int id_;
	static unsigned int current_id_;

	
};
