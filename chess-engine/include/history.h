#pragma once

#include "types.h"
#include <memory>

struct Piece;

struct History{
	std::unique_ptr<Piece> piece;
	int from_index, to_index;
	Color color;
    
	History(std::unique_ptr<Piece> _piece, int from_index, int to_index, Color _color);
};
