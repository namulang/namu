#pragma once

#include "../../Commons/Templates/NEArrayTemplate/NEArrayTemplate.hpp"
#include "../../Commons/Units/NEArgumentBase/NEArgumentBase.hpp"
#include "../NEArgumentInterfaceList/NEArgumentInterfaceList.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<NEArgumentBase*, true>;
	
	class NE_DLL NEArgumentSet : public NEArrayTemplate<NEArgumentBase*, true>
	{
	public:
		typedef NEArgumentSet ThisClass;
		typedef NEArrayTemplate<NEArgumentBase*, true> SuperClass;

	public:
		friend class NEModule;	//	NEModule 내에서만 serialize를 사용하도록 하기 위함.

	public:
		using SuperClass::insert;
		using SuperClass::push;
		using SuperClass::pushFront;
		using SuperClass::create;

	public:
		NEArgumentSet();
		NEArgumentSet(type_count size);
		NEArgumentSet(const ThisClass& rhs);

	public:
		ThisClass& operator=(const ThisClass& rhs);

	public:	
		type_result bind(NEArgumentInterfaceList& basises);
		type_index push(NEArgumentInterfaceBase& basis);
		type_index pushFront(NEArgumentInterfaceBase& basis);
		type_index push(NEArgumentInterfaceList& basises);
		type_index insert(type_index index, NEArgumentInterfaceBase& basis);

	public:
		bool isBinded() const;
		type_result bind();	

	private:	//	!Important private임에 유의하라. 자세한 내용은 serialize(NEBinaryFileSaver& saver) const의 구현부 주석을 참조할 것
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;	//	virtual을 사용해야 하므로 private임에도 앞에 언더바(_)를 붙이지 않는다
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
	};
}