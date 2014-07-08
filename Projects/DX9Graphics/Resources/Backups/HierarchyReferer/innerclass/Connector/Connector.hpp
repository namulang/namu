class NE_DLL Connector : public Referer::Connector
{
	typedef Referer::Connector SuperClass;

public:
	type_result connect(NEKeyCodeSet& keyset)
	{
		SuperClass::connect(keyset);

		if(keyset.getLength() < 5) return RESULT_TYPE_ERROR | RESULT_WRONG_BOUNDARY | RESULT_WRONG_PARAMETER | RESULT_WRONG_POINTER_ADDRESSING;
		for(int n=1; n < 5 ;n++)
			if( ! &keyset[n] ) return RESULT_TYPE_ERROR | RESULT_WRONG_POINTER_ADDRESSING | RESULT_WRONG_PARAMETER | RESULT_WRONG_BOUNDARY;

		_face_type = static_cast<NEUByteKey*>( &(keyset[3]) );
		_ball_size = static_cast<NEFloatKey*>( &(keyset[4]) );

		return RESULT_SUCCESS;
	}

public:
	NEUByteKey& getFaceType()
	{
		return *_face_type;
	}
	const NEUByteKey& getFaceType() const
	{
		return *_face_type;
	}
	NEFloatKey& getBallSize()
	{
		return *_ball_size;
	}
	const NEFloatKey& getBallSize() const
	{
		return *_ball_size;
	}

private:
	NEUByteKey* _face_type;
	NEFloatKey* _ball_size;
};