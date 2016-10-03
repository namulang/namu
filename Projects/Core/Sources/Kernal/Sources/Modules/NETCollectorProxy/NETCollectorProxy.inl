#pragma once

#include "../NETCollector/NETCollector.inl"

namespace NE
{
	template <typename T, template <typename> class BinderType>
	class NETCollectorProxy : public NETCollector<Trait>
	{
		typedef NETCollectorProxy<T, BinderType> _This;

		NE_DECLARE_CLASS_ONLY(_This, NETCollector<T>)

	protected:
		typedef NETTraitDeterminder<T>::Template 	Collector;
		typedef NETTraitDeterminder<T>::Trait		Trait;
		typedef BinderType<Trait>					BeanType;
		typedef NETIterator<BeanType>				BeanIterator;
		typedef NETCIterator<BeanType>				BeanCIterator;

	protected:
		class Iterator : public NETIterator<Trait>
		{
			NE_DECLARE_CLASS_ONLY(Iterator, NETIterator<Trait>)

		public:
			Iterator(NETBinder<BeanIterator>& bean_iteratored);

		public:
			type_bool operator==(const This& rhs) const;			

		public:
			virtual const Trait& get() const;
			virtual Trait& get();
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
		class CIterator : public NETCIterator<Trait>
		{
			NE_DECLARE_CLASS_ONLY(CIterator, NETCIterator<Trait>)

		public:
			CIterator(NETBinder<BeanCIterator>& bean_iteratored);

		public:
			type_bool operator==(const This& rhs) const;			

		public:
			virtual const Trait& get() const;
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
		virtual NETBinder<NETCIterator<Trait>> getIterator(type_index index) const;
		virtual NETBinder<NETIterator<Trait>> getIterator(type_index index);
		virtual type_index insert(const NETCIterator<Trait>& where, const Trait& source);
		virtual type_index insert(const NETCIterator<Trait>& where, const NETCIterator<Trait>& from, const NETCIterator<Trait>& end);
		virtual type_index remove(const NETCIterator<Trait>& from, const NETCIterator<Trait>& end);
		virtual Trait& getElement(type_index index);
		virtual const Trait& getElement(type_index index) const;
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