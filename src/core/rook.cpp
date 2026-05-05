#include "piece.h"
#include "board.h"
#include "types.h"

using namespace std;

Rook :: Rook(int row_, int col_, int price_, Color _color){
    this->row = row_;
    this->col = col_;
    this->price = price_;
    this->color = _color;
}

bool Rook :: ISPOSSIBLEMOVE(int to_row, int to_col, const ChessBoard& board) const{
    if(to_row < 0 || to_row >= 8 || to_col < 0 || to_col >= 8) return false;
    if(to_row == row && to_col == col) return false;
    if(board.pieces[board.Index(to_row, to_col)] != nullptr && board.pieces[board.Index(to_row, to_col)]->color == color) return false;
    if(to_row == this->row && to_col != this->col){
        int to_index = board.Index(to_row, to_col), index = board.Index(this->row, this->col), direction = (to_index > index) ? 1 : -1;
        for(int i = 1; i < abs(to_index - index); i++){
            if(board.pieces[index + direction*i] != nullptr) return false;
        }
        return true;
    }
    if(to_row != this->row && to_col == this->col){
        int to_index = board.Index(to_row, to_col), index = board.Index(this->row, this->col), direction = (to_index > index) ? 8 : -8;
        for(int i = 1; i < abs(to_index - index)/8; i++){
            if(board.pieces[index + direction*i] != nullptr) return false;
        }
        return true;
    }
    return false;
}

string Rook :: getSymbol() const {
    if(this->color == white) return "WR";
    return "BR";
}

unique_ptr<Piece> Rook :: clone() const{
    return make_unique<Rook>(this->row, this->col, this->price, this->color);
}