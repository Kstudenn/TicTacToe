//
// Created by Kacper on 18.06.2018.
//
#include "../Headers/Game.hpp"
#include <iostream>

Game::Game(int boardSize) : boardSize(boardSize) {

    board=new char*[boardSize];

    for(int i=0;i<boardSize;i++) {

        board[i] = new char[boardSize];
        for (int j = 0; j <boardSize ; ++j)
            board[i][j]=' ';
    }
}


Game::~Game() {

    for(int i=0;i<boardSize;i++)
        delete [] board[i];
    delete [] board;
}


int Game::minimax(char gracz, int poziom)
{
    int licznik = 0;
    int w,k;

    // sprawdzamy, czy jest wygrana
    if(isTie()) return 0;
    for(int i = 0; i < boardSize; i++)  //TUTAJ
        for(int j = 0; j < boardSize; j++)//TUTAJ
            if(board[i][j] == ' ')
            {
                board[i][j] = gracz;
                w = i; k = j;  // gdyby był remis
                licznik++;     // zliczamy wolne pola

                bool test = isWinning(gracz);

                board[i][j] = ' ';
                if(test)
                {
                    if(!poziom) board[i][j] = gracz;
                    return gracz == 'x' ? -1 : 1;
                }
            }

    // sprawdzamy, czy jest remis

    if(licznik == 1)
    {
        if(!poziom) board[w][k] = gracz;
        return 0;
    }

    // wybieramy najkorzystniejszy ruch dla gracza

    int v;
    int vmax;

    vmax = gracz == 'x' ? 2 : -2;   //Tutaj 2 -2

    for(int i = 0; i < boardSize; i++)      //TUTAJ
        for(int j = 0; j < boardSize; j++)  //TUTAJ
            if(board[i][j] == ' ')
            {
                board[i][j] = gracz;
                v = minimax(gracz == 'x' ? 'o' : 'x', poziom + 1);
                board[i][j] = ' ';

                if(((gracz == 'x') && (v < vmax)) || ((gracz == 'o') && (v > vmax)))
                {
                    vmax = v; w = i; k = j;
                }
            }

    if(!poziom) board[w][k] = gracz;

    return vmax;
}

bool Game::isWinning(char player) {
    if(boardSize==3){
        // przekątne

        if((board[0][0] == player) && (board[1][1] == player) && (board[2][2] == player)) return true;

        if((board[0][2] == player) && (board[1][1] == player) && (board[2][0] == player)) return true;

        // wiersze i kolumny

        for(int i = 0; i < 3; i++)
        {

            if((board[i][0] == player) && (board[i][1] == player) && (board[i][2] == player)) return true;

            if((board[0][i] == player) && (board[1][i] == player) && (board[2][i] == player)) return true;
        }
        return false;
    }
    else {
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                if (board[i][j] == player) {
                    if (checkHorizon(i, j)) return true;//return board[i][j];
                    if (checkVertical(i, j))return true;//board[i][j];
                    if (checkSlant(i, j)) return true;//board[i][j];
                }
            }
        }
        return false;
    }
}

void Game::setMark(){
    int move1,move2;
    bool isMarked=false;
    do {
        while(true) {
            std::cout << "Twoj ruch > ";
            std::cin >> move1 >> move2;
            if (move1-1 >-1 && move1-1<boardSize &&move2-1>-1 &&move2-1<boardSize)
                break;
            else std::cout << "Bledene, sprobuj ponownie\n";
        }
        move1-=1;
        move2-=1;
        if (isEmpty(move1, move2)) {
            board[move1][move2] = 'o';
            isMarked=true;
        }
        else
            std::cout << "Pole jest zajete, sprobuj ponownie\n";
    }while(!isMarked);
}

bool Game::isTie(){
    for (int i = 0; i <boardSize ; ++i)
        for (int j = 0; j < boardSize; ++j)
            if(board[i][j]==' ')
                return false;
    return true;
}

