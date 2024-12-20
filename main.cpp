#include <bits/stdc++.h>
using namespace std;
#include "inputValidator.h"
#include "GameUniverse.h"
#include "5x5TicTacToe.h"
#include "4x4_TicTacToe.h"
#include "MisereTicTacToe.h"
#include "UltimateTicTacToe.h"
#include "Sus.h"
#include "FourInARow.h"
#include "WordTicTacToeAI.h"
#include "Numerical_TicTacToe .h"
#include "Pyramid_TicTacToe.h"
#include "Pyramid_MinMaxPlayer.h"
#include "WordTicTacToe.h"
inputValidator input;

template < template <typename> class GameHumanPlayer, template <typename> class GameRandomPlayer, template <typename> class GameAIPlayer , typename symbolType>
void getPlayrs(auto B, Player<char>* players[], char p1, char p2, bool swapNames = false) {

    auto setPlayer = [](auto B, Player<char>* &player, int choice, char symbol, string name) {
        if (1 == choice) {
            player = new GameHumanPlayer< symbolType >(name, symbol);
        }
        else if (2 == choice) {
            player = new GameRandomPlayer< symbolType >(symbol);
        }
        else {
            player= new GameAIPlayer< symbolType >(symbol);
        }
        player->setBoard(B);
    };

    auto getPlayer = [&](char symbol, string &name) {
        cout << endl;
        cout << "Please Enter player data:" << endl;
        cout << " * Choose Player " << symbol << " type:" << endl;
        cout << "     1. Human" << endl;
        cout << "     2. Random player" << endl;
        cout << "     3. Smart AI player" << endl;
        cout << "Enter your choice : ";
        int choice = input.readRangeChoice(1 , 3);
        if (1 == choice) {
            cout << " * Enter Player " << symbol << " name:";
            name = input.readLine();
        }
        else {
            name = "Smart AI Player" + symbol;
        }
        return choice;
    };
    vector< string > names(2);
    vector< int > type(2);
    vector< symbolType > symbols = {p1 , p2};
    type[0] = getPlayer(p1 , names[0]);
    type[1] = getPlayer(p2 , names[1]);
    setPlayer(B , players[0] , type[0], symbols[0] , names[0 ^ swapNames]);
    setPlayer(B , players[1] , type[1], symbols[1] , names[1 ^ swapNames]);
}

template < template <typename> class GameHumanPlayer, template <typename> class GameRandomPlayer, typename symbolType>
void getPlayrs(auto B, Player<symbolType>* players[], char p1, char p2, bool swapNames = false) {

    auto setPlayer = [](auto B, Player<symbolType>* &player, int choice, symbolType symbol, string name) {
        if (1 == choice) {
            player = new GameHumanPlayer< symbolType >(name, symbol);
        }
        else if (2 == choice) {
            player = new GameRandomPlayer< symbolType >(symbol);
        }
        player->setBoard(B);
    };

    auto getPlayer = [&](symbolType symbol, string &name) {
        cout << endl;
        cout << "Please Enter player data:" << endl;
        cout << " * Choose Player " << symbol << " type:" << endl;
        cout << "     1. Human" << endl;
        cout << "     2. Random player" << endl;
        cout << "Enter your choice : ";
        int choice = input.readRangeChoice(1 , 2);
        if (1 == choice) {
            cout << " * Enter Player " << symbol << " name:";
            name = input.readLine();
        }
        else {
            name = "Smart AI Player" + symbol;
        }
        return choice;
    };
    vector< string > names(2);
    vector< int > type(2);
    vector< symbolType > symbols = {p1 , p2};
    type[0] = getPlayer(p1 , names[0]);
    type[1] = getPlayer(p2 , names[1]);
    setPlayer(B , players[0] , type[0], symbols[0] , names[0 ^ swapNames]);
    setPlayer(B , players[1] , type[1], symbols[1] , names[1 ^ swapNames]);
}

template <typename symbolType>
void checkWinner(auto myBoard, Player<symbolType>* players[]) {
    if(myBoard->isWinner(players[0]->getsymbol())) {
        cout << players[0]->getname() << " is winner" << endl;
    }
    else if(myBoard->isWinner(players[1]->getsymbol())) {
        cout << players[1]->getname() << " is winner" << endl;
    }
    else {
        cout << "It is a draw!" << endl;
    }
}

template <typename symbolType>
void cleanEnvironment(auto board, Player<symbolType>* players[]) {
    delete board;
    for (int i = 0; i <= 1; i++) {
        delete players[i];
    }
}

void game_1_PyramicTicTacToe() {
    Player<char>* players[2];
    Pyramid_Board<char>* myBoard = new Pyramid_Board<char>();
    getPlayrs<Pyramid_Player , Pyramid_Random_Player , Pyramid_MinMax_Player , char>(myBoard , players , 'X' , 'O');
    GameManager<char> gameManger(myBoard, players);
    gameManger.run();
    cleanEnvironment<char>(myBoard , players);
}

void game_2_FourInRow() {
    Player<char>* players[2];
    Four_InRow_Board<char>* myBoard = new Four_InRow_Board<char>();
    getPlayrs<Four_InRow_Player , Four_InRow_Random_Player , char>(myBoard , players , 'X' , 'O');
    GameManager<char> gameManger(myBoard, players);
    gameManger.run();
    cleanEnvironment<char>(myBoard , players);
}

