#include "Backtracking.h"
#include <iostream>
#include <windows.h>

using namespace std;

Backtracking::Backtracking() {
}

/*Backtracking::Backtracking(const Backtracking& orig) {
}*/

void Backtracking::vueltaAtras(Game gameAct, Game &gameSol, Piece hand [], bool visitados [], int mejorPunt, int depth){  //depth comienza en 3 por la cant de piezas
    if ((depth == 0) && (gameAct.getScore() > mejorPunt)){
            mejorPunt=gameAct.getScore();
            gameSol=gameAct;
    }
    else if (depth>0)
        for (int pos =0; pos < gameAct.getHandSize(); pos++)
            if (visitados[pos] == false)
                for (int x=0; x< gameAct.getWidth(); x++)
                    for (int y=0; y< gameAct.getHeight(); y++)
                        if (!gameAct.checkPiece(hand[pos],x,y)){
                            Game copia(gameAct);
                            copia.addPieceToBoard(hand[pos],x,y);
                            copia.refreshBoard(hand[pos]);
                            //Sleep(100);
                            //copia.printBoard();
                            visitados[pos] = true;
                            vueltaAtras(copia, gameSol, hand, visitados, gameSol.getScore(), depth-1);
                            visitados[pos] = false;
                        }
}


Backtracking::~Backtracking() {
}