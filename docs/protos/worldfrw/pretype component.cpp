class Result {
	wint warn(.....);
	wint err(....);
	wint info(....);
	wint dbg(..);

	template <typename T>
	T returns() {
		return TNuller<T>::null();
	}
	template <typename T>
	T returns(T value) {
		return value;
	}
};

class Integer : ?? {
	virtual Refer toImplicitly(const Class& cls) {
		//	TODO: 묵시적 캐스팅 구현.
		//	else
		return Super::toImplicitly(cls);
	}
};
