//	---------------------------------------------------------------------------------
//	클래스명:	NETKeySelector
//	설명	:	키 선택자. 
//				노드 선택자, 모듈 선택자를 각각 하나씩 가지고 있으며, 노드 선택자가 
//				가져온 노드를 타겟으로 삼아 모듈을 선택(Select)한다.
//				노드 선택자의 종류 * 모듈 선택자의 종류 만큼의 클래스가 존재하게 된다.
//	관계	:	기반클래스.	NEKey
//	특성	:	1	노드선택자를 멤버변수로 가지고 있다.
//				2	!주의!	부분 serialize를 지원하지 않는다!
//							자세한 사항은 NENodeSelector의 헤더를 참조.
//	알고리즘:	파생클래스의 알고리즘을 따른다.
//	사용방법:	getNode()로 노드를 선택한다.
//				getModule()로 노드를 선택한다.
//				이 때, getModule()을 실행하면 내부에서 getNode()를 실행하므로 둘을
//				섞어서 사용하면 안된다.
//	메모	:	
//	히스토리:	2011-08-04	이태훈	작성
//	---------------------------------------------------------------------------------
//	extend, assign 무한 루프 이슈:
//		source는 this를 selector로 포함시키고,
//		this는 source를 포함시키는 상태에서 extend 혹은 assign을 하면
//		무한 루프를 돌게 된다.
//
//	Selector 연산 정책:
//		같은 KeySelector끼리는 셀렉터 끼리의 assign, isLower, isEqualTo (이하 모든 연산)
//		을 수행한다.
//		KeySelector가 아닌 Key를 일반Key라고 하자.
//		일반키와 KeySelector의 경우에는, 
//			*this(Selector).assign/add/multiply(일반Key)의 경우는 this가 참조하는 첫번째키만 assign을 한다.
//			다만, result가 this인 경우에는 참조하는 키 각각에 대해서 연산한다.
//			예)
//				KeySelector k1, k2;  NEIntKey src, src0, src1, src2, trg;
//				// k1은 src0, src1, src2, k2를 가리키고 있을때,
//				k1.assign(trg, src);	//	trg = src0 + src 처럼 동작한다.
//				k1.assign(k1, src);		//	src0 = src0 + src
//										//	src1 = src1 + src
//										//	src2 = src2 + src 가 각각 수행된다.
//										//	k2는 셀렉터이므로, "셀렉터 = 셀렉터" 
//										//	연산이 되기에 수행하지 않는다.
//				k1 += src;				//	도 assign(k1, src)와 같다.
//
//		이하 isLower, isEqualTo는 this가 참조하는 키들 각각에 대해서 연산한다.
#pragma once

//	include:
#include "../NETModuleSelector/NETModuleSelector.hpp"
#include "../NEKeyBinder/NEKeyBinder.hpp"

namespace NE
{		
	template <typename NodeSelector, NEType::Type type> 
	class NETKeySelector : public NodeSelector
	{
		NE_DECLARE_CLASS(NETKeySelector, NENodeSelector)

	public:
		typedef This Trait;

		//	생성자:
	public:
		NETKeySelector(const NETString& keyname = "");
		NETKeySelector(NEType::Type manager_type, const NETString& keyname = "");
		NETKeySelector(const NETKeySelector& source);

		//	소멸자:
	public:
		virtual ~NETKeySelector();

		//	연산자 오버로딩:
	public:
		const NETKeySelector& operator=(const NETKeySelector& source);
		const NETKeySelector& operator=(const NEKey& source);
		bool operator==(const NETKeySelector& source) const;
		bool operator!=(const NETKeySelector& source) const;

	public:
		Trait& getValue() { return *this; }	//	NEKey에 대한 클래스 템플릿 호환을 위해 만들어둔다.
		const Trait& getValue() const { return *this; }
		const NETString& getKeyName() const { return _keyname; }
		void setKeyName(const NETString& new_name);
		//	인터페이스:	
		//		상속:
		//			NEKeySelectorInterface:
	public:
		virtual type_result initializeReferingPoint()
		{
			SuperClass::initializeReferingPoint();		

			_is_key_returned_once = false;

			if(_binder.isBinded()) return RESULT_SUCCESS;

			_key_index = NE_INDEX_ERROR;
			_binder.release();

			return RESULT_SUCCESS;
		}
		virtual type_result bind();
		virtual type_result unbind();
		virtual type_bool isBinded() const;

	public:
		virtual type_result assign(const NEKey& source);
		virtual type_result add(NEKey& result, const NEKey& operand2) const;
		virtual type_result multiply(NEKey& result, const NEKey& operand2) const;
		virtual bool isEqualTo(const NEKey& source) const;
		virtual bool isLower(const NEKey& source) const;
		virtual void releaseValue();

	public:
		//			NEObject:
		virtual void release();
		virtual NEObject& clone() const;
		virtual NEType::Type getType() const;
		virtual type_result isValid() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	public:
		type_index getKeyIndex() const;
		NEKey& getKey();
		NEKey& peekKey();
		const NEKey& peekKey() const;
		NEKeyBinder& getBinder();
		const NEKeyBinder& getBinder() const;
		type_bool& isUsingAutoBinding();
		type_bool isUsingAutoBinding() const;

	protected:
		void _release();
		const NETKeySelector<NodeSelector, type>& _assign(const NETKeySelector<NodeSelector, type>& source);
		NEKey& _getKeyByBinder();

	private:
		typedef type_result (NEKey::*BinaryOperation)(NEKey&, const NEKey&) const;
		type_result _operateToReferencingKeys(BinaryOperation method, NEKey& result, const NEKey& operand2) const;
		typedef bool (NEKey::*UnaryOperation)(const NEKey&) const;
		bool _operateToReferencingKeys(UnaryOperation method, const NEKey& source) const;
		NEKey& _findKeyByName(NEKeyCodeSet& keyset);

		//	멤버변수:
	private:
		type_index _key_index;
		NETString _keyname;
		NEKeyBinder	_binder;
		type_bool _use_auto_binding;
		type_bool _is_key_returned_once;
	};
}

#include "NETKeySelector.inl"