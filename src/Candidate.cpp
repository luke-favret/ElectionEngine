#pragma once
#include <iostream>
#include "Candidate.h"

unsigned int Candidate::current_id_ = 0;
std::ostream& operator<<(std::ostream& os, Candidate& cd)
{
	std::string space = ": ";
	std::string pt = "Party: ";

	os << std::to_string(cd.id_ + 1) << space << cd.name_ << "\t" << pt << cd.aligned_party_ << std::endl;
	return os;
}
