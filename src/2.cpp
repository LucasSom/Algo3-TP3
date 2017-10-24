#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <sys/stat.h>

using namespace std;

std::random_device rd;
std::mt19937 generator(rd());

void send(const std::string& msg) {
    std::cout << msg << std::endl;
}

void send(int msg) {
    std::cout << msg << std::endl;
}

int read_int() {
    std::string msg;
    std::cin >> msg;
    if (msg == "salir") {
        send("listo");
        std::exit(0);
    }
    return std::stoi(msg);
}

std::string read_str() {
    std::string msg;
    std::cin >> msg;
    if (msg == "salir") {
        send("listo");
        std::exit(0);
    }
    return msg;
}







//RECORDAR TODOS LOS PARAMETROS QUE AGREGAMOS, PONERSELOS EN CADA LLAMADA DE PUNTAJES ¿Y EN LA DE PARAMETRIZABLE?


int puntaje(int rows, int columns, int c, int p, const vector<vector<int>>& tablero, int ultimajugada){
	//ideas de puntajes:
	
	//cantidad de fichas en los bordes
	//cantidad de fichas en las esquinas
	//cantidad de fichas en el centro
	//cantidad de fichas consecutivas, donde agregar una suma mucho mas. (¿mirar solo las utiles? i.e las extensibles a un 4 en linea)
	//cantidad de posibles 4 en linea que puedo formar
	//gano +inf y si pierdo es -inf

	//tratar de maximizar mi putntaje, o minimizar el de el, o maximizar la diferencia (me parece mejor la ultima pero puede ser otro parámetro)
	
	
	
	
		
	
	
	
	}

















int parametrizable (int rows, int columns, int c, int p, vector<vector<int>>& tablero, int ultimajugada ){
	//vamos a asignar un puntaje a cada tablero y de las ocho opciones posibles vamos a tomar la de major puntaje
	//esta sería la parte golosa. Los parámetros serían los puntajes que suman de diversos cosas
	
	vector<int> posibles;
	for(int h=0;h<columns;++h){
		if(tablero[h].size()<rows){ posibles.push_back(h);}
	}
	
	
	//si o si hay una jugada posibles pues sino seria empate
	tablero[posibles[0]].push_back(1);
	int maximopuntaje=puntaje(rows, columns, c, p, tablero, ultimajugada);
	int maxpos=posibles[0];
	tablero[posibles[0]].pop_back();
	
	for(int q=1; q< posibles.size();++q){
		tablero[posibles[q]].push_back(1);
		if(puntaje(rows, columns, c, p, tablero, ultimajugada)>maximopuntaje){
			maximopuntaje=puntaje(rows, columns, c, p, tablero, ultimajugada);
			maxpos= posibles[q];
			}
		tablero[posibles[q]].pop_back();		
	}
	
	return maxpos;
}

	
	
	









int main() {

    //std::default_random_engine generator;
    std::string msg, color, oponent_color, go_first;
    int columns, rows, c, p, move;

    while (true) {
        color = read_str();
        oponent_color = read_str();

        columns = read_int();
        rows = read_int();
        c = read_int();
        p = read_int();
		//std::vector<int> board(columns);
		vector<vector<int>>tablero (columns);
		//la primer cordenada del tablero es la columna, y la segunda es la fila
        
        //for(int i=0; i<columns; ++i) board[i] = 0;
		
		p=2*p;//CAMBIO CHEBAR FICHAS, AHORA CUENTO FICHAS TOTALES
        go_first = read_str();
        if (go_first == "vos") {
            move = parametrizable(rows, columns, c, p, tablero, -1);
            tablero[move].push_back(1); //juego yo
            //board[move]++;
            --p;
            send(move);
        }

        while (true) {
            msg = read_str();
            if (msg == "ganaste" || msg == "perdiste" || msg == "empataron") {
                break;
            }
			tablero[std::stoi(msg)].push_back(2);//juega el
			--p; //CAMBIO CHEBAR FICHAS AHORA CUENTO FICHAS TOTALES
            //board[std::stoi(msg)]++;
            move = parametrizable(rows, columns, c, p, tablero, std::stoi(msg));
            tablero[move].push_back(1); //juego yo
            //board[move]++;
            --p;
            send(move);
        }
    }

    return 0;
}
