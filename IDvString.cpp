#include"hypns.hpp"
#include<sstream>
#include<regex>
#include <iterator>

using namespace std;
using namespace hns;



template<typename Out>
void split(const std::string &s, char delim, Out result) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

vector<string> IDvSplit(string in, char deli) {
	return split(in, deli);
}

// Eine Listen Objekt welches eine Checkfunktion besitzt
struct PevoxList {
protected:
	vector<string> tempList;
	bool its_locked;
public:
	PevoxList() { its_locked = false; }
	void add(const char* inC) {
		if (its_locked == false)
			tempList.push_back(inC);
		else
			return; 
	}
	void add(string inQ) { add(inQ.c_str()); }
	bool onList(const char* inA) {
		for (int i = 0; i < tempList.size(); i++) {
			if (tempList[i] == inA) {
				return true;
			}
		}
		return false;
	}
	bool onList(string inStr) { return onList(inStr.c_str()); }
};

PevoxList itsAPrivChar() {
	PevoxList newList;
	newList.add("P");
	newList.add("R");
	newList.add("V");
	newList.add("1");
	newList.add("9");
	newList.add("2");
	return newList;
}

PevoxList itsAStringDelimeter() {
	PevoxList newList;
	newList.add("-");
	newList.add(".");
	newList.add(":");
	return newList;
}

PevoxList itsAllowedChar() {
	PevoxList newList;
	newList.add("-");
	newList.add(".");
	newList.add(":");
	newList.add("0");
	newList.add("1");
	newList.add("2");
	newList.add("3");
	newList.add("4");
	newList.add("5");
	newList.add("6");
	newList.add("7");
	newList.add("8");
	newList.add("9");
	newList.add("A");
	newList.add("B");
	newList.add("C");
	newList.add("D");
	newList.add("E");
	newList.add("F");
	newList.add("G");
	newList.add("H");
	newList.add("I");
	newList.add("J");
	newList.add("K");
	newList.add("L");
	newList.add("M");
	newList.add("N");
	newList.add("O");
	newList.add("P");
	newList.add("Q");
	newList.add("R");
	newList.add("S");
	newList.add("T");
	newList.add("U");
	newList.add("V");
	newList.add("W");
	newList.add("X");
	newList.add("Y");
	newList.add("Z");
	return newList;
}

char GiveBigChar(char chr) {
	if (chr == 'a')
		return 'A';
	else if (chr == 'b')
		return 'B';
	else if (chr == 'c')
		return 'C';
	else if (chr == 'd')
		return 'D';
	else if (chr == 'e')
		return 'E';
	else if (chr == 'f')
		return 'F';
	else if (chr == 'g')
		return 'G';
	else if (chr == 'h')
		return 'H';
	else if (chr == 'i')
		return 'I';
	else if (chr == 'j')
		return 'J';
	else if (chr == 'k')
		return 'K';
	else if (chr == 'l')
		return 'L';
	else if (chr == 'm')
		return 'M';
	else if (chr == 'n')
		return 'N';
	else if (chr == 'o')
		return 'O';
	else if (chr == 'p')
		return 'P';
	else if (chr == 'q')
		return 'Q';
	else if (chr == 'r')
		return 'R';
	else if (chr == 's')
		return 'S';
	else if (chr == 't')
		return 'T';
	else if (chr == 'u')
		return 'U';
	else if (chr == 'v')
		return 'V';
	else if (chr == 'w')
		return 'W';
	else if (chr == 'x')
		return 'X';
	else if (chr == 'y')
		return 'Y';
	else if (chr == 'z')
		return 'Z';
	else
		return chr;
}

string chartostring_Q(char chr) {
	stringstream ss;
	ss << chr;
	return ss.str();
}

bool itsDeliChar_Q(char in) {
	if (itsAStringDelimeter().onList(chartostring_Q(in)) == true) {
		return true;
	}
	return false;
}

IDvString hns::SelfID() {
	IDvString tids;
	tids.func_string = true;
	tids.itsUsed = true;
	tids.IDvHash = "%LOCAL_ID%";
	tids.buffer = "%LOCAL_ID%";
	return tids;
}

IDvString hns::UnkownID()
{
	IDvString tids;
	tids.func_string = true;
	tids.itsUsed = true;
	tids.IDvHash = "%UNKOWN_ID%";
	tids.buffer = "%UNKOWN_ID%";
	return tids;
}

bool syntaxcheck_Q(string qst) {
	string str(qst);

	for (int i = 0; i < str.size(); i++) {
		if (itsAllowedChar().onList(chartostring_Q(GiveBigChar(str[i]))) != true) {
			return false;
		}
	}
	char b = 'N';
	for (int i = 0; i < str.size(); i++) {
		if (itsAStringDelimeter().onList(chartostring_Q((GiveBigChar(str[i])))) == true) {
			b = str[i];
			break;
		}
	} 
	if (b != 'N' && split(str, b).size() != 0) {
		vector<string> tsvec = IDvSplit(str, b);
		if (tsvec.size() >= 3) {
			return true;
		}
	}
	else
		return false;
		
}

int giveStringType_Q(string str) {
	if (syntaxcheck_Q(str) == true) {
		char b = 'N';
		for (int i = 0; i < str.size(); i++) {
			if (itsAStringDelimeter().onList(chartostring_Q((GiveBigChar(str[i])))) == true) {
				b = str[i];
				break;
			}
		}
		if (b != 'N' && split(str, b).size() != 0) {
			vector<string> tsvec = IDvSplit(str, b);
			if (tsvec.size() >= 3) {
				regex e1("[P][R][0-9][1-9]");
				regex e2("[P][1-9][0-9][1-9]");
				if (regex_match(tsvec[0], e1)) {
					return 1;
				}
				else if (regex_match(tsvec[0], e2)) {
					return 1;
				}
				else
					return 0;
			}
			else
				return 10;
		}
		else
			return 11;
	}
	else
		return 12;
}

int hns::IDvString::write(const char* cstr)
{
	if (syntaxcheck_Q(cstr) == true) {
		this->buffer = cstr;
		this->type = giveStringType_Q(cstr);
		this->itsUsed = true;
		this->func_string = false;
		return 0;
	}
	return 1;
}
