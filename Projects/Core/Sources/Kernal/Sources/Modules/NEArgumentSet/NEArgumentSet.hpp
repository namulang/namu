#pragma once

#include "../../Commons/Templates/NEArrayTemplate/NEArrayTemplate.hpp"
#include "../../Commons/Units/NEArgumentBase/NEArgumentBase.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<NEArgumentBase*, false>;

	class NE_DLL NEArgumentSet : public NEArrayTemplate<NEArgumentBase*, false>
	{
	public:
		typedef NEArgumentSet ThisClass;
		typedef NEArrayTemplate<NEArgumentBase*, false> SuperClass;

	public:
		NEArgumentSet();
		NEArgumentSet(type_count size);
		NEArgumentSet(const ThisClass& rhs);

	public:
		bool isBinded() const;
		type_result bind();	

	public:
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;	//	virtual을 사용해야 하므로 private임에도 앞에 언더바(_)를 붙이지 않는다
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
	};
}