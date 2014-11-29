#pragma once

#include "../WNDSpy/WNDSpy.hpp"

namespace NE
{
	class NE_DLL CharInputSpy : public WNDSpy
	{
	public:
		typedef CharInputSpy ThisClass;
		typedef WNDSpy SuperClass;

	public:
		NETArgument<NEModuleSelector> arg_window_selector;
		NETArgument<NETStringKey> arg_sentence;
		NETArgument<NEUIntKey> arg_max_delay;

	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray);
		virtual type_result _onFetchModule();
		virtual type_result _onExecute();

	public:
		CharInputSpy();

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;

	public:
		virtual void release();
		virtual NEObject& clone() const;
		/*
			왜 _delay_start_time은 serialize 하지 않는가:
				_delay_start_time은 프로그램이 개시후 얼마나 지났는가를 timeGetTime로부터의 
				값으로 저장한다. 그런데 timeGetTime은 우리가 setter할 수 없으므로,
				_delay_start_time을 저장 할 수 없다.
		*/
	private:
		int _delay_start_time;
	};
}