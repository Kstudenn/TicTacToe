#include "Headers/Game.hpp"
#include <iostream>

int main(){
    int tmp=0;
    std::cout<<"Wybierz dlugosc planszy> ";
    std::cin>>tmp;
    Game TicTacToe(tmp);
    std::cout<<"Wybierz ilosc pkt. do wygrania> ";
    std::cin>>tmp;
    TicTacToe.setWiningAmount(tmp);

    TicTacToe.showBoard();
    std::cout<<"Rozmiar "<<TicTacToe.getWiningAmount();
    while(true) {
        TicTacToe.setMark();
        TicTacToe.showBoard();
        if(TicTacToe.isWinning('o')){
            std::cout<<"Wygrales";
            break;
        }
        else
            std::cout<<"Wciaz gramy\n";
        TicTacToe.minimax('x', 0);
        TicTacToe.showBoard();
        if(TicTacToe.isWinning('x')){
            std::cout<<"Przegrales";
            break;
        }
        if(TicTacToe.isTie()) {
            std::cout << "Remis";
            break;
        }
    }
}