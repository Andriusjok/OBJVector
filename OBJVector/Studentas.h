#pragma once
#include "header.h"
#include "Zmogus.h"
#include "vector"
using std::vector;
//#include "Vector.h"
class Studentas : public Zmogus
{
protected:
	vector<int> v_;
	int e_;
	double galutinis_;	
	double galutmed_;
public:
	
	Studentas(string pavarde = "", string vardas = "", double e = 0, double galutinis = 0, double galutinismed = 0) : Zmogus(pavarde, vardas), e_(e), galutinis_(galutinis), galutmed_(galutinis) { }
	Studentas(ifstream& input, unsigned int &Vilgis, unsigned int &Pilgis);
	inline string vardas() const {return vardas_;}
	inline string pavarde() const {return pavarde_;}
	double galutinisVid() const {return galutinis_;}
	double galutinisMed() const {return galutmed_;}

void verification(){}
	void setVardas(string vardas) {vardas_ = vardas;}
	void setPavarde(string pavarde) {pavarde_ = pavarde;}
	void setE(int e) {e_ = e;}
	void pushV(int v) {v_.push_back(v);}
	void reserveV(int rsize) {v_.reserve(rsize);}
	void setEback();
	void FindLongest(vector<Studentas> &input, unsigned int &Vilgis, unsigned int &Pilgis);

	void getAverage();
	void getMedian();


	// operatoriai

void operator +=(int b);

int operator >>(unsigned int & b);


int operator <<(unsigned int & b);

	};







bool compare_by_word(const Studentas& lhs, const Studentas& rhs);
bool compare_by_name(const Studentas& lhs, const Studentas& rhs);
bool compare_by_grades(const Studentas& lhs);
bool compare_by_mediana(const Studentas& lhs);