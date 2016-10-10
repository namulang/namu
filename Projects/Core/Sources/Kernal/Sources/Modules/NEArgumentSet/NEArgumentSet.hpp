#pragma once

#include "../NETVector/NETVector.hpp"
#include "../NEArgumentBase/NEArgumentBase.hpp"
#include "../NETShallower/NETShallower.hpp"

namespace NE
{
	template
	class NE_DLL NETShallower<NETVector<NEArgumentBase>>;

	class NE_DLL NEArgumentSet : public NETShallower<NETVector<NEArgumentBase>>
	{
		typedef NETShallower<NETVector<NEArgumentBase>> _Super;

		NE_DECLARE_CLASS(NEArgumentSet, _Super)

	public:
		NEArgumentSet();
		NEArgumentSet(type_count size);
		NEArgumentSet(const This& rhs);

	public:
		type_bool isBinded() const;
		type_result bind();	

	public:
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;	//	virtual을 사용해야 하므로 private임에도 앞에 언더바(_)를 붙이지 않는다
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
	};
}