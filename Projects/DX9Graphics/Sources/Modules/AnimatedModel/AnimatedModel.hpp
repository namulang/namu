#pragma once

#include "../Model/Model.hpp"

namespace DX9Graphics
{
	class TabledTexture;

	class NE_DLL AnimatedModel : public Model
	{
	public:
		typedef AnimatedModel ThisClass;
		typedef Model SuperClass;

	public:
		AnimatedModel()
			: SuperClass()
		{
			_release();
		}
		AnimatedModel(const ThisClass& source)
			: SuperClass(source)
		{
			_assign(source);
		}
		~AnimatedModel()
		{
			
		}

	public:
		const ThisClass& operator=(const ThisClass& source)
		{
			SuperClass::operator=(source);

			return _assign(source);
		}
		bool operator==(const ThisClass& source) const
		{
			if(SuperClass::operator!=(source)) return false;
			return _delay == source._delay;
		}
		bool operator!=(const ThisClass& source) const
		{
			return ! operator==(source);
		}

	public:
		type_int& getAnimationIndex()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_int&>(consted_this->getAnimationIndex());
		}
		const type_int& getAnimationIndex() const
		{
			const NEKey& somekey = getKeySet()[21];
			if( ! somekey.isSubClassOf(NEType::NEINT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 21번키가 NEINT_KEY키여야 합니다.");
				const type_int* nullpoint = 0;
				return *nullpoint;
			}

			const NEIntKey& target = static_cast<const NEIntKey&>(somekey);
			return target.getValue();
		}
		type_int& getKeyFrame()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_int&>(consted_this->getKeyFrame());
		}
		const type_int& getKeyFrame() const
		{
			const NEKey& somekey = getKeySet()[22];
			if( ! somekey.isSubClassOf(NEType::NEINT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 22번키가 NEINT_KEY키여야 합니다.");
				const type_int* nullpoint = 0;
				return *nullpoint;
			}

			const NEIntKey& target = static_cast<const NEIntKey&>(somekey);
			return target.getValue();
		}	
		type_int& getDelayPerFrame()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_int&>(consted_this->getDelayPerFrame());
		}
		const type_int& getDelayPerFrame() const
		{
			const NEKey& somekey = getKeySet()[23];
			if( ! somekey.isSubClassOf(NEType::NEINT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 23번키가 NEINT_KEY키여야 합니다.");
#pragma warning(push)
#pragma warning(disable: 4172)
				const type_int* nullpoint = 0;
				return *nullpoint;
#pragma warning(pop)
			}

			const NEIntKey& target = static_cast<const NEIntKey&>(somekey);
			return target.getValue();
		}
		type_int getDelay() const { return _delay; }
		type_result setDelay(type_int new_delay) { _delay = new_delay; return RESULT_SUCCESS; 	}

	public:
		virtual type_result execute();
		virtual type_result initialize()
		{
			SuperClass::initialize();

			NEKeyCodeSet& keyset = getKeySet();
			keyset.resize(keyset.getSize() + 3);
			keyset.push(NEIntKey(0));				//	20:	AnimationIndex
			keyset.push(NEIntKey(0));				//	21:	FrameKey
			keyset.push(NEIntKey(-2));				//	22:	DelayPerFrame. -1은 AUTO로, TabledTexture에 할당된 Delay 타임을 그대로 사용한다.

			return RESULT_SUCCESS;
		}
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
		virtual void release()
		{
			SuperClass::release();
			
			_release();
		}

	private:
		type_result _adjustValuesBy(const TabledTexture& tabled);
		type_result _updateDelayBy(const TabledTexture& tabled_has_max_delay);
		void _release()
		{
			_delay = 0;
		}
		ThisClass& _assign(const ThisClass& source)
		{
			if(this == &source) return *this;

			_delay = source._delay;

			return *this;
		}

	private:
		type_int _delay;
	};
}