bool Game::isEmpty(int wiersz, int kolumna){

    return board[wiersz][kolumna] == ' ' ? true : false;
}

void Game::showBoard() {

    for (int j = 0; j <boardSize; ++j) {
        for (int i = 0; i < boardSize; ++i) {

            std::cout<<" "<<board[j][i]<<" ";
            if(i!=boardSize-1)
                std::cout<<"|";
            else
                std::cout<<std::endl;
        }
        if(j==boardSize-1) break;
        for (int k = 0; k <boardSize*4; ++k)
            std::cout<<"-";
        std::cout<<std::endl;
    }
}

bool Game::checkHorizon (int wiersz, int kolumna){

    char mark=board[wiersz][kolumna];
    int markAmount=0;

    for (int j = 0;kolumna+j>=0 ; --j) {

        if(board[wiersz][kolumna+j]==mark)
            markAmount+=1;
        else break;
    }
    markAmount-=1;

    for (int i = 0; kolumna+i<boardSize ; ++i) {

        if (board[wiersz][kolumna+i] == mark)
            markAmount += 1;
        else break;
    }
    if (markAmount>=Game::winingAmount)
        return true;
    else if(markAmount<Game::winingAmount)
        return false;
};


bool Game::checkVertical (int wiersz, int kolumna){

    char mark=board[wiersz][kolumna];
    int markAmount=0;

    for (int j = 0;wiersz+j>=0 ; --j) {
        if(board[wiersz+j][kolumna]==mark)
            markAmount+=1;
        else break;
    }
    markAmount-=1;
    for (int i = 0; wiersz+i<boardSize; ++i) {
        if (board[wiersz+i][kolumna] == mark)
            markAmount += 1;
        else break;
    }
    if (markAmount>=Game::winingAmount)
        return true;
    else if(markAmount<Game::winingAmount)
        return false;
};


bool Game::checkSlant (int line, int column){

    char mark=board[line][column];
    int markAmount=0;

    //Druga ćwiartka
    for (int i = 0; line+i<boardSize && column+i<boardSize; ++i) {
        if(line+i<0 || line+i>boardSize-1) break;
        if(column+i<0 || column+i>boardSize-1) break;
        if(board[line+i][column+i]==mark)
            markAmount+=1;
        else break;
    }
    markAmount-=1;
    //Trzecia ćwiartka
    for (int j = 0; line+j>=0 && column+j>=0 ; --j) {
        if(line+j<0 || line+j>boardSize-1) break;
        if(column+j<0 || column+j>boardSize-1) break;

        if(board[line+j][column+j]==mark)
            markAmount+=1;
        else break;
    }
    if (markAmount>=Game::winingAmount)
        return true;

    markAmount=0;

    //Pierwsza Cwiartka
    for (int decreasesNumber=0, increasesNuber=0; line+decreasesNumber>=0, column+increasesNuber>=boardSize ; --decreasesNumber,++increasesNuber) {
        if(line+decreasesNumber<0 || line+decreasesNumber>boardSize-1) break;
        if(column+increasesNuber<0 || column+increasesNuber>boardSize-1) break;

        if(board[line+decreasesNumber][column+increasesNuber]==mark)
            markAmount+=1;
        else break;
    }
    markAmount-=1;
    //Czwarta Cwiartka
    for (int decreasesNumber=0, increasesNuber=0; column+decreasesNumber>=0, line+increasesNuber>=boardSize ; --decreasesNumber,++increasesNuber) {
        if(line+increasesNuber<0 || line+increasesNuber>boardSize-1) break;
        if(column+decreasesNumber<0 || column+decreasesNumber>boardSize-1) break;

        if(board[line+increasesNuber][column+decreasesNumber]==mark)
            markAmount+=1;
        else break;
    }
    if (markAmount>=Game::winingAmount)
        return true;
    else if(markAmount<Game::winingAmount)
        return false;
}

void Game::setWiningAmount(int winingAmount) {
    Game::winingAmount = winingAmount;
}

int Game::getWiningAmount() const {
    return winingAmount;
};
