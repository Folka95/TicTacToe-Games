#ifndef _WORD_MINMAX_PLAYER_H
#define _WORD_MINMAX_PLAYER_H

template <typename T>
class Word_MinMax_Player : public Player<T> {
    unordered_set<string> dictionary;
    vector<T> allSymbols;

    int calculateMinMax(T symbol, bool isMaximizing);
    pair<int, int> getBestMove(T symbol);
    bool isWinningMove(int x, int y, T symbol);
    bool tryRandomMove(int& x, int& y);
    bool isWordFormed();
    std::vector<string> getLines();

public:
    Word_MinMax_Player(T symbol);
    Word_MinMax_Player(T symbol, const string filename);
    ~Word_MinMax_Player();
    void getmove(int& x, int& y) override;
};

template <typename T>
Word_MinMax_Player<T>::Word_MinMax_Player(T symbol)
: Player<T>(symbol){
    this->name = "AI Player";
    for (char c = 'A'; c <= 'Z'; c++) allSymbols.push_back(c);
    allSymbols.push_back(0);
}

template <typename T>
Word_MinMax_Player<T>::Word_MinMax_Player(T symbol, const string filename) : Player<T>(symbol){
    this->name = "AI Player";
    for (char c = 'A'; c <= 'Z'; c++) allSymbols.push_back(c);
    allSymbols.push_back(0);
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open dictionary file!" << endl;
        exit(1);
    }
    string word;
    while (file >> word) {
        for(auto &c : word) {
            c = toupper(c);
        }
        dictionary.insert(word);
    }
    file.close();
}

template <typename T>
void Word_MinMax_Player<T>::getmove(int& x, int& y) {

    srand(static_cast<unsigned>(time(0)));
    this->symbol = 'A' + rand() % 26;
    auto bestMove = getBestMove(this->symbol);
    x = bestMove.first;
    y = bestMove.second;
}

template <typename T>
int Word_MinMax_Player<T>::calculateMinMax(T symbol,bool isMaximizing) {
    if (this->boardPtr->is_win()) return isMaximizing ? -1 : 1;
    if (this->boardPtr->is_draw()) return 0;

    int bestValue = isMaximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (this->boardPtr->update_board(i, j,  symbol)) {
                int value = calculateMinMax(symbol,!isMaximizing);
                this->boardPtr->update_board(i, j, 0);
                if (isMaximizing) bestValue = max(bestValue, value);
                else bestValue = min(bestValue, value);

            }
        }
    }

    return bestValue;
}

template <typename T>
std::pair<int, int> Word_MinMax_Player<T>::getBestMove(T symbol) {
    int bestValue = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (this->boardPtr->update_board(i, j, symbol)) {
                int moveValue = calculateMinMax(symbol,false);
                this->boardPtr->update_board(i, j, 0);
                if (moveValue > bestValue) {
                    bestValue = moveValue;
                    bestMove = {i, j};
                }
            }
        }
    }

    return bestMove;
}


template <typename T>
bool Word_MinMax_Player<T>::isWinningMove(int x, int y, T symbol) {
    this->boardPtr->update_board(x, y, symbol);
    bool isWin = isWordFormed();
    this->boardPtr->update_board(x, y, 0);
    return isWin;
}


template <typename T>
bool Word_MinMax_Player<T>::isWordFormed() {
    vector<string> lines = getLines();
    for (const auto& line : lines)
        if (dictionary.find(line) != dictionary.end()) {return true;}

    return false;
}


template <typename T>
vector<string> Word_MinMax_Player<T>::getLines() {return this->boardPtr->get_lines();}

#endif // _WORD_MINMAX_PLAYER_H
