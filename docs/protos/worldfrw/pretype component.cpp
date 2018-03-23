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
