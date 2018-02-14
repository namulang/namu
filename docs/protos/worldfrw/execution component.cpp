class InstanceBlock : public Thing {
	friend class Weak;
	//	_strong을 위해서다.
	wcount getCount() const { return _strong; }
	Result& _increaseCount() {
		_strong++;
		return Success;
	}
	Result& _decreaseCount() {
		if(--_strong <= 0)
			release();
		return Success;
	}
	//	Strong reference 카운트다.
	wcount _strong;
	Instance& get();
	const Instance& get() const;
	Result& release();
};
