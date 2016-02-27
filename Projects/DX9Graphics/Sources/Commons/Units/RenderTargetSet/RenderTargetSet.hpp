#pragma once 

#include "../RenderTarget/RenderTarget.hpp"

namespace DX9Graphics
{
	/*
	왜	RenderTarget*, true로 생성하는가:
	RenderTarget생성자를 보면 알 수 있다. ShaderProgram*를 가져야 하는, 디자인
	패턴을 사용하므로 기본생성자로는 생성할 수 없기 때문이다.
	*/
	template
	class NE_DLL NETArray<RenderTarget*, true>;

	class NE_DLL RenderTargetSet : public NETArray<RenderTarget*, true>
	{
	public:
		typedef NETArray<RenderTarget*, true> SuperClass;
		typedef RenderTargetSet ThisClass;
		typedef RenderTarget Trait;

	public:
		RenderTargetSet()
			: SuperClass()
		{
			_filled_target_index = 0;
		}

	public:
		type_result notifyTargetFilled()
		{
			_filled_target_index++;
			_filled_target_index %= 2;

			return RESULT_SUCCESS;
		}
		Trait& getFilledTarget()
		{
			return getElement(_filled_target_index);
		}
		const Trait& getFilledTarget() const
		{
			return getElement(_filled_target_index);
		}
		Trait& getEmptyTarget()
		{
			return getElement(getEmptyTargetIndex());
		}
		const Trait& getEmptyTarget() const
		{
			return getElement(getEmptyTargetIndex());
		}
		type_int getFilledTargetIndex() const { return _filled_target_index; }
		type_int getEmptyTargetIndex() const
		{
			return (_filled_target_index + 1) % getSize();
		}

	public:
		virtual void release()
		{
			SuperClass::release();

			_filled_target_index = 0;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	public:
		type_result initialize(DX9& dx9);

	private:
		type_int _filled_target_index;
	};
}