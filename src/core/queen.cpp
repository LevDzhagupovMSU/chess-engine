#include "piece.h"
#include "board.h"
#include "types.h"

using namespace std;

Queen :: Queen(int row_, int col_, int price_, Color _color){
    this->row = row_;
    this->col = col_;
    this->price = price_;
    this->color = _color;
}

bool Queen :: ISPOSSIBLEMOVE(int to_row, int to_col, const ChessBoard& board) const{
    if(to_row < 0 || to_row >= 8 || to_col < 0 || to_col >= 8) return false;
    if(board.pieces[board.Index(to_row, to_col)] != nullptr && board.pieces[board.Index(to_row, to_col)]->color == this->color) return false;
    if(abs(to_row - this->row) == abs(to_col - this->col)){
        int checkRow = (to_row > this->row) ? 1: -1;
        int checkCol = (to_col > this->col) ? 1: -1;
        int diff = abs(to_row - this->row);
        for(int i = 1; i < diff; i++){
            if(board.pieces[board.Index(this->row + checkRow*i, this->col + checkCol*i)] != nullptr) return false;
        }
        return true;
    }
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

string Queen :: getSymbol() const {
    if(this->color == white) return "WQ";
    return "BQ";
}

unique_ptr<Piece> Queen :: clone() const{
    return make_unique<Queen>(this->row, this->col, this->price, this->color);
}