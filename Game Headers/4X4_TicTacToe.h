#ifndef _4X4_TICTACTOE_H
#define _4X4_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>

using namespace std;

template <typename T>
class TTT4x4Board : public Board<T> {
public:
    TTT4x4Board();
    pair<int, int> getMove();
    string getname();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;

private:
    vector<pair<int, int>> positions[2];
    void initialize_positions();
};

template <typename T>
class TTT4x4Player : public Player<T> {
public:
    TTT4x4Player(string name, T symbol);

    void getmove(int& to_x, int& to_y) override;
};

template <typename T>
class TTT4x4RandomPlayer : public RandomPlayer<T> {
public:
    TTT4x4RandomPlayer(T symbol);
    static  bool flag;
    void getMove(int& from_x, int& from_y);
    void getmove(int& to_x, int& to_y) override;
};
template <typename T>
bool TTT4x4RandomPlayer<T>::flag = false;//--------------------------------------- IMPLEMENTATION

template <typename T>
TTT4x4Board<T>::TTT4x4Board() {
    this->rows = this->columns = 4;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    initialize_positions();
}

template <typename T>
void TTT4x4Board<T>::initialize_positions() {
    positions[0] = {{3, 0}, {0, 1}, {3, 2}, {0, 3}};
    for (auto& pos : positions[0]) {this->board[pos.first][pos.second] = 'X';}

    positions[1] = {{0, 0}, {3, 1}, {0, 2}, {3, 3}};
    for (auto& pos : positions[1]) {this->board[pos.first][pos.second] = 'O';}
}

template <typename T>
bool TTT4x4Board<T>::update_board(int x, int y, T symbol) {

    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) return false;
    pair<int, int> m = getMove();

    if (this->board[x][y] != 0 || this->board[m.first][m.second] != symbol) return false;

    if (!(abs(m.first - x) == 1 && m.second == y) && !(abs(m.second - y) == 1 && m.first == x)) {return false;}


    this->board[m.first][m.second] = 0;
    this->board[x][y] = toupper(symbol);
    this->n_moves++;

    return true;
}


template <typename T>
void TTT4x4Board<T>::display_board() {
    cout << "  0   1   2   3" << endl;
    for (int i = 0; i < this->rows; i++) {
        cout << i << " ";
        for (int j = 0; j < this->columns; j++) {
            cout << this->board[i][j];
            if (j < 3) cout << " | ";
        }
        cout << endl;
        if (i < 3) cout << " ---*---*---*---" << endl;
    }
}

template <typename T>
bool TTT4x4Board<T>::is_win() {

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] != 0) {
                T symbol = this->board[i][j];

                if (j <= this->columns - 3 && this->board[i][j + 1] == symbol && this->board[i][j + 2] == symbol) return true;

                if (i <= this->rows - 3 && this->board[i + 1][j] == symbol && this->board[i + 2][j] == symbol) return true;

                if (i <= this->rows - 3 && j <= this->columns - 3 && this->board[i + 1][j + 1] == symbol && this->board[i + 2][j + 2] == symbol) return true;

                if (i <= this->rows - 3 && j >= 2 && this->board[i + 1][j - 1] == symbol && this->board[i + 2][j - 2] == symbol) return true;
            }
        }
    }
    return false;
}

template <typename T>
bool TTT4x4Board<T>::is_draw() {return (this->n_moves == 16 && !is_win());}

template <typename T>
bool TTT4x4Board<T>::game_is_over() {return is_win();}

template <typename T>
TTT4x4Player<T>::TTT4x4Player(string name, T symbol) : Player<T>(name, symbol) {}
template <typename T>
pair<int, int> TTT4x4Board<T>::getMove(){
    int from_x, from_y;
    if (TTT4x4RandomPlayer<T>::flag==false) {
        cout << "From (x y): ";
        cin >> from_x >> from_y;
    }else {
        from_x = rand() % 4;
        from_y = rand() % 4;
    }
    return {from_x, from_y};
}


template <typename T>
void TTT4x4Player<T>::getmove(int& to_x, int& to_y) {
    cout << "\n" << this->name << " (" << this->symbol << "), enter your move: \n";
    cout << "To (x y): ";
    TTT4x4RandomPlayer<T>::flag=false;
    cin >> to_x >> to_y;
}

template <typename T>
TTT4x4RandomPlayer<T>::TTT4x4RandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = "Random Computer Player";

    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void TTT4x4RandomPlayer<T>::getmove(int& to_x, int& to_y) {
    to_x = rand() % this->dimension;
    to_y = rand() % this->dimension;
    flag=true;
}

#endif // _4X4_TICTACTOE_H
