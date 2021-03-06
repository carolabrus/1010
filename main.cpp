#include <cstdlib>
#include <iostream>
#include "Game.h"
#include "Backtracking.h"
#include "PrintToConsole.h"
#include "HeuristicLine.h"
#include "HeuristicHighestScore.h"
#include "HeuristicSurroundingArea.h"
#include <windows.h>
#include <limits>

using namespace std;

PrintToConsole print;

////////////////////////////////////////////////////////////////////////////////

void singlePlayer(list<Piece> pieces, Game game) {
    
    list<Piece> hand;
    while (hand.empty()){
        Piece arrPieces[game.getHandSize()];
        game.getPiecesToPlay(pieces, arrPieces);
        for (int i=0; i<game.getHandSize(); i++)
            hand.push_back(arrPieces[i]);
        
        while ((!hand.empty()) && (game.movesLeft(hand))){
            //system("cls");
            print.printBoard(game.getBoard());
            cout << endl;
            
            list<Piece>:: iterator it_show = hand.begin();
            for (int i=0; i<hand.size(); i++){
                cout << "Pieza ID: "<< (*it_show).getID() << endl;
                it_show++;
            }
            
            cout << endl << endl << "Score:  " << game.getScore() << endl;
            
            int x=0;
            int y=0;
            int pieza=0;
            
            cout << endl << "elegi la pieza: ";
            cin >> pieza;
            cout << pieza << endl << "elegi la x: ";
            cin >> x;
            cout << x << endl << "elegi la y: ";
            cin >> y;
            cout << y << endl;
            
            list<Piece>:: iterator it = hand.begin();
            switch (pieza)
            {
                case 0:
                    if (game.addPieceToBoard(*it,x,y)){ //si se inserto
                        game.refreshBoard(*it);
                        hand.erase(it);
                    }
                    break;
                case 1:
                    for (int i=0; i<1; i++){
                    it++;}
                    if (game.addPieceToBoard(*it,x,y)){ //si se inserto
                        game.refreshBoard(*it);
                        hand.erase(it);
                    }
                    break;
                case 2:
                    for (int i=0; i<2; i++){
                    it++;}
                    if (game.addPieceToBoard(*it,x,y)){ //si se inserto
                        game.refreshBoard(*it);
                        hand.erase(it);
                    }
                    break;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void autoPlay(list<Piece> pieces, Game game, Backtracking bt) {
    Game solucion = Game();
    bool end = false;
    bool visitados [game.getHandSize()]; 
    Piece hand [game.getHandSize()];
    
    for (int i=0; i<game.getHandSize(); i++){
        visitados[i] = false;
    }
    
    while (end!=true){
        game.getPiecesToPlay(pieces, hand);
        
        for (int i=0; i<game.getHandSize(); i++)
            cout << "Pieza ID: "<< hand[i].getID() << endl;
        int m = numeric_limits<int>::min();                     //se inicializa con el menor de los enteros.
        solucion.reset();
        bt.vueltaAtras(game,solucion,hand,visitados,m,game.getHandSize());

        cout << endl;
        if (solucion.getScore()==0)
            end = true;
        else{
            print.printBoard(solucion.getBoard());
            cout << "Score de solucion: " << solucion.getScore() << endl;
            cout << "Lineas borradas so far: " << solucion.getLinesDeleted() << endl;
            cout << endl;
        }
        
        game=solucion;
    }
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
    
    ////////////////////////////////// PIEZAS //////////////////////////////////
    
    Piece p0 = Piece(0);
    p0.addCoord(0,0);
    
    Piece p1 = Piece(1);     //Palito de 2 vertical
    p1.addCoord(0,0);        // ■
    p1.addCoord(0,1);        // ■
    
    Piece p2 = Piece(2);     //Palito de 2 horizontal
    p2.addCoord(0,0);        // ■ ■
    p2.addCoord(1,0);
     
    Piece p3 = Piece(3);     //Palito de 3 vertical
    p3.addCoord(0,0);        // ■
    p3.addCoord(0,1);        // ■
    p3.addCoord(0,2);        // ■
    
    Piece p4 = Piece(4);     //Palito de 3 horizontal
    p4.addCoord(0,0);        // ■ ■ ■
    p4.addCoord(1,0);
    p4.addCoord(2,0);
    
    Piece p5 = Piece(5);     //Palito de 4 vertical
    p5.addCoord(0,0);        // ■
    p5.addCoord(0,1);        // ■
    p5.addCoord(0,2);        // ■
    p5.addCoord(0,3);        // ■
    
    Piece p6 = Piece(6);     //Palito de 4 horizontal
    p6.addCoord(0,0);        // ■ ■ ■ ■
    p6.addCoord(1,0);
    p6.addCoord(2,0);
    p6.addCoord(3,0);
    
    Piece p7 = Piece(7);     //Palito de 5 vertical
    p7.addCoord(0,0);        // ■
    p7.addCoord(0,1);        // ■
    p7.addCoord(0,2);        // ■
    p7.addCoord(0,3);        // ■
    p7.addCoord(0,4);        // ■
    
    Piece p8 = Piece(8);     //Palito de 5 horizontal
    p8.addCoord(0,0);        // ■ ■ ■ ■ ■
    p8.addCoord(1,0);
    p8.addCoord(2,0);
    p8.addCoord(3,0);
    p8.addCoord(4,0);
    
    Piece p9 = Piece(9);     //cuadrado 2x2
    p9.addCoord(0,0);        // ■ ■
    p9.addCoord(0,1);        // ■ ■
    p9.addCoord(1,0);
    p9.addCoord(1,1);

    Piece p10 = Piece(10);   //cuadrado 3x3
    p10.addCoord(0,0);        // ■ ■ ■
    p10.addCoord(0,1);        // ■ ■ ■
    p10.addCoord(0,2);        // ■ ■ ■
    p10.addCoord(1,0);
    p10.addCoord(1,1);
    p10.addCoord(1,2);
    p10.addCoord(2,0);
    p10.addCoord(2,1);
    p10.addCoord(2,2);
    
    Piece p11 = Piece(11);   // ■ ■
    p11.addCoord(0,0);       // ■
    p11.addCoord(1,0);
    p11.addCoord(0,1);
    
    Piece p12 = Piece(12);   //   ■
    p12.addCoord(0,0);       // ■ ■
    p12.addCoord(0,1);
    p12.addCoord(-1,1);
    
    Piece p13 = Piece(13);   // ■ ■
    p13.addCoord(0,0);       //   ■
    p13.addCoord(1,0);
    p13.addCoord(1,1);
    
    Piece p14 = Piece(14);   // ■
    p14.addCoord(0,0);       // ■ ■
    p14.addCoord(0,1);
    p14.addCoord(1,1);
    
    Piece p15 = Piece(15);   // ■ ■ ■
    p15.addCoord(0,0);       // ■
    p15.addCoord(1,0);       // ■
    p15.addCoord(2,0);
    p15.addCoord(0,1);
    p15.addCoord(0,2);
    
    Piece p16 = Piece(16);   //     ■
    p16.addCoord(0,0);       //     ■
    p16.addCoord(0,1);       // ■ ■ ■
    p16.addCoord(0,2);
    p16.addCoord(-1,2);
    p16.addCoord(-2,2);
    
    Piece p17 = Piece(17);   // ■ ■ ■
    p17.addCoord(0,0);       //     ■
    p17.addCoord(1,0);       //     ■
    p17.addCoord(2,0);
    p17.addCoord(2,1);
    p17.addCoord(2,2);
    
    Piece p18 = Piece(18);   // ■
    p18.addCoord(0,0);       // ■
    p18.addCoord(0,1);       // ■ ■ ■
    p18.addCoord(0,2);
    p18.addCoord(1,2);
    p18.addCoord(2,2);
    
    /*Piece p19 = Piece(19);   //pieza grande
    p19.addCoord(0,0);
    p19.addCoord(0,1);
    p19.addCoord(0,2);
    p19.addCoord(0,3);
    p19.addCoord(0,4);
    p19.addCoord(0,5);
    p19.addCoord(0,6);
    p19.addCoord(1,0);
    p19.addCoord(2,0);
    p19.addCoord(3,0);
    p19.addCoord(4,0);
    p19.addCoord(5,0);
    p19.addCoord(6,0);
    p19.addCoord(1,6);
    p19.addCoord(2,6);
    p19.addCoord(3,6);
    p19.addCoord(4,6);
    p19.addCoord(5,6);
    p19.addCoord(6,6);
    
    Piece p20 = Piece(20);
    p20.addCoord(0,0);
    p20.addCoord(1,0);
    p20.addCoord(2,0);
    p20.addCoord(3,0);
    p20.addCoord(4,0);
    p20.addCoord(5,0);
    p20.addCoord(6,0);
    p20.addCoord(7,0);
    p20.addCoord(8,0);
    p20.addCoord(0,1);
    p20.addCoord(0,2);
    p20.addCoord(0,3);
    p20.addCoord(0,4);
    p20.addCoord(0,5);
    p20.addCoord(0,6);
    p20.addCoord(0,7);
    p20.addCoord(0,8);
    p20.addCoord(1,1);
    p20.addCoord(1,2);
    p20.addCoord(1,3);
    p20.addCoord(1,4);
    p20.addCoord(1,5);
    p20.addCoord(1,6);
    p20.addCoord(1,7);
    p20.addCoord(1,8);
    
    Piece p21 = Piece(21);   //cuadrado 4x4
    p21.addCoord(0,0);
    p21.addCoord(0,1);
    p21.addCoord(0,2);
    p21.addCoord(0,3);
    p21.addCoord(1,0);
    p21.addCoord(1,1);
    p21.addCoord(1,2);
    p21.addCoord(1,3);
    p21.addCoord(2,0);
    p21.addCoord(2,1);
    p21.addCoord(2,2);
    p21.addCoord(2,3);
    p21.addCoord(3,0);
    p21.addCoord(3,1);
    p21.addCoord(3,2);
    p21.addCoord(3,3);

    Piece p22 = Piece(22);     // ■ ■ ■ ■ ■ ■ ■
    p22.addCoord(0,0);         // ■
    p22.addCoord(1,0);         // ■
    p22.addCoord(2,0);         // ■
    p22.addCoord(3,0);         // ■
    p22.addCoord(4,0);         // ■
    p22.addCoord(5,0);         // ■
    p22.addCoord(6,0);         //
    p22.addCoord(7,0);
    p22.addCoord(0,1);
    p22.addCoord(0,2);
    p22.addCoord(0,3);
    p22.addCoord(0,4);
    p22.addCoord(0,5);
    p22.addCoord(0,6);
    p22.addCoord(0,7);
    
    Piece p23 = Piece(23);   //cuadrado 3x3
    p23.addCoord(0,0);
    p23.addCoord(0,1);
    p23.addCoord(0,2);
    p23.addCoord(1,0);
    p23.addCoord(1,1);
    p23.addCoord(1,2);
    p23.addCoord(2,0);
    p23.addCoord(2,1);
    p23.addCoord(2,2);
    
    Piece p24 = Piece(24);     // ■ ■ ■ ■ ■ ■ ■ //■
    p24.addCoord(0,0);
    p24.addCoord(1,0);
    p24.addCoord(2,0);
    p24.addCoord(3,0);
    p24.addCoord(4,0);
    p24.addCoord(5,0);
    p24.addCoord(6,0);
    //p24.addCoord(7,0);
    
    Piece p25 = Piece(25);
    p25.addCoord(0,0);          // ■
    p25.addCoord(0,1);          // ■
    p25.addCoord(0,2);          // ■
    p25.addCoord(0,3);          // ■
    p25.addCoord(0,4);          // ■
    p25.addCoord(0,5);          // ■
    p25.addCoord(0,6);          // ■
    //p25.addCoord(0,7);          // ■*/

    //////////////////////////////// END PIEZAS ////////////////////////////////
    
    Game game = Game();
    list<Piece> pieces;
    pieces.push_back(p0);
    pieces.push_back(p1);
    pieces.push_back(p2);
    pieces.push_back(p3);
    pieces.push_back(p4);
    pieces.push_back(p5);
    pieces.push_back(p6);
    pieces.push_back(p7);
    pieces.push_back(p8);
    pieces.push_back(p9);
    pieces.push_back(p10);
    pieces.push_back(p11);
    pieces.push_back(p12);
    pieces.push_back(p13);
    pieces.push_back(p14);
    pieces.push_back(p15);
    pieces.push_back(p16);
    pieces.push_back(p17);
    pieces.push_back(p18);

    /////////////////////////////////// MENU ///////////////////////////////////
    print.printStartScreen();
    print.printStartMenu();
    int keepPlaying = 1;
    int gameOption = 0;
    while ((gameOption <1) || (gameOption>3) || (keepPlaying == 1)) {
        cin >> gameOption;
        cout << endl;
        if (gameOption == 1){
            singlePlayer(pieces, game);
            print.printGameOver();
            game.reset();
        }
        else if (gameOption == 2){
            print.printBacktrackingMenu();
            int backOption = 0;
            Backtracking bt = Backtracking();
            while ((backOption < 1) || (backOption > 7)){
                cin >> backOption;
                cout << endl;
                if (backOption == 1){
                    Heuristic *heuristicHS = new HeuristicHighestScore();
                    bt.addToList(heuristicHS, 1);
                    autoPlay(pieces, game, bt);
                    print.printGameOver();
                }
                else if (backOption == 2){
                    Heuristic *heuristicR = new HeuristicLine(&game, true);
                    bt.addToList(heuristicR, 1);
                    autoPlay(pieces, game, bt);
                    print.printGameOver();
                }
                else if (backOption == 3){
                    Heuristic *heuristicC = new HeuristicLine(&game, false);
                    bt.addToList(heuristicC, 1);
                    autoPlay(pieces, game, bt);
                    print.printGameOver();
                }
                else if (backOption == 4){
                    Heuristic *heuristicC = new HeuristicLine(&game, false);
                    Heuristic *heuristicR = new HeuristicLine(&game, true);
                    bt.addToList(heuristicC, 0.5);
                    bt.addToList(heuristicR, 0.5);
                    autoPlay(pieces, game, bt);
                    print.printGameOver();
                }
                else if (backOption == 5){
                    Heuristic *heuristicSA = new HeuristicSurroundingArea(&game);
                    bt.addToList(heuristicSA, 1);
                    autoPlay(pieces, game, bt);
                    print.printGameOver();
                }
                else if (backOption == 6){
                    Heuristic *heuristicC = new HeuristicLine(&game, false);
                    Heuristic *heuristicR = new HeuristicLine(&game, true);
                    Heuristic *heuristicSA = new HeuristicSurroundingArea(&game);
                    bt.addToList(heuristicC, 0.2);
                    bt.addToList(heuristicR, 0.2);
                    bt.addToList(heuristicSA, 0.6);
                    autoPlay(pieces, game, bt);
                    print.printGameOver();
                }
            }
        }
        
        if (gameOption != 3){
            print.printKeepMenu();
            cin >> keepPlaying;
            if (keepPlaying == 1){
                print.printStartMenu();
            }
        }
        else keepPlaying = 2;
    }
    
    return 0;
}