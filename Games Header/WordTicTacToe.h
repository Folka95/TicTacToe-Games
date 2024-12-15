#ifndef _WORDTICTACTOE_H
#define _WORDTICTACTOE_H

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>

using namespace std;

template <typename T>
class Word_Board : public Board<T> {
private:
    unordered_set<string> dictionary;
    void loadDictionary(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Error: Unable to open dictionary file!" << endl;
            exit(1);
        }
        string word;
        while (file >> word) dictionary.insert(word);
        file.close();
    }

public:


    Word_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    bool check_word(const string& word);
};

template <typename T>
class Word_Player : public Player<T> {
public:
    Word_Player(string name, T symbol);
    void getmove(int& x, int& y);


};

template <typename T>
class Word_Random_Player : public RandomPlayer<T> {
public:
    Word_Random_Player(T symbol);
    void getmove(int& x, int& y);

};

template <typename T>
Word_Board<T>::Word_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    loadDictionary("dic.txt");
}

template <typename T>
bool Word_Board<T>::update_board(int x, int y, T symbol) {

    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || symbol == 0)) {
        if (symbol == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(symbol);
        }
        return true;
    }
    return false;
}


template <typename T>
void Word_Board<T>::display_board() {
    cout << "  0   1   2" << endl;
    for (int i = 0; i < 3; i++) {
        cout << i << " ";
        for (int j = 0; j < 3; j++) {
            cout << this->board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << " ---*---*---" << endl;
    }
}

template <typename T>
bool Word_Board<T>::is_win() {

    vector<string> lines;

    for (int i = 0; i < 3; i++) lines.push_back(string(1, this->board[i][0]) + string(1, this->board[i][1]) + string(1, this->board[i][2]));

    for (int j = 0; j < 3; j++) {
        string column = "";
        for (int i = 0; i < 3; i++) column += this->board[i][j];
        lines.push_back(column);
    }

    string diagonal1 = "", diagonal2 = "";
    for (int i = 0; i < 3; i++) {
        diagonal1 += this->board[i][i];
        diagonal2 += this->board[i][2 - i];
    }
    lines.push_back(diagonal1);
    lines.push_back(diagonal2);

    for (auto& line : lines) if (dictionary.find(line) != dictionary.end()) return true;

    return false;
}

template <typename T>
bool Word_Board<T>::is_draw() {return (this->n_moves == 9 && !is_win());}


template <typename T>
bool Word_Board<T>::game_is_over() { return is_win() || is_draw(); }

template <typename T>
bool Word_Board<T>::check_word(const string& word) {return word.size() == 3;}

template <typename T>
Word_Player<T>::Word_Player(string name,T symbol) : Player<T>(name,this->symbol) {}

template <typename T>
void Word_Player<T>::getmove(int& x, int& y) {
    cout << this->name << " enter your move (row, column, letter): ";
    cin >> x >> y >> this->symbol;
    this->symbol = toupper(this->symbol);
}

template <typename T>
Word_Random_Player<T>::Word_Random_Player(T symbol) : RandomPlayer<T>(this->symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Word_Random_Player<T>::getmove(int& x, int& y) {
        x = rand() % this->dimension;
        y = rand() % this->dimension;
        this->symbol = 'A' + rand() % 26;
}


#endif //_WORDTICTACTOE_H
