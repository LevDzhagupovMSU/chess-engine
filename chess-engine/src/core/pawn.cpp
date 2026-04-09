#include "piece.h"
#include "board.h"
#include "types.h"

using namespace std;

Pawn :: Pawn(int row_, int col_, int price_, Color _color){
    this->row = row_;
    this->col = col_;
    this->price = price_;
    this->color = _color;
}


bool Pawn :: ISPOSSIBLEMOVE(int to_row, int to_col, const ChessBoard& board) const{
    if (to_row < 0 || to_row >= 8 || to_col < 0 || to_col >= 8) return false;
    int direction = (this->color == white) ? -1 : 1;
    int index = board.Index(to_row, to_col);
    if(to_col == this->col && to_row == this->row + direction && board.pieces[index] == nullptr) return true;
    if(to_col == this->col && to_row == this->row + 2*direction && (row == 1 || row == 6) && board.pieces[board.Index(to_row, to_col)] == nullptr){
        if(board.pieces[board.Index(this->row + direction, to_col)] == nullptr) return true;
    }
    if(abs(to_col - this->col) == 1 && to_row == this->row + direction && board.pieces[index] != nullptr){
        if(board.pieces[index]->color != this->color) return true;
    }
    return false;
}


string Pawn :: getSymbol() const {
    if(this->color == white) return "WP";
    return "BP";
}

unique_ptr<Piece> Pawn :: clone() const{
    return make_unique<Pawn>(this->row, this->col, this->price, this->color);
}