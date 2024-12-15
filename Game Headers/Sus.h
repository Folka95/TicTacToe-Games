#ifndef SUS_H
#define SUS_H


// <-- Header --> //

template < typename DataType >
class _Sus_Board : public Board< DataType > {
    char Empty = ' ';
    vector< pair< pair< int , int > , pair< int , int > > > winPatterns;
    int p1Score, p2Score;
    bool firstPass;
    pair< char , char > getSymbols();
    bool getPoint(int i, int j);
public:
    _Sus_Board ();
    bool update_board (int x , int y , DataType symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    bool isWinner(char c);
    int getN_moves();
};


template < typename DataType >
class _Sus_Player : public Player< DataType > {
public:
    _Sus_Player (string name, DataType symbol);
    void getmove(int& x, int& y) ;
};


template < typename DataType >
class _Sus_Random_Player : public RandomPlayer< DataType >{
public:
    _Sus_Random_Player (DataType symbol);
    void getmove(int &x, int &y) ;
};

// <-- Implementation --> //

template<typename DataType>
bool _Sus_Board< DataType >::getPoint(int x, int y) {
    int cnt = 0;
    for(int i = 1; i <= this->rows; i++) {
        if( x == i &&
            this->board[i][1] == 'S' &&
            this->board[i][2] == 'U' &&
            this->board[i][3] == 'S' ) {
            cnt++;
            }
    }
    for(int j = 1; j <= this->columns; j++) {
        if( y == j &&
           this->board[1][j] == 'S' &&
           this->board[2][j] == 'U' &&
           this->board[3][j] == 'S' ) {
            cnt++;
           }
    }
    if( y == x &&
       this->board[1][1] == 'S' &&
       this->board[2][2] == 'U' &&
       this->board[3][3] == 'S' ) {
        cnt++;
       }
    if( y + x == 4 &&
        x != y &&
       this->board[1][3] == 'S' &&
       this->board[2][2] == 'U' &&
       this->board[3][1] == 'S' ) {
        cnt++;
       }
    return cnt;
}



template < typename DataType >
_Sus_Board< DataType >::_Sus_Board() {
    Empty = ' ';
    p1Score = p2Score = 0;
    firstPass = false;
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
bool _Sus_Board< DataType >::update_board(int r, int c, DataType symbol) {
    if(this->n_moves == 9) {
        firstPass = true;
        return true;
    }
    if(inRange(r , 1 , this->rows) && inRange(c , 1 , this->columns)) {
        if(Empty == (this->board)[r][c]) {
            (this->n_moves)++;
            (this->board)[r][c] = toupper(symbol);
            if(this->n_moves % 2) {
                p1Score += getPoint(r , c);
            }
            else {
                p2Score += getPoint(r , c);
            }
            if(this->n_moves == 9) {
                if(p1Score > p2Score) {
                    firstPass = true;
                }
            }
            return true;
        }
    }
    return false;
}

template< typename DataType >
void _Sus_Board< DataType >::display_board() {
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
bool _Sus_Board< DataType >::is_win() {
    if(9 == this->n_moves) {
        return firstPass;
    }
    return false;
}

template< typename DataType >
bool _Sus_Board< DataType >::is_draw() {
    return (9 == this->n_moves && p1Score == p2Score);
}

template< typename DataType >
bool _Sus_Board< DataType >::game_is_over() {
    return (9 == this->n_moves);
}

template< typename DataType >
int _Sus_Board< DataType >::getN_moves(){
    return this->n_moves;
}





template < typename DataType >
_Sus_Player< DataType >::_Sus_Player(string name, DataType symbol) : Player< DataType >(name, symbol){}

template<typename DataType>
void _Sus_Player< DataType >::getmove(int &x, int &y) {
    if(this->boardPtr->getN_moves() == 9) {
        return;
    }
    inputValidator input;
    cout << "Please, enter a valid empty cell from 1 to 9: ";
    int idx = input.readRangeChoice(1 , 9);
    y = idx % 3 == 0 ? 3 : idx % 3;
    x = (idx + 2) / 3;
}




template < typename DataType >
_Sus_Random_Player< DataType >::_Sus_Random_Player(DataType symbol) : RandomPlayer< DataType >(symbol) {
    this->name = "Random Computer ";
    this->name += symbol;
}

template<typename DataType>
void _Sus_Random_Player< DataType >::getmove(int &x, int &y) {
    if(this->boardPtr->getN_moves() == 9) {
        return;
    }
    int idx = rand() % 9 + 1;
    y = idx % 3 == 0 ? 3 : idx % 3;
    x = (idx + 2) / 3;
}


#endif //SUS_H
