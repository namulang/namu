#include "NEModule.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	//	--------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEModule::NEModule()
#pragma warning(push)
#pragma warning(disable: 4355)	//	Warning C4355:	this 포인터를 생성자에서 사용하였다
		: NENamedUnit(), _arguments(this)
	{
		_release();
	}		



	//	--------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	--------------------------------------------------------------------------------
	NE_DLL NEModule::NEModule(const NEModule& source)
		: NENamedUnit(source), _arguments(this, source._arguments)
	{
		_assign(source);
	}


	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEModule::~NEModule()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEModule::operator==(const NEModule& source) const
	{
		if(this == &source) return true;
		if(NENamedUnit::operator==(source) == false) return false;
		if(_arguments != source._arguments) return false;
		
		return true;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEModule::operator!=(const NEModule& source) const
	{
		return !(operator==(source));
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileLoader NE_DLL &NEModule::serialize(NEBinaryFileLoader& loader)
	{
		NENamedUnit::serialize(loader);

		/*
			모듈의 scriptcode는 그대로 저장/로드 되어서는 안된다.
			시스템에 따라서 변경될 수 있기 때문이다.
		*/
		_scriptcode = Kernal::getInstance().getModuleManager().getModule(getHeader()).getScriptCode();

		bindArguments();
		//	왜 BindArguments()를 해주는 가:
		//		NEArgumentSet은 NEArrayTemplate<NEArguement*, true>로써, serialize를 직접 구현해야하나,
		//		아직은 어느 NEArgumentSet인지 가져오는 부분이 구현하지 않았기 때문이다.
		//		그래서 NEModule에서만 NEArgumentSet::serialize를 호출 할 수 있다는 제한을 걸고,
		//		NEArgumentSet::serialize는 "이미 인스턴스가 존재한다" 고 가정하고 serialize(loader)를
		//		수행한다.
		//		그래서, 여기서 이미 인스턴스를 맞춰줄 필요가 있기에, bindArgument를 수행한다.
		
		return _arguments.serialize(loader);	
	}

	NEBinaryFileSaver& NEModule::serialize(NEBinaryFileSaver& saver) const
	{
		NENamedUnit::serialize(saver);

		/*
			Argument의 저장:
				NEKeyNameBinder::serialize를 참고 해보면 상위클래스인 NEKeyBinder를 호출하지 않는다.
				이는 의도적인 행동으로, 바인딩 결과물인 NEKeyBinder 객체의 데이터를 공유하지 않기 위함이다.
					"상위클래스의 바인딩결과 정보는 공유(저장 및 로드)할 수 없다" 
				에 따라, 매 로드시마다 바인딩을 시도 하게 된다.
		*/
		return _arguments.serialize(saver);	//	private 접근자이므로 friend가 효력을 발휘하기 위해 직접 호출한다
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEType::Type NE_DLL NEModule::getType() const
	{
		return NEType::NEMODULE;
	}


	type_result NE_DLL NEModule::_onModuleFetched()
	{
		return RESULT_SUCCESS | RESULT_ABORT_ACTION;
	}

	void NEModule::release()
	{
		SuperClass::release();

		_release();
	}

	type_result NEModule::isValid() const
	{
		type_result result = SuperClass::isValid();
		if(NEResult::hasError(result)) return result;
		result = _arguments.isValid();
		if(NEResult::hasError(result)) return result;

		return RESULT_SUCCESS;
	}

	const NEModule& NEModule::operator=(const ThisClass& rhs)
	{
		if(this == &rhs) return *this;

		SuperClass::operator=(rhs);

		return _assign(rhs);
	}

	void NEModule::_release()
	{
		_arguments.release();
	}

	type_result NEModule::bindArguments()
	{
		NEArgumentInterfaceList tray;
		_onArgumentsFetched(tray);

		return _bindArguments(tray);
	}

	type_result NEModule::_bindArguments(NEArgumentInterfaceList& args)
	{
		_arguments.create(args.getLength());

		type_result r = 0;

		for(int n=0; n < args.getLength() ;n++)
			r |= _arguments.push(args[n]);

		return r;
	}

	type_result NEModule::_onArgumentsFetched(NEArgumentInterfaceList& tray)
	{
		return RESULT_SUCCESS;
	}

	type_result NEModule::initialize()
	{
		bindArguments();

		return RESULT_SUCCESS;
	}

	NEModule& NEModule::_assign(const ThisClass& rhs)
	{
		if(this == &rhs) return *this;

		_arguments = rhs._arguments;	//	NEArgumentSet은 NEArgumentTemplate::operator=를 호출하고, 이는 바인딩 결과물을 제외한 내용들만 할당이 일어나게 된다. => 바인딩 준비 OK

		return *this;
	}

	type_result NEModule::_onExecute()
	{
		return RESULT_SUCCESS;
	}

	type_result NEModule::execute()
	{
		if( ! _arguments.isBinded())
			_arguments.bind();

		return _onExecute();
	}
}
