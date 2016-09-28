#pragma once

#include "../NETCollector/NETCollector.inl"

namespace NE
{
	template <template <typename> Collector, typename T>
	class NE_DLL NETDeeper : public NETCollector<T>
	{
		NE_DECLARE_CLASS_ONLY(NETDeeper<Collector<T>>, NETCollector<T>)

	public:
		virtual NETBinder<NETCIterator<T>> getIterator(type_index index) const;
		virtual NETBinder<NETIterator<T>> getIterator(type_index index);
		virtual type_index insert(const NETCIterator<T>& where, const T& source);
		virtual type_index insert(const NETCIterator<T>& where, NETCIterator<T> from, const NETCIterator<T>& end);
		virtual type_index remove(NETCIterator<T> from, const NETCIterator<T>& end);
		virtual T& getElement(type_index index);
		virtual const T& getElement(type_index index) const;
		//		NELengthedObject:
		virtual type_index getLength() const;
		//		NEObject:
		virtual void release();
		virtual type_result isValid() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);


	private:
		Collector<NETBinder<T>> _proxy;
	};
}