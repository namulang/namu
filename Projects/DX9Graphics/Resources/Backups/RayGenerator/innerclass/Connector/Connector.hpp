class NE_DLL Connector : public DependentModuleTemplate::Connector
{
	typedef WindowDependentModule::Connector SuperClass;

public:
	type_result connect(NEKeyCodeSet& keyset)
	{
		SuperClass::connect(keyset);

		if(keyset.getLength() < 3) return RESULT_TYPE_ERROR | RESULT_WRONG_BOUNDARY | RESULT_WRONG_PARAMETER | RESULT_WRONG_POINTER_ADDRESSING;
		for(int n=0; n < 3 ;n++)
			if( ! &keyset[0] ) return RESULT_TYPE_ERROR | RESULT_WRONG_POINTER_ADDRESSING | RESULT_WRONG_PARAMETER | RESULT_WRONG_BOUNDARY;

		_referer_selector = static_cast<NEModuleSelector*>( &(keyset[1]) );
		_camera_selector = static_cast<NEModuleSelector*>( &(keyset[2]) );

		return RESULT_SUCCESS;
	}

public:
	NEModuleSelector& getRefererSelector()
	{
		return *_referer_selector;
	}
	const NEModuleSelector& getRefererSelector() const
	{
		return *_referer_selector;
	}
	NEModuleSelector& getCameraSelector()
	{
		return *_camera_selector;
	}
	const NEModuleSelector& getCameraSelector() const
	{
		return *_camera_selector;
	}

private:
	NEModuleSelector* _referer_selector;
	NEModuleSelector* _camera_selector;
};