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



//Dado un tablero de c en linea y columna donde se realizo la ultima jugada, decide si el jugador i gano o no
bool ganojugador(vector<vector<int>> tablero, int i, int c, int ultimajugada){
	
    
	 if(ultimajugada==-1){if(c==1) {return true;}else{return false;}}
     //Por si es la primer jugada, nadie gano aun, salvo sea 1 en linea.
	 
     //Por si es la primer jugada, nadie gano aun
	 if (tablero[ultimajugada][tablero[ultimajugada].size()-1]!=i) return false; //tablero[j].size()-1 es la ultima fila con fichas de la columna j
	 bool esMio = true;
		
		
		 //checkear si hay c en linea en la columna
		 if (tablero[ultimajugada].size() < c){
			 esMio=false;//si la columna tiene menos fichas que c, no checkeamos
		 }else{
			 int k=tablero[ultimajugada].size()-1; //k es la fila que voy a chequear ahora
			 while (tablero[ultimajugada].size()-k<=c && esMio){
				 if (tablero[ultimajugada][k] != i) esMio=false;		 
				 --k;
			 }
			 if (esMio) return true;
		 }
		 
		
		///////////////////////////////////////////////////////////////////////////////////////////// 
		 //checkear si hay c en linea en la fila
		 esMio = true;
		 int k=ultimajugada;
		 int contador=0;
		 while (esMio && k>=0 && contador<c){
			 //calculamos cuantos de los que estan a la izquierda de j son iguales
			 if (tablero[k].size()>=tablero[ultimajugada].size() && tablero[k][tablero[ultimajugada].size()-1]==i){
				 ++contador;
			 }else{
				 esMio = false;
			 }
			 --k;
		 }
		 ///////////////////////Calcular a derecha//////////////////////////////
		 k=ultimajugada;
		 --contador;
		 esMio=true;
		 while (esMio && k<tablero.size() && contador<c){
			 //calculamos a la derecha de j
			 if (tablero[k].size()>=tablero[ultimajugada].size() && tablero[k][tablero[ultimajugada].size()-1]==i){
				 ++contador;
			 }else{
				 esMio = false;
			 }
			 ++k;
		 }
		 if (contador==c) return true;
		 //Por la guarda del while, o bien contador es  <c (salimos del while por alguna de las otras razones)
		 //o bien es igual a c por lo que no tiene sentido que el checkeo sea con >= 

		/////////////////////////////////////////////////////////////////////////////////////////////
		 //checkear si hay c en linea en diagonal hacia arriba (de izq a der)
		 esMio = true;
		 int col=ultimajugada;
		 int fil=tablero[ultimajugada].size()-1;
		 contador=0;
		 while (esMio && col>=0 && fil>=0 && contador<c){
			 //calculamos cuantos de los que estan a la izquierda de j son iguales
			 if (tablero[col].size()>=tablero[ultimajugada].size()-(ultimajugada-col) && tablero[col][fil]==i){
			 	++contador;
			 }else{
				 esMio = false;
			 }
			 --col;
			 --fil;
		 }
		 ///////////////////////Calcular a derecha//////////////////////////////
		 col=ultimajugada;
		 fil=tablero[ultimajugada].size()-1;
		 --contador;
		 esMio=true;
		 
		 while (esMio && col<tablero.size() && contador<c){
			 //calculamos a la derecha de j
			 if (tablero[col].size()>=tablero[ultimajugada].size()+(col-ultimajugada) && tablero[col][fil]==i){
				  ++contador;
			 }else{
				 esMio = false;
			 }
			 ++col;
			 ++fil;
		 }
		 if (contador==c) return true;
		 
		 //////////////////////////////////////////////////////////////////////////////////////////////
		 //checkear si hay c en linea en diagonal hacia abajo
		 esMio = true;
		 col=ultimajugada;
		 fil=tablero[ultimajugada].size()-1;
		 contador=0;
		 while (esMio && col>=0 && contador<c){
			 //calculamos cuantos de los que estan a la izquierda de j son iguales
			 if (tablero[col].size()>=tablero[ultimajugada].size()+(ultimajugada-col) && tablero[col][fil]==i){
				 ++contador;
			 }else{
				 esMio = false;
			 }
			 --col;
			 ++fil;
		 }
		 ///////////////////////Calcular a derecha//////////////////////////////
		 col=ultimajugada;
		 fil=tablero[ultimajugada].size()-1;
		 --contador;
		 esMio=true;
		 
		 while (esMio && col<tablero.size() && fil>=0 && contador<c){
			 //calculamos a la derecha de j
			 if (tablero[col].size()>=tablero[ultimajugada].size()-(col-ultimajugada) && tablero[col][fil]==i){
				 ++contador;
			 }else{
				 esMio = false;
			 }
			 ++col;
			 --fil;
		 }
		 if (contador==c) return true;
		 
	 return false;
}


