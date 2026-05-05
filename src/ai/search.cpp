#include "board.h"
#include "piece.h"

#include <climits>
#include <vector>

using namespace std;

pair<int, int> ChessBoard :: getAiMove(Color ai_color, int depth) const{
    vector<vector<pair<int, int>>> ai_moves;
    for(int k = 0; k < NUM_SQUARES; k++){
        if(this->pieces[k] && this->pieces[k]->color == ai_color){
            auto moves = this->pieces[k]->FINDPOSSIBLEMOVES(*this);
            vector<pair<int, int>> ai_legalMoves;
            if(this->check){
                for(const auto& move : moves){
                    if(this->wouldSafeKing(move)) ai_legalMoves.push_back(move);
                }
            }
            else{
                for(const auto& move: moves){
                    if(this->isLegalMove(move)) ai_legalMoves.push_back(move);
                }
            }
            if(!ai_legalMoves.empty()) ai_moves.push_back(std::move(ai_legalMoves));
        }
    }
    if (ai_moves.empty()) return {-1, -1};
    auto evaluate = ai_EvaluateMoves(ai_moves, depth);
    int bestScore = INT_MIN;
    pair<int, int> bestMove = {-1, -1};
    for (size_t i = 0; i < ai_moves.size(); ++i) {
        for (size_t j = 0; j < ai_moves[i].size(); ++j) {
            if (evaluate[i][j] > bestScore) {
                bestScore = evaluate[i][j];
                bestMove = ai_moves[i][j];
            }
        }
    }    
    return bestMove;
}

vector<vector<int>> ChessBoard :: ai_EvaluateMoves(const vector<vector<pair<int, int>>>& ai_moves, int depth) const{
    vector<vector<int>> evaluations;
    for(const auto& piece_ai_moves : ai_moves){
        vector<int> moves_evaluate;
        for(const auto& ai_move : piece_ai_moves){
            moves_evaluate.push_back(ai_EvaluateSingleMove(ai_move, depth));
        }
        evaluations.push_back(moves_evaluate);
    }
    return evaluations;
}

int ChessBoard :: ai_EvaluateSingleMove(const pair<int, int>& ai_move, int depth) const{
    ChessBoard tmp(*this);
    Color movingColor = this->pieces[ai_move.first]->color;
    tmp.pieces[ai_move.first]->makeMove(ai_move.second, tmp);
    if (depth <= 1) {
        return tmp.evaluatePosition(movingColor);
    }
    Color opponentColor = (movingColor == white) ? black : white;
    vector<pair<int, int>> opponentMoves;
    for (int i = 0; i < NUM_SQUARES; ++i) {
        if (tmp.pieces[i] && tmp.pieces[i]->color == opponentColor) {
            auto moves = tmp.pieces[i]->FINDPOSSIBLEMOVES(tmp);
            for (const auto& move : moves) {
                if (tmp.isLegalMove(move)) opponentMoves.push_back(move);
            }
        }
    }
    if (opponentMoves.empty()) {
        if (tmp.isCheck(opponentColor)) return 1000000; 
        return 0; 
    }
    int worstScore = INT_MAX;
    for (const auto& move : opponentMoves) {
        int score = tmp.ai_EvaluateSingleMove(move, depth - 1);
        if (score < worstScore) worstScore = score;
    }
    return -worstScore;
}