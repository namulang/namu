//	Interpreting에 의해서 나오게 되는 모든 산물들.
class Origin : public Object { //	Origin은 또다른 Origin들을 composition으로 가질 수 있다.
	class Pos : public Object { // Pos는 visible해야 한다. IDE에서도 사용해야 하니까.
		Pos(wint row, wint col);

		This& operator=(const This& rhs);
		wbool operator==(const This& rhs) const;
		wbool operator!=(const This& rhs) const;
		wbool operator<(const This& rhs);
		wbool operator<=(const This& rhs);
		wbool operator>(const This& rhs);
		wbool operator>=(const This& rhs);

		wint getRow() const { return _row; }
		wint getCol() const { return _col; }

		wint _row;
		wint _col;
	};

	Origin(const Pos& start = Pos(), const Pos& end = Pos());

	const Pos& getStart() const;
	const Pos& getEnd() const;
	const Origin& getOwner() const { return _owner; }
	Origin& getOwner() { return _owner; }

	Pos _start;
	Pos _end;
	Origin& _owner;
};
