# El makefile genera cuatro jugadores que resultaron de la experimentacion
# para poder correr con el juez de la catedra. 
# Tambien genera el jugador minimax con y sin poda y el 3a y 3b
# si se desean correr para experimentar. 

all: ej1a ej1b ej3a ej3b jugGrid jugNuestro jugGenBack jugGenF2

ej1a: 1a.cpp
	g++ -std=c++11 1a.cpp -o ej1a  

ej1b: 1b.cpp
	g++ -std=c++11 1b.cpp -o ej1b  

ej3a: 3a.cpp
	g++ -std=c++11 3a.cpp -o ej3a

ej3b: 3b.cpp
	g++ -std=c++11 3b.cpp -o ej3b

jugGrid: leeJugadoresEntrega.cpp
	g++ -D GRID -std=c++11 leeJugadoresEntrega.cpp -o jugadorGrid

jugNuestro: leeJugadoresEntrega.cpp
	g++ -D BUENO -std=c++11 leeJugadoresEntrega.cpp -o jugadorNuestro
	
jugGenBack: leeJugadoresEntrega.cpp
	g++ -D GENBACKTRACK -std=c++11 leeJugadoresEntrega.cpp -o jugadorGeneticoBacktrack

jugGenF2: leeJugadoresEntrega.cpp
	g++ -D GENFITNESS2 -std=c++11 leeJugadoresEntrega.cpp -o jugadorGeneticoFitness2

clean:
	rm -f ej1a ej1b ej3a ej3b jugadorGrid jugadorNuestro jugadorGeneticoBacktrack jugadorGeneticoFitness2
