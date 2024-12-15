#ifndef INC_5X5TICTACTOE_H
#define INC_5X5TICTACTOE_H
#define inRange(x , l , r) (l <= x && x <= r)

// <-- Header --> //

template < typename DataType >
class _5x5TicTacToe_Board : public Board< DataType > {
    char Empty = ' ';
    vector< pair< pair< int , int > , pair< int , int > > > winPatterns;
    int calculateScore(char tar);
    pair< char , char > getSymbols();
public:
    _5x5TicTacToe_Board ();
    bool update_board (int x , int y , DataType symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    bool isWinner(char c);
};


template < typename DataType >
class _5x5TicTacToe_Player : public Player< DataType > {
public:
    _5x5TicTacToe_Player (string name, DataType symbol);
    void getmove(int& x, int& y) ;
};


template < typename DataType >
class _5x5TicTacToe_Random_Player : public RandomPlayer< DataType >{
public:
    _5x5TicTacToe_Random_Player (DataType symbol);
    void getmove(int &x, int &y) ;
};


template <typename DataType>
class _5x5TicTacToe_AI_Player : public RandomPlayer< DataType > {
private:
    pair< int , int > getBestMove();
    int minMax(auto &myBoard, char me, char opp, bool isMaximizing);
    pair< char , char > getSymbols();
public:
    _5x5TicTacToe_AI_Player(DataType symbol);
    void getmove(int &x, int &y);

};


// <-- Implementation --> //

template< typename DataType >
_5x5TicTacToe_Board< DataType >::_5x5TicTacToe_Board() {
    Empty = ' ';
    winPatterns = {
    { {0 , -1} , {0 , 1} },
    { {-1 , 0} , {1 , 0} },
    { {-1 , -1} , {1 , 1} },
    { {1 , -1} , {-1 , 1} },
    };
    this->rows = this->columns = 5;
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
bool _5x5TicTacToe_Board< DataType >::update_board(int r, int c, DataType symbol) {
    if(inRange(r , 1 , this->rows) && inRange(c , 1 , this->columns)) {
        if(Empty == (this->board)[r][c]) {
            (this->board)[r][c] = toupper(symbol);
            (this->n_moves)++;
            return true;
        }
        else if(symbol == Empty) {
            (this->board)[r][c] = Empty;
            (this->n_moves)--;
            return true;
        }
    }
    return false;
}

template< typename DataType >
void _5x5TicTacToe_Board< DataType >::display_board() {
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
        cout << string(5 * 5 + 5 + 1 , '-') << endl;
    }
    cout << endl;
}

template< typename DataType >
int _5x5TicTacToe_Board< DataType >::calculateScore(char tar) {
    int ans = 0;
    for(int i = 1; i <= this->rows; i++) {
        for(int j = 1; j <= this->columns; j++) {
            if((this->board)[i][j] != tar)
                continue;
            for(auto &[cell1 , cell2] : winPatterns) {
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
                    ans += (this->board)[i][j] == (this->board)[x1][y1] && (this->board)[i][j] == (this->board)[x2][y2];
                   }
            }
        }
    }
    return ans;
}

template< typename DataType >
pair< char , char > _5x5TicTacToe_Board< DataType >::getSymbols() {
    char p1 = Empty;
    char p2 = Empty;
    for(int i = 1; i <= this->rows; i++) {
        for(int j = 1; j <= this->columns; j++) {
            if( (this->board)[i][j] != Empty ) {
                if( (this->board)[i][j] != p1 ) {
                    p1 = (this->board)[i][j];
                }
                else {
                    p2 = (this->board)[i][j];
                    break;
                }
            }
        }
    }
    return { p1 , p2 };
}

template< typename DataType >
bool _5x5TicTacToe_Board< DataType >::isWinner(char c) {
    if(this->n_moves != this->rows * this->columns - 1)
        return false;
    auto [p1 , p2] = getSymbols();
    if(p1 == c) {
        return calculateScore(p1) < calculateScore(p2);
    }
    else {
        return calculateScore(p2) < calculateScore(p1);
    }
}

template< typename DataType >
bool _5x5TicTacToe_Board< DataType >::is_win() {
    return false;
}

template< typename DataType >
bool _5x5TicTacToe_Board< DataType >::is_draw() {
    return false;
}

template< typename DataType >
bool _5x5TicTacToe_Board< DataType >::game_is_over() {
    return (24 == this->n_moves);
}










template< typename DataType >
_5x5TicTacToe_Player< DataType >::_5x5TicTacToe_Player(string name, DataType symbol) : Player< DataType >(name, symbol){}

template< typename DataType >
void _5x5TicTacToe_Player< DataType >::getmove(int &x, int &y) {
    inputValidator input;
    cout << "Please, enter a valid empty cell from 1 to 25: ";
    int idx = input.readRangeChoice(1 , 25);
    y = idx % 5 == 0 ? 5 : idx % 5;
    x = (idx + 4) / 5;
}





template < typename DataType >
_5x5TicTacToe_Random_Player< DataType >::_5x5TicTacToe_Random_Player(DataType symbol) : RandomPlayer< DataType >(symbol){
    this->name = "Random Computer player " + symbol;
    this->dimension = 5;
}

template < typename DataType >
void _5x5TicTacToe_Random_Player< DataType >::getmove(int &x, int &y) {
    y = rand() % (this->dimension) + 1;
    x = rand() % (this->dimension) + 1;
}





template < typename DataType >
_5x5TicTacToe_AI_Player< DataType >::_5x5TicTacToe_AI_Player(DataType symbol) : RandomPlayer< DataType >(symbol){
    this->name = "AI Computer player " + symbol;
    this->dimension = 5;
}

template < typename DataType >
pair< char , char > _5x5TicTacToe_AI_Player< DataType >::getSymbols() {
    return {'X' , 'O'};
}

template < typename DataType >
int _5x5TicTacToe_AI_Player< DataType >::minMax(auto &myBoard, char me, char opp, bool isMaximizing) {
    if(this->boardPtr->is_win()) {
        return (isMaximizing ? -1 : 1);
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
pair< int , int > _5x5TicTacToe_AI_Player< DataType >::getBestMove() {
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
void _5x5TicTacToe_AI_Player< DataType >::getmove(int &x, int &y) {
    auto [xx , yy] = getBestMove();
    x = xx;
    y = yy;
}


#endif //INC_5X5TICTACTOE_H