#include "piece.h"
#include "board.h"
#include "types.h"

#include <iostream>
#include <vector>               
#include <string>
#include <memory>

using namespace std;

Piece :: Piece(){
    col = 0;
    row = 0;
    color = white;
}
Piece :: Piece(Color _color){
    this->color = _color;
}

vector<pair<int, int>> Piece :: FINDPOSSIBLEMOVES(const ChessBoard& board) const{
        vector<pair<int, int>> possibleMoves;
        for(int row_ = 0; row_ < 8; row_++){
            for(int col_ = 0; col_ < 8; col_++){
                if(this->ISPOSSIBLEMOVE(row_, col_, board)) 
                     possibleMoves.push_back(make_pair(board.Index(this->row, this->col), board.Index(row_, col_)));
            }
        }
    return possibleMoves;
}

bool Piece :: ISPOSSIBLEMOVE(int index, const ChessBoard& board) const{
    return ISPOSSIBLEMOVE(index / 8, index % 8, board);
}

void Piece :: makeMove(int to_index, ChessBoard& board){
    auto& piece_ptr = board.pieces[board.Index(this->row, this->col)];
    Color _color = piece_ptr->color;
    if(dynamic_cast<King*>(piece_ptr.get())){
        (piece_ptr->color == white ? board.white_kingIndex : board.black_kingIndex) = to_index;
        if(abs(to_index - board.Index(this->row, this->col)) == 2){
            int direction = (to_index > board.Index(this->row, this->col)) ? 1 : -1;
            int rookFrom, rookTo;
            if(_color == white) {
                rookFrom = (direction == 1) ? 63 : 56;
                rookTo = (direction == 1) ? to_index - 1 : to_index + 1;
            } 
            else {
                rookFrom = (direction == 1) ? 7 : 0;
                rookTo = (direction == 1) ? to_index - 1 : to_index + 1;
            }  
            board.pieces[rookTo] = move(board.pieces[rookFrom]);
            board.pieces[rookFrom] = nullptr;    
            if(board.pieces[rookTo]) {
                board.pieces[rookTo]->row = rookTo / 8;
                board.pieces[rookTo]->col = rookTo % 8;
            }
        }
    }
    board.moves_record.push_back(History(piece_ptr->clone(),board.Index(this->row, this->col), to_index, _color));
    board.pieces[to_index] = move(piece_ptr);
    piece_ptr = nullptr;
    if(board.pieces[to_index]) {
        board.pieces[to_index]->row = to_index/8;
        board.pieces[to_index]->col = to_index%8;
    }
}