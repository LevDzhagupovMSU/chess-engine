#include "board.h"
#include "piece.h"
#include "history.h"
#include "types.h"

#include <vector>
#include <memory>
#include <iostream>
#include <string>

ChessBoard :: ChessBoard(){
    pieces.resize(NUM_SQUARES);
    
    pieces[0] = std::make_unique<Rook>(0, 0, 500, black);    
    pieces[1] = std::make_unique<Knight>(0, 1,320, black);  
    pieces[2] = std::make_unique<Bishop>(0, 2,330, black);  
    pieces[3] = std::make_unique<Queen>(0, 3, 900, black);   
    pieces[4] = std::make_unique<King>(0, 4, 50000, black);    
    pieces[5] = std::make_unique<Bishop>(0, 5, 330, black);  
    pieces[6] = std::make_unique<Knight>(0, 6, 320, black); 
    pieces[7] = std::make_unique<Rook>(0, 7, 500, black);    
    
    for(int col = 0; col < BOARD_SIZE; col++) {
        pieces[BOARD_SIZE + col] = std::make_unique<Pawn>(1, col, 100, black);
    }

    for(int col = 0; col < BOARD_SIZE; col++) {
        pieces[48 + col] = std::make_unique<Pawn>(6, col, 100, white);
    }
    
    pieces[56] = std::make_unique<Rook>(7, 0, 500, white);  
    pieces[57] = std::make_unique<Knight>(7, 1, 320, white); 
    pieces[58] = std::make_unique<Bishop>(7, 2, 330, white); 
    pieces[59] = std::make_unique<Queen>(7, 3, 900, white);  
    pieces[60] = std::make_unique<King>(7, 4, 50000, white);   
    pieces[61] = std::make_unique<Bishop>(7, 5, 330, white); 
    pieces[62] = std::make_unique<Knight>(7, 6, 320, white); 
    pieces[63] = std::make_unique<Rook>(7, 7, 500, white);
    
    this->white_kingIndex = Index(7, 4);
    this->black_kingIndex = Index(0, 4);

}

ChessBoard :: ChessBoard(const ChessBoard& board){
    this->pieces.resize(NUM_SQUARES);
    for(int k = 0; k < NUM_SQUARES; k++){
        if (board.pieces[k]) this->pieces[k] = board.pieces[k]->clone();
    }
    for(const auto& move_record : board.moves_record){
        this->moves_record.push_back(History(move_record.piece->clone(), 
        move_record.from_index, 
        move_record.to_index, 
        move_record.color));
    }
    this->white_kingIndex = board.white_kingIndex;
    this->black_kingIndex = board.black_kingIndex;
}

void ChessBoard :: setPiece(int _row, int _col, std::unique_ptr<Piece> piece){
    pieces[Index(_row, _col)] = std::move(piece);
}   

int ChessBoard :: Index(int row, int col) const{
    return BOARD_SIZE*row + col;
}

Piece* ChessBoard :: getPiece(int _row, int _col){
    return pieces[Index(_row, _col)].get();
}

void ChessBoard :: display(){
    std::string razdel = "  +----+----+----+----+----+----+----+----+";
    std::cout << std::endl << razdel << std::endl;
    for(int row = 0; row < BOARD_SIZE; row++){
        std::cout << BOARD_SIZE - row << " | ";
        for(int col = 0; col < BOARD_SIZE; col++){
            if(pieces[Index(row, col)] == nullptr){
                std::cout << "  " << " | ";
                continue;
            }
            std::cout << pieces[Index(row, col)]->getSymbol() << " | ";
        }
        std::cout << std::endl << razdel << std::endl;
    }
    std::cout << "    a    b    c    d    e    f    g    h" << std::endl;
}