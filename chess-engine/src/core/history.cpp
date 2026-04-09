#include "history.h"
#include "piece.h"

History :: History(std::unique_ptr<Piece> _piece, int from_index_, int to_index_, Color _color){
		this->piece = move(_piece);
		this->from_index = from_index_;
		this->to_index = to_index_;
		color = _color;
	}