#include"hypns.hpp"
#include"tinyxml2.h"
#include<sstream>

using namespace hns;
using namespace std;

#define PACKAGE ((const char*)"PACKAGE")
#define RAW_PACKAGE
#define PACKAGE_TYPE ((const char*)"pType")
#define OBJECT_HEADER ((const char*)"OBJECT")
#define OBJECT_TYPE ((const char*)"oType")
/// Paket Typen werden erstellt
#define INITD_P ((const char*)"INITD")
#define PIPE_P ((const char*)"PIPE")
// Objekt Typen werden definiert
#define BIN_OBJ ((const char*)"BIN")
// Maximale Anzahl an zugelassenen Objekten
#define MAX_OBJ ((int)3)
//Package Meta Daten
#define FROM_META ((const char*)"FRM")
#define TO_META ((const char*)"TO")

namespace hc {
	int writeToIDvString(const char* in) {
		return 0;
	}
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
	 void add(string inQ) {add(inQ.c_str());}
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

struct PackageObject {
protected:
	string poType;
	string poData;
public:
	PackageObject(const char* type, const char* datas) {
		if (sizeof(type) != 0 && sizeof(datas) != 0) {
			this->poType = type; 
			this->poData = datas;
		}
	}
	PackageObject(string type, string datas) { PackageObject(type.c_str(),datas.c_str()); }
	const char* GiveObjectType() { return poType.c_str(); }
	const char* GiveOjectData() { return poData.c_str(); }
	bool itsusd() { if (poData.size() != 0 && poType.size() != 0) return true; else return false; }
	string GiveObjectHash() { 
		hash<string> hs;
		stringstream ss;
		ss << OBJECT_TYPE <<":"<< poType;
		ss << "@" << poData;
		size_t strHash = hs(ss.str());
		stringstream ss2;
		ss2 << strHash;
		return ss2.str();
	}
};

string LastPackageHash;

PevoxList itsAPackageType() {
	PevoxList newList;
	newList.add(INITD_P);
	return newList;
}

PevoxList itsAObjectType() {
	PevoxList newList;
	newList.add(BIN_OBJ);
	return newList;
}

PevoxList itsPipeElement() {
	PevoxList newList;
	newList.add(INITD_P);
	return newList;
}

hns::PackageHandler::PackageHandler(const char* cstrIN) {
	// XML Handler wird erstellt
	tinyxml2::XMLDocument xmlunit;
	tinyxml2::XMLError eResult = xmlunit.Parse(cstrIN);
	// Es wird geprüft ob es sich um einen Gültigen XML-String handelt
	if (eResult != tinyxml2::XML_SUCCESS) {
		// Schreibt den Fehlercode in den PackageHandler
		this->L_O_state = 1016369;
		// Das Paket wird als nicht benutzbar deklariert
		this->cann_used = false;
		return;
	}else if (eResult == tinyxml2::XML_SUCCESS) {
		// Es wird geprüft ob ein Package-Header angegeben wurde
		if (xmlunit.FirstChildElement(PACKAGE)){
			tinyxml2::XMLElement *pRoot = xmlunit.FirstChildElement(PACKAGE);
			// Es wird geprüft ob ein Paket Typ angeben wurde
			if (pRoot->Attribute(PACKAGE_TYPE)) {
				// Es wird geprüft ob ein Gültiger Paket Typ angeben wurde
				if (itsAPackageType().onList((const char*)pRoot->Attribute(PACKAGE_TYPE)) == true) {
					cout << "Package Type -> " << "(" << pRoot->Attribute(PACKAGE_TYPE) << ")" << endl;
					// Es wird überprüft welche Meta Daten in dem Paket enthalten sind
					IDvString from_;
					IDvString to_;
					bool writeError;
					string errorPosition_q1 = "c";
					// Es wird geprüft ob ein Absender angeben wurde
					if (pRoot->Attribute(FROM_META)) {
						if (from_.write(pRoot->Attribute(FROM_META)) != 0) {
							writeError = true;
							errorPosition_q1 = "FROM_META";
						}
					}
					else
						from_ = UnkownID();
					// Es wird geprüft ob ein Ziel angegeben wurde
					if (pRoot->Attribute(TO_META)) {
						if (from_.write(pRoot->Attribute(TO_META)) != 0) {
							writeError = true;
							errorPosition_q1 = "TO_META";
						}
					}
					else
						to_ = SelfID();

					// Es wird geprüft ob Fehler Aufgetreten sind
					if (errorPosition_q1 != (string)"c") {
						return;
					}
					// Es werden alle gefunden Objekte auf gültigkeit geprüft und dann gelistet
					vector<PackageObject> ObjectBuffer;
					int i = 0;
					for (tinyxml2::XMLElement* e = pRoot->FirstChildElement(OBJECT_HEADER); e != NULL; e = e->NextSiblingElement(OBJECT_HEADER)) {
						// Es wird geprüft ob i = MAX_OBJ ist, sollte i=MAX_OBJ sein so wird kein weiters Object geschrieben
						if (i != MAX_OBJ) {
							// Alle Elemente werden auf Object Type geprüft, des weitern wird geprüft ob Daten Enthalten sind
							if (itsAObjectType().onList(e->Attribute(OBJECT_TYPE)) == true && e->GetText() != "") {
								// Gefundene Elemente werden gelistet
								PackageObject pobj((e->Attribute(OBJECT_TYPE)), e->GetText());
								// Es wird geprüft ob das Letze Object und dieses Object Identisch sind
								if (pobj.GiveObjectHash() != LastPackageHash) {
									LastPackageHash = pobj.GiveObjectHash();
									//cout << "ObjectHash: " << pobj.GiveObjectHash() << endl;
									ObjectBuffer.push_back(pobj);
									// i wird um 1 Multipliziert
									i++;
								}
							}
						}
					}
					// Es wird geprüft ob Mindestens ein Objekt gefunden wurde
					if (ObjectBuffer.size() == 0)
						return;
					// Nun werden alle Wichtigen Daten geschrieben
					// Neues MetaObjekt wird erzeugt und befüllt
					PackageMeteDatas newPMD;
					newPMD.to = to_;
					// Es wird geprüft ob ein Absender angegeben wurde
					newPMD.from = from_;
					// Metadaten werden nun geschrieben
					this->MeteBuff = newPMD;
					// Objekte werden geschrieben



					cout << "Sizeof(ObjectBuffer) >> " << ObjectBuffer.size()<<"/"<< MAX_OBJ << endl;
				}
				cann_used = true;
				pType = 23123;
				return;
			}
		}// Es wird geprüft ob ein RAW-Package-Header angegeben wurde
		else if (xmlunit.FirstChildElement(RAW_PACKAGE)) {

		}
	}

}

hns::PackageHandler::PackageHandler(std::string strin) {
	PackageHandler::PackageHandler((const char*)strin.c_str());
}

bool hns::PackageHandler::coutpck() {
	if (this->pType != 0 && this->cann_used == true) {
		if (this->ObjectBuff.fObjectTypes.size() != 0)
			return true;
		else
			return false;
	}else 
		return false;
}

Package hns::PackageHandler::GivePackage() {
	Package returnPackage;
	if (this->cann_used == true) {
		return returnPackage;
	}else
		return Package();
}