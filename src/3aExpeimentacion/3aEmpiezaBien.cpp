#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <sys/stat.h>
#include <cmath>
#include <cassert>


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
		
};


//---------------------FUNCIONES QUE DETERMINAN SI UN JUGADOR YA GANO O NO-------------

//determina si dado un tablero gano el jugador i:
bool ganojugador(vector<vector<int>> tablero, int i, int c, int ultimajugada){
	
	 if(ultimajugada==-1){if(c==1) {return true;}else{return false;}}
     //Por si es la primer jugada, nadie gano aun, salvo sea 1 en linea.
     
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
	
	//el checkeo de si gano o pierdo en el proximo turno lo hace la funcion parametrizable
	
	
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
		//si puedo ganar, gano
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



//----------------- GRID SEARCH------------------------


//funcion que da un float random en el intervalo cerrado [min,max]
float float_rand( float min, float max ){
    float scale = (float)rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}

//función que sortea un parametro random
void paramrandom(parametro& param, int c){
	
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
}


//se fija si un jugador desafiante le gana al jugador mejor
bool nuevoCampeon (int rows, int columns, int c, int p, parametro mejor, parametro desafiante){

	int empiezaDesafiante = juez(rows,columns,c,p,1,desafiante,mejor);
	int empiezaCampeon = juez(rows,columns,c,p,1,mejor,desafiante);

	if(empiezaDesafiante==1 && empiezaCampeon==2) {
		//si le gana al mejor hasta ahora siendo primero y segundo
		return true;// pasa a ser el nuevo mejor		
	}
	
	if(empiezaDesafiante==1 && empiezaCampeon==0) {
		//si le gana y empata al mejor hasta ahora siendo primero y segundo respectivamente
		return true;// pasa a ser el nuevo mejor
	}

	if(empiezaDesafiante==0 && empiezaCampeon==2) {
		//si le empata y gana al mejor hasta ahora siendo primero y segundo respectivamente
		return true;// pasa a ser el nuevo mejor
	}
	return false;
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




//funcion del punto 3.a que busca parametros que optimicen 
parametro gridsearch(int rows, int columns, int c, int p){

	parametro param= leerParametroDeValores(c, "NuestroJugadorBueno.txt");
/*
	cerr<< param.esquinaparam.first << endl; 
	cerr<<param.esquinaparam.second<< endl;
	cerr<<param.bordeparam.first<< endl;
	cerr<<param.bordeparam.second<< endl;
	cerr<<	param.libertadparam.first << endl;
	cerr<<	param.libertadparam.second << endl;
	cerr<<param.consecparam.first << endl;
	cerr<<param.consecparam.second << endl;
	cerr<<param.centroparam.first << endl;
	cerr<<	param.centroparam.second<< endl;
	cerr<<param.extproxparam.first << endl;
	cerr<<param.extproxparam.second << endl;
	cerr<<param.extparam.first << endl;
	cerr<<param.extparam.second << endl;
	cerr<<param.biextparam.first << endl;
	cerr<<param.biextparam.second << endl;
	

	for(int k=0;k<3;++k){
		cerr<< param.extensiblesprox[k]<< endl;
		cerr<<param.extensibles[k]<< endl;
		cerr<<param.biextensibles[k]<< endl;
		cerr<<param.consecutivos[k]<< endl;
	}
	
*/

	parametro mejor=param;


	vector<float> valoresDiscretos = {-1, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1}

	///for (int u=0; u<4; ++u){
		for(int k=0;k<c-1;++k){
			for (int i=0; i<valoresDiscretos.size(); ++i) {
				param.extensiblesprox[k] = valoresDiscretos[i];
				for (int j=0; j<valoresDiscretos.size(); ++j) {
					param.extensibles[k] = valoresDiscretos[j];
					if (nuevoCampeon(rows, columns, c, p, mejor, param)) {mejor = param;}				
				}
			}
			//para que los proximos parametros tengan estos ya optimizados, si no estarian con desventaja.
			param = mejor;

			for (int l=0; l<valoresDiscretos.size(); ++l) {
				param.biextensibles[k] = valoresDiscretos[l];
				for (int r=0; r<valoresDiscretos.size(); ++r) {
				param.biextensibles[k] = valoresDiscretos[r];
					if (nuevoCampeon(rows, columns, c, p, mejor, param)) {mejor = param;}
				}
			}
			//para que los proximos parametros tengan estos ya optimizados, si no estarian con desventaja.
			param = mejor;
		}



		//optimizamos biextparam
		for (int i=0; i<valoresDiscretos.size(); ++i) {
				param.extensiblesprox[k] = valoresDiscretos[i];

			for (int j=0; j<valoresDiscretos.size(); ++j) {
				param.biextparam.second = valoresDiscretos[j];
				if (nuevoCampeon(rows, columns, c, p, mejor, param)) {mejor = param;}
			}
		}	
		//para que los proximos parametros tengan estos ya optimizados, si no estarian con desventaja.
		param = mejor;


		cerr << "estoy avanzando a";
		//optimizamos extproxparam
		for (int i=0; i<valoresDiscretos.size(); ++i) {
			param.extproxparam.first = valoresDiscretos[i];

			for (int j=0; j<valoresDiscretos.size(); ++j) {
				param.extproxparam.second = valoresDiscretos[j];
				if (nuevoCampeon(rows, columns, c, p, mejor, param)) {mejor = param;}
			}
		}	
		//para que los proximos parametros tengan estos ya optimizados, si no estarian con desventaja.
		param = mejor;
	
		//optimizamos extparam
		for (int i=0; i<valoresDiscretos.size(); ++i) {
			param.extparam.first = valoresDiscretos[i];

			for (int j=0; j<valoresDiscretos.size(); ++j) {
				param.extparam.second = valoresDiscretos[j];
				if (nuevoCampeon(rows, columns, c, p, mejor, param)) {mejor = param;}
			}
		}	
		//para que los proximos parametros tengan estos ya optimizados, si no estarian con desventaja.
		param = mejor;


		//optimizamos equinaparam
		for (int i=0; i<valoresDiscretos.size(); ++i) {
			param.esquinaparam.first = valoresDiscretos[i];

			for (int j=0; j<valoresDiscretos.size(); ++j) {
				param.esquinaparam.second = valoresDiscretos[j];
				if (nuevoCampeon(rows, columns, c, p, mejor, param)) {mejor = param;}
			}
		}
		//para que los proximos parametros tengan estos ya optimizados, si no estarian con desventaja.
		param = mejor;


		cerr << "estoy avanzando b";
		//optimizamos bordeparam
		for (int i=0; i<valoresDiscretos.size(); ++i) {
			param.bordeparam.first = valoresDiscretos[i];

			for (int j=0; j<valoresDiscretos.size(); ++j) {
				param.bordeparam.second = valoresDiscretos[j];
				if (nuevoCampeon(rows, columns, c, p, mejor, param)) {mejor = param;}
			}
		}
		//para que los proximos parametros tengan estos ya optimizados, si no estarian con desventaja.
		param = mejor;
	
		//optimizamos libertadparam
		for (int i=0; i<valoresDiscretos.size(); ++i) {
			param.libertadparam.first = valoresDiscretos[i];

			for (int j=0; j<valoresDiscretos.size(); ++j) {
				param.libertadparam.second = valoresDiscretos[j];
				if (nuevoCampeon(rows, columns, c, p, mejor, param)) {mejor = param;}
			}
		}	
		//para que los proximos parametros tengan estos ya optimizados, si no estarian con desventaja.
		param = mejor;

		//optimizamos consecparam	
		for (int i=0; i<valoresDiscretos.size(); ++i) {
			param.consecparam.first = valoresDiscretos[i];

			for (int j=0; j<valoresDiscretos.size(); ++j) {
				param.consecparam.second = valoresDiscretos[j];
				if (nuevoCampeon(rows, columns, c, p, mejor, param)) {mejor = param;}
			}
		}	
		//para que los proximos parametros tengan estos ya optimizados, si no estarian con desventaja.
		param = mejor;
	
		//optimizamos centroparam
		for (int i=0; i<valoresDiscretos.size(); ++i) {
			param.centroparam.first = valoresDiscretos[i];

			for (int j=0; j<valoresDiscretos.size(); ++j) {
				param.centroparam.second = valoresDiscretos[j];
				if (nuevoCampeon(rows, columns, c, p, mejor, param)) {mejor = param;}
			}
		}	
		//para que los proximos parametros tengan estos ya optimizados, si no estarian con desventaja.
		param = mejor;

	///}


	return mejor;
}	
	


int escribirParametro(int c, parametro param){
	
	ofstream valores;
	valores.open ("chebarAVER2.txt");
	
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

	assert(param.extensiblesprox.size() == k);

	return 0;
}


//-----------------------MAIN--------------------------
//Este es un main trucho para que me de el resultado de grid-search
int main(){
	srand((unsigned int)time(NULL));
	int columns = 7;
	int rows = 6;
	int c = 4;
	int p = 50; 
	parametro param=gridsearch(columns,rows,c,p);

	escribirParametro(c, param);

	/*
	cout<< "param esquina1:"<< param.esquinaparam.first << endl; 
	cout<< "param esquina2:"<<param.esquinaparam.second<< endl;
	cout<<"param borde1:"<<param.bordeparam.first<< endl;
	cout<<"param borde2:"<<param.bordeparam.second<< endl;
	cout<<"param centro1:"<<param.centroparam.first << endl;
	cout<<"param centro2:"<<	param.centroparam.second<< endl;
	cout<<"param libertad1:"<<	param.libertadparam.first << endl;
	cout<<"param libertad2:"<<	param.libertadparam.second << endl;
	cout<<"param consec1:"<<param.consecparam.first << endl;
	cout<<"param consec2:"<<param.consecparam.second << endl;
	cout<<"param extprox1:"<<param.extproxparam.first << endl;
	cout<<"param extprox2:"<<param.extproxparam.second << endl;
	cout<<"param ext1:"<<param.extparam.first << endl;
	cout<<"param ext2:"<<param.extparam.second << endl;
	cout<<"param biext1:"<<param.biextparam.first << endl;
	cout<<"param biext2:"<<param.biextparam.second << endl;
	
	cout<< "extprox; " << "ext; " << "biext; "<< "consec; "<< endl;
	
	for(int k=0;k<c-1;++k){
		cout<< param.extensiblesprox[k]<< ";  ";
		cout<<param.extensibles[k]<< ";  ";
		cout<<param.biextensibles[k]<< ";  ";
		cout<<param.consecutivos[k]<< endl;
	}
	*/
	
	return 0;
	}
	
