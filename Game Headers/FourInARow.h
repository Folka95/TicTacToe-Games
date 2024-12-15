#ifndef FOUR_IN_A_ROW_H
#define FOUR_IN_A_ROW_H

template <typename T>
class Four_InRow_Board:public Board<T> {
public:
    Four_InRow_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Four_InRow_Player : public Player<T> {
public:
    Four_InRow_Player (string name, T symbol);
    ~Four_InRow_Player ();
    void getmove(int& x, int& y) ;

};

template <typename T>
class Four_InRow_Random_Player : public RandomPlayer<T>{
public:
    Four_InRow_Random_Player (T symbol);
    ~Four_InRow_Random_Player ();
    void getmove(int &x, int &y) ;
};



template <typename T>
Four_InRow_Board<T>::Four_InRow_Board() {
    this->rows = 6;
    this->columns = 7;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) this->board[i][j] = 0;
    }
    this->n_moves = 0;
}

template <typename T>
bool Four_InRow_Board<T>::update_board(int x, int y, T symbol) {
    if (y < 0 || y >= this->columns) return false;
    for (int i = this->rows - 1; i >= 0; i--) {
        if (this->board[i][y] == 0) {
            this->board[i][y] = symbol;
            this->n_moves++;
            return true;
        }
    }
    return false;
}

template <typename T>
void Four_InRow_Board<T>::display_board() {
    cout << "  0   1   2   3   4   5   6   7" << endl;
    for (int i = 0; i < this->rows; i++) {
        cout << i << " ";
        for (int j = 0; j < this->columns; j++) {
            cout << this->board[i][j];
            if (j < 7) cout << " | ";
        }
        cout << endl;
        if (i < 5) cout << " ---*---*---*---*---*---*---*---" << endl;
    }
}

template <typename T>
bool Four_InRow_Board<T>::is_win() {

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns - 3; j++) {
            if (this->board[i][j] != 0 && this->board[i][j + 1] == this->board[i][j] &&
                this->board[i][j + 2] == this->board[i][j] && this->board[i][j + 3] == this->board[i][j]) {
                return true;
                }
        }
    }

    for (int i = 0; i < this->rows - 3; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] != 0 && this->board[i + 1][j] == this->board[i][j] &&
                this->board[i + 2][j] == this->board[i][j] && this->board[i + 3][j] == this->board[i][j]) {
                return true;
                }
        }
    }


    for (int i = 0; i < this->rows - 3; i++) {
        for (int j = 0; j < this->columns - 3; j++) {
            if (this->board[i][j] != 0 && this->board[i + 1][j + 1] == this->board[i][j] &&
                this->board[i + 2][j + 2] == this->board[i][j] && this->board[i + 3][j + 3] == this->board[i][j]) {
                return true;
                }
        }
    }

    for (int i = 0; i < this->rows - 3; i++) {
        for (int j = 3; j < this->columns; j++) {
            if (this->board[i][j] != 0 && this->board[i + 1][j - 1] == this->board[i][j] &&
                this->board[i + 2][j - 2] == this->board[i][j] && this->board[i + 3][j - 3] == this->board[i][j]) {
                return true;
                }
        }
    }

    return false;
}

template <typename T>
bool Four_InRow_Board<T>::is_draw() {return (this->n_moves == 47 && !is_win());}

template <typename T>
bool Four_InRow_Board<T>::game_is_over() {return is_win() || is_draw();}

template <typename T>
Four_InRow_Player<T>::Four_InRow_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Four_InRow_Player<T>::getmove(int& x, int& y) {
    cout << endl;
    cout << "enter your move (column): ";
    cin >> y;
}

template <typename T>
Four_InRow_Random_Player<T>::Four_InRow_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Four_InRow_Random_Player<T>::getmove(int& x, int& y) {y = rand() % this->dimension;}

#endif // FOUR_IN_A_ROW_H
