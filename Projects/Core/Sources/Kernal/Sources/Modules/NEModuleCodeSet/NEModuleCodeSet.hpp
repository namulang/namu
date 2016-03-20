#pragma once

#include "../NETArray/NETArray.hpp"
#include "../NETEnlistableSet/NETEnlistableSet.hpp"
#include "../NEModule/NEModule.hpp"

namespace NE
{
	template 
	class NE_DLL NETArray<type_code, false, NEModule>;
	template 
	class NE_DLL NETEnlistableSet< NETArray<type_code, false, NEModule> >;

	class NE_DLL NEModuleCodeSet : public NETEnlistableSet<NETArray<type_code, false, NEModule> >, public NEExecutable
	{
		typedef NETEnlistableSet<NETArray<type_code, false, NEModule>> _Super;

		NE_DECLARE_CLASS(NEModuleCodeSet, _Super)

	public:
		typedef type_code InnerTrait;
		typedef NEModule OuterTrait;

	public:
		friend class NENode;
		friend class NEKeyCodeSet;
		//friend class NEIndexedNodeSet;

	public:
		NEModuleCodeSet();
		NEModuleCodeSet(type_index size);
		NEModuleCodeSet(const This& source);

	public:
		virtual ~NEModuleCodeSet();

	public:
		const This& operator+=(const This& source);
		This operator+(const This& source) const;

	public:
		virtual type_result execute();

	public:
		virtual type_index insert(type_index, const NEModule& source);
		virtual type_index remove(type_index index);
		virtual type_result resize(type_index new_size);

	public:
		virtual NEModule& getElement(type_index index);
		virtual const NEModule& getElement(type_index index) const;
		virtual type_result setElement(type_index index, const NEModule& source);
		virtual type_index find(const NEModule& source) const;

	public:
		virtual void release();

	protected:
		NEIndexedModuleSet& _getModuleSet();
		const NEIndexedModuleSet& _getModuleSet() const;
		const This& _assign(const This& source);

	private:
		virtual type_result _onEnlisted() { return RESULT_SUCCESS; }
	};
}