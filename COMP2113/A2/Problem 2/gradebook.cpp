#include "gradebook.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

bool processfile(const string& filename, map<string, int>& scores){
	ifstream file(filename);
	if(!file.is_open())
		return false;
	
	string line;
	bool err=0;
	while(getline(file,line)){
		if(line.empty()) continue;
		stringstream ss(line);
		string id,scstr,ext;
		if(!(ss>>id>>scstr) or ss>>ext){
		    err=1;
		    continue;
		}
		try{
			size_t pos;
			int sc=stoi(scstr,&pos);
			if(pos!=scstr.length()){
			    err=1;
			    continue;
			}
			if(sc<0 or sc>100){
			    err=1;
			    continue;
			}
			if(scores.find(id)==scores.end() or sc>scores[id])
				scores[id]=sc;
		} catch(...){
			err=1;
		}
	}
	
	file.close();
	return !err;
}
void pr(const map<string, int>& scores){
	int H=0,L=100,p=0;
	string stu_h="",stu_l="";
	for(auto const& x: scores){
		const string id=x.first;
		const int sc=x.second;
		if(sc>H) H=sc,stu_h=id;
		if(sc<L) L=sc,stu_l=id;
		if(sc>=50) p++;
	}
	cout<<"Top: "<<stu_h<<' '<<H<<endl;
	cout<<"Bottom: "<<stu_l<<' '<<L<<endl;
	cout<<"Pass: "<<p<<endl;
	cout<<"Total: "<<scores.size();
}
