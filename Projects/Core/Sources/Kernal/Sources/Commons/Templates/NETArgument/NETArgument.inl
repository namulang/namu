namespace NE
{
	template <typename T>
	NETArgument<T>::NETArgument(NEArgumentBase::Purpose limitation) 
		: SuperClass(T().getType(), limitation)
	{

	}

	template <typename T>
	NEObject& NETArgument<T>::clone() const
	{
		return *(new ThisClass(*this));
	}

	template <typename T>
	NEType::Type NETArgument<T>::getType() const
	{
		return NEType::NETARGUMENT;
	}

	template <typename T>
	typename const T::Trait& NE::NETArgument<T>::getValue() const
	{
		const NEKey& binded = getBinded();
		if( &binded)
		{
			if(isValidToBind(binded))
				return (static_cast<const T&>(binded)).getValue();
			else
			{
				_for_casting = binded;
				return _for_casting.getValue();
			}
		}

		return getDefault();
	}

	template <typename T>
	type_result NE::NETArgument<T>::setDefault(typename const T::Trait& source)
	{
		_default_key.getValue() = source;

		return RESULT_SUCCESS;
	}

	template <typename T>
	const NEKey& NE::NETArgument<T>::getDefaultKey() const
	{
		return _default_key;
	}

	template <typename T>
	NEKey& NE::NETArgument<T>::getDefaultKey()
	{
		return _default_key;
	}

	template <typename T>
	type_result NE::NETArgument<T>::setValue(typename const T::Trait& source)
	{
		NEKey& binded = getBinded();
		if(	! &binded)
			return setDefault(source);


		//	main:
		if(isValidToBind(binded))
		{
			T& casted = static_cast<T&>(binded);
			casted.getValue() = source;
		}
		else
			binded = T(source);

		return RESULT_SUCCESS;			
	}

	template <typename T>
	typename const T::Trait& NE::NETArgument<T>::getDefault() const
	{
		return _default_key.getValue();
	}
	template <typename T>
	void NE::NETArgument<T>::release()
	{
		SuperClass::release();
		_for_casting.release();
		_default_key.release();
	}

	template <typename T>
	type_result NE::NETArgument<T>::isValid() const
	{
		type_result result = SuperClass::isValid();
		if(NEResult::hasError(result)) return result;

		return _default_key.isValid();
	}

	template <typename T>
	NEBinaryFileSaver& NE::NETArgument<T>::serialize(NEBinaryFileSaver& saver) const
	{
		SuperClass::serialize(saver);

		return saver << _default_key;
	}

	template <typename T>
	NEBinaryFileLoader& NE::NETArgument<T>::serialize(NEBinaryFileLoader& loader)
	{
		SuperClass::serialize(loader);

		return loader >> _default_key;
	}

	template <typename T>
	class NE_DLL NETLimitedArgument : public NEArgumentBase
	{
	public:
		typedef NETLimitedArgument ThisClass;
		typedef NEArgumentBase SuperClass;

	public:
		NETLimitedArgument()
			: SuperClass(T().getType())
		{

		}
		NETLimitedArgument(const ThisClass& rhs)
			: SuperClass(rhs), _default_key(rhs._default_key)
		{

		}

	public:
		typename T::Trait& getValue()
		{
			NEKey& binded = getBinded();
			if( &binded					&&
				isValidToBind(binded)	)
				return static_cast<T&>(binded).getValue();

			return getDefault();
		}
		typename const T::Trait& getValue() const
		{
			ThisClass* unconsted = const_cast<ThisClass*>(this);

			return unconsted->getValue();
		}
		typename T::Trait& getDefault()
		{
			return _default_key.getValue();
		}
		typename const T::Trait& getDefault() const
		{
			return _default_key.getValue();
		}

	public:
		virtual	NEKey& getDefaultKey()
		{
			return _default_key;
		}
		virtual const NEKey& getDefaultKey() const
		{
			return _default_key;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
		virtual void release()
		{
			SuperClass::release();

			_default_key.release();
		}
		virtual type_result isValid() const
		{
			type_result result = SuperClass::isValid();
			if(NEResult::hasError(result)) return result;

			return _default_key.isValid();
		}
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
		{
			SuperClass::serialize(loader);

			return loader >> _default_key;
		}
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
		{
			SuperClass::serialize(saver);

			return saver << _default_key;
		}

	private:
		T _default_key;
	};	

	template <>
	class NE_DLL NETArgument<NEBooleanSetKey> : public NETLimitedArgument<NEBooleanSetKey>{};
	template <>
	class NE_DLL NETArgument<NEByteSetKey> : public NETLimitedArgument<NEByteSetKey>{};
	template <>
	class NE_DLL NETArgument<NEUByteSetKey> : public NETLimitedArgument<NEUByteSetKey>{};
	template <>
	class NE_DLL NETArgument<NEShortSetKey> : public NETLimitedArgument<NEShortSetKey>{};
	template <>
	class NE_DLL NETArgument<NEUShortSetKey> : public NETLimitedArgument<NEUShortSetKey>{};
	template <>
	class NE_DLL NETArgument<NEIntSetKey> : public NETLimitedArgument<NEIntSetKey>{};
	template <>
	class NE_DLL NETArgument<NEUIntSetKey> : public NETLimitedArgument<NEUIntSetKey>{};
	template <>
	class NE_DLL NETArgument<NEInt64SetKey> : public NETLimitedArgument<NEInt64SetKey>{};
	template <>
	class NE_DLL NETArgument<NEFloatSetKey> : public NETLimitedArgument<NEFloatSetKey>{};
	template <>
	class NE_DLL NETArgument<NEDoubleSetKey> : public NETLimitedArgument<NEDoubleSetKey>{};
	template <>
	class NE_DLL NETArgument<NEStringSetKey> : public NETLimitedArgument<NEStringSetKey>{};
	template <>
	class NE_DLL NETArgument<NEModuleCodeSetKey> : public NETLimitedArgument<NEModuleCodeSetKey>{};
	template <>
	class NE_DLL NETArgument<NENodeCodeSetKey> : public NETLimitedArgument<NENodeCodeSetKey>{};



	template <typename T>
	class NE_DLL NETSelectorArgument : public NEArgumentBase
	{
	public:
		typedef NETSelectorArgument ThisClass;
		typedef NEArgumentBase SuperClass;

	public:
		NETSelectorArgument()
			: SuperClass(T().getType())
		{
			_release();
		}
		NETSelectorArgument(const ThisClass& rhs)
			: SuperClass(rhs)			
		{
			_assign(rhs);
		}

	public:
		typename T::Trait& getValue()
		{
			NEKey& binded = getBinded();
			if (&binded					&&
				isValidToBind(binded))
				return static_cast<T&>(binded).getValue();

			return getDefault();
		}
		typename const T::Trait& getValue() const
		{
			ThisClass* unconsted = const_cast<ThisClass*>(this);

			return unconsted->getValue();
		}
		typename T::Trait& getDefault()
		{
			return _default_key.getValue();
		}
		typename const T::Trait& getDefault() const
		{
			return _default_key.getValue();
		}
		bool isPeekingLockActivated() const
		{
			return _is_peeking_lock_activated;
		}
		bool isUsingPeekingLock() const
		{
			return _use_peeking_lock;
		}
		bool wasKeyUsingPeekingLock() const
		{
			return _origins_peeking_lock;
		}
		type_result setUsingPeekingLock(bool new_peeking_lock)
		{
			_use_peeking_lock = new_peeking_lock;

			getValue().isPeekingLocked() = _use_peeking_lock;

			return RESULT_SUCCESS;
		}

	public:
		virtual	NEKey& getDefaultKey()
		{
			return _default_key;
		}
		virtual const NEKey& getDefaultKey() const
		{
			return _default_key;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
		virtual void release()
		{
			SuperClass::release();

			_release();
		}
		virtual type_result isValid() const
		{
			type_result result = SuperClass::isValid();
			if (NEResult::hasError(result)) return result;

			return _default_key.isValid();
		}
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
		{
			SuperClass::serialize(loader);

			return loader >> _default_key >> _use_peeking_lock >> _origins_peeking_lock >> _is_peeking_lock_activated;
		}
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
		{
			SuperClass::serialize(saver);

			return saver << _default_key << _use_peeking_lock << _origins_peeking_lock << _is_peeking_lock_activated;
		}

	private:
		bool _canActivatePeekingLock(T& target)
		{
			//	Argument 값을 할당:
			//		원본이 Lock이 걸려 있지 않을때만 Argument의 Lock이 적용된다.
			//		다시 말하면, 원본이 Lock이 걸려 있다면, Argument의 값으로 unlock 할 수 없다.
			return ! target.isPeekingLocked();
		}
		type_result _enterPeekingLockMode(T& target)
		{
			_is_peeking_lock_activated = _canActivatePeekingLock(target);
			if( ! _is_peeking_lock_activated)
			{
				_origins_peeking_lock = false;

				return RESULT_SUCCESS | RESULT_ABORT_ACTION;
			}


			//	원본 저장:
			_origins_peeking_lock = target.isPeekingLocked();
			target.isPeekingLocked() = _use_peeking_lock;

			return RESULT_SUCCESS;
		}
		type_result _leavePeekingLockMode(T& target)
		{
			if(isPeekingLockActivated())
			{
				target.isPeekingLocked() = _origins_peeking_lock;
				_origins_peeking_lock = false;
				_is_peeking_lock_activated = false;
			}

			return RESULT_SUCCESS;
		}
		virtual type_result _onPrepareExecute()
		{
			return _enterPeekingLockMode(getValue());
		}
		virtual type_result _onPostExecute()
		{
			return _leavePeekingLockMode(getValue());
		}
		ThisClass& _assign(const ThisClass& source)
		{
			if(this == &source) return *this;

			_default_key = source._default_key;
			_use_peeking_lock = source._use_peeking_lock;
			_origins_peeking_lock = source._origins_peeking_lock;
			_is_peeking_lock_activated = source._is_peeking_lock_activated;

			return *this;
		}
		void _release()
		{
			_default_key.release();
			_use_peeking_lock = false;
			_origins_peeking_lock = false;
			_is_peeking_lock_activated = false;
		}

	private:
		T _default_key;
		bool _is_peeking_lock_activated;
		bool _use_peeking_lock;
		bool _origins_peeking_lock;
	};

	template <>
	class NE_DLL NETArgument<NENodeSelector> : public NETSelectorArgument<NENodeSelector>{};
	template <>
	class NE_DLL NETArgument<NEModuleSelector> : public NETSelectorArgument<NEModuleSelector>{};
	template <>
	class NE_DLL NETArgument<NEKeySelector> : public NETSelectorArgument<NEKeySelector>{};

	template <>
	class NE_DLL NETArgument<NEKey> : public NEArgumentBase	
	{	
	public:	
		typedef NETArgument ThisClass;	
		typedef NEArgumentBase SuperClass;	
		typedef NEKey T;

	public:
		NETArgument();
		NETArgument(const ThisClass& rhs);

	public:
		virtual	NEKey& getDefaultKey();
		virtual const NEKey& getDefaultKey() const;
		virtual NEObject& clone() const;	
	};
}