void game_3_5x5TicTacToe() {
    Player<char>* players[2];
    _5x5TicTacToe_Board<char>* myBoard = new _5x5TicTacToe_Board<char>();
    getPlayrs<_5x5TicTacToe_Player , _5x5TicTacToe_Random_Player , _5x5TicTacToe_AI_Player , char>(myBoard , players , 'X' , 'O');
    GameManager<char> gameManger(myBoard, players);
    gameManger.run();
    checkWinner<char>(myBoard , players);
    cleanEnvironment<char>(myBoard , players);
}

void game_4_WordTicTacToe() {
    Player<char>* players[2];
    Word_Board<char>* myBoard = new Word_Board<char>();
    getPlayrs<Word_Player , Word_Random_Player , Word_MinMax_Player , char>(myBoard , players , '1' , '2');
    for(int i = 0; i < 2; i++) {
        if(players[i]->getname() == "AI Player") {
            auto symbol = players[i]->getsymbol();
            delete players[i];
            players[i] = new Word_MinMax_Player< char > (symbol , "dic.txt");
        }
    }
    GameManager<char> gameManger(myBoard, players);
    gameManger.run();
    cleanEnvironment<char>(myBoard , players);
}

void game_5_NumericalTicTacToe() {
    Player<int>* players[2];
    Numerical_Board<int>* myBoard = new Numerical_Board<int>();
    getPlayrs<Numerical_Player , Numerical_Random_Player , int>(myBoard , players , 1 , 2);
    GameManager<int> gameManger(myBoard, players);
    gameManger.run();
    cleanEnvironment<int>(myBoard , players);
}

void game_6_MisereTicTacToe() {
    Player<char>* players[2];
    _MisereTicTacToe_Board<char>* myBoard = new _MisereTicTacToe_Board<char>();
    getPlayrs<_MisereTicTacToe_Player , _MisereTicTacToe_Random_Player , _MisereTicTacToe_AI_Player , char>(myBoard , players , 'X' , 'O' ,true);
    GameManager<char> gameManger(myBoard, players);
    gameManger.run();
    cleanEnvironment<char>(myBoard , players);
}

void game_7_4x4TicTacToe() {
    Player<char>* players[2];
    TTT4x4Board<char>* myBoard = new TTT4x4Board<char>();
    getPlayrs<TTT4x4Player , TTT4x4RandomPlayer , char>(myBoard , players , 'X' , 'O');
    GameManager< char > gameManger(myBoard, players);
    gameManger.run();
    cleanEnvironment<char>(myBoard , players);
}

void game_8_UltimateTicTacToe() {
    Player<char>* players[2];
    _UltimateTicTacToe_Board<char>* myBoard = new _UltimateTicTacToe_Board<char>();
    getPlayrs<_UltimateTicTacToe_Player , _UltimateTicTacToe_Random_Player , char>(myBoard , players , 'X' , 'O');
    GameManager< char > gameManger(myBoard, players);
    gameManger.run();
    cleanEnvironment<char>(myBoard , players);
}

void game_9_Sus() {
    Player<char>* players[2];
    _Sus_Board<char>* myBoard = new _Sus_Board<char>();
    getPlayrs<_Sus_Player , _Sus_Random_Player , char>(myBoard , players , 'S' , 'U');
    GameManager< char > gameManger(myBoard, players);
    gameManger.run();
    cleanEnvironment<char>(myBoard , players);
}

bool getChoice(int &choice) {
    // system("cls");
    // cout << "\033[2J\033[H";
    cout << endl;
    cout << "Game Menu :-" << endl;
    cout << "1- Pyramid Tic Tac Toe    2- Four In Row             3- 5x5 Tic Tac Toe" << endl;
    cout << "4- Word Tic Tac Toe       5- Numerical Tic Tac Toe   6- Misere Tic Tac Toe" << endl;
    cout << "7- 4x4 Tic Tac Toe        8- Ultimate Tic Tac Toe    9- Sus " << endl;
    cout << "0 - Exit" << endl;
    cout << "Enter your choice :";
    choice = input.readRangeChoice(0 , 9);
    if(choice == 0)
        return false;
    return true;
}

int main()
{
    cout << "Welcome to the best Tic Tac Toe version!!!!" << endl;

    int choice = 0;
    do {
        if (1 == choice) {
            game_1_PyramicTicTacToe();
        }
        else if (2 == choice) {
            game_2_FourInRow();
        }
        else if (3 == choice) {
            game_3_5x5TicTacToe();
        }
        else if (4 == choice) {
            game_4_WordTicTacToe();
        }
        else if (5 == choice) {
            game_5_NumericalTicTacToe();
        }
        else if (6 == choice) {
            game_6_MisereTicTacToe();
        }
        else if (7 == choice) {
            game_7_4x4TicTacToe();
        }
        else if (8 == choice) {
            game_8_UltimateTicTacToe();
        }
        else if (9 == choice) {
            game_9_Sus();
        }
        // system("PAUSE");
    }while(getChoice(choice));
    cout << "Finally this is working!!!!!!!!" << endl;
    return 0;
}
