#include "piece.h"
#include "board.h"
#include "types.h"

using namespace std;

Bishop :: Bishop(int row_, int col_, int price_, Color _color){
    this->row = row_;
    this->col = col_;
    this->price = price_;
    this->color = _color;
}

bool Bishop :: ISPOSSIBLEMOVE(int to_row, int to_col, const ChessBoard& board) const{
    if(to_row < 0 || to_row >= 8 || to_col < 0 || to_col >= 8) return false;
    if(to_row == row || to_col == col) return false;
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
    return false;
}

string Bishop :: getSymbol() const {
    if(this->color == white) return "WB";
    return "BB";
}

unique_ptr<Piece> Bishop :: clone() const{
    return make_unique<Bishop>(this->row, this->col, this->price, this->color);
}
