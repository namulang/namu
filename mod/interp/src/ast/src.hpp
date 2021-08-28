#pragma once

#include "../common.hpp"

namespace wrd {

	class src : public typeProvidable {
		WRD_INTERFACE(src, typeProvidable)

	public:
		src(): _row(0), _col(0) {}
		src(int row, int col): _row(row), _col(col) {}

	public:
		int getRow() const { return _row; }
		int getCol() const { return _col; }

	private:
		int _row;
		int _col;
	};
}
