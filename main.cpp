#include <bits/stdc++.h>
using namespace std;


#include "inputValidator.h"
#include "GameUniverse.h"
#include "5x5TicTacToe.h"
#include "MisereTicTacToe.h"
#include "Sus.h"
inputValidator input;


template < template <typename> class GameHumanPlayer, template <typename> class GameRandomPlayer, template <typename> class GameAIPlayer , typename symbolType>
void getPlayrs(auto B, Player<char>* players[], char p1, char p2, bool hasAi, bool swapNames = false) {

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
        if(hasAi) {
            cout << "     3. Smart AI player" << endl;
        }
        cout << "Enter your choice : ";
        int choice = input.readRangeChoice(1 , 3 - !hasAi);
        if (1 == choice) {
            cout << " * Enter Player " << symbol << " name:";
            name = input.readLine();
        }
        else {
            name = "Smart AI Player";
        }
        return choice;
    };
    vector< string > names(2);
    vector< int > type(2);
    vector< symbolType > symbols = {p1 , p2};
    // auto getPlayer = [](Player<char>* &player, char symbol) {
    //     cout << "Player " << symbol << " .." << endl;
    //     string name = "Player";
    //     name += symbol;
    //     player = new GameHumanPlayer< symbolType >(name, symbol);
    // };
    type[0] = getPlayer(p1 , names[0]);
    type[1] = getPlayer(p2 , names[1]);
    setPlayer(B , players[0] , type[0], symbols[0] , names[0 ^ swapNames]);
    setPlayer(B , players[1] , type[1], symbols[1] , names[1 ^ swapNames]);
}

void checkWinner(auto myBoard, Player<char>* players[]) {
    if(myBoard->isWinner(players[0]->getsymbol())) {
        cout << "P 1 is winner" << endl;
    }
    else if(myBoard->isWinner(players[1]->getsymbol())) {
        cout << "P 2 is winner" << endl;
    }
    else {
        cout << "draw" << endl;
    }
}

void cleanEnvironment(auto board, Player<char>* players[]) {
    delete board;
    for (int i = 0; i <= 1; i++) {
        delete players[i];
    }
}

void game_3_5x5TicTacToe() {
    Player<char>* players[2];
    _5x5TicTacToe_Board<char>* myBoard = new _5x5TicTacToe_Board<char>();
    getPlayrs<_5x5TicTacToe_Player , _5x5TicTacToe_Random_Player , _5x5TicTacToe_AI_Player , char>(myBoard , players , 'X' , 'O' , true);
    GameManager<char> gameManger(myBoard, players);
    gameManger.run();
    checkWinner(myBoard , players);
    cleanEnvironment(myBoard , players);
}

void game_6_MisereTicTacToe() {
    Player<char>* players[2];
    _MisereTicTacToe_Board<char>* myBoard = new _MisereTicTacToe_Board<char>();
    getPlayrs<_MisereTicTacToe_Player , _MisereTicTacToe_Random_Player , _MisereTicTacToe_AI_Player , char>(myBoard , players , 'X' , 'O' , false);
    GameManager<char> gameManger(myBoard, players);
    gameManger.run();
    cleanEnvironment(myBoard , players);
}

void game_9_Sus() {
    Player<char>* players[2];
    _Sus_Board<char>* myBoard = new _Sus_Board<char>();
    getPlayrs<_Sus_Player , _Sus_Random_Player , _Sus_AI_Player , char>(myBoard , players , 'S' , 'U' , false);
    GameManager< char > gameManger(myBoard, players);
    gameManger.run();
    cleanEnvironment(myBoard , players);
}

int main()
{
    cout << "Choose your game please" << endl;
    // game_9_Sus();
    cout << "Finally this is working!!!!!!!!" << std::endl;
    return 0;
}
