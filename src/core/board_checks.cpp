#include "board.h"
#include "piece.h"
#include "types.h"

#include <vector>
#include <memory>
#include <algorithm>

bool ChessBoard :: isCheck(Color _color) const{ //Если _color = white, то проверяет на шах для белых
    int kingIndex = (_color == white) ? this->white_kingIndex : this->black_kingIndex;
    for(auto& piece : pieces){
        if(piece && piece->color != _color){
            auto moves = piece->FINDPOSSIBLEMOVES(*this);
            for(auto& move : moves){
                if(move.second == kingIndex){
                    return true;
                }
            }
        }
    }
    return false;
}

bool ChessBoard::isCheckMate(Color _color) {
    if (!isCheck(_color)) { 
        return false;
    }
    return !hasAnyLegalMove(_color);
}

bool ChessBoard::hasAnyLegalMove(Color _color) {
    for(int i = 0; i < NUM_SQUARES; i++) {
        if(pieces[i] && pieces[i]->color == _color) {
            auto moves = pieces[i]->FINDPOSSIBLEMOVES(*this);
            for(const auto& move : moves) {
                ChessBoard temp(*this);
                temp.pieces[move.first]->makeMove(move.second, temp);
                if(!temp.isCheck(_color)) return true;
            }
        }
    }
    return false;
}

bool ChessBoard :: wouldSafeKing(const std::pair<int, int>& move) const{
    if (!pieces[move.first]) return false;         
    Color pieceColor = pieces[move.first]->color; 
    ChessBoard tempBoard(*this);
    tempBoard.pieces[move.first]->makeMove(move.second, tempBoard);
    return !tempBoard.isCheck(pieceColor);
}

bool ChessBoard :: isLegalMove(const std::pair<int, int>& move) const {
    if (!pieces[move.first]) return false;         
    Color pieceColor = pieces[move.first]->color; 
    ChessBoard tempBoard(*this);
    tempBoard.pieces[move.first]->makeMove(move.second, tempBoard);
    return !tempBoard.isCheck(pieceColor);
}

bool ChessBoard :: isItPossibleToCastle(Color _color, int rook_index) const{ // Проверка на рокировку для _color
    for(const auto& move_record : this->moves_record){
        if(move_record.piece->color == _color){
            if(dynamic_cast<King*>(move_record.piece.get())) return false;
            if(move_record.from_index == rook_index) return false;
        }
    }
    return true;
}

bool ChessBoard :: isSquaredAttacked(int index, Color attackerColor) const{
    for(const auto& piece : this->pieces){
        if(piece && piece->color == attackerColor){
        if(piece->ISPOSSIBLEMOVE(index, *this)) {
                return true;
            }
        }
    }
    return false;
}