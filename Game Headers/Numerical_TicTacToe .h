#ifndef _NUMERICAL_TIC_TAC_TOE_H
#define _NUMERICAL_TIC_TAC_TOE_H

template <typename T>
class Numerical_Board : public Board<T> {
public:
    Numerical_Board();
    int visited[10] = {0};
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Numerical_Player : public Player<T> {
    int turn;

public:
    Numerical_Player(string name, T symbol);
    ~Numerical_Player();
    void getmove(int& x, int& y);
};

template <typename T>
class Numerical_Random_Player : public RandomPlayer<T> {
    int turn;
public:
    Numerical_Random_Player(T symbol);
    ~Numerical_Random_Player();
    void getmove(int& x, int& y);
};


template <typename T>
Numerical_Board<T>::Numerical_Board() {
    this->rows = this->columns = 3;
    this->board = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new int[this->columns]();
    }
    this->n_moves = 0;
}

template <typename T>
bool Numerical_Board<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0 && visited[symbol] == 0) {
        this->board[x][y] = symbol;
        visited[symbol] = 1;
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void Numerical_Board<T>::display_board() {
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
bool Numerical_Board<T>::is_win() {
    for (int i = 0; i < this->rows; ++i) {
        if ((this->board[i][0] + this->board[i][1] + this->board[i][2] == 15 &&
             this->board[i][0] * this->board[i][1] * this->board[i][2] != 0) ||
            (this->board[0][i] + this->board[1][i] + this->board[2][i] == 15 &&
             this->board[0][i] * this->board[1][i] * this->board[2][i] != 0)) {
            return true;
        }
    }

    if ((this->board[0][0] + this->board[1][1] + this->board[2][2] == 15 &&
         this->board[0][0] * this->board[1][1] * this->board[2][2] != 0) ||
        (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15 &&
         this->board[0][2] * this->board[1][1] * this->board[2][0] != 0)) {
        return true;
    }

    return false;
}

template <typename T>
bool Numerical_Board<T>::is_draw() {return (this->n_moves == 9 && !is_win());}

template <typename T>
bool Numerical_Board<T>::game_is_over() {return is_win() || is_draw();}

template <typename T>
Numerical_Player<T>::Numerical_Player(string name, T symbol):Player<T>(name, symbol) {
    this->turn = symbol % 2;
}

template <typename T>
void Numerical_Player<T>::getmove(int& x, int& y) {
    cout << this->name << " enter your move (row, column, number): " << endl;
    cin >> x >> y >> this->symbol;
    while ((turn % 2 != 0 && this->symbol % 2 == 0) ||
           (turn % 2 == 0 && this->symbol % 2 != 0) ||
           this->symbol <= 0 || this->symbol >= 10) {
        cout << this->name << " Invalid move. Enter a valid number: " << endl;
        cin >> this->symbol;
    }
}

template <typename T>
Numerical_Random_Player<T>::Numerical_Random_Player(T symbol)
    : RandomPlayer<T>(symbol){
    this->turn = symbol % 2;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Numerical_Random_Player<T>::getmove(int& x, int& y) {
    do {
        x = rand() % 3;
        y = rand() % 3;
        this->symbol = 1 + rand() % 9;
    } while ((turn % 2 != 0 && this->symbol % 2 == 0) ||
             (turn % 2 == 0 && this->symbol % 2 != 0) );
}

#endif //_NUMERICAL_TIC_TAC_TOE_H
