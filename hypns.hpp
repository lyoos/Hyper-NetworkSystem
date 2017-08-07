#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>

#ifdef DEBUG   
#include"debugTools.hpp"
#endif

#if defined FILE_H
#define D_BUG_INCLUDE ((bool)true)
#else
#define D_BUG_INCLUDE ((bool)false)
#endif

namespace hns {


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
		PackageObject(string type, string datas) { PackageObject(type.c_str(), datas.c_str()); }
		const char* GiveObjectType() { return poType.c_str(); }
		const char* GiveOjectData() { return poData.c_str(); }
		bool itsusd() { if (poData.size() != 0 && poType.size() != 0) return true; else return false; }
		string GiveObjectHash();
	};

	/*
	Speichert alle wichtigen Paket Objekte ab
	*/
	struct PackageObjectDatas{std::vector<const char*> fObjectTypes; std::map<const char*, std::string> objDatas;};
	/* Überprüft ob es sich bei dem String um eine IDv Handelt */
	bool itsaCorrectIDv(std::string str);
	/*
	in einem IDvString können nur IDv Adressen gespeichert werden.
	*/
	struct IDvString {
	private:
		std::string buffer;
		std::string IDvHash;
		bool func_string;
		int type;
		bool itsUsed;
		// Schreibt einen String in den IDv String sofern dieser gültig ist
		int write(const char*);
	public:
		// Erstellt einen Leeren IDv String
		IDvString() { itsUsed = false; func_string = false; }
		// Dieser String gibt die ID aus
		std::string GiveID() { return buffer; }
		// Dieser String gibt den Hasch-Wert der IDv aus
		std::string GiveHash() { return IDvHash; }
		// Dieser int gibt an um was für eine ID es sich Handelt
		int GiveStringType() { return type; }
		// Gibt an ob der String beschrieben wurde
		bool StringUsedCheck() { return itsUsed; }
		friend class PackageHandler;
		friend IDvString SelfID();
		friend IDvString UnkownID();
	};
	IDvString SelfID();
	IDvString UnkownID();
	/*
	Speichert alle wichtigen Paket Meta Datan ab
	*/
	struct PackageMeteDatas { IDvString from, to; };
	/*
	Eine Package speichert eine Package ab ähnlich wie in einem String.
	*/
	class Package {
	protected:
		// Speichert alle Paket Objekte ab
		PackageObjectDatas ObjectBuff;		
		// Speichert die Meta Data eines Paketes ab, zb von, an, Session ID, Package ID
		PackageMeteDatas MeteBuff;		
		// Gibt den Status des Aktuellen Paketes an
		int cpstate();
		// Gibt an ob das Paket beschrieben wurde
		bool psww();
	public:
	};
	/* 
	Package Handler, sind die erste Instance wenn es darum geht Rohdaten in eine Package zu laden,
	hierbei kann dies z.b aus einer Datei heraus oder aus einem String passieren.
	*/
	class PackageHandler {
	private:
		int L_O_state = 0;					// Gibt den Statuscode der Letzten Operation aus
		int nlType = 0;						// Gibt an ob das Paket mit UDP oder TCP versand wurde
		int mType = 0;						// Gibt z.b aus ob das Paket ein Stream oder eine DirektSend ist
		int pType = 0;						// Gibt den Pakettypen an
		bool cann_used = false;				// Solange dieser Wert auf False steht kann ein solches Paket nicht verwendet werden
		PackageObjectDatas ObjectBuff;		// Speichert alle Paket Objekte ab
		PackageMeteDatas MeteBuff;			// Speichert die Meta Data eines Paketes ab, zb von, an, Session ID, Package ID
	public:
		// Erstellt aus einem String ein Package, solange der Synatx richtig ist
		PackageHandler(const char*);		
		// Erstellt aus einem String ein Package, solange der Synatx richtig ist
		PackageHandler(std::string);		
		// Diese Funkion gibt aus ob das Package richtig ist und ob eine Ausgabe als Package möglich ist
		bool coutpck();		
		// Gibt die ausgewerteten Daten in ein Package weiter
		Package GivePackage();
	};
	/*
	Package Creator, mit diesem Objekt können sie neue Pakete erstellen, defenieren sie dabei Genau wie das Paket aufgebaut werden soll und befüllen es am nurnoch mit Daten und können es Direkt absenden
	*/
	class PackageCreator {

	};

}