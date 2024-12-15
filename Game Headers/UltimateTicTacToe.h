#ifndef ULTIMATETICTACTOE_H
#define ULTIMATETICTACTOE_H



// <-- Header --> //

template < typename DataType >
class _UltimateTicTacToe_Board : public Board< DataType > {
    char Empty = ' ';
    DataType solveSubGrid(int i, int j);
public:
    _UltimateTicTacToe_Board ();
    bool update_board (int x , int y , DataType symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};


template < typename DataType >
class _UltimateTicTacToe_Player : public Player< DataType > {
public:
    _UltimateTicTacToe_Player (string name, DataType symbol);
    void getmove(int& x, int& y) ;
};


template < typename DataType >
class _UltimateTicTacToe_Random_Player : public RandomPlayer< DataType >{
public:
    _UltimateTicTacToe_Random_Player (DataType symbol);
    void getmove(int &x, int &y) ;
};



// <-- Implementation --> //

template < typename DataType >
_UltimateTicTacToe_Board< DataType >::_UltimateTicTacToe_Board() {
    Empty = ' ';
    this->rows = this->columns = 9;
    this->board = new char*[ this->rows + 1 ];
    for(int i = 1; i <= this->rows; i++) {
        (this->board)[i] = new char[ this->columns + 1 ];
        for(int j = 1; j <= this->columns; j++) {
            (this->board)[i][j] = Empty;
        }
    }
    this->n_moves = 0;
}

template< typename DataType >
bool _UltimateTicTacToe_Board< DataType >::update_board(int r, int c, DataType symbol) {
    if(inRange(r , 1 , this->rows) && inRange(c , 1 , this->columns)) {
        if(Empty == (this->board)[r][c]) {
            if(this->solveSubGrid( (r - 1) / 3 , (c - 1) / 3 ) == Empty) {
                (this->board)[r][c] = toupper(symbol);
                (this->n_moves)++;
                return true;
            }
        }
        else if(Empty == symbol) {
            (this->board)[r][c] = toupper(symbol);
            (this->n_moves)--;
            return true;
        }
    }
    return false;
}


template< typename DataType >
void _UltimateTicTacToe_Board< DataType >::display_board() {
    cout << endl;
    for(int i = 1; i <= this->rows; i++) {
        for(int j = 1; j <= this->columns; j++) {
            if((this->board)[i][j] != Empty) {
                cout << (j % 3 == 1 ? " | " : "|") << setw(3) << setfill(' ');
                cout << (this->board)[i][j] << "  ";
            }
            else {
                cout << (j % 3 == 1 ? " | " : "|") << setw(3) << setfill(' ') << (i - 1) * this->columns + j << "  ";
            }
        }
        cout << "|" << endl;
        cout << string(9 * 7 - 2 , '-') << endl;
    }
    cout << endl;
}

template< typename DataType >
DataType _UltimateTicTacToe_Board< DataType >::solveSubGrid(int x, int y) {
    x *= 3;
    y *= 3;
    for(int i = 1; i <= 3; i++) {
        if(this->board[i + x][1 + y] == this->board[i + x][2 + y] && this->board[i + x][2 + y] == this->board[i + x][3 + y] && this->board[i + x][1 + y] != Empty) {
            return this->board[i + x][1 + y];
        }
        if(this->board[1 + x][i + y] == this->board[2 + x][i + y] && this->board[2 + x][i + y] == this->board[3 + x][i + y] && this->board[1 + x][i + y] != Empty) {
            return this->board[1 + x][i + y];
        }
    }
    if(this->board[1 + x][1 + y] == this->board[2 + x][2 + y] && this->board[2 + x][2 + y] == this->board[3 + x][3 + y] && this->board[3 + x][3 + y] != Empty) {
        return this->board[1 + x][1 + y];
    }
    if(this->board[1 + x][3 + y] == this->board[2 + x][2 + y] && this->board[2 + x][2 + y] == this->board[3 + x][1 + y] && this->board[2 + x][2 + y] != Empty) {
        return this->board[1 + x][3 + y];
    }
    return Empty;
}

template< typename DataType >
bool _UltimateTicTacToe_Board< DataType >::is_win() {
    DataType summary[4][4];
    for(int i = 1; i <= 3; i++) {
        for(int j = 1; j <= 3; j++) {
            summary[i][j] = solveSubGrid(i - 1 , j - 1);
        }
    }
    for(int i = 1; i <= 3; i++) {
        if(summary[i][1] == summary[i][2] && summary[i][2] == summary[i][3] && summary[i][1] != Empty) {
            return true;
        }
        if(summary[1][i] == summary[2][i] && summary[2][i] == summary[3][i] && summary[1][i] != Empty) {
            return true;
        }
    }
    if(summary[1][1] == summary[2][2] && summary[3][3] == summary[2][2] && summary[2][2] != Empty) {
        return true;
    }
    if(summary[1][3] == summary[2][2] && summary[2][2] == summary[3][1] && summary[2][2] != Empty) {
        return true;
    }
    return false;
}

template< typename DataType >
bool _UltimateTicTacToe_Board< DataType >::is_draw() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(this->solveSubGrid(i , j) == Empty) {
                return false;
            }
        }
    }
    return true;
}

template< typename DataType >
bool _UltimateTicTacToe_Board< DataType >::game_is_over() {
    return is_win() || is_draw();
}


template< typename DataType >
_UltimateTicTacToe_Player< DataType >::_UltimateTicTacToe_Player(string name, DataType symbol) : Player< DataType >(name, symbol){}

template< typename DataType >
void _UltimateTicTacToe_Player< DataType >::getmove(int &x, int &y) {
    inputValidator input;
    cout << "Please, enter a valid empty cell from 1 to 81: ";
    int idx = input.readRangeChoice(1 , 81);
    y = idx % 9 == 0 ? 9 : idx % 9;
    x = (idx + 8) / 9;
}


template < typename DataType >
_UltimateTicTacToe_Random_Player< DataType >::_UltimateTicTacToe_Random_Player(DataType symbol) : RandomPlayer< DataType >(symbol){
    this->name = "Random Computer player ";
    this->name += symbol;
    this->dimension = 9;
}

template < typename DataType >
void _UltimateTicTacToe_Random_Player< DataType >::getmove(int &x, int &y) {
    auto next = [](int l, int r) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<long long> distr(l , r);
        return distr(gen);
    };
    y = next(1 , this->dimension);
    x = next(1 , this->dimension);
}

#endif //ULTIMATETICTACTOE_H
