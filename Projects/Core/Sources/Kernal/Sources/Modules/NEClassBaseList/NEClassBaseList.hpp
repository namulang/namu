//	Comments:	
//	Memo	:
//	Author	:	2016-02-27	kniz
//	---------------------------------------------------------------------------------

#pragma once

#include "../NEClassBase/NEClassBase.hpp"
#include "../NETList/NETList.hpp"

namespace NE
{
	//	Why this class should be declared to class explicitly:
	//		Because of possibility of being used to forward-declaration, 
	//		This has to be as class, not typedef such as 
	//
	//			"typedef NETList<NEClassBase*, true> NEClassBaseList;
	template
	class NE_DLL NETList<NEClassBase*, true>;

	class NE_DLL NEClassBaseList : public NETList<NEClassBase*, true>
	{
		//	to sidestep against wrong argument parsing of the macro below 
		//	for preprocessor:
		//		if original class name witch starts with 'NETList<NE~~" 
		//		is used as argument of the DECLARE_CLASS argument,
		//		that macro will be regonize that you give to it 3 arguments
		//		not 2, because of comma of the class template's one.		
		typedef NETList<NEClassBase*, true> _Super;
		
		NE_DECLARE_CLASS(NEClassBaseList, Super)
	public:
		NEClassBaseList();
		NEClassBaseList(const This& rhs);
	public:
		virtual ~NEClassBaseList();
	};
}