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
private:
    int minMax(auto &myBoard, char me, char opp, bool isMaximizing);
    pair< int , int > getBestMove();
    pair< char , char > getSymbols();
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
        else if(Empty == symbol) {
            (this->board)[r][c] = toupper(symbol);
            (this->n_moves)--;
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
        cout << string(5 * 3 + 3 + 1 , '-') << endl;
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
    this->name = "Random Computer player ";
    this->name += symbol;
    this->dimension = 3;
}

template < typename DataType >
void _MisereTicTacToe_Random_Player< DataType >::getmove(int &x, int &y) {
    auto next = [](int l, int r) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<long long> distr(l , r);
        return distr(gen);
    };
    y = next(1 , this->dimension);
    x = next(1 , this->dimension);
}





template < typename DataType >
_MisereTicTacToe_AI_Player< DataType >::_MisereTicTacToe_AI_Player(DataType symbol) : RandomPlayer< DataType >(symbol){
    this->name = "AI Computer player " + symbol;
    this->dimension = 3;
}

template < typename DataType >
pair< char , char > _MisereTicTacToe_AI_Player< DataType >::getSymbols() {
    return {'X' , 'O'};
}


template < typename DataType >
int _MisereTicTacToe_AI_Player< DataType >::minMax(auto &myBoard, char me, char opp, bool isMaximizing) {
    if(this->boardPtr->is_win()) {
        return (isMaximizing ? 1 : -1);
    }
    const char Empty = ' ';
    int val = 0;
    for(int i = 1; i <= this->dimension; i++) {
        for(int j = 1; j <= this->dimension; j++) {
            if(this->boardPtr->update_board(i , j , me)) {
                int curVal = minMax(myBoard , opp , me , !isMaximizing);
                if(val == -1) {
                    val = curVal;
                }
                else {
                    if(isMaximizing) {
                        val = max(val , curVal);
                    }
                    else {
                        val = min(val , curVal);
                    }
                }
                this->boardPtr->update_board(i , j , Empty);
            }
        }
    }
    return val;
}


template < typename DataType >
pair< int , int > _MisereTicTacToe_AI_Player< DataType >::getBestMove() {
    auto [me , opp] = getSymbols();
    if(this->getsymbol() == opp) {
        swap(me , opp);
    }
    const char Empty = ' ';
    int maxVal = -1;
    int xx = 1;
    int yy = 1;
    for(int i = 1; i <= this->dimension; i++) {
        for(int j = 1; j <= this->dimension; j++) {
            if(this->boardPtr->update_board(i , j , me)) {
                int curVal = minMax(i, opp , me , false);
                if(maxVal == -1 || maxVal < curVal) {
                    maxVal = curVal;
                    xx = i;
                    yy = j;
                }
                this->boardPtr->update_board(i , j , Empty);
            }
        }
    }
    return {xx , yy};
}


template < typename DataType >
void _MisereTicTacToe_AI_Player< DataType >::getmove(int &x, int &y) {
    auto [xx , yy] = getBestMove();
    x = xx;
    y = yy;
}

#endif //MISERETICTACTOE_H
