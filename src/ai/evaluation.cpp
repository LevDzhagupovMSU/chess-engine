#include "board.h"
#include "piece.h"
#include "types.h"

#include <vector>
#include <unordered_map>


int ChessBoard :: evaluatePosition(Color perspective) const {
    int score = 0;
    // Оценка материала и позионной структуры
    for(const auto& piece : this->pieces){
        if(piece){
            int sgn = (piece->color == perspective) ? 1 : -1, index = Index(piece->row, piece->col);
            if (piece->color == black) {
                int row = piece->row;
                int col = piece->col;
                index = (7 - row) * 8 + col;  // зеркальное отражение
            }
            if(dynamic_cast<Pawn*>(piece.get())){
                score += PAWN_PST[index] * sgn;
                score += piece->price * sgn; 
                continue;
            }
            if(dynamic_cast<Knight*>(piece.get())){
                score += KNIGHT_PST[index] * sgn;
                score += piece->price * sgn; 
                continue;
            }
            if(dynamic_cast<Bishop*>(piece.get())){
                score += BISHOP_PST[index] * sgn;
                score += piece->price * sgn; 
                continue;
            }
            if(dynamic_cast<Rook*>(piece.get())) {
                score += ROOK_PST[index] * sgn;
                score += piece->price * sgn; 
                continue;
            }
            if(dynamic_cast<Queen*>(piece.get())){
                score += QUEEN_PST[index] * sgn;
                score += piece->price * sgn; 
                continue;
            }
            if(dynamic_cast<King*>(piece.get())){
                score += KING_PST[index] * sgn;
                score += piece->price * sgn; 
                continue;
            }
        }
    }
    // Оценка мобильности текущей позиции
    int white_mobility = 0, black_mobility = 0;
    for(const auto& piece : this->pieces){
        if(piece){
            int mobility = piece->FINDPOSSIBLEMOVES(*this).size();
            if(piece->color == white) white_mobility += mobility;
            else black_mobility += mobility;
        }
    }
    score += (perspective == white) ? (white_mobility - black_mobility) * 5 : (black_mobility - white_mobility) * 5;
    // Защита и атака фигур
    for(const auto& check_piece : pieces){
        if (!check_piece) continue;
        int attackers = 0; int defenders = 0;
        for(const auto& piece : pieces){
            if (!piece) continue;
            if(piece && piece->ISPOSSIBLEMOVE(check_piece->row,check_piece->col, *this)){
                if(piece->color != check_piece->color) attackers++;
                else defenders++;
            }
        }
        int delta = 0;
        if(attackers > defenders) delta -= check_piece->price/2;
        else if(attackers == defenders) delta -= 20;
        else delta += check_piece->price/4;
        if(check_piece->color == perspective){
            score += delta;
        }
        else score -= delta;
    }
    // Развитие в дебюте
    if(this->moves_record.size() < 20){
        std::unordered_map<int, int> piecePath; 
        int whiteDev = 0, blackDev = 0;
        for (const auto& rec : moves_record) {
            int moveCount = piecePath[rec.from_index] + 1;
            piecePath[rec.to_index] = moveCount; 
            if (moveCount == 1) {
                if (dynamic_cast<Knight*>(rec.piece.get()) || dynamic_cast<Bishop*>(rec.piece.get()))
                    (rec.color == white) ? whiteDev += 150 : blackDev += 150;
                else if (dynamic_cast<Pawn*>(rec.piece.get()))
                    (rec.color == white) ? whiteDev += 100 : blackDev += 100;
            } 
            else {
                int penalty = (moveCount - 1) * 50;
                (rec.color == white) ? whiteDev -= penalty : blackDev -= penalty;
            }
        }
        score += (whiteDev - blackDev);
    }
    return score;
}



const int PAWN_PST[NUM_SQUARES] = {
    0,   0,   0,   0,   0,   0,   0,   0,
    3,   7,   6,  12,   8,  10,   7,   3,
    14,  22,  32,  41,  44,  49,  33,  15,
    46,  78, 125, 288, 169,  75,  58,  38,
    100,119, 205, 336, 210, 110,  78,  85,
    112,119, 101,  32,  81,  91, 185, 147,
    55,  69,  93, 141, 102,  67,  72,  57,
    0,   0,   0,   0,   0,   0,   0,   0
};

const int KNIGHT_PST[NUM_SQUARES] = {
    290,	300,	300,	300,	300,	300,	300,	290,
    300,	305,	305,	305,	305,	305,	305,	300,
    300,	305,	325,	325,	325,	325,	305,	300,
    300,	305,	325,	325,	325,	325,	305,	300,
    300,	305,	325,	325,	325,	325,	305,	300,
    300,	305,	320,	325,	325,	325,	305,	300,
    300,	305,	305,	305,	305,	305,	305,	300,
    290,	310,	300,	300,	300,	300,	310,	290
};

const int BISHOP_PST[NUM_SQUARES] = {
    320,	320,	320,	320,	320,	320,	320,	320,
    322,	322,	322,	322,	322,	322,	322,	322,
    320,	322,	325,	325,	325,	325,	322,	320,
    320,	325,	330,	330,	330,	330,	325,	320,
    320,	330,	330,	330,	330,	330,	330,	320,
    320,	325,	325,	325,	325,	325,	325,	320,
    320,	320,	320,	320,	320,	320,	320,	320,
    320,	320,	320,	320,	320,	320,	320,	320
};

const int ROOK_PST[NUM_SQUARES] = {
	500,	500,	500,	500,	500,	500,	500,	500,
	520,	520,	520,	520,	520,	520,	520,	520,
	500,	500,	500,	500,	500,	500,	500,	500,
	500,	500,	500,	500,	500,	500,	500,	500,
	500,	500,	500,	500,	500,	500,	500,	500,
	500,	500,	500,	500,	500,	500,	500,	500,
	500,	500,	500,	500,	500,	500,	500,	500,
	500,	500,	500,	510,	510,	505,	500,	500
};

const int QUEEN_PST[NUM_SQUARES] = {
	980,	980,	990,	1000,	1000,	990,	980,	980,
	980,	990,	1000,	1010,	1010,	1000,	990,	980,
	990,	1000,	1010,	1020,	1020,	1010,	1000,	990,
	1000,	1010,	1020,	1030,	1030,	1020,	1010,	1000,
	1000,	1010,	1020,	1030,	1030,	1020,	1010,	1000,
	990,	1000,	1010,	1020,	1020,	1010,	1000,	990,
	980,	990,	1000,	1010,	1010,	1000,	990,	980,
	980,	980,	990,	1000,	1000,	990,	980,	980
};

const int KING_PST[NUM_SQUARES] = {
	-95,	-95,	-90,	-90,	-90,	-90,	-95,	-95,
	-95,	-50,	-50,	-50,	-50,	-50,	-50,	-95,
	-90,	-50,	-20,	-20,	-20,	-20,	-50,	-90,
	-90,	-50,	-20,	0,	    0,	    -20,	-50,	-90,
	-90,	-50,	-20,	0,	    0,	    -20,	-50,	-90,
	-90,	-50,	-20,	-20,	-20,    -20,	-50,	-90,
	-95,	-50,	-50,	-50,	-50,	-50,	-50,	-95,
	-95,	-95,	-90,	-90,	-90,	-90,	-95,	-95
};