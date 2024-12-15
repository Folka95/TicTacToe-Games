#ifndef _PYRAMID_TIC_TAC_TOE_H
#define _PYRAMID_TIC_TAC_TOE_H

template <typename T>
class Pyramid_Board : public Board<T> {
public:
    Pyramid_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Pyramid_Player : public Player<T> {
public:
    Pyramid_Player(string name, T symbol);
    ~Pyramid_Player();
    void getmove(int& x, int& y);
};


template <typename T>
class Pyramid_Random_Player : public RandomPlayer<T> {
public:
    Pyramid_Random_Player(T symbol);
    ~Pyramid_Random_Player();
    void getmove(int& x, int& y);
};

template <typename T>
Pyramid_Board<T>::Pyramid_Board() {
    this->rows = 3;
    this->columns = 5;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[(2 * i) + 1];
        for (int j = 0; j < (2 * i) + 1; j++) this->board[i][j] = 0;

    }
    this->n_moves = 0;
}

template <typename T>
bool Pyramid_Board<T>::update_board(int x, int y, T symbol) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| symbol == 0)) {
        if (symbol == 0){
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
void Pyramid_Board<T>::display_board() {

    cout << endl;
    cout << "Pyramid Tic-Tac-Toe" << endl;
    cout << "-------------------" << endl;
        cout <<setw(7) << "[" << this-> board[0][0] << "]" << endl;

        cout <<setw(4) << "[" << this-> board[1][0] << "]"
             << setw(0) << "[" << this-> board[1][1] << "]"
             << setw(0) << "[" << this-> board[1][2] << "]" << endl;


        cout <<setw(1) << "[" << this-> board[2][0] << "]"
             << setw(0) << "[" << this-> board[2][1] << "]"
             << setw(0) << "[" << this-> board[2][2] << "]"
             << setw(0) << "[" << this-> board[2][3] << "]"
             << setw(0) << "[" << this-> board[2][4] << "]" << endl;

        cout << "-------------------" << endl;
}

template <typename T>
bool Pyramid_Board<T>::is_win() {

    if ((this-> board[1][0] != 0 && this-> board[1][1] == this-> board[1][0] && this-> board[1][2] == this-> board[1][0]) ||
            (this-> board[2][0] != 0 && this-> board[2][1] == this-> board[2][0] && this-> board[2][2] == this-> board[2][0]) ||
            (this-> board[2][1] != 0 && this-> board[2][2] == this-> board[2][1] && this-> board[2][3] == this-> board[2][1]) ||
            (this-> board[2][2] != 0 && this-> board[2][3] == this-> board[2][2] && this-> board[2][4] == this-> board[2][2])) {
        return true;}

    if (this-> board[0][0] != 0 &&this-> board[0][0] == this-> board[1][1] && this-> board[1][1] == this-> board[2][2]) return true;
    if (this-> board[0][0] != 0 &&this-> board[0][0] == this-> board[1][0] && this-> board[1][0] == this-> board[2][0]) return true;
    if (this-> board[0][0] != 0 &&this-> board[0][0] == this-> board[1][2] && this-> board[1][2] == this-> board[2][4]) return true;


    if (this-> board[0][0] != 0 && this-> board[1][0] == this-> board[0][0] && this-> board[2][0] == this-> board[0][0]) return true;
    if (this-> board[0][0] != 0 && this-> board[1][2] == this-> board[0][0] && this-> board[2][4] == this-> board[0][0]) return true;


    return false;
}

template <typename T>
bool Pyramid_Board<T>::is_draw() {return this->n_moves == 9 && !is_win();}

template <typename T>
bool Pyramid_Board<T>::game_is_over() {return is_win() || is_draw();}

template <typename T>
Pyramid_Player<T>::Pyramid_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Pyramid_Player<T>::getmove(int& x, int& y) {
    cout << this->name << ", Please enter your row from(0 : 2): " << endl;
    cin >> x;
    cout << endl;
    cout << this->name << ", Please enter your column: " << endl;
    cin >> y;
}

template <typename T>
Pyramid_Random_Player<T>::Pyramid_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Pyramid_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % (2 * x + 1);
}

#endif //_PYRAMID_TIC_TAC_TOE_H
