namespace NE
{
	template <typename T>
	class NETClass<T, NETTemplate> : public NETTemplate<T>
	{
	public:
		static const bool = IS_ADT = false;//
		static const bool = IS_TEMPLATE = true;
	};
}