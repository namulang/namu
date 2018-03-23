//	Interpreting에 의해서 나오게 되는 모든 산물들.
class Source : public Node {
	struct SrcPos {
		int col;
		int row;
	};
	SrcPos _start;
	SrcPos _end;
};
