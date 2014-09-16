#include "NECodeSet.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NECodeSet::NECodeSet()
		: SuperClass()
	{
		_type = NECodeType::UNDEFINED;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NECodeSet::NECodeSet(type_count size)
		: SuperClass(size)
	{
		_type = NECodeType::UNDEFINED;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NECodeSet::NECodeSet(const NECodeSet& source)
		: SuperClass(source)
	{
		_type = source._type;
	}

	NECodeSet::NECodeSet(NECodeType::CodeType initial_type)
		: SuperClass()
	{
		setCodeType(initial_type);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NECodeSet::~NECodeSet()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NECodeSet NE_DLL &NECodeSet::operator+=(const NECodeSet& source)
	{
		SuperClass::operator+=(source);

		return *this;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NECodeSet NE_DLL NECodeSet::operator+(const NECodeSet& source) const
	{
		NECodeSet buffer(getSize() + source.getSize());

		buffer.push(*this);
		buffer.push(source);
		
		return buffer;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEType::Type NE_DLL NECodeSet::getType() const
	{
		return NEType::NECODE_SET;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-19	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	//	save는 기존의 NEPointerArray로도 가능하다
	NEBinaryFileSaver NE_DLL &NECodeSet::serialize(NEBinaryFileSaver& saver) const
	{	
		saver << (type_uint) _type;
		if(_type == NECodeType::SCRIPT)
			return _serializeByScript(saver);

		return SuperClass::serialize(saver);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-19	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileLoader NE_DLL &NECodeSet::serialize(NEBinaryFileLoader& loader)
	{	
		type_uint bucket = 0;
		loader >> bucket;
		_type = NECodeType::CodeType(bucket);
		if(_type == NECodeType::SCRIPT)
			return _serializeByScript(loader);

		return SuperClass::serialize(loader);		
	}

	NEObject NE_DLL &NECodeSet::clone() const
	{
		return *(new ThisClass(*this));
	}

	type_index NECodeSet::insert(type_index index, const NEExportable::Identifier& identifier)
	{
		if(_type == NECodeType::SCRIPT)
		{
			const NEModule& fetched = Kernal::getInstance().getModuleManager().getModule(identifier);
			if( ! &fetched)
			{
				KERNAL_ERROR("주어진 Identifier로 모듈을 가져오지 못했습니다.");
			}
			return insert(index, fetched.getScriptCode());
		}

		KERNAL_ERROR("Script용 CodeSet이 아닌데요");
		return NE_INDEX_ERROR;
	}

	type_index NECodeSet::push(const NEExportable::Identifier& identifier)
	{
		return insert(getLength(), identifier);
	}

	type_index NECodeSet::pushFront(const NEExportable::Identifier& identifier)
	{
		return insert(0, identifier);
	}

	type_result NECodeSet::setCodeType(NECodeType::CodeType type)
	{ 
		using namespace NECodeType;
		switch(type)
		{
		case SCRIPT:	case GROUP:	case NAME:	case PRIORITY:
			_type = type; 
			return RESULT_SUCCESS;
		}

		KERNAL_ERROR("잘못된 NECodeType 입니다.");
		return RESULT_TYPE_ERROR;			
	};

	NECodeType::CodeType NECodeSet::getCodeType() const
	{
		return _type;
	}

	void NECodeSet::release()
	{
		_type = NECodeType::UNDEFINED;

		return SuperClass::release();
	}

	NEBinaryFileSaver& NECodeSet::_serializeByScript(NEBinaryFileSaver& saver) const
	{
		//	pre:
		//		타겟팅:
		const NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		//		길이정보 저장:
		saver << _size << _length;


		//	main:		
		//		모듈 저장 시작:	현재 입력된 코드들은 이미 모듈매니져에 등록된 모듈의 스크립트 
		//						아이디와 동기화 되어 있다는 전제하에 진행한다.
		NEExportable::Identifier itr;
		for(type_index n=0; n < _length ;n++)
		{			
			type_code script_code = getElement(n);
			const NEModule& module = moduler.getModuleSet()[script_code];
			if( ! &module )
			{
				KERNAL_ERROR("모듈이 없습니다.");
				continue;
			}

			itr = module.getHeader();
			saver << itr;
		}


		//	post:
		return saver;
	}

	NEBinaryFileLoader& NECodeSet::_serializeByScript(NEBinaryFileLoader& loader)
	{
		//	pre:
		//		타겟팅:
		const NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		//		길이 정보 로드:
		int	length	= 0,
			size	= 0;
		loader >> size >> length;
		create(size);


		//	main:
		//		모듈 로드 시작:
		NEExportable::Identifier identifier;
		for(type_index n=0; n < length ;n++)
		{	
			loader >> identifier;

			const NEModule& module = moduler.getModule(identifier);
			type_code script_code = &module ? module.getScriptCode() : -1;

			push(script_code);
		}


		//	post:
		return loader;
	}

}