#include "piece.h"
#include "board.h"
#include "types.h"

using namespace std;

Knight :: Knight(int row_, int col_, int price_, Color _color){
    this->row = row_;
    this->col = col_;
    this->price = price_;
    this->color = _color;
}

bool Knight :: ISPOSSIBLEMOVE(int to_row, int to_col, const ChessBoard& board) const{
    if(to_row < 0 || to_row >= 8 || to_col < 0 || to_col >= 8) return false;
    if(board.pieces[board.Index(to_row, to_col)] == nullptr || board.pieces[board.Index(to_row, to_col)]->color != this->color){
        if(((abs(to_row - this->row) == 2) && (abs(to_col - this->col) == 1))|| 
        ((abs(to_row - this->row)) == 1 && (abs(to_col - this->col) == 2))) 
                            return true;
    }
    return false;
}

string Knight :: getSymbol() const {
    if(this->color == white) return "WN";
    return "BN";
}

unique_ptr<Piece> Knight :: clone() const{
    return make_unique<Knight>(this->row, this->col, this->price, this->color);
}