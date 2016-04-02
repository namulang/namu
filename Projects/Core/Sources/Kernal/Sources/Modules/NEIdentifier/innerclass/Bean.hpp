///	@class	Beans
/// @brief	innerclass of @NEIdentifier.
///			Because NEIdentifier can be wrapped by its inheritted class, it can'
///			t have actual memberdata. For convenience of users, we'll declare th
///			at Wrapper class to derived one of NEIdentifier.
///			So in conclusion, if we make decision that NEIdentifier hold these m
///			emeberdata, it makes happen to its wrapper class also have useless m
///			emberdata.
///			So we should let NEIdentifer have pointer of Bean, in order to deter
///			mine for its derived class whether want to have these memberdata or n
///			ot.
struct NE_DLL Bean 
{
	NETString	name;
	NETString	author;
	type_int	interface_revision;
};

class NEPackage;

union NE_DLL BeanOrWrapper
{
	Bean* bean;
	NEPackage* package;
};