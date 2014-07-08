class NE_DLL BoundingSphere : public NEObject
{
public:
	BoundingSphere()
	{
		_release();
	}
	BoundingSphere(const BoundingSphere& source)
	{
		_assign(source);
	}

public:
	const BoundingSphere& operator=(const BoundingSphere& source)
	{
		return _assign(source);
	}
	bool operator==(const BoundingSphere& source) const
	{
		if(_center == source._center) return false;
		if(_radius != source._radius) return false;

		return true;
	}
	bool operator!=(const BoundingSphere& source) const
	{
		return ! operator==(source);
	}

public:
	D3DXVECTOR3& getCenter()
	{
		return _center;
	}
	const D3DXVECTOR3& getCenter() const
	{
		return _center;
	}
	float& getRadius()
	{
		return _radius;
	}
	float getRadius() const
	{
		return _radius;
	}
	bool isInitialized() const
	{
		return _radius <= 0.0f;
	}

public:
	virtual void release()
	{
		_center.x = 0.0f;
		_center.y = 0.0f;
		_center.z = 0.0f;
		_radius = 0.0f;
	}
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _center.x << _center.y << _center.z << _radius;
	}
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _center.x >> _center.y >> _center.z >> _radius;
	}
	virtual NEObject& clone() const
	{
		return *(new BoundingSphere(*this));
	}
	virtual type_result isValid() const
	{
		if(_radius <= 0.0f) return RESULT_TYPE_ERROR;

		return RESULT_SUCCESS;
	}

private:
	void _release()
	{
		_center.x = 0.0f;
		_center.y = 0.0f;
		_center.z = 0.0f;
		_radius = 0.0f;
	}
	const BoundingSphere& _assign(const BoundingSphere& source)
	{
		if(this == &source) return *this;

		_center = source._center;
		_radius = source._radius;

		return *this;
	}	

private:
	D3DXVECTOR3 _center;
	float _radius;
};