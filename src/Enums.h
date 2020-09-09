#pragma once
#include <iostream>
enum class Party {None, Posadist, AlsoPosadist, MeowMeow};

inline std::ostream& operator<<(std::ostream& os, Party& pt) {
	std::string party_name;
	switch (pt) {
	case Party::None: party_name = "None"; break;
	case Party::Posadist: party_name = "Posadist"; break;
	case Party::AlsoPosadist: party_name = "AlsoPosadist"; break;
	case Party::MeowMeow: party_name = "MeowMeow"; break;
	default: party_name = "PARTY NAME ERROR"; 
	}

	os << party_name;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const Party& pt) {
	std::string party_name;
	switch (pt) {
	case Party::None: party_name = "None"; break;
	case Party::Posadist: party_name = "Posadist"; break;
	case Party::AlsoPosadist: party_name = "AlsoPosadist"; break;
	case Party::MeowMeow: party_name = "MeowMeow"; break;
	default: party_name = "PARTY NAME ERROR";
	}

	os << party_name;
	return os;
}