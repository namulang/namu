namespace NE
{
	template <typename T, NEType::Type type>
	NETArithmeticKey<T, type>::NETArithmeticKey(const T& source, const NETString& keyname)
		: SuperClass(source, keyname)
	{

	}

	template <typename T, NEType::Type type>
	NETArithmeticKey<T, type>::NETArithmeticKey(const ThisClass& source)
		: SuperClass(source)
	{

	}
	
	template <typename T, NEType::Type type>
	NETArithmeticKey<T, type>::NETArithmeticKey(const NEKey& source)
		: SuperClass(source)
	{
		assign(source);
	}

	template <typename T, NEType::Type type>
	bool NETArithmeticKey<T, type>::isEqualTo(const NEKey& source) const
	{
		//	pre:
		if (this == &source) return true;



		//	main:
		//		버퍼 생성:
		ThisClass buffer;
		//		버퍼에 할당:
		type_result result = buffer.assign(source);
		if (NEResult::hasError(result))
			return false;



		//	post:
		return _value == buffer._value;
	}

	template <typename T, NEType::Type type>
	NEObject& NETArithmeticKey<T, type>::clone() const
	{
		return *(new ThisClass(*this));
	}
	
	//	---------------------------------------------------------------------------------
	//	설명	:	NEKey끼리 캐스팅 없이 할당이 가능하게 하는 함수. operator=와 같다.
	//				내부에서 캐스팅을 실시한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	/*
	NEManagedNodeSet과 NEManagedModuleSet은 기본 assign을 사용한다.
	*/
	template <typename T, NEType::Type type>
	type_result NETArithmeticKey<T, type>::assign(const NEKey& source)
	{
		if (!&source) return RESULT_TYPE_ERROR | RESULT_WRONG_PARAMETER | RESULT_WRONG_POINTER_ADDRESSING | RESULT_ABORT_ACTION;
		if (this == &source) return RESULT_SUCCESS | RESULT_ABORT_ACTION | RESULT_ABORT_ACTION;
		if (isSubClassOf(NEType::NENODE_SELECTOR_BASE)) return RESULT_TYPE_ERROR | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;
		if ( ! isEqualTypeWith(source)) return RESULT_TYPE_ERROR | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;

		SuperClass::assign(source);
		_value = static_cast<const NETArithmeticKey<T, type>&>(source).getValue();

		return RESULT_SUCCESS;
	}
	template <>
	type_result NETArithmeticKey<type_bool, NEType::NEBOOLEAN_KEY>::assign(const NEKey& source);
	template <>
	type_result NETArithmeticKey<type_byte, NEType::NEBYTE_KEY>::assign(const NEKey& source);
	template <>
	type_result NETArithmeticKey<type_ubyte, NEType::NEUBYTE_KEY>::assign(const NEKey& source);
	template <>
	type_result NETArithmeticKey<type_char, NEType::NECHAR_KEY>::assign(const NEKey& source);
	template <>
	type_result NETArithmeticKey<type_wchar, NEType::NEWCHAR_KEY>::assign(const NEKey& source);
	template <>
	type_result NETArithmeticKey<type_short, NEType::NESHORT_KEY>::assign(const NEKey& source);
	template <>
	type_result NETArithmeticKey<type_ushort, NEType::NEUSHORT_KEY>::assign(const NEKey& source);
	template <>
	type_result NETArithmeticKey<type_int, NEType::NEINT_KEY>::assign(const NEKey& source);
	template <>
	type_result NETArithmeticKey<type_uint, NEType::NEUINT_KEY>::assign(const NEKey& source);
	template <>
	type_result NETArithmeticKey<type_float, NEType::NEFLOAT_KEY>::assign(const NEKey& source);
	template <>
	type_result NETArithmeticKey<type_double, NEType::NEDOUBLE_KEY>::assign(const NEKey& source);
	template <>
	type_result NETArithmeticKey<type_int64, NEType::NEINT64_KEY>::assign(const NEKey& source);


	template <typename T, NEType::Type type>
	bool NETArithmeticKey<T, type>::isLower(const NEKey& source) const
	{
		//	pre:
		if (!&source) return false;



		//	main:
		//		버퍼 정의:
		NETArithmeticKey<T, type> buffer;
		//		버퍼에 할당:
		type_result result = buffer.assign(source);
		if (NEResult::hasError(result))
			return false;



		//	post:
		return _value < buffer._value;
	}


	template <typename T, NEType::Type type>
	type_result NETArithmeticKey<T, type>::add(NEKey& result, const NEKey& operand2) const
	{
		ThisClass converted;
		converted.assign(operand2);		
		
		return result.assign(ThisClass(getValue() + converted.getValue()));
	}

	template <typename T, NEType::Type type>
	type_result NETArithmeticKey<T, type>::multiply(NEKey& result, const NEKey& operand2) const
	{
		ThisClass converted;
		converted.assign(operand2);

		return result.assign(ThisClass(getValue() * converted.getValue()));
	}

	template <typename T, NEType::Type type>
	type_result NETArithmeticKey<T, type>::makeReciprocal()
	{
		if (_value == 0)
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		_value = 1 / _value;

		return RESULT_SUCCESS;
	}

	template <typename T, NEType::Type type>
	type_result NETArithmeticKey<T, type>::negate()
	{
		_value = -_value;

		return RESULT_SUCCESS;
	}
}