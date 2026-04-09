#pragma once
#include "types.h"
#include "piece.h"
#include "history.h"
#include <vector>

struct ChessBoard {
	std::vector<std::unique_ptr<Piece>> pieces;

	bool check = false;
    bool checkMate = false; 
	int white_kingIndex = -1;
    int black_kingIndex = -1;

    std::vector<History> moves_record;

	ChessBoard();
	ChessBoard(const ChessBoard& board);

    void setPiece(int _row, int _col, std::unique_ptr<Piece> piece);
    int Index(int row, int col) const;
    Piece* getPiece(int _row, int _col);
    void display();

    bool isCheck(Color _color) const;
	bool isCheckMate(Color _color);
    bool hasAnyLegalMove(Color _color);
	bool wouldSafeKing(const std::pair<int, int>& move) const;
	bool isLegalMove(const std::pair<int, int>& move) const;
	bool isItPossibleToCastle(Color _color, int rook_index) const;
	bool isSquaredAttacked(int index, Color attackerColor) const;

    std::pair<int, int> getAiMove(Color ai_color, int depth) const;
    int ai_EvaluateSingleMove(const std::pair<int, int>& ai_move, int depth) const;
    
    private:
	std::vector<std::vector<int>> ai_EvaluateMoves(const std::vector<std::vector<std::pair<int, int>>>& ai_moves, int depth) const;
	int evaluatePosition(Color player) const;
};