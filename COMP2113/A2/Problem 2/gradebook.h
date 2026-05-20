#ifndef GRADEBOOK_H
#define GRADEBOOK_H

#include <string>
#include <map>
using namespace std;

bool processfile(const string& filename, map<string,int>& scores);
void pr(const map<string,int>& scores);

#endif 
