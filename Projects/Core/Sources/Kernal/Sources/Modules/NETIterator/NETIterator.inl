#pragma once

#include "../NEIteratorBase/NEIteratorBase.hpp"
#include "../NETBinder/NETBinder.hpp"

namespace NE
{
	//	What you have to know when you make subclass for NETIterator<T>:
	//		Don't define methods return its own class as return-type.
	//		So, don't do like below,
	//
	//			class MyIterator : public NETIterator<T> {
	//				MyIterator& operator++();
	//			}
	//
	//		But use this instead of above one if you have to.
	//
	//			NETIterator<T>& operator++();
	template <typename T>
	class NETCIterator : public NEIteratorBase 
	{
		//	we're declaring this as Interface class even though this can be Class:
		//		There is no default constructor, so this can't be instantiated by 
		//		NE_DECLARE_CLASS macro.
		NE_DECLARE_INTERFACE_ONLY(NETCIterator, NEIteratorBase)

	protected:
		NETCIterator();
	public:
		NETCIterator(const NEIteratorBase& origin);	//	actually, we've to use NEBinder<This>& instead of this.
		NETCIterator(const This& rhs);
		virtual ~NETCIterator();

	public:
		virtual type_result next(type_count step_for_next);
		virtual type_result back(type_count step_for_back);
		virtual const T& get() const;
		//	from NEObject:
		virtual NEObject& clone() const;
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual type_result isValid() const;

	public:
		//	Method hiding:
		This& operator=(const This& rhs);
		type_bool operator==(const This& rhs) const;
		type_bool operator!=(const This& rhs) const;
		This& operator++();
		This& operator--();
		This operator+(type_count step_for_next);
		This operator-(type_count step_for_back);
		const T& operator*() const;
		const T& operator->() const;

	private:
		void _release();
		This& _assign(const This& rhs);

	protected:
		//	Why does this class use proxy?:
		//		This'll be used at NETCollector hierarchy. And in order to return
		//		Iterator instance by value at NETCollector class, we've to use
		//		proxy which contains how iterate instance cursor.
		NETBinder<NEIteratorBase> _proxy;	// TODO: this should be changed to NEBinder
	};

	template <typename T>
	class NETIterator : public NETCIterator 
	{
		NE_DECLARE_INTERFACE_ONLY(NETIterator, NEIteratorBase)

	protected:
		NETIterator();
	public:
		NETIterator(const NEIteratorBase& origin);	//	actually, we've to use NEBinder<This>& instead of this.
		NETIterator(const This& rhs);
		virtual ~NETIterator();

	public:
		virtual T& get();
		virtual NEObject& clone() const;

	public:
		//	Method hiding:
		This& operator++();
		This& operator--();
		This operator+(type_count step_for_next);
		This operator-(type_count step_for_back);
		T& operator*();
		T& operator->();
	};
}