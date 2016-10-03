#pragma once

#include "../NETCollector/NETCollector.inl"

namespace NE
{
	template <template <typename> Collector, typename T, template <typename> class BinderType>
	class NETCollectorProxy : public NETCollector<T>
	{
		typedef NETCollectorProxy<Collector<T>> _This;

		NE_DECLARE_CLASS_ONLY(_This, NETCollector<T>)

	protected:
		typedef BinderType<T>			BeanType;
		typedef NETIterator<BeanType>	BeanIterator;
		typedef NETCIterator<BeanType>	BeanCIterator;


	protected:
		class Iterator : public NETIterator<T>
		{
			NE_DECLARE_CLASS_ONLY(Iterator, NETIterator<T>)

		public:
			Iterator(NETBinder<BeanIterator>& bean_iteratored);

		public:
			type_bool operator==(const This& rhs) const;			

		public:
			virtual const T& get() const;
			virtual T& get();
			virtual type_bool isEnd() const;
			virtual type_result next(type_index step_for_next);
			virtual type_result back(type_index step_for_back);
			//		NELengthedObject:
			virtual type_index getLength() const;
			//		NEObject:
			virtual void release();
			virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
			virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
			virtual type_result isValid() const;

		private:
			NETBinder<BeanIterator> _proxied;
		};
		class CIterator : public NETCIterator<T>
		{
			NE_DECLARE_CLASS_ONLY(CIterator, NETCIterator<T>)

		public:
			CIterator(NETBinder<BeanCIterator>& bean_iteratored);

		public:
			type_bool operator==(const This& rhs) const;			

		public:
			virtual const T& get() const;
			virtual type_bool isEnd() const;
			virtual type_result next(type_index step_for_next);
			virtual type_result back(type_index step_for_back);
			//		NELengthedObject:
			virtual type_index getLength() const;
			//		NEObject:
			virtual void release();
			virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
			virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
			virtual type_result isValid() const;

		private:
			NETBinder<BeanCIterator> _proxyied;
		};

	public:
		virtual NETBinder<NETCIterator<T>> getIterator(type_index index) const;
		virtual NETBinder<NETIterator<T>> getIterator(type_index index);
		virtual type_index insert(const NETCIterator<T>& where, const T& source);
		virtual type_index insert(const NETCIterator<T>& where, const NETCIterator<T>& from, const NETCIterator<T>& end);
		virtual type_index remove(const NETCIterator<T>& from, const NETCIterator<T>& end);
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
		Collector<BeanType> _proxy;
	};
}