#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <sys/stat.h>
#include <cmath>


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
	if (tablero[0].size()!=0 && tablero[0][0]==i) {--enesquina;} //la esquina inf izq
	if (tablero[columns-1].size()!=0 && tablero[columns-1][0]==i) {--enesquina;} //la esquina inf der
	if (tablero[0].size()==rows && tablero[0][rows-1]==i) {--enesquina;} //la esquina sup izq
	if (tablero[columns-1].size()==rows && tablero[columns-1][rows-1]==i) {--enesquina;} //la esquina sup der
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
		//si voy a perder, la salvo.
		tablero[posibles[a]].push_back(2);
		if( perdi(tablero,c,ultimajugada) ) {tablero[posibles[a]].pop_back(); return posibles[a];}
		tablero[posibles[a]].pop_back();
	}
	
	//si o si hay una jugada posibles pues sino seria empate
	tablero[posibles[0]].push_back(1);
	float maximopuntaje=puntaje(rows, columns, c, p, tablero, posibles[0], param);
	int maxpos=posibles[0];
	tablero[posibles[0]].pop_back();
	
	for(int q=1; q< posibles.size();++q){
		tablero[posibles[q]].push_back(1);
		if(puntaje(rows, columns, c, p, tablero, posibles[q],param)>maximopuntaje){
			maximopuntaje=puntaje(rows, columns, c, p, tablero, posibles[q],param);
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



//----------------- ALGORITMO GENETICO------------------------

//FITNESS1
	//idea: ver cantidad de partidos no perdidos sobre total jugados del mejor de la generacion. juega contra 
	//todos los de su generacion. Podria jugar contra los mejores de generaciones pasadas sino.
	
	
	
//FITNESS2
	//idea: ver cantidad de partidos no perdidos sobre total jugados del peor de la generacion, da poblacion pareja
	// ESTARIA BUENO ALGO QUE SEA MAS EXTERNO A LA GENERACION NUESTRA PER SE, que  mida cuan buena es PUERTAS AFUERA
	// o tambien ver partidos ganados sobre total jugados, como podria ser jugar contra mejores de viejas generaciones	
	
	
	
//MUTACION
	//idea: simple, tener un porcentaje fijo y en cada variable tira random si se da el porcentaje de mutacion

//funcion que da un float random en el intervalo cerrado [min,max]
float float_rand( float min, float max ){
    float scale = (float)rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}	
	
//param es el paremtro a mutar, rate indica la proba de mutar, min y max son los rangos en que estan los puntajes
//de todas las cosas.
void mutacion(parametro param, float rate, float min, float max){
	
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
	//muto aleatoriamente los vectores
	if(float_rand(0,1)<rate){ if(copiode==p1){copiode=p2;}else{copiode=p1;}}
	for(int k=0;k<p1.extensibles.size();++k){
		param.extensiblesprox[k]=copiode.extensiblesprox[k];
	}
	
	if(float_rand(0,1)<rate){ if(copiode==p1){copiode=p2;}else{copiode=p1;}}
	for(int k=0;k<p1.extensibles.size();++k){
		param.extensibles[k]=copiode.extensibles[k];
	}
		
	if(float_rand(0,1)<rate){ if(copiode==p1){copiode=p2;}else{copiode=p1;}}
	for(int k=0;k<p1.extensibles.size();++k){
		param.biextensibles[k]=copiode.biextensibles[k];
	}
	
	if(float_rand(0,1)<rate){ if(copiode==p1){copiode=p2;}else{copiode=p1;}}
	for(int k=0;k<p1.extensibles.size();++k){
		param.consecutivos[k]=copiode.consecutivos[k];
	}
	
	return param;
}


//SELECCION1
	//idea: quedarse con un porcentaje de los de mejor fitness, mediante un torneo entre todos contra todos.
	//Luego los cruzamos de alguna forma  y dan el doble. Conservar siempre al mejor individuo copiado tal cual



//SELECCION2
	//idea: agarrar varios al azar y elegir el mejor y cruzarlo con otro elegido de la misma forma. Repetir asi
	//hasta tener todos los que queremos. Conservar siempre al mejor individuo copiado tal cual




//EL AGORITMO GENETICO PER SE
/*Evaluar es ver el fitnes, y el t determina el numero de generacion
 
 	t = 0;
	inicializar Poblacion (t); 
	evaluar Poblacion (t);
	Mientras (no se cumpla la condición de parada) hacer
		t = t + 1
		seleccionar P(t) desde P(t-1)
		Reproducir P(t)
		mutación P(t)
		evaluar P(t)

 */


//--------------------MAIN-------------------
//Este es un main trucho para que me de el resultado del genetico
int main(){
	}
	
