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

std::random_device rd;
std::mt19937 generator(rd());
#define INF std::numeric_limits<float>::max();
#define INFneg std::numeric_limits<float>::min();


//------------------ ESTRUCTURA QUE CONTIENE LOS PARAMETROS QUE TOMARA LA FUNCION PARAMETRIZABLE--------------

struct parametro{
	//cada par es el puntaje que le doy a la cualidad del tablero, en el primer lugar lo que valen los mios
	// y en el segundo lugar los de el. Siempre hago cantMiosCualidad*MiValor-cantSuyosCualidad*SuValor
	
	//los vectores asignan en particular cuanto vale para cada longitud. Tienen c-1 elementos, que son las c-1
	//longitudes posibles.
	
	pair<float,float> esquinaparam, bordeparam, centroparam, libertadparam;
		
	vector<float> consecutivos; //tiene que tener c-1 cosas
	
	pair<float,float> consecparam;
	
	vector<float> extensiblesprox; //tiene que tener c-1 cosas
	
	pair<float,float> extproxparam;
	
	vector<float> extensibles; //tiene que tener c-1 cosas
	
	pair<float,float> extparam;

	vector<float> biextensibles; //tiene que tener c-1 cosas
	
	pair<float,float> biextparam;	
		
	bool operator ==(const parametro& p){} 	
};


//---------------------FUNCIONES QUE DETERMINAN SI UN JUGADOR YA GANO O NO-------------