bool gane ( const vector<vector<int>>& tablero, int c, int ultimajugada){
	return ganojugador(tablero, 1, c, ultimajugada);	
}
	
bool perdi (const vector<vector<int>>& tablero, int c, int ultimajugada){
	return ganojugador(tablero, 2, c, ultimajugada);	
}


// la función minimax devuelve un par, el primer elemento es la posición donde consigue el mejor valor posible
// es decir la jugada óptima desde el tablero de entrada, el segundo elemento es el mejor valor que
// se puede conseguir al hacer esa jugada.

// A cada tablero posible solo le doy tres valores (-1, 0, 1) para diferenciar entre situaciones en las que tengo
// estrategia ganadora, situaciones de empate, o el otro tiene estrategia ganadora respectivamente. Como son solo
// esos tres valores, se que cuando quiero inicializar alfa y beta en -infinito o +infinito para la poda,
// puedo inicializarlos en -2 y 2 y se van a comportar como -infinito y +infinito
pair<int,int> minimax(int rows, int columns, int c, int p, vector<vector<int>> tablero,  bool maximizo, int alfa, int beta, int ultimajugada){
	//el 888888888888 y -88888888 son numeros de relleno, porque aun no inicialize. Uso el negativo para que no
	//afecte al tomar maximo entre 0,1 y -1
	
	
	if(gane(tablero, c, ultimajugada)) {return make_pair(88888888,1);} //gane
	
	if(perdi(tablero, c, ultimajugada)) {return make_pair(88888888,-1);} //perdi
	
	if(p==0) { return make_pair(88888888,0);} //empate, no hay fichas
	
	vector<std::pair<int,int> > posibles;
	for(int h=0;h<columns;++h){
		if(tablero[h].size()<rows){ posibles.push_back(make_pair(h,-88888888));}
		//el -88888888 es que aun no se el puntaje que da ese nodo en el arbol minimax
	}
	
	if(posibles.size()==0) {return make_pair(88888888,0);} //empate, se lleno el tablero

	int mejorPos = posibles[0].first;
	int mejorValorMaximizo= -88888888; //Segun minimice o maximice quiero que se inicialice en algo >1 o <-1
	int mejorValorMinimizo= 88888888;  //sería el equivalente a +INF y -INF con el que uno empieza en la poda alpha-beta
	
	//hago la recursion, llamando al siguiente en el arbol de minimax
	for(int i=0; i<posibles.size(); ++i){
		vector<vector<int>> tablero2=tablero;
		int quienva;
		if(maximizo) {quienva=1;} else {quienva=2; }
		tablero2[posibles[i].first].push_back(quienva); //juego el o yo, segun minimice o maximice respectivamente.
        posibles[i].second = minimax(rows, columns, c, p-1, tablero2, not maximizo, alfa, beta, posibles[i].first).second;
		if (maximizo && posibles[i].second > mejorValorMaximizo) {
				mejorPos = posibles[i].first;
				mejorValorMaximizo = posibles[i].second;
        }
        if (not maximizo && posibles[i].second < mejorValorMinimizo) {
            mejorPos = posibles[i].first;
            mejorValorMinimizo = posibles[i].second;
        }
            
        alfa = max(alfa, mejorValorMaximizo);
        beta = min(beta, mejorValorMinimizo);

        if (alfa >= beta) {
            break;
        }
	}
	if(maximizo) {
		return make_pair(mejorPos, mejorValorMaximizo);
	} else {
		return make_pair(mejorPos, mejorValorMinimizo);
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
		vector<vector<int>>tablero (columns);

		p=2*p;//Cuento fichas totales
        go_first = read_str();
        if (go_first == "vos") {
            move = minimax(rows, columns, c, p, tablero, true, -2, 2, -1).first;
            tablero[move].push_back(1); //juego yo
            --p;
            send(move);
        }

        while (true) {
            msg = read_str();
            if (msg == "ganaste" || msg == "perdiste" || msg == "empataron") {
                break;
            }
			tablero[std::stoi(msg)].push_back(2);//juega el
			--p; //Recordar que contamos fichas totales
            move = minimax(rows, columns, c, p, tablero, true, -2, 2, std::stoi(msg)).first;
            tablero[move].push_back(1); //juego yo
            --p;
            send(move);
        }
    }

    return 0;
}
