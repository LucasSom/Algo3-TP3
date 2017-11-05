#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <sys/stat.h>
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <string>

using namespace std;

string crear(int columns, int rows, int c, int p){
	
	string res;
	res="python c_linea.py --blue_player ./genera2 --red_player ./random_player --first azul  --columns ";
	res=res+ to_string(columns);
	res=res+ " --rows ";
	res=res+ to_string(rows);
	res=res+ " --p ";
	res=res+  to_string(p);
	res=res+ " --c ";
	res=res+ to_string(c);
	res=res+ " --iterations 10";
	return res;
}
int main(){
	
	int k=20;
	srand((unsigned int)time(NULL));
	for(int columns=2;columns<=k;++columns){	
		for (int rows=2;rows<=k;++rows){
			int p=columns*rows;
			int c= (rand() % (min(columns,rows)-1))+2;
				
			string a = crear(columns, rows, c, p);
			system(a.c_str());	

		}
	}
	return 0;
}
