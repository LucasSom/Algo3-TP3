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


/*
void relleno(vector<std::pair<int,int> > posibles, int rows, int columns, int c, int& p, vector<int> board, bool maximizo){
	
	
	}
*/


bool ganojugador(vector<vector<int>> tablero, int i){
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

bool gane ( const vector<vector<int>>& tablero){
	return ganojugador(tablero,1);	
}
	
bool perdi (const vector<vector<int>>& tablero){
	return ganojugador(tablero,2);	
}



// A cada tablero posible solo le doy tres valores (-1, 0, 1) para diferenciar entre situaciones en las que tengo
// estrategia ganadora, situaciones de empate, o el otro tiene estrategia ganadora respectivamente. Como son solo
// esos tres valores, se que cuando quiero inicializar alfa y beta en -infinito o +infinito para la poda,
// puedo inicializarlos en -2 y 2 y se van a comportar como -infinito y +infinito
pair<int,int> minimax(int rows, int columns, int c, int p, vector<vector<int>> tablero,  bool maximizo, int alfa, int beta){
	//el 888888888888 y -88888888 son numeros de relleno, porque aun no inicialize. Uso el negativo para que no
	//afecte al tomar maximo entre 0,1 y -1
	
	
	if(gane(tablero)) {return make_pair(88888888,1);} //gane
	
	if(perdi(tablero)) {return make_pair(88888888,-1);} //perdi
	
	if(p==0) { return make_pair(88888888,0);} //empate, no hay fichas
	
	vector<std::pair<int,int> > posibles;
	for(int h=0;h<columns;++h){
		if(tablero[h].size()<rows){ posibles.push_back(make_pair(h,-88888888));}
		//el -88888888 es que aun no se el puntaje que da ese nodo en el arbol minimax
	}
	
	if(posibles.size()==0) {return make_pair(88888888,0);} //empate, se lleno el tablero
	
	
	//CAMBIO MATO
	//CAMBIO MATO
	//CAMBIO MATO
	//CAMBIO MATO
	//CAMBIO MATO
	//CAMBIO MATO
	//CAMBIO MATO

	//hago la recursion, llamando al siguiente en el arbol de minimax
	for(int i=0; i<posibles.size(); ++i){
		vector<vector<int>> tablero2=tablero;
		int quienva;
		if(maximizo) {quienva=1;} else {quienva=2; }
		tablero2[posibles[i].first].push_back(quienva); //juego el o yo, segun minimice o maximice respectivamente.
		if (maximizo) {
			posibles[i].second = minimax(rows, columns, c, p-1, tablero2, not maximizo, , ).second;
		} else {
			posibles[i].second = minimax(rows, columns, c, p-1, tablero2, not maximizo, , ).second;
		}
	}
	
	
	
	if (maximizo) {
		//agarro la columna que da el maximo y devuelvo.
		int maxpos=posibles[0].first;
		int maximo=posibles[0].second;
		for (int h=1;h<columns;++h) {
			if (maximo<posibles[h].second) {maximo=posibles[h].second; maxpos=posibles[h].first;};
		}
		
		return make_pair(maxpos, posibles[maxpos].second) ;//donde tenia que jugar y cual es el resultado en ese orden	
	} else {
		//CAMBIO MATO
		//CAMBIO MATO
		//CAMBIO MATO
		//CAMBIO MATO
		//CAMBIO MATO
		//CAMBIO MATO
		//CAMBIO MATO
		//CAMBIO MATO

		//agarro la columna que da el maximo y devuelvo.
		int minpos=posibles[0].first;
		int minimo=posibles[0].second;
		for (int h=1;h<columns;++h) {
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
		//CAMBIO MATO
		//CAMBIO MATO
		//CAMBIO MATO
		//CAMBIO MATO
		//CAMBIO MATO
		//CAMBIO MATO
		//CAMBIO MATO
		//std::vector<int> board(columns);
		vector<vector<int>>tablero (columns);

        for(int i=0; i<columns; ++i) board[i] = 0;

        go_first = read_str();
        if (go_first == "vos") {
            move = minimax(rows, columns, c, p, tablero, true, -2, 2).first;
            tablero[move].push_back(1); //juego yo
            //board[move]++;
            //--p;
            send(move);
        }

        while (true) {
            msg = read_str();
            if (msg == "ganaste" || msg == "perdiste" || msg == "empataron") {
                break;
            }
			tablero[std::stoi(msg)].push_back(2);//juega el
            //board[std::stoi(msg)]++;
            move = minimax(rows, columns, c, p, tablero, true, -2, 2).first;
            tablero[move].push_back(1); //juego yo
            //board[move]++;

            //CAMBIO MATO
            //CAMBIO MATO
            //CAMBIO MATO
            //CAMBIO MATO
            //CAMBIO MATO
            //CAMBIO MATO
            --p;
            send(move);
        }
    }

    return 0;
}
