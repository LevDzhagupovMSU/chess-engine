#include "piece.h"
#include "board.h"
#include "types.h"

using namespace std;

King :: King(int row_, int col_, int price_, Color _color){
    this->row = row_;
    this->col = col_;
    this->price = price_;
    this->color = _color;
}

bool King :: ISPOSSIBLEMOVE(int to_row, int to_col, const ChessBoard& board) const{
    if(to_row < 0 || to_row >= 8 || to_col < 0 || to_col >= 8) return false;
    if(board.pieces[board.Index(to_row, to_col)] != nullptr && board.pieces[board.Index(to_row, to_col)]->color == this->color) return false;
    if(abs(to_row - this->row) > 1 || abs(to_col - this->col) > 1 || (to_row == this->row && to_col == this->col) ) return false;
    if(to_row - this->row == 0 && abs(to_col - this->col) == 2){ // Проверяем рокировку
        Color _color = board.pieces[board.Index(this->row, this->col)]->color;
        if(board.isCheck(_color)) return false;
        int direction = (to_col - this->col == 2) ? 1 : -1 ; // 1 - прайвая ладья, -1 - левая ладья
        int rook_index = (direction == 1) ? 
        ((_color == white) ? 63 : 7) : 
        ((_color == white) ? 56 : 0);
        int step = (rook_index > board.Index(this->row, this->col)) ? 1 : -1;
        for(int i = board.Index(this->row, this->col) + step; 
            i != rook_index; 
            i += step) {
            if(board.pieces[i] != nullptr) return false;
        }
        return board.isItPossibleToCastle(_color, rook_index);
    }

    return true;
}

string King :: getSymbol() const {
    if(this->color == white) return "WK";
    return "BK";
}

unique_ptr<Piece> King :: clone() const{
    return make_unique<King>(this->row, this->col, this->price, this->color);
}