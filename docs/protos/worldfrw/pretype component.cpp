class Result {
	wint warn(.....);
	wint err(....);
	wint info(....);
	wint dbg(..);

	template <typename T>
	T returns() {
		return T();
	}
	template <typename T>
	T returns(T value) {
		return value;
	}
	template <typename T>
	T& returnsNullref() {
		return TNuller<T>::ref;
	}
};
