class NE_DLL Connector : public Camera::Connector
{
	typedef Camera::Connector SuperClass;
public:
	type_result connect(NEKeyCodeSet& keyset)
	{
		SuperClass::connect(keyset);

		if(keyset.getLength() < 28) return RESULT_TYPE_ERROR | RESULT_WRONG_BOUNDARY | RESULT_WRONG_PARAMETER | RESULT_WRONG_POINTER_ADDRESSING;
		for(int n=20; n < 28 ;n++)
			if( ! &keyset[n] ) return RESULT_TYPE_ERROR | RESULT_WRONG_POINTER_ADDRESSING | RESULT_WRONG_PARAMETER | RESULT_WRONG_BOUNDARY;

		_fovy = static_cast<NEFloatKey*>( &(keyset[21]) );
		_aspect = static_cast<NEFloatKey*>( &(keyset[22]) );
		_z_near = static_cast<NEFloatKey*>( &(keyset[23]) );
		_z_far = static_cast<NEFloatKey*>( &(keyset[24]) );
		_light_x = static_cast<NEFloatKey*>( &keyset[25] );
		_light_y = static_cast<NEFloatKey*>( &keyset[26] );
		_light_z = static_cast<NEFloatKey*>( &keyset[27] );

		return RESULT_SUCCESS;
	}

public:
	NEFloatKey& getFOVY()
	{
		return *_fovy;
	}
	const NEFloatKey& getFOVY() const
	{
		return *_fovy;
	}
	NEFloatKey& getAspect()
	{
		return *_aspect;
	}
	const NEFloatKey& getAspect() const
	{
		return *_aspect;
	}
	NEFloatKey& getZNear()
	{
		return *_z_near;
	}
	const NEFloatKey& getZNear() const
	{
		return *_z_near;
	}
	NEFloatKey& getZFar()
	{
		return *_z_far;
	}
	const NEFloatKey& getZFar() const
	{
		return *_z_far;
	}
	NEFloatKey& getLightX() { return *_light_x;}
	const NEFloatKey& getLightX() const { return *_light_x; }
	NEFloatKey& getLightY() { return *_light_y; }
	const NEFloatKey& getLightY() const {return *_light_y;}
	NEFloatKey& getLightZ() { return *_light_z; }
	const NEFloatKey& getLightZ() const { return *_light_z; }

private:
	NEFloatKey* _fovy;
	NEFloatKey* _aspect;
	NEFloatKey* _z_near;
	NEFloatKey* _z_far;
	NEFloatKey* _light_x;
	NEFloatKey* _light_y;
	NEFloatKey* _light_z;
};