//determina si dado un tablero gano el jugador i:
bool ganojugador(vector<vector<int>> tablero, int i, int c, int ultimajugada){
	
	 if(ultimajugada==-1){if(c==1) {return true;}else{return false;}}
     //CAMBIO CHEBAR, AGREGUE ESTO, COSA QUE SI HAY QUE PONER UNA SOLA Y SOS EL PRIMERO EN JUGAR YA GANASTE
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
			 	//yo pondría si empieza a funcionar mal tablero[col].size()>=fil+1
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
//determina si dado un tablero gane yo (el jugador 1):
bool gane ( const vector<vector<int>>& tablero, int c, int ultimajugada){
	return ganojugador(tablero, 1, c, ultimajugada);	
}
//determina si dado un tablero perdí yo (el jugador 1), o sea gano el otro (jugador 2):	
bool perdi (const vector<vector<int>>& tablero, int c, int ultimajugada){
	return ganojugador(tablero, 2, c, ultimajugada);	
}


//------------------FUNCIONES PARA DETECTAR CARACETRISTICAS PARA PUNTAJES----------------



//cuenta fichas en algun borde del jugador i:
int enborde(int rows,int columns,const vector<vector<int>>& tablero, int i){
	int enborde=0;
	for (int h=0; h<columns; ++h){
		if (tablero[h].size()!=0 && tablero[h][0]==i) {++enborde;} //en la fila de abajo
		if (tablero[h].size()==rows && tablero[h][rows-1]==i) {++enborde;} //en la fila de arriba de todo
	}
	for (int h=0; h<tablero[0].size(); ++h){
		if(tablero[0][h]==i){++enborde;}//en primera columna
	}
	for (int h=0; h<tablero[columns-1].size(); ++h){
		if(tablero[columns-1][h]==i){++enborde;}//en ultima columna
	}
	if (tablero[0].size()!=0 && tablero[0][0]==i) {--enborde;} //conte dos veces la esquina inf izq
	if (tablero[columns-1].size()!=0 && tablero[columns-1][0]==i) {--enborde;} //conte dos veces la esquina inf der
	if (tablero[0].size()==rows && tablero[0][rows-1]==i) {--enborde;} //conte dos veces la esquina sup izq
	if (tablero[columns-1].size()==rows && tablero[columns-1][rows-1]==i) {--enborde;} //conte dos veces la esquina sup der
	return enborde;
	
	}
//cuenta fichas en alguna esquina el jugador i:
int enesquinas(int rows,int columns,const vector<vector<int>>& tablero, int i){
	int enesquina=0;
	if (tablero[0].size()!=0 && tablero[0][0]==i) {++enesquina;} //la esquina inf izq
	if (tablero[columns-1].size()!=0 && tablero[columns-1][0]==i) {++enesquina;} //la esquina inf der
	if (tablero[0].size()==rows && tablero[0][rows-1]==i) {++enesquina;} //la esquina sup izq
	if (tablero[columns-1].size()==rows && tablero[columns-1][rows-1]==i) {++enesquina;} //la esquina sup der
	return enesquina;
	
	}
//cuenta fichas en el centro del jugador i:
int encentro(int rows,int columns,const vector<vector<int>>& tablero, int i){
	int encentro=0;
	if(columns % 2 == 0){//si hay pares columnas, hay dos centrales, cuento la que aparece solo si es par
		for (int h=0; h<tablero[(columns/2) - 1].size(); ++h){
			if (tablero[(columns/2) - 1].size()!=0 && tablero[(columns/2) -1][h]==i) {++encentro;} 
		}
	}
	for (int h=0; h<tablero[columns/2].size(); ++h){
		if (tablero[columns/2].size()!=0 && tablero[columns/2][h]==i) {++encentro;} //cuento en el centro
	}

	return encentro;
	
	}
//cuenta la cantidad de libertades que tiene una casilla (o sea casillas sin nada que sean vecinas):
int libertades(int q, int h, const vector<vector<int>>&  tablero){
	int res=0;
	if(q+1<tablero.size() && tablero[q+1].size()<h+2){
		++res; //sumo el de arriba a la der si esta vacio
		if(tablero[q+1].size()<h+1){++res;} //sumo el de la der si esta vacio
		if(tablero[q+1].size()<h){++res;}	 //sumo el de abajo a la der si esta vacio	
	}
	if(q-1>=0 && tablero[q-1].size()<h+2){
		++res; //sumo el de arriba a la izq si esta vacio
		if(tablero[q-1].size()<h+1){++res;} //sumo el de la izq si esta vacio
		if(tablero[q-1].size()<h){++res;}	//sumo el de abajo a la izq si esta vacio	
	}
	if(tablero[q].size()==h+1){ ++res;} //sumo la de arriba si esta vacía	
	return res;
}
//suma todas las libertades de todas las fichas del jugador i:
int libres (int rows,int columns,const vector<vector<int>>& tablero, int i){
	int resultado=0;
	for(int q=0; q< columns;++q){
		for(int h=0; h<tablero[q].size();++h){
			if(tablero[q][h]==i) {resultado=resultado+libertades(q,h,tablero);}	
		}
	}
	return resultado;
}
//cuenta las fichas consecutivas de cualquier tamaño entre 1 y c-1 que tiene el jugador i:
vector<int> consec(int rows, int columns, const vector<vector<int>>& tablero, int c, int i){
	vector<int> res(c,0); //cantidad de consecutivas que tengo. En el lugar i aparecen la cantidad que tienen i. Las que tienen 0 las desestimo, puede decir cualquier cosa ahi
	//miro en las columnas
	for(int h=0;h<columns;++h){
		int contador=0;
		int k=tablero[h].size()-1; 
		while (k>=0){
			if(tablero[h][k]==i){
				++contador;
			}else{
				++res[contador]; //agrego una de longitud contador
				contador=0;
			}
			 --k;
		}
		++res[contador];
	}	
		
		
	//miro en las filas
	for(int h=0;h<rows;++h){
		int contador=0;
		int k=columns-1; 
		while (k>=0){
			if(tablero[k].size()>h && tablero[k][h]==i){
				++contador;
			}else{
				++res[contador]; //agrego una de longitud contador
				contador=0;
			}
			 --k;
		}
		++res[contador];
	}
	
	//miro en diagonal de arriba der a abajo izq
	
	//primero cuento las que estan debajo de la diagonal principal, incluyendo esta
	for(int h=rows-1;h>=0;--h){
		int contador=0;
		int k=columns-1;		 
		while (k>=0 && h>=0){
			if(tablero[k].size()>h && tablero[k][h]==i){
				++contador;
			}else{
				++res[contador]; //agrego una de longitud contador
				contador=0;
			}
			 --k;
			 --h;
		}
	}
	//ahora las que estan por encima de la diagonal principal
	for(int k=columns-2;k>=0;--k){
		int contador=0;
		int h=rows-1;		 
		while (k>=0 && h>=0){
			if(tablero[k].size()>h && tablero[k][h]==i){
				++contador;
			}else{
				++res[contador]; //agrego una de longitud contador
				contador=0;
			}
			 --k;
			 --h;
		}
		++res[contador];
	}
	
	
	
	
	//miro en diagonal de arriba izq a abajo der
	
	//primero cuento las que estan debajo de la diagonal principal, incluyendo esta
	for(int h=rows-1;h>=0;--h){
		int contador=0;
		int k=0;		 
		while (k<columns && h>=0){
			if(tablero[k].size()>h && tablero[k][h]==i){
				++contador;
			}else{
				++res[contador]; //agrego una de longitud contador
				contador=0;
			}
			 ++k;
			 --h;
		}
		++res[contador];
	}
	//ahora las que estan por encima de la diagonal principal
	for(int k=1;k<columns;++k){
		int contador=0;
		int h=rows-1;		 
		while (k<columns && h>=0){
			if(tablero[k].size()>h && tablero[k][h]==i){
				++contador;
			}else{
				++res[contador]; //agrego una de longitud contador
				contador=0;
			}
			 ++k;
			 --h;
		}
		++res[contador];
	}
	
	
	return res;
}
//cuenta las fichas consecutivas que son extensibles en el proximo turnode cualquier tamaño entre 1 y c-1 
//que tiene el jugador i:
vector<int> extprox(int rows, int columns, const vector<vector<int>>& tablero, int c, int i){
	vector<int> res(c,0); //cantidad de consecutivas extensibles en el proximo movimiento. En el lugar i aparecen la cantidad que tienen i ahora. Las que tienen 0 las desestimo, puede decir cualquier cosa ahi
	for(int h=0;h<columns;++h){
	if(tablero[h].size()<rows){
		
		//miro la columna
		int contador=0;
		int k=tablero[h].size()-1; 
		while (k>=0 && tablero[h][k]==i){
			++contador;
			--k;
		}
		++res[contador];
		
		
		//miro la fila 
		contador=0;
		//primero hacia la izq
		k=h-1; 
		while (k>=0 && tablero[k].size()>tablero[h].size() && tablero[k][tablero[h].size()]==i){
			++contador;
			--k;
		}
		//miro la fila hacia la der
		k=h+1; 
		while (k<columns && tablero[k].size()>tablero[h].size() && tablero[k][tablero[h].size()]==i){
			++contador;
			++k;
		}
		if(contador>=c){++res[c-1];}else{++res[contador];} //si es de mas de c no me importa, es de largo c
		
		
		
		//miro diagonal de abajo izq a arriba der
		contador=0;
		//primero hacia abajo izq
		k=h-1; 
		int q=tablero[h].size()-1;
		while (k>=0 && q>=0 && tablero[k].size()>q && tablero[k][q]==i){
			++contador;
			--k;
			--q;
			
		}
		//ahora hacia arriba der
		k=h+1; 
		q=tablero[h].size()+1;
		while (k<columns && q<rows && tablero[k].size()>q && tablero[k][q]==i){
			++contador;
			++k;
			++q;			
		}
		if(contador>=c){++res[c-1];}else{++res[contador];}; //si es de mas de c no me importa, es de largo c
		
		
		
		
		
		
		//miro diagonal de abajo der a arriba izq
		contador=0;
		//primero hacia abajo der
		k=h+1; 
		q=tablero[h].size()-1;
		while (k<columns && q>=0 && tablero[k].size()>q && tablero[k][q]==i){
			++contador;
			++k;
			--q;
			
		}
		//ahora hacia arriba izq
		k=h-1; 
		q=tablero[h].size()+1;
		while (k>=0 && q<rows && tablero[k].size()>q && tablero[k][q]==i){
			++contador;
			--k;
			++q;			
		}
		if(contador>=c){++res[c-1];}else{++res[contador];} //si es de mas de c no me importa, es de largo c
		
	}	
			
	}
	
	return res;
		
}
//cuenta las fichas consecutivas  que son extensibles en algun turno y tambien las que se pueden extender 
//en ambos sentidos de cualquier tamaño entre 1 y c-1 que tiene el jugador i:
pair<vector<int>,vector<int> > ext(int rows, int columns, const vector<vector<int>>& tablero, int c, int i){
	vector<int> res(c,0); //cantidad de extensibles en algun turno. En el lugar i aparecen la cantidad que tienen i. Las que tienen 0 las desestimo, puede decir cualquier cosa ahi
	vector<int> res2(c,0); //los doble extensibles
	
	//miro en las columnas
	for(int h=0;h<columns;++h){
		int contador=0;
		int k=tablero[h].size()-1; 
		while (k>=0){
			if(tablero[h][k]==i){++contador;}else{break;}
			--k;
		}
		if(tablero[h].size()<columns){++res[contador];} //si es extensible
	}	
		
		
	//miro en las filas
	for(int h=0;h<rows;++h){
		bool extensible=false;
		int contador=0;
		int anterior=0;
		int k=columns-1; 
		while (k>=0){
			if(tablero[k].size()>h && tablero[k][h]==i){
				++contador;
			}else{
				if(extensible && anterior+contador>=c){++res[c-1];}else{++res[anterior+contador];} 
				if(tablero[k].size()>h){
					extensible=false;
					anterior=0;
				}
				if(tablero[k].size()<=h){
					if(extensible){++res2[contador];} //si es extensible por dos lados
					extensible=true;
					anterior=contador;
				}
				contador=0;
			}
			 --k;
		}
		if(extensible && anterior+contador>=c){++res[c-1];}else{++res[anterior+contador];}  //si es extensible
	}
	
	//miro en diagonal de arriba der a abajo izq
	
	//primero cuento las que estan debajo de la diagonal principal, incluyendo esta
	for(int h=rows-1;h>=0;--h){
		bool extensible=false;
		int contador=0;
		int anterior=0;
		int k=columns-1;		 
		while (k>=0 && h>=0){
			if(tablero[k].size()>h && tablero[k][h]==i){
				++contador;
			}else{
				if(extensible && anterior+contador>=c){++res[c-1];}else{++res[anterior+contador];} 
				
				if(tablero[k].size()>h){
					extensible=false;
					anterior=0;
				}
				if(tablero[k].size()<=h){
					if(extensible){++res2[contador];} //si es extensible por dos lados
					extensible=true;
					anterior=contador;
				}
				contador=0;
			}
			 --k;
			 --h;
		}
		if(extensible && anterior+contador>=c){++res[c-1];}else{++res[anterior+contador];}  //si es extensible

	}
	//ahora las que estan por encima de la diagonal principal
	for(int k=columns-2;k>=0;--k){
		bool extensible=false;
		int contador=0;
		int anterior=0;
		int h=rows-1;		 
		while (k>=0 && h>=0){
			if(tablero[k].size()>h && tablero[k][h]==i){
				++contador;
			}else{
				if(extensible && anterior+contador>=c){++res[c-1];}else{++res[anterior+contador];} 
				
				if(tablero[k].size()>h){
					extensible=false;
					anterior=0;
				}
				if(tablero[k].size()<=h){
					if(extensible){++res2[contador];} //si es extensible por dos lados
					extensible=true;
					anterior=contador;
				}
				contador=0;
			}
			 --k;
			 --h;
		}
		if(extensible && anterior+contador>=c){++res[c-1];}else{++res[anterior+contador];}  //si es extensible

	}
	
	
	
	
	//miro en diagonal de arriba izq a abajo der
	
	//primero cuento las que estan debajo de la diagonal principal, incluyendo esta
	for(int h=rows-1;h>=0;--h){
		bool extensible=false;
		int contador=0;
		int anterior=0;
		int k=0;		 
		while (k<columns && h>=0){
			if(tablero[k].size()>h && tablero[k][h]==i){
				++contador;
			}else{
				if(extensible && anterior+contador>=c){++res[c-1];}else{++res[anterior+contador];} 
				
				if(tablero[k].size()>h){
					extensible=false;
					anterior=0;
				}
				if(tablero[k].size()<=h){
					if(extensible){++res2[contador];} //si es extensible por dos lados
					extensible=true;
					anterior=contador;
				}
				contador=0;
			}
			 ++k;
			 --h;
		}
		if(extensible && anterior+contador>=c){++res[c-1];}else{++res[anterior+contador];}  //si es extensible

	}
	//ahora las que estan por encima de la diagonal principal
	for(int k=1;k<columns;++k){
		bool extensible=false;
		int contador=0;
		int anterior=0;
		int h=rows-1;		 
		while (k<columns && h>=0){
			if(tablero[k].size()>h && tablero[k][h]==i){
				++contador;
			}else{
				if(extensible && anterior+contador>=c){++res[c-1];}else{++res[anterior+contador];} 
				
				if(tablero[k].size()>h){
					extensible=false;
					anterior=0;
				}
				if(tablero[k].size()<=h){
					if(extensible){++res2[contador];} //si es extensible por dos lados
					extensible=true;
					anterior=contador;
				}
				contador=0;
			}
			 ++k;
			 --h;
		}
		if(extensible && anterior+contador>=c){++res[c-1];}else{++res[anterior+contador];}  //si es extensible

	}
	
	
	return make_pair(res,res2);
}




//--------------FUNCION DE PUNTAJE----------------------------

//funcion que dado un tablero le asigna un puntaje:
float puntaje(int rows, int columns, int c, int p, const vector<vector<int>>& tablero, int ultimajugada, parametro param){
	//el parametro de entrada consecutivos es un vector que tiene en la i coordenada el valor de las tiras de largo i+1. Consecutivos tiene c-1 elementos
	//idem para extensibles
	
	if( gane(tablero,c,ultimajugada)) {return INF;} //si gane da infinito CHECKEAR Q ESTE BIEN Y DE ESO POSTA
	
	//if( perdi(tablero,c,ultimajugada)) {return INFneg;} //si perdi da -infinito CHECKEAR Q ESTE BIEN Y DE ESO POSTA
	//NO TIENE SENTIDO, NUNCA VOY A TENER UN TABLERO EN EL QUE YA PERDI, SI ME TOCA JUGAR A MI
	
	
	
	//cuento los que estan en el borde, mias y de el.
	int enborde1=enborde(rows,columns,tablero,1);
	int enborde2=enborde(rows,columns,tablero,2);
	//cuento la cantidad de fichas que estan en una esquina, mias y de el.
	int enesquinas1=enesquinas(rows,columns,tablero,1);
	int enesquinas2=enesquinas(rows,columns,tablero,2);
	//cuento la cantidad de fichas en el centro 
	int encentro1=encentro(rows,columns,tablero,1);
	int encentro2=encentro(rows,columns,tablero,2);
	//cuento la cantidad de casillas libres alrededor de cada ficha mia
	int libres1=libres(rows,columns,tablero,1);
	int libres2=libres(rows,columns,tablero,2);
	//cantidad de fichas consecutivas
	vector<int> consecutivas1=consec(rows,columns,tablero,c,1);
	vector<int> consecutivas2=consec(rows, columns, tablero, c, 2);
	//cantidad de inmediatemente extensibles en la proxima jugada
	vector<int> extensiblesprox1=extprox(rows,columns,tablero,c,1);
	vector<int> extensiblesprox2=extprox(rows, columns, tablero, c, 2);
	//cantidad de  extensibles en cualquier momento 
	vector<int> extensibles1=ext(rows,columns,tablero,c,1).first;
	vector<int> extensibles2=ext(rows, columns, tablero, c, 2).first;
	//cantidad de  bi-extensibles en cualquier momento (Extensibles en ambos sentidos)
	vector<int> biextensibles1=ext(rows,columns,tablero,c,1).second;
	vector<int> biextensibles2=ext(rows, columns, tablero, c, 2).second;
	
	
	float subtotalA=0;
	for(int h=1;h<consecutivas1.size();++h){
		subtotalA= subtotalA + param.consecutivos[h-1]*(param.consecparam.first*consecutivas1[h]-param.consecparam.second*consecutivas2[h]);
		subtotalA= subtotalA + param.extensiblesprox[h-1]*(param.extproxparam.first*extensiblesprox1[h]-param.extproxparam.second*extensiblesprox2[h]);
		subtotalA= subtotalA + param.extensibles[h-1]*(param.extparam.first*extensibles1[h]-param.extparam.second*extensibles2[h]);
		subtotalA= subtotalA + param.biextensibles[h-1]*(param.biextparam.first*biextensibles1[h]-param.biextparam.second*biextensibles2[h]);
		//La idea es poner dos parametros que dan el peso de cada uno. Para los demas no lo hice xq no parecian
		//cosas tan relevantes y lo hace muy engorroso
	}

	
		
	float total=0;
	total= (enborde1*param.bordeparam.first-enborde2*param.bordeparam.second);
	total= total + (enesquinas1*param.esquinaparam.first-enesquinas2*param.esquinaparam.second);
	total= total + (encentro1*param.centroparam.first-encentro2*param.centroparam.second);
	total= total + (libres1*param.libertadparam.first-libres2*param.libertadparam.second);
	total= total + subtotalA;
	return total;
	
	
	
	
	//ideas de puntajes:
	
	//--------------HECHO--------------------
	//cantidad de fichas en los bordes HECHO
	//cantidad de fichas en las esquinas HECHO
	//cantidad de fichas en el centro HECHO
	//contar casillas libres alrededor de cada mia. HECHO
	//cantidad de fichas consecutivas, donde agregar una suma mucho mas. HECHO 
	//gano +inf y si pierdo es -inf HECHO
	//contar TODAS las extensibles, no solo las de la proxima jugada, para cada largo HECHO
	//cpntar las extensibles en AMBOS sentidos para cada largo HECHO
	
	
	//----------A HACER -----------
	
	//EN EXTENSIBLES (en general, no en el caso de inmediatamente extensibles que ese esta bien): 
	//NO CUENTO ACA SI CON UN MOVIMIENTO DOS DE 1 SE UNEN EN UNA DE 3, HACER ESTO
	//INCLUSO CREO QUE LA QUE CUENTA EXTENSIBLES ESTA MAL... BUSCAR OTRA FORMA...
	//soy chebar, creo que solucion esto, contando que dosd e 1 se unen en una de 3 para TODOS los extensibles
	//y también contando bien todo porque antes estaba medio mal. Lo hice agregando eso de anterior, CHECKEAR
	// (Esto lo hace la funcion ext)
	

	//Agregar las biextensibles en el proximo?
	
	//hacer parametros para cada jugada, o dividir en etapas y hacer parametros para cada etapa
	
	
	
	
	//-------LO HACEMOS DESPUES Y NO TAN UTIL COMO LO DE ARRIBA. IDEAS VIEJAS----------
	
	//eso de cant de fichas en el centro se puede definir mejor... podria contar varias centrales, y hasta cierta altura para ser mas fino, o contar por cada columna..
	//tratar de maximizar mi putntaje, o minimizar el de el, o maximizar la diferencia (me parece mejor la ultima pero puede ser otro parámetro y que decida entre las tres)
	//contar si hay lugares consecutivos (al menos dos, uno encima de otro) donde ambos extienden y de que largo
	
	
	}


//---------------FUNCION QUE DECIDE QUE JUGAR------------------------

//funcion del punto 2 que decide dado un tablero cual es la proxima jugada a realizar: (es greedy, mira toda las
//opciones y elije la que maximice el puntaje del tablero)

int parametrizable (int rows, int columns, int c, int p, vector<vector<int>>& tablero, int ultimajugada, parametro param ){
	//vamos a asignar un puntaje a cada tablero y de las ocho opciones posibles vamos a tomar la de major puntaje
	//esta sería la parte golosa. Los parámetros serían los puntajes que suman de diversos cosas
	
	vector<int> posibles;
	for(int h=0;h<columns;++h){
		if(tablero[h].size()<rows){ posibles.push_back(h);}
	}
	
	
	for(int a=0; a<posibles.size();++a){
		//si voy a ganar, lo hago.
		tablero[posibles[a]].push_back(1);
		if( gane(tablero,c,posibles[a]) ) {tablero[posibles[a]].pop_back(); return posibles[a];}
		tablero[posibles[a]].pop_back();
	}
	
		
	for(int a=0; a<posibles.size();++a){
		//si voy a perder, la salvo.
		tablero[posibles[a]].push_back(2);
		if( perdi(tablero,c,posibles[a]) ) {tablero[posibles[a]].pop_back(); return posibles[a];}
		tablero[posibles[a]].pop_back();
	}
	
	
	
	//si o si hay una jugada posibles pues sino seria empate
	tablero[posibles[0]].push_back(1);
	float maximopuntaje=puntaje(rows, columns, c, p, tablero, posibles[0], param);
	int maxpos=posibles[0];
	tablero[posibles[0]].pop_back();
	
	for(int q=1; q< posibles.size();++q){
		tablero[posibles[q]].push_back(1);
		float puntajeActual = puntaje(rows, columns, c, p, tablero, posibles[q],param);
		if(puntajeActual>maximopuntaje){
			maximopuntaje=puntajeActual;
			maxpos= posibles[q];
			}
		tablero[posibles[q]].pop_back();		
	}
	
	return maxpos;
}


//-------------------------JUEZ NUESTRO-----------------

//decide de dos jugadors que usan los parametros p1 y p2 quien gana o si es empate. devuelve 0 si empate, 1 si 
//gana el de p1 y 2 si gana el de  p2. Ambos jugadores utilizan la funcion parametrizable para jugar
int juez (int rows, int columns, int c, int p, int primero, parametro p1, parametro p2){

	vector<vector<int>> tablero (columns);//la primer cordenada del tablero es la columna, y la segunda es la fila
	p=2*p; //cuento fichas totales
	int LeTocaA=primero;
	int ultimajugada=-1;
	
	while (true) {
		if(gane(tablero, c, ultimajugada)) {return 1;} //gano el 1
		if(perdi(tablero, c, ultimajugada)) {return 2;} //perdio el 1, gano el 2
		if(p==0){return 0;} //empate no hay mas fichas
		bool lleno=true;
		int h=0;
		while( h<columns && lleno){
			if(tablero[h].size()<rows){ lleno=false;}
			++h;
		}
		if (lleno) {return 0;} //empate se lleno el tablero y no gano nadie
		
		
		parametro param;
		int move;
		if(LeTocaA==1){ 
			move = parametrizable(rows, columns, c, p, tablero, ultimajugada, p1);
			tablero[move].push_back(LeTocaA); //juega quien corresponda
			LeTocaA=2;
		}else{
			move = parametrizable(rows, columns, c, p, tablero, ultimajugada, p2);
			tablero[move].push_back(LeTocaA); //juega quien corresponda
			LeTocaA=1;
		}
		--p;
		ultimajugada=move;
	}
}


//funcion que da un float random en el intervalo cerrado [min,max]
float float_rand( float min, float max ){
    float scale = (float)rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}	
	
//función que sortea un parametro random
parametro paramrandom(int c){
	parametro param;
	float min=-1;
	float max=1;
	//los parametros que determinan el peso de mi jugada respecto a la del rival van entre -1 y 1
	param.esquinaparam.first = float_rand(min,max);
	param.esquinaparam.second = float_rand(min,max);
	param.bordeparam.first = float_rand(min,max);
	param.bordeparam.second = float_rand(min,max);
	param.libertadparam.first = float_rand(min,max);
	param.libertadparam.second = float_rand(min,max);
	param.consecparam.first = float_rand(min,max);
	param.consecparam.second = float_rand(min,max);
	param.centroparam.first = float_rand(min,max);
	param.centroparam.second = float_rand(min,max);
	param.extproxparam.first = float_rand(min,max);
	param.extproxparam.second = float_rand(min,max);
	param.extparam.first = float_rand(min,max);
	param.extparam.second = float_rand(min,max);
	param.biextparam.first = float_rand(min,max);
	param.biextparam.second = float_rand(min,max);
	
	//los parametros que determinan el puntaje otorgado a cada linea de determinada longitud de cierta 
	//caracteristica va entre -1 y 1.
	vector<float> vacio;
	param.consecutivos=vacio;
	param.extensibles=vacio;
	param.extensiblesprox=vacio;
	param.biextensibles=vacio;
	for(int k=0;k<c-1;++k){
		param.extensiblesprox.push_back(float_rand(min,max));
		param.extensibles.push_back(float_rand(min,max));
		param.biextensibles.push_back(float_rand(min,max));
		param.consecutivos.push_back(float_rand(min,max));
	}
	return param;
}
	

//----------------- ALGORITMO GENETICO------------------------

//FITNESS1
	//idea: ver cantidad de partidos no perdidos sobre total jugados juega contra 
	//todos los de su generacion.
	//ES BASTANTE MALA, SE PODRIA MEJORAR, QUE JUEGUE CONTRA OTROS TAMBIEN, EXTERNOS
float fitness1(parametro param, vector<parametro> poblacion, int rows,int  columns, int c,int  p){
	float noperdio=0;
	for(int i=0;i<poblacion.size();++i){
		if(juez(rows,columns,c,p, 1, param,poblacion[i]) !=2) {++noperdio;}
		if(juez(rows,columns,c,p, 2, param, poblacion[i]) !=2) {++noperdio;}
	}
	float x= 2*poblacion.size();
	float resultado=noperdio/x;
	return resultado;	
}
	
	
//FITNESS2
	//idea: ver cantidad de partidos no perdidos sobre total jugados del peor de la generacion, da poblacion pareja
	// ESTARIA BUENO ALGO QUE SEA MAS EXTERNO A LA GENERACION NUESTRA PER SE, que  mida cuan buena es PUERTAS AFUERA
	// o tambien ver partidos ganados sobre total jugados, como podria ser jugar contra mejores de viejas generaciones	
float fitness2(parametro param, vector<parametro> poblacion, int rows, int  columns, int c, int  p, int k){
	//k es el valor del bonus si es segundo (pues ganar o empatar siendo segundo vale mas que siendo primero)
	float puntaje=0;
	int pierde=0;
	int empata=5;
	int gana=10;
	for(int i=0;i<poblacion.size();++i){
		//empate siendo primero
		if(juez(rows,columns,c,p, 1, param, poblacion[i])==0) puntaje+=empata;
		//empate siendo segundo
		if(juez(rows,columns,c,p, 2, param, poblacion[i])==0) puntaje+=empata+k;
		//gano siendo primero
		if(juez(rows,columns,c,p, 1, param, poblacion[i])==1) puntaje+=gana;
		//gano siendo segundo
		if(juez(rows,columns,c,p, 2, param, poblacion[i])==1) puntaje+=gana+2*k;
		//pierdo siendo primero
		if(juez(rows,columns,c,p, 1, param, poblacion[i])==2) puntaje+=pierde;
		//pierdo siendo segundo
		if(juez(rows,columns,c,p, 2, param, poblacion[i])==2) puntaje+=pierde+k/2;

	}
	
	float x=(2*poblacion.size());
	float resultado = puntaje/x;
	return resultado;	
}
	

//estos primero dos nums se cambian (el ganar y perder) si leTocaA 2
//el primer int es 1 si ya gano el jug 1, 2 si ya perdio el jug 1, 0 si ya empato, 3 si no sabe como termina
//el segundo int es en que columna juega. Solo me importa en la primera llamada igual, no las recursivas
//profundidad es que tan a futuro estoy viendo, nunca quiero ver mas de 4 a futuro
//llega a ver si alguno puede ganar poniendo 2 fichas
pair<int,int> backtracking(int rows, int columns, int c, int p, vector<vector<int>>& tablero, int LeTocaA, int ultimajugada, int profundidad) {

	int NoLeToca;
	if (LeTocaA==1) {NoLeToca=2;} else {NoLeToca=1;}


	if (perdi(tablero, c, ultimajugada)) {return make_pair(2,0);}//si ya termino el partido da lo mismo que juego
	if (gane(tablero, c, ultimajugada)) {return make_pair(1,0);}//si ya termino el partido da lo mismo que juego
	//en estos casos devuelvo el numero del jugador que gano


	if(p==0){return make_pair(0,0);} //empate no hay mas fichas
	bool lleno=true;
	int h=0;
	while( h<columns && lleno){
		if(tablero[h].size()<rows){ lleno=false;}
		++h;
	}
	if (lleno) {return make_pair(0,0);} //empate se lleno el tablero y no gano nadie, me da lo mismo que juego


	if (profundidad>4) {return make_pair(3, rand() % columns);}



	bool elOtroGana = false;
	vector <int> todosLosQueMeGana;
	bool puedoEmpatar = false;
	int comoEmpatar = 0;

	vector<int> posibles;
	for (int m=0; m<columns; ++m){
		posibles.push_back(m);
	}
	random_shuffle(posibles.begin(), posibles.end()); //para que no resulte que se prueban mas los partidos en los
	//que el backtracking juega mas a la izquierda

	int m=0;
	while (m<columns) {//me estoy fijando que pasa si yo juego m en este turno
		
		tablero[posibles[m]].push_back(LeTocaA);
		pair<int, int> siJuegoM;
		siJuegoM = backtracking(rows, columns, c, p, tablero, NoLeToca, posibles[m], profundidad+1);
		tablero[posibles[m]].pop_back();

		if (siJuegoM.first==LeTocaA) {return make_pair(LeTocaA,posibles[m]);}
		if (siJuegoM.first==0) {puedoEmpatar=true; comoEmpatar=posibles[m];}
		if (siJuegoM.first==NoLeToca) {elOtroGana=true; todosLosQueMeGana.push_back(posibles[m]);}

		++m;
	}

	if (puedoEmpatar) {return make_pair(0,comoEmpatar);}

	if (elOtroGana) {

		vector<bool> dondeNoPierdo (columns, true); //va a tener un true si puedo jugar ahi sin perder
		for (int n=0; n<todosLosQueMeGana.size(); ++n){
			dondeNoPierdo[todosLosQueMeGana[n]] = false; //en los lugares que me gana se que no quiero jugar
		}

		vector<int> dondePuedoJugar;
		for (int n=0; n<dondeNoPierdo.size(); ++n) {
			if (dondeNoPierdo[n]==true) {dondePuedoJugar.push_back(n);}
		}

		if (dondePuedoJugar.size()>0) {
			int donde = rand() % dondePuedoJugar.size();
			return make_pair(3, dondePuedoJugar[donde]);
		}
	}



	return make_pair(3, rand() % columns);

}



//devuelve 0,1,2 segun quien gano
int juezBacktrack (int rows, int columns, int c, int p, parametro param, int empieza){
	
	int rta = 0;

	vector<vector<int>> tablero (columns);//la primer cordenada del tablero es la columna, y la segunda es la fila
	p=2*p; //cuento fichas totales
	int ultimajugada=-1;
	int LeTocaA = empieza;

	while (true) {
		if(gane(tablero, c, ultimajugada)) {return 1;} //gano el 1
		if(perdi(tablero, c, ultimajugada)) {return 2;} //perdio el 1, gano el 2
		if(p==0){return 0;} //empate no hay mas fichas
		bool lleno=true;
		int h=0;
		while( h<columns && lleno){
			if(tablero[h].size()<rows){ lleno=false;}
			++h;
		}
		if (lleno) {return 0;} //empate se lleno el tablero y no gano nadie
		

		int move;
		if(LeTocaA==1){ 
			move = parametrizable(rows, columns, c, p, tablero, ultimajugada, param);
			tablero[move].push_back(LeTocaA); //juega quien corresponda
			LeTocaA=2;
		}else{
			pair<int,int> rta = backtracking(rows, columns, c, p, tablero, 2, ultimajugada, 1);
			move = rta.second;
			tablero[move].push_back(LeTocaA); //juega quien corresponda
			LeTocaA=1;
		}
		--p;
		ultimajugada=move;
	}
}


float fitnessBacktrack(parametro param, int tamanoPoblacion, int rows, int  columns, int c, int  p, int k){
	//k es el valor del bonus si es segundo (pues ganar o empatar siendo segundo vale mas que siendo primero)
	float puntaje=0;
	int pierde=0;
	int empata=5;
	int gana=10;
	for(int i=0;i<25;++i){
		int resultEmpezandoParam = juezBacktrack(rows,columns,c,p,param,1);
		int resultEmpezandoBacktrack = juezBacktrack(rows,columns,c,p,param,2);
		//empate siendo primero
		if(resultEmpezandoParam==0) puntaje+=empata;
		//empate siendo segundo
		if(resultEmpezandoBacktrack==0) puntaje+=empata+k;
		//gano siendo primero
		if(resultEmpezandoParam==1) puntaje+=gana;
		//gano siendo segundo
		if(resultEmpezandoBacktrack==1) puntaje+=gana+2*k;
		//pierdo siendo primero
		if(resultEmpezandoParam==2) puntaje+=pierde;
		//pierdo siendo segundo
		if(resultEmpezandoBacktrack==2) puntaje+=pierde+k/2;

	}
	
	float x=(2*tamanoPoblacion);
	float resultado = puntaje/x;
	return resultado;	
}
	
	
//MUTACION
	//idea: simple, tener un porcentaje fijo y en cada variable tira random si se da el porcentaje de mutacion


	
//param es el paremtro a mutar, rate indica la proba de mutar, min y max son los rangos en que estan los puntajes
//de todas las cosas.
void mutacion(parametro& param, float rate, float min, float max){
	
	// PARA QE NO SEA MUY CAOTICA LA EVOLUCION ES OTRA OPCION QUE EN VEZ DE QUE MUTE A UN RANDOM CUALQUIER
	//QUE MUTE A ALGO COMO nuevo=viejo+(float_rand(min,max)*mutSize) DONDE mutSize ES ALGO COMO EL MUTATION RATE,
	// UN PARAMETRO DEL GENETICO Y QU SEA UN VALOR COMO 0.05 0.1 0.2 IDEA PARA EXPERIMENTAR.

	//muto aleatoriamente los parametros que son solo numeros
	if(float_rand(0,1)<rate){param.esquinaparam.first = float_rand(min,max);}
	if(float_rand(0,1)<rate){param.esquinaparam.second = float_rand(min,max);}
	if(float_rand(0,1)<rate){param.bordeparam.first = float_rand(min,max);}
	if(float_rand(0,1)<rate){param.bordeparam.second = float_rand(min,max);}
	if(float_rand(0,1)<rate){param.libertadparam.first = float_rand(min,max);}
	if(float_rand(0,1)<rate){param.libertadparam.second = float_rand(min,max);}
	if(float_rand(0,1)<rate){param.consecparam.first = float_rand(min,max);}
	if(float_rand(0,1)<rate){param.consecparam.second = float_rand(min,max);}
	if(float_rand(0,1)<rate){param.centroparam.first = float_rand(min,max);}
	if(float_rand(0,1)<rate){param.centroparam.second = float_rand(min,max);}
	if(float_rand(0,1)<rate){param.extproxparam.first = float_rand(min,max);}
	if(float_rand(0,1)<rate){param.extproxparam.second = float_rand(min,max);}
	if(float_rand(0,1)<rate){param.extparam.first = float_rand(min,max);}
	if(float_rand(0,1)<rate){param.extparam.second = float_rand(min,max);}
	if(float_rand(0,1)<rate){param.biextparam.first = float_rand(min,max);}
	if(float_rand(0,1)<rate){param.biextparam.second = float_rand(min,max);}
	//muto aleatoriamente los vectores
	for(int k=0;k<param.extensibles.size();++k){
		if(float_rand(0,1)<rate){param.extensiblesprox[k]=(float_rand(min,max));}
		if(float_rand(0,1)<rate){param.extensibles[k]=(float_rand(min,max));}
		if(float_rand(0,1)<rate){param.biextensibles[k]=(float_rand(min,max));}
		if(float_rand(0,1)<rate){param.consecutivos[k]=(float_rand(min,max));}
	}
	
}


//CROSSOVER
	//idea: simple, tener un porcentaje fijo que dice si hay crossover y cambia y lo ejecuto cada vez en cada 
	//cosa, puede pasar varias veces en un mismo cruzamiento o ninguna. Los vectores y los pares de parametros
	//son caracteristicas que van juntas. O sea, los pairs y vectors, se copian entero de alguno de los dos siempre.
	// es como si fueran un solo gen que lo agarras o del padre o de la madre
parametro crossover(parametro p1, parametro p2, float rate, float min, float max){
	
	parametro param;
	//empiezo con p1 y si corresponde cambio
	parametro copiode=p1;
	if(float_rand(0,1)<rate){ if(copiode==p1){copiode=p2;}else{copiode=p1;}}
		param.esquinaparam.first = copiode.esquinaparam.first;
		param.esquinaparam.second = copiode.esquinaparam.second;
	if(float_rand(0,1)<rate){ if(copiode==p1){copiode=p2;}else{copiode=p1;}}
		param.bordeparam.first = copiode.bordeparam.first;
		param.bordeparam.second = copiode.bordeparam.second;
	if(float_rand(0,1)<rate){ if(copiode==p1){copiode=p2;}else{copiode=p1;}}
		param.libertadparam.first = copiode.libertadparam.first;
		param.libertadparam.second = copiode.libertadparam.second;
	if(float_rand(0,1)<rate){ if(copiode==p1){copiode=p2;}else{copiode=p1;}}
		param.consecparam.first = copiode.consecparam.first;
		param.consecparam.second = copiode.consecparam.second;
	if(float_rand(0,1)<rate){ if(copiode==p1){copiode=p2;}else{copiode=p1;}}
		param.centroparam.first = copiode.centroparam.first;
		param.centroparam.second = copiode.centroparam.second;
	if(float_rand(0,1)<rate){ if(copiode==p1){copiode=p2;}else{copiode=p1;}}
		param.extproxparam.first = copiode.extproxparam.first;
		param.extproxparam.second = copiode.extproxparam.second;
	if(float_rand(0,1)<rate){ if(copiode==p1){copiode=p2;}else{copiode=p1;}}
		param.extparam.first = copiode.extparam.first;
		param.extparam.second = copiode.extparam.second;
	if(float_rand(0,1)<rate){ if(copiode==p1){copiode=p2;}else{copiode=p1;}}
		param.biextparam.first = copiode.biextparam.first;
		param.biextparam.second = copiode.biextparam.second;

	//CHE QUIZAS ESTARIA BUENO QUE PUEDACOPIAR PARTE DE UN VECTOR DE UN PADREY PARTE DEL OTRO NO?
	//SE HARIA ASI PONELE. OTRA IDEA PARA EXPERIMENTAR
		/*
		//muto aleatoriamente los vectores
	for(int k=0;k<p1.extensibles.size();++k){
		if(float_rand(0,1)<rate){ if(copiode==p1){copiode=p2;}else{copiode=p1;}}
		param.extensiblesprox.push_back(copiode.extensiblesprox[k]);
	}
*/
	//muto aleatoriamente los vectores
	for(int k=0;k<p1.extensibles.size();++k){
		if(float_rand(0,1)<rate){ if(copiode==p1){copiode=p2;}else{copiode=p1;}}
	
		param.extensiblesprox.push_back(copiode.extensiblesprox[k]);
	}
	
	for(int k=0;k<p1.extensibles.size();++k){
		if(float_rand(0,1)<rate){ if(copiode==p1){copiode=p2;}else{copiode=p1;}}
	
		param.extensibles.push_back(copiode.extensibles[k]);
	}
		
	for(int k=0;k<p1.extensibles.size();++k){
		if(float_rand(0,1)<rate){ if(copiode==p1){copiode=p2;}else{copiode=p1;}}
	
		param.biextensibles.push_back(copiode.biextensibles[k]);
	}
	
	for(int k=0;k<p1.extensibles.size();++k){
		if(float_rand(0,1)<rate){ if(copiode==p1){copiode=p2;}else{copiode=p1;}}
	
		param.consecutivos.push_back(copiode.consecutivos[k]);
	}
	
	return param;
}


//SELECCION1
	//idea: quedarse con la mitad de los de mejor fitness.Luego los cruzo agarrando aleatoriamente dos de ellos
	// hasta que tenga una poblacion del mismo tamaño que antes.
	// Conservar siempre al mejor individuo copiado tal cual
	//POSIBLE MODIFICACION, TOMAR ALEATORIOS DONDE CUANTO MAS ARRIBA ESTAS MAS CHANCES TENES. ES FACIL DE HACER.
	
	//NOTA: RECORDAR QUE USA FITNESS1 POR COMO ESTA POR AHORA
vector<parametro> seleccion1(vector<parametro> poblacion, float pcrossover, float min, float max, int rows, int columns, int c, int p){
	
	//ofstream myfile;
	//myfile.open ("3b1seleccion1crossoverB0.4.csv", std::ios_base::app);
	vector<parametro> poblacionnueva;
	
	int k=2;//PARA FITNESS2 EXPERIMENTAR
	vector<float> fitnessValues;
	for (int i=0;i<poblacion.size();++i){
		///fitnessValues.push_back(fitness1(poblacion[i], poblacion, rows, columns, c, p));
		fitnessValues.push_back(fitness2(poblacion[i], poblacion, rows, columns, c, p, k));
	}

	float maximo=fitnessValues[0];
	int maxpos=0;
	for(int i=1;i<poblacion.size();++i){
		
		if(fitnessValues[i]>maximo){
			maximo= fitnessValues[i];
			maxpos=i;
		}
	}
	poblacionnueva.push_back(poblacion[maxpos]); //elitismo, siempre dejo al mejor
	
	//ordeno ascendente por fitness

	for (int j=poblacion.size()-1;j>=0;--j){
		//esto de aca me da el maximo de lo que queda, siempre lo pongo ultimo;
		maximo= fitnessValues[0];
		maxpos=0;
		for(int i=1;i<j;++i){
			if(fitnessValues[i]>maximo){
				maximo= fitnessValues[i];
				maxpos=i;
			}
		}
		swap(fitnessValues[maxpos],fitnessValues[j]);
		swap(poblacion[maxpos],poblacion[j]);
	}


	
	
	//myfile << fitnessValues[fitnessValues.size()-1] << ",";	
	
	//myfile << fitnessValues[0] << ",";	
	
	float suma=fitnessValues[0];
	for(int i=1;i<poblacion.size();++i){
			suma=suma+fitnessValues[i];
	}
	//myfile << suma/poblacion.size() << ",";
	
	//myfile << fitnessValues[poblacion.size()/2] << ",";	
	//myfile.close();

	while (poblacionnueva.size()<poblacion.size()){
		int x, y;
		x= rand() % (poblacion.size()-poblacion.size()/2) + poblacion.size()/2;
		y= rand() % (poblacion.size()-poblacion.size()/2) + poblacion.size()/2;
		//PUEDO VARIAR QUE SEAN LA MITAD, PUEDO ELEGIR X E Y DE ALGUN OTRO PORCENTAJE DE MEJORES
		poblacionnueva.push_back(crossover(poblacion[x],poblacion[y], pcrossover, min, max) );		
	}
	
	return poblacionnueva;
}



//SELECCION2
	//idea: agarrar varios al azar y elegir el mejor y cruzarlo con otro elegido de la misma forma. Repetir asi
	//hasta tener todos los que queremos.  Hago como minitorneos y asi elijo a cada padre.
	//Conservar siempre al mejor individuo copiado tal cual
	
	
	//NOTA: RECORDAR QUE USA FITNESS1 POR COMO ESTA POR AHORA
pair<vector<parametro>,parametro> seleccion2(vector<parametro> poblacion, float pcrossover, float min, float max, int rows, int columns, int c, int p){
	
	
	ofstream myfile;
	myfile.open ("geneticoBacktrack.csv", std::ios_base::app);
	vector<parametro> poblacionnueva;
	int k=2;//PARA FITNESS2 EXPERIMENTAR
	
	vector<float> fitnessValues;
	for (int i=0;i<poblacion.size();++i){
		//fitnessValues.push_back(fitness1(poblacion[i], poblacion, rows, columns, c, p));
		fitnessValues.push_back(fitnessBacktrack(poblacion[i], poblacion.size(), rows, columns, c, p, k));
	}

	
	ofstream todosFitness;
	todosFitness.open("geneticoBacktrackTodosFitness.csv", std::ios_base::app);
	for (int i=0;i<poblacion.size();++i){
		todosFitness<<","<<fitnessValues[i];
	}	
	todosFitness<<endl;	
	todosFitness.close();


	float maximo=fitnessValues[0];
	int maxpos=0;
	for(int i=1;i<poblacion.size();++i){
		if(fitnessValues[i]>maximo){
			maximo= fitnessValues[i];
			maxpos=i;
		}
	}
	poblacionnueva.push_back(poblacion[maxpos]); //elitismo, siempre dejo al mejor
	parametro mejorJugador = poblacion[maxpos];
	
	myfile << fitnessValues[maxpos] << ",";	
	
	float minimo=fitnessValues[0];
	int minpos=0;
	for(int i=1;i<poblacion.size();++i){
		if(fitnessValues[i]<minimo){
			minimo= fitnessValues[i];
			minpos=i;
		}
	}
	
	myfile << fitnessValues[minpos] << ",";	
	
	
	float suma=fitnessValues[0];
	for(int i=1;i<poblacion.size();++i){
			suma=suma+fitnessValues[i];
	}
	myfile << suma/poblacion.size() << ",";
	
	
	int posicion;
	for(int i=0;i<poblacion.size();++i){
		int contador=0;
		for(int j=0;j<poblacion.size();++j){
			if(fitnessValues[j]<=fitnessValues[i]) {++contador;}
		}
		if(contador>=poblacion.size()/2){posicion=i;}
	}
	myfile << fitnessValues[posicion] << ",";
	
	myfile.close();
	
	
	
	
	
	int tamano=poblacion.size()*2/10; //indica cantidad de los jugadores que elijo
	
	while (poblacionnueva.size()<poblacion.size()){
		
		vector<parametro> padres;
		for(int h=0;h<2;++h){
			
			vector<int> random;
			for(int q=0;q<tamano;++q){
				int x= rand() % (poblacion.size());
				random.push_back(x);
			}

			//HAY OTRA FORMA DE HACERLO QU ES HACERQUE SOLO COMPITAN ETRE
			//ELLOS DIEZ Y SEDEJA AL MEJOR, NO SE QUE OPCION SERA MEJOR. QUE COMPITAN ENTRE ELLOS 10 DA MENOS INFO
			//PERO JUSTMNTE LES DA MAS OPORTUNIDAD DE COSAS RARAS. SERIA CON ESTO COMENADO

		//	vector<float> fitnessValuesChico;
		//	for (int i=0;i<random.size();++i){
		//		fitnessValues.push_back(fitness1(random[i], random, rows, columns, c, p));
		//	}

			float maximo=fitnessValues[random[0]];
			int maxpos=0;
			for(int i=1;i<random.size();++i){
				if(fitnessValues[random[i]]>maximo){
					maximo= fitnessValues[random[i]];
					maxpos=i;
			}
			padres.push_back(poblacion[random[maxpos]]);
			}
		}
		//PUEDO VARIAR QUE SEAN LA MITAD, PUEDO ELEGIR X E Y DE ALGUN OTRO PORCENTAJE DE MEJORES
		poblacionnueva.push_back(crossover(padres[0],padres[1], pcrossover, min, max) );		
	}
	
	return make_pair(poblacionnueva, mejorJugador);
	
}



int escribirParametro(int c, parametro param){
	
	ofstream valores;
	valores.open ("jugadorGeneticoBacktrack.txt", std::ofstream::out | std::ofstream::trunc);
	
	valores << param.esquinaparam.first << "\n";
	valores << param.esquinaparam.second << "\n";
	valores << param.bordeparam.first  << "\n";
	valores << param.bordeparam.second  << "\n";
	valores << param.libertadparam.first << "\n";
	valores << param.libertadparam.second << "\n";
	valores << param.consecparam.first << "\n";
	valores << param.consecparam.second << "\n";
	valores << param.centroparam.first << "\n";
	valores << param.centroparam.second << "\n";
	valores << param.extproxparam.first << "\n";
	valores << param.extproxparam.second << "\n";
	valores << param.extparam.first  << "\n";
	valores << param.extparam.second  << "\n";
	valores << param.biextparam.first << "\n";
	valores << param.biextparam.second  << "\n";
	

	int k=0;
	for(k=0;k<c-1;++k){
		valores << param.extensiblesprox[k] << "\n";
		valores << param.extensibles[k] << "\n";
		valores << param.biextensibles[k] << "\n";
		valores << param.consecutivos[k] << "\n";
	}

	valores.close();


	return 0;
}


parametro leerParametroDeValores(int c, string a){

	parametro param;

	ifstream valores;
	valores.open (a);
	

	valores >> param.esquinaparam.first;
	valores >> param.esquinaparam.second;
	valores >> param.bordeparam.first;
	valores >> param.bordeparam.second;
	valores >> param.libertadparam.first;
	valores >> param.libertadparam.second;
	valores >> param.consecparam.first;
	valores >> param.consecparam.second;
	valores >> param.centroparam.first;
	valores >> param.centroparam.second;
	valores >> param.extproxparam.first;
	valores >> param.extproxparam.second;
	valores >> param.extparam.first;
	valores >> param.extparam.second;
	valores >> param.biextparam.first;
	valores >> param.biextparam.second ;
	
	//los parametros que determinan el puntaje otorgado a cada linea de determinada longitud de cierta 
	//caracteristica va entre -1 y 1.
	vector<float> vacio;
	param.consecutivos=vacio;
	param.extensibles=vacio;
	param.extensiblesprox=vacio;
	param.biextensibles=vacio;
	for(int k=0;k<c-1;++k){
		float n;
		valores >> n;
		param.extensiblesprox.push_back(n);
		valores >> n;
		param.extensibles.push_back(n);
		valores >> n;
		param.biextensibles.push_back(n);
		valores >> n;
		param.consecutivos.push_back(n);
	}


	return param;
}



//EL AGORITMO GENETICO PER SE
parametro genetico(int rows, int columns, int c, int p){
	
	ofstream myfile;
	myfile.open ("geneticoBacktrack.csv", std::ios_base::app);
	myfile<<"generacion,maxFitness,minFitness,fitnessPromedio,mediaDelFitness," << endl;
	myfile.close();
	//determino parametros que luego podemos modificar segun gustemos
	int tamanopoblacion=50;
	float min=-1;
	float max=1;
	float pmutar=0.005;
	float pcrossover=0.4;
	int totalgeneraciones=100;
	int k=2; //PARA FITNESS2 EXPERIMENTAR
	
		
	int generacion=1;
	
	vector<parametro> poblacion;

	for(int i=1;i<=tamanopoblacion;++i){
		poblacion.push_back(paramrandom(c));
	}
	
	ofstream todosFitness;
	todosFitness.open("geneticoBacktrackTodosFitness.csv", std::ios_base::app);
	todosFitness<<"generacion";
	for (int i=0;i<poblacion.size();++i){
		todosFitness<<","<<"valor"<<i;
	}
	todosFitness<<endl;	
	todosFitness.close();

	while(generacion<totalgeneraciones){
		//puse esta como basica pero se puede poner una condicion de corte mucho mejor
		//podria ser por ejemplo que el mejor de la poblacion no mejora durante tantas veces
		for(int i=1;i<poblacion.size();++i){
			mutacion(poblacion[i],pmutar, min, max);
		}

		myfile.open ("geneticoBacktrack.csv", std::ios_base::app);
		myfile << generacion << ",";
		myfile.close();		  
			
		todosFitness.open("geneticoBacktrackTodosFitness.csv", std::ios_base::app);
		todosFitness<<generacion<<",";	
		todosFitness.close();

		//SELECCIONAMOS Y ACTUALIZAMOS POBLACION CON CROSSOVER DE POR MEDIO
		pair<vector<parametro>, parametro> seleccionados = seleccion2(poblacion,pcrossover,min,max, rows, columns, c, p);
		poblacion = seleccionados.first;
		parametro mejorJugador = seleccionados.second;
		myfile.open ("geneticoBacktrack.csv", std::ios_base::app);
		myfile << "\n";
		myfile.close();	
		

		escribirParametro(c,mejorJugador);

		++generacion;
		cerr<<generacion<<endl;
		
	}
	
	
	
	myfile.open ("geneticoBacktrack.csv", std::ios_base::app);
	myfile << generacion << ",";
	vector<float> fitnessValues;
	for (int i=0;i<poblacion.size();++i){
		///fitnessValues.push_back(fitness1(poblacion[i], poblacion, rows, columns, c, p));
		fitnessValues.push_back(fitness2(poblacion[i], poblacion, rows, columns, c, p, k));
	}

	todosFitness.open("geneticoBacktrackTodosFitness.csv", std::ios_base::app);
	todosFitness<<generacion;	
	for (int i=0;i<poblacion.size();++i){
		todosFitness<<","<<fitnessValues[i];
	}
	todosFitness<<endl;	
	todosFitness.close();

	float maximo=fitnessValues[0];
	int maxpos=0;
	for(int i=1;i<poblacion.size();++i){
		if(fitnessValues[i]>maximo){
			maximo= fitnessValues[i];
			maxpos=i;
		}
	}
	
	myfile << fitnessValues[maxpos] << ",";	
	
	float minimo=fitnessValues[0];
	int minpos=0;
	for(int i=1;i<poblacion.size();++i){
		if(fitnessValues[i]<minimo){
			minimo= fitnessValues[i];
			minpos=i;
		}
	}
	
	myfile << fitnessValues[minpos] << ",";	
	
	
	float suma=fitnessValues[0];
	for(int i=1;i<poblacion.size();++i){
			suma=suma+fitnessValues[i];
	}
	myfile << suma/poblacion.size() << ",";
	
	
	int posicion;
	for(int i=0;i<poblacion.size();++i){
		int contador=0;
		for(int j=0;j<poblacion.size();++j){
			if(fitnessValues[j]<=fitnessValues[i]) {++contador;}
		}
		if(contador>=poblacion.size()/2){posicion=i;}
	}
	myfile << fitnessValues[posicion] << ",";
	
	myfile.close();
	
	
	
	return poblacion[maxpos];

}


//--------------------MAIN-------------------
//Este es un main trucho para que me de el resultado del genetico
int main(){
	srand((unsigned int)time(NULL));

	parametro param=genetico(6,7,4,50);

	escribirParametro(4,param);
}	
