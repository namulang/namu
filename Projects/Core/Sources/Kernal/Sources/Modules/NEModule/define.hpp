#define DEFINE_MODULE	\
	public:	virtual NEObject& clone() const { return *(new ThisClass(*this)); }
