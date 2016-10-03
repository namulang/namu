#include "NETCollectorProxy.inl"

namespace NE
{
#define _TEMPLATE   template <typename <typename> Template, typename T>
#define _OWNERNAME  NETCollectorProxy<Collector<T>>
#define _NAME       _OWNERNAME##::Iterator

	NE_DEFINE_CLASS_ONLY_2(_NAME, NE_MACRO_FUNNEL(_TEMPLATE));

	_TEMPLATE
	_NAME::Iterator(NETBinder<BeanIterator>& bean_iterator)
		: _proxied(bean_iterator);
	{        

	}

	_TEMPLATE
	type_bool _NAME::operator==(const This& rhs) const
	{
		return  Super::operator==(rhs)  &&
			_proxied == rhs._proxied;
	}

	_TEMPLATE
	const T& _NAME::get() const
	{
		This* unconsted = const_cast<This*>(this);

		return unconsted->get();
	}

	_TEMPLATE
	T& _NAME::get() 
	{
		//  TODO: code refactorying needs with NETNuller
		//  with NETNuller:
		//      return ***_proxied;
		T* nullpointer = NE_NULL;
		BeanIterator& bean_e = *_proxied;
		if( ! &bean_e) return *nullpointer;

		BeanType& bean = bean_e->get();
		if( ! &bean) return *nullpointer;

		return *bean;
	}

	_TEMPLATE
	type_bool _NAME::isEnd() const
	{
		return _proxied.isEnd();
	}

	_TEMPLATE
	type_result _NAME::next(type_index step_for_next)
	{
		return _proxied.next(step_for_next);
	}

	_TEMPLATE
	type_result _NAME::back(type_index step_for_back)
	{
		return _proxied.back(step_for_back);
	}

	_TEMPLATE
	type_index getLength() const
	{
		return _proxied.getLength();
	}

	_TEMPLATE
	void _NAME::release()
	{
		_proxied.release();
	}

	_TEMPLATE
	NEBinaryFileSaver& _NAME::serialize(NEBinaryFileSaver& saver) const
	{
		Super::serialize(saver);

		return saver << _proxied;
	}

	_TEMPLATE
	NEBinaryFileLoader& _NAME::serialize(NEBinaryFileLoader& loader)
	{
		Super::serialize(loader);

		return loader >> _proxied;
	}

	_TEMPLATE
	type_result _NAME::isValid() const
	{
		type_result result = Super::isValid();
		if(NEResult::hasError(result)) return RESULT_TYPE_ERROR;

		return _proxied.isValid(); 
	}

#undef  _NAME
#define _NAME   _OWNERNAME##::CIterator

	NE_DEFINE_CLASS_ONLY_2(_NAME, NE_MACRO_FUNNEL(_TEMPLATE));

	_TEMPLATE
	_NAME::CIterator(NETBinder<BeanIterator>& bean_iterator)
		: _proxied(bean_iterator)
	{

	}

	_TEMPLATE
	type_bool _NAME::operator==(const This& rhs) const
	{
		return  Super::operator==(rhs)  &&
			_proxied == rhs._proxied;
	}

	_TEMPLATE
	const T& _NAME::get() const
	{
		//  TODO: code refactorying needs with NETNuller
		//  with NETNuller:
		//      return ***_proxied;
		const T* nullpointer = NE_NULL;
		BeanCIterator& bean_e = *_proxied;
		if( ! &bean_e) return *nullpointer;

		const BeanType& bean = bean_e->get();
		if( ! &bean) return *nullpointer;

		return *bean;
	}

	_TEMPLATE
	type_bool _NAME::isEnd() const
	{
		return _proxied.isEnd();
	}

	_TEMPLATE
	type_result _NAME::next(type_index step_for_next)
	{
		return _proxied.next(step_for_next);
	}

	_TEMPLATE
	type_result _NAME::back(type_index step_for_back)
	{
		return _proxied.back(step_for_back);
	}

	_TEMPLATE
	type_index getLength() const
	{
		return _proxied.getLength();
	}

	_TEMPLATE
	void _NAME::release()
	{
		_proxied.release();
	}

	_TEMPLATE
	NEBinaryFileSaver& _NAME::serialize(NEBinaryFileSaver& saver) const
	{
		Super::serialize(saver);

		return saver << _proxied;
	}

	_TEMPLATE
	NEBinaryFileLoader& _NAME::serialize(NEBinaryFileLoader& loader)
	{
		Super::serialize(loader);

		return loader >> _proxied;
	}

	_TEMPLATE
	type_result _NAME::isValid() const
	{
		type_result result = Super::isValid();
		if(NEResult::hasError(result)) return RESULT_TYPE_ERROR;

		return _proxied.isValid(); 
	}

#undef  _NAME

	NE_DEFINE_CLASS_ONLY_2(_OWNERNAME, NE_MACRO_FUNNEL(_TEMPLATE))

	_TEMPLATE
	NETBinder<NETCIterator<T>> _OWNERNAME::getIterator(type_index index) const
	{
		//  iterating:
		NETBinder<BeanCIterator> iteratored = _proxy.getIterator(index);
		iteratored += index;

		//  packaging the return:
		return NETBinder<NETCIterator<T>>( *(new CIterator(iteratored)) );
	}

	_TEMPLATE
	NETBinder<NETIterator<T>> _OWNERNAME::getIterator(type_index index)
	{
		//  iterating:
		NETBinder<BeanIterator> iteratored = _proxy.getIterator(index);
		iteratored += index;

		//  packaging the return:
		return NETBinder<NETIterator<T>>( *(new Iterator(iteratored)) );
	}

	_TEMPLATE
	type_index _OWNERNAME::insert(const NETCIterator<T>& where, const T& source)
	{
		return _proxy.insert(where, NETBinder<T>(source));
	}

	_TEMPLATE
	type_index _OWNERNAME::insert(const NETCIterator<T>& where, const NETCIterator<T>& from, const NETCIterator<T>& end)
	{
		return _proxy.insert(where, from, end);
	}

	_TEMPLATE
	type_index _OWNERNAME::remove(const NETCIterator<T>& from, const NETCIterator<T>& end)
	{
		return _proxy.remove(from, end);
	}

	_TEMPLATE
	T& _OWNERNAME::getElement(type_index index)
	{
		return *_proxy.getElement(index);
	}

	_TEMPLATE
	const T& _OWNERNAME::getElement(type_index index) const
	{
		return *_proxy.getElement(index);
	}

	_TEMPLATE
	type_index _OWNERNAME::getLength() const 
	{
		return _proxy.getLength();
	}

	_TEMPLATE
	void _OWNERNAME::release()
	{
		Super::release();

		_proxy.release();
	}

	_TEMPLATE
	type_result _OWNERNAME::isValid() const
	{
		type_result result = Super::isValid();
		if(NEResult::hasError(result)) return result;

		return _proxy.isValid();
	}

	_TEMPLATE
	NEBinaryFileSaver& _OWNERNAME::serialize(NEBinaryFileSaver& saver) const
	{
		Super::serialize(saver);

		return saver << _proxy;
	}

	_TEMPLATE
	NEBinaryFileLoader& _OWNERNAME::serialize(NEBinaryFileLoader& loader)
	{
		Super::serialize(loader);

		return loader >> _proxy;
	}

#undef _OWNERNAME
#undef _TEMPLATE
}