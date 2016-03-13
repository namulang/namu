namespace NE
{
	template <typename T, typename MetaClass = T::MetaClass>
	type_bool NE::NETClass<T, MetaClass>::isTempate() const
	{
		return IS_TEMPLATE;
	}

	template <typename T, typename MetaClass = T::MetaClass>
	type_bool NE::NETClass<T, MetaClass>::isTemplateStatically()
	{
		return IS_TEMPLATE;
	}

	template <typename T, typename MetaClass = T::MetaClass>
	type_bool NE::NETClass<T, MetaClass>::isInstantiable() const
	{
		return IS_ADT;
	}

	template <typename T, typename MetaClass = T::MetaClass>
	type_bool NE::NETClass<T, MetaClass>::isInstantiableStatically()
	{
		return IS_ADT;
	}
}