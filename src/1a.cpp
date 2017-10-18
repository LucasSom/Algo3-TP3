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



bool ganojugador(vector<vector<int>> tablero, int i, int ultimajugada){
	//ESTA FUNCION TIENE QUE DECIDIR SI DADO EL TABLERO (NO ESTA COMPLETO, ES VECTOR DE VECTORES DE DISTINTOS 
	//TAMAÑOS, NO ES MATRIZ GANA EL JUGADOR i. CONSIDERANDO QUE HAY UN i EN LA POSICION EN LA QUE JUGO EL JUGADOR i
	//EJEMPLO DE TABLERO:
	/*
	 * 
	 * 1
	 * 1       2 
	 * 2   1 2 1 1
	 * 2   2 2 1 1
	 * 1 2 1 1 2 2
	 * ACA SI FUESE CUATRO EN LINEA, GANO EL 2 PORQUE TIRO UNA DIAGONAL DE 4. SI LLAMAS GANOJUGADOR(TABLERO,2)
	 * DEBERIA DAR TRUE
	 * */
}

bool gane ( const vector<vector<int>>& tablero, int ultimajugada){
	return ganojugador(tablero,1, ultimajugada);	
}
	
bool perdi (const vector<vector<int>>& tablero, int ultimajugada){
	return ganojugador(tablero,2, ultimajugada);	
}



// la función minimax devuelve un par, el primer elemento es la posición donde consigue el mejor valor posible
// es decir la jugada óptima desde el tablero de entrada, el segundo elemento es el mejor valor que
// se puede conseguir al hacer esa jugada.
pair<int,int> minimax(int rows, int columns, int c, int p, vector<vector<int>> tablero,  bool maximizo, int ultimajugada){
	//el 888888888888 y -88888888 son numeros de relleno, porque aun no inicialize. Uso el negativo para que no
	//afecte al tomar maximo entre 0,1 y -1
	
	
	if(gane(tablero, ultimajugada)) {return make_pair(88888888,1);} //gane
	
	if(perdi(tablero, ultimajugada)) {return make_pair(88888888,-1);} //perdi
	
	if(p==0) { return make_pair(88888888,0);} //empate, no hay fichas
	
	vector<std::pair<int,int> > posibles;
	for(int h=0;h<columns;++h){
		if(tablero[h].size()<rows){ posibles.push_back(make_pair(h,-88888888));}
		//el -88888888 es que aun no se el puntaje que da ese nodo en el arbol minimax
	}
	
	if(posibles.size()==0) {return make_pair(88888888,0);} //empate, se lleno el tablero

	//hago la recursion, llamando al siguiente en el arbol de minimax
	for(int i=0; i<posibles.size(); ++i){
		vector<vector<int>> tablero2=tablero;
		int quienva;
		if(maximizo) {quienva=1;} else {quienva=2; }
		tablero2[posibles[i].first].push_back(quienva); //juego el o yo, segun minimice o maximice respectivamente.
		if (maximizo) {
			posibles[i].second = minimax(rows, columns, c, p-1, tablero2, not maximizo, posibles[i].first).second;
		} else {
			posibles[i].second = minimax(rows, columns, c, p-1, tablero2, not maximizo, posibles[i].first).second;
		}
	}
	
	if (maximizo) {
		//agarro la columna que da el maximo y devuelvo.
		int maxpos=posibles[0].first;
		int maximo=posibles[0].second;
		for (int h=1;h<posibles.size();++h) {
			if (maximo<posibles[h].second) {maximo=posibles[h].second; maxpos=posibles[h].first;};
		}
		
		return make_pair(maxpos, posibles[maxpos].second) ;//donde tenia que jugar y cual es el resultado en ese orden	
	} else {
		
		//agarro la columna que da el minimo y devuelvo.
		int minpos=posibles[0].first;
		int minimo=posibles[0].second;
		for (int h=1;h<posibles.size();++h) {
			if (minimo>posibles[h].second) {minimo=posibles[h].second; minpos=posibles[h].first;};
		}
		
		return make_pair(minpos, posibles[minpos].second) ;//donde tenia que jugar y cual es el resultado en ese orden

	}
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

        go_first = read_str();
        if (go_first == "vos") {
            move = minimax(rows, columns, c, p, tablero, true, -1).first;
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
            //board[std::stoi(msg)]++;
            move = minimax(rows, columns, c, p, tablero, true, std::stoi(msg)).first;
            tablero[move].push_back(1); //juego yo
            //board[move]++;
            --p;
            send(move);
        }
    }

    return 0;
}
