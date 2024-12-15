#ifndef MISERETICTACTOE_H
#define MISERETICTACTOE_H


// <-- Header --> //

template < typename DataType >
class _MisereTicTacToe_Board : public Board< DataType > {
    char Empty = ' ';
    vector< pair< pair< int , int > , pair< int , int > > > lossPatterns;
public:
    _MisereTicTacToe_Board ();
    bool update_board (int x , int y , DataType symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};


template < typename DataType >
class _MisereTicTacToe_Player : public Player< DataType > {
public:
    _MisereTicTacToe_Player (string name, DataType symbol);
    void getmove(int& x, int& y) ;
};


template < typename DataType >
class _MisereTicTacToe_Random_Player : public RandomPlayer< DataType >{
public:
    _MisereTicTacToe_Random_Player (DataType symbol);
    void getmove(int &x, int &y) ;
};


template <typename DataType>
class _MisereTicTacToe_AI_Player : public RandomPlayer< DataType > {
public:
    _MisereTicTacToe_AI_Player(DataType symbol);
    void getmove(int &x, int &y);
};


// <-- Implementation --> //

template < typename DataType >
_MisereTicTacToe_Board< DataType >::_MisereTicTacToe_Board() {
    Empty = ' ';
    lossPatterns = {
        { {0 , -1} , {0 , 1} },
        { {-1 , 0} , {1 , 0} },
        { {-1 , -1} , {1 , 1} },
        { {1 , -1} , {-1 , 1} },
        };
    this->rows = this->columns = 3;
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
bool _MisereTicTacToe_Board< DataType >::update_board(int r, int c, DataType symbol) {
    if(inRange(r , 1 , this->rows) && inRange(c , 1 , this->columns)) {
        if(Empty == (this->board)[r][c]) {
            (this->board)[r][c] = toupper(symbol);
            (this->n_moves)++;
            return true;
        }
    }
    return false;
}

template< typename DataType >
void _MisereTicTacToe_Board< DataType >::display_board() {
    cout << endl;
    for(int i = 1; i <= this->rows; i++) {
        for(int j = 1; j <= this->columns; j++) {
            if((this->board)[i][j] != Empty) {
                cout << "|" << setw(3) << setfill(' ');
                cout << (this->board)[i][j] << "  ";
            }
            else {
                cout << "|" << setw(3) << setfill(' ') << (i - 1) * this->columns + j << "  ";
            }
        }
        cout << "|" << endl;
        cout << string(3 * 3 + 3 + 1 , '-') << endl;
    }
    cout << endl;
}


template< typename DataType >
bool _MisereTicTacToe_Board< DataType >::is_win() {
    for(int i = 1; i <= this->rows; i++) {
        for(int j = 1; j <= this->columns; j++) {
            if(this->board[i][j] == Empty)
                continue;
            for(auto &[cell1 , cell2] : lossPatterns) {
                auto [dx1 , dy1] = cell1;
                auto [dx2 , dy2] = cell2;
                int x1 = i + dx1;
                int y1 = j + dy1;
                int x2 = i + dx2;
                int y2 = j + dy2;
                if(inRange(x1 , 1 , this->rows) &&
                   inRange(y1 , 1 , this->columns) &&
                   inRange(x2 , 1 , this->rows) &&
                   inRange(y2 , 1 , this->columns) ) {
                    if(this->board[i][j] == this->board[x1][y1] && this->board[i][j] == this->board[x2][y2])
                        return true;
                   }
            }
        }
    }
    return false;
}

template< typename DataType >
bool _MisereTicTacToe_Board< DataType >::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template< typename DataType >
bool _MisereTicTacToe_Board< DataType >::game_is_over() {
    return is_win() || is_draw();
}




template< typename DataType >
_MisereTicTacToe_Player< DataType >::_MisereTicTacToe_Player(string name, DataType symbol) : Player< DataType >(name, symbol){}

template< typename DataType >
void _MisereTicTacToe_Player< DataType >::getmove(int &x, int &y) {
    inputValidator input;
    cout << "Please, enter a valid empty cell from 1 to 9: ";
    int idx = input.readRangeChoice(1 , 9);
    y = idx % 3 == 0 ? 3 : idx % 3;
    x = (idx + 2) / 3;
}





template < typename DataType >
_MisereTicTacToe_Random_Player< DataType >::_MisereTicTacToe_Random_Player(DataType symbol) : RandomPlayer< DataType >(symbol){
    this->name = "Random Computer player " + symbol;
    this->dimension = 3;
}

template < typename DataType >
void _MisereTicTacToe_Random_Player< DataType >::getmove(int &x, int &y) {
    y = rand() % (this->dimension) + 1;
    x = rand() % (this->dimension) + 1;
}





template < typename DataType >
_MisereTicTacToe_AI_Player< DataType >::_MisereTicTacToe_AI_Player(DataType symbol) : RandomPlayer< DataType >(symbol){
    this->name = "AI Computer player " + symbol;
    this->dimension = 3;
}

template < typename DataType >
void _MisereTicTacToe_AI_Player< DataType >::getmove(int &x, int &y) {
    y = rand() % (this->dimension) + 1;
    x = rand() % (this->dimension) + 1;
}


#endif //MISERETICTACTOE_H
