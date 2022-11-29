//
// Created by Kacper on 18.06.2018.
//

#ifndef GRA_2_GAME_HPP
#define GRA_2_GAME_HPP

class Game{
private:
    char **board;
    int boardSize;
    int winingAmount;

public:
    void setWiningAmount(int winingAmount);

    int getWiningAmount() const;

    Game(int boardSize);
    virtual ~Game();
    int minimax(char,int);
    bool isWinning(char );
    void showBoard();
    bool checkHorizon(int, int);
    bool checkVertical(int, int);
    bool checkSlant(int, int);
    bool isEmpty(int, int);
    bool isTie();
    void setMark();
};
#endif //GRA_2_GAME_HPP
