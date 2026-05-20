#include "gradebook.h"
#include <iostream>
#include <map>
#include <string>
using namespace std;
int main(int argc, char* argv[]){
	map<string,int> scores;
	for(int i=1;i<argc;i++){
		if(!processfile(argv[i],scores))
			cout<<argv[i]<<": error processing file\n";
	}
	pr(scores);
	return 0;
}
