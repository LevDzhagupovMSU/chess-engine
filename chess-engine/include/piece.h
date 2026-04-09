#pragma once

#include "types.h"
#include <vector>
#include <memory>
#include <string>

class ChessBoard;

struct Piece{
	int row, col, price;
	Color color;

	Piece();
	Piece(Color _color);
    virtual ~Piece() = default;

	virtual std::string getSymbol() const = 0;
    virtual std::vector<std::pair<int, int>> FINDPOSSIBLEMOVES(const ChessBoard& board) const;
	virtual void makeMove(int to_index, ChessBoard& board);
	virtual bool ISPOSSIBLEMOVE(int to_row, int to_col, const ChessBoard& board) const =0;
	virtual bool ISPOSSIBLEMOVE(int index, const ChessBoard& board) const;

	virtual std::unique_ptr<Piece> clone() const=0;
};

struct Pawn : Piece {
	Pawn(int row, int col, int price, Color _color);
	std::string getSymbol() const override;
    std::unique_ptr<Piece> clone() const override;
	bool ISPOSSIBLEMOVE(int to_row, int to_col, const ChessBoard& board) const override;
};

struct Knight : Piece {
	Knight(int row, int col, int price, Color _color);
	std::string getSymbol() const override;
    std::unique_ptr<Piece> clone() const override;
	bool ISPOSSIBLEMOVE(int to_row, int to_col, const ChessBoard& board) const override;
};

struct Bishop : Piece {
	Bishop(int row, int col, int price, Color _color);
	std::string getSymbol() const override;
    std::unique_ptr<Piece> clone() const override;
	bool ISPOSSIBLEMOVE(int to_row, int to_col, const ChessBoard& board) const override;
};

struct Rook  : Piece {
	Rook(int row, int col, int price, Color _color);
	std::string getSymbol() const override;
    std::unique_ptr<Piece> clone() const override;
	bool ISPOSSIBLEMOVE(int to_row, int to_col, const ChessBoard& board) const override;
};

struct Queen  : Piece {
	Queen(int row, int col, int price, Color _color);
	std::string getSymbol() const override;
    std::unique_ptr<Piece> clone() const override;
	bool ISPOSSIBLEMOVE(int to_row, int to_col, const ChessBoard& board) const override;
};

struct King  : Piece {
	King(int row, int col, int price, Color _color);

	std::string getSymbol() const override;
    std::unique_ptr<Piece> clone() const override;
	bool ISPOSSIBLEMOVE(int to_row, int to_col, const ChessBoard& board) const override;
};