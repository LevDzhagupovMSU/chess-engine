#include "chess.h"

#include <iostream>
#include <windows.h>

using namespace std;

bool checkMovePlayer(string str);
pair<int, int> parsing(const string& str);
using namespace std;

int main(){
    SetConsoleOutputCP(CP_UTF8);
    string playerColor;
    cout << "Движок игры в шахматы" << endl;
    cout << "Выберите цвет:\n  0 - играть белыми (вы ходите первым)\n  1 - играть чёрными\n> ";
    getline(cin, playerColor);
    const Color player = (playerColor == "1") ? black : white;
    const Color ai_player = (player == white) ? black : white;
    if(player == white && playerColor != "0"){
        cout << "0 - Белые, 1 - Черные";
    }
    cout << "Формат ходов: e2-e4" << endl;
    ChessBoard board;
    board.display();
    while (!board.checkMate){
        if(player == white){
        string playerMove_string;
        cout << "Сделайте ход" << endl;
        getline(cin, playerMove_string);
        if(!checkMovePlayer(playerMove_string)){
            cout << "Неверный Формат Хода!" << endl;
            continue;
        }
        pair<int, int> player_move = parsing(playerMove_string);
        if(!board.pieces[player_move.first]){
            cout << "Нет фигуры на этой клетки" << endl;
            continue;
        }
        if (board.pieces[player_move.first]->color != player) {
            cout << "Это не ваша фигура!" << endl;
            continue;
        }
        if(!(board.pieces[player_move.first]->ISPOSSIBLEMOVE(player_move.second / 8, player_move.second % 8, board))){
            cout << "Нарушение Правил, Невозможнный ход!"<< endl;
            continue;
        }
        if (!board.isLegalMove(player_move))
        {
            cout << "Невозможный ход! (оставляет короля под шахом или нарушает правила)" << endl;
            continue;
        }
        board.pieces[player_move.first]->makeMove(player_move.second, board);
        board.check = board.isCheck(ai_player);
        if(board.check) cout << "Шах!" << endl;
        board.checkMate = board.isCheckMate(ai_player);
        if (board.checkMate) {
            board.display();
            break;
        }
        pair<int, int> ai_move = board.getAiMove(ai_player, 3);
        if (ai_move.first == -1) {
            board.display();
            if (board.checkMate) {
                cout << "Мат! Вы победили!" << endl;
            } else {
                cout << "Пат! Ничья!" << endl;
            }
            break;
        }
        board.pieces[ai_move.first]->makeMove(ai_move.second, board);
        board.check = board.isCheck(player);         
        board.checkMate = board.isCheckMate(player);    
        if (board.checkMate) {
            board.display();
            cout << "Мат! AI победил!" << endl;
            break;
        }
        if (!board.check && !board.hasAnyLegalMove(player)) {
            board.display();
            cout << "Пат! Ничья!" << endl;
            break;
        }
        board.display();
        }
    }
}


bool checkMovePlayer(string str){
    string temp = "abcdefgh";
    if(str.length() != 5) return false;
    pair<size_t, size_t> pos = make_pair(str.find('-'), str.find(' '));
    if(pos.first == string::npos && pos.second == string::npos) return false;
    string from = str.substr(0,2);
    string to = str.substr(3,2);
    if(temp.find(from[0]) == string::npos || temp.find(to[0]) == string::npos) return false;
    if(!(from[1] - '1' >= 0 && from[1] - '1' <= 7) || !(to[1] - '1' >= 0 && to[1] - '1' <= 7)) return false;
    
    return true;
}

pair<int, int> parsing(const string& str) {
    string files = "abcdefgh";
    string from = str.substr(0, 2);
    string to   = str.substr(3, 2);
    size_t from_col = files.find(from[0]);
    size_t to_col   = files.find(to[0]);
    int from_rank_char = from[1] - '1'; 
    int to_rank_char   = to[1]   - '1'; 
    if (from_col == string::npos || to_col == string::npos ||
        from_rank_char < 0 || from_rank_char > 7 ||
        to_rank_char   < 0 || to_rank_char   > 7) {
        return {-1, -1};
    }
    size_t from_row = 7 - from_rank_char; 
    size_t to_row   = 7 - to_rank_char;
    int from_index = static_cast<int>(8 * from_row + from_col);
    int to_index   = static_cast<int>(8 * to_row   + to_col);
    return {from_index, to_index};
}