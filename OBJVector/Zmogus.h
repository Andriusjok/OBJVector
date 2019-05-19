#pragma once
#include "header.h"
	class Zmogus {
	protected:
		string vardas_;
		string pavarde_;
	public:

			Zmogus(string pavarde="",string vardas=""):pavarde_(pavarde),vardas_(vardas){}

		virtual void verification() = 0;
		void setPav(string pavarde) {pavarde_=pavarde;}
		void setVard(string vardas) {vardas_=vardas;}
		string getPav(string pavarde){return pavarde_;}
		string getVard(string vardas){return vardas_;}
	};