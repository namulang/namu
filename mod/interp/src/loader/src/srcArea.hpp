#pragma once

#include "../../common.hpp"

namespace wrd {

	class srcArea : public typeProvidable {
		WRD_INTERFACE(srcArea, typeProvidable)

	public:
		srcArea(): _row(0), _col(0) {}
		srcArea(int row, int col): _row(row), _col(col) {}

	public:
		int getRow() const { return _row; }
		int getCol() const { return _col; }

	private:
		int _row;
		int _col;
	};
}
