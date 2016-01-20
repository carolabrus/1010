#ifndef PIECE_H
#define PIECE_H

#include <list>
#include <utility>

using namespace std;


class Piece {
public:
    Piece();
    Piece(const Piece& orig);
    Piece(int);                             //constructor con inicializador de ID
    int getID();                            //devuelve ID
    void addCoord(int, int);                //añade una coordenada a la pieza.
    list<pair<int,int> > getCoords ();      //devuelve la forma de la pieza en una lista de pares.
    int getSize();                          //devuelve la cantidad de coordenadas que tiene la pieza. El tamaño de la lista de pares piece.
    void mostrar();                         //imprime las coordenadas de la pieza. Utilizado para control y debbuging.
    virtual ~Piece();
private:
    int ID;
    list<pair<int,int> > piece;
};

#endif /* PIECE_H */

/*Cada pieza consta de un identificador (ID). Su forma viene dada por las
 coordenadas que se almacenan en una lista de pares. A partir de la clase Piece
 se puede crear cualquier pieza que se desee.*/