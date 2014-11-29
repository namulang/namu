#include "NEArgumentInterfaceList.hpp"

namespace NE
{
	NEBinaryFileSaver& NEArgumentInterfaceList::serialize(NEBinaryFileSaver& saver) const
	{
		for (const SuperClass::Iterator* itr = getIterator(0); itr; itr = itr->getNext())
			saver << itr->getValue();

		return saver;
	}

	NEBinaryFileLoader& NEArgumentInterfaceList::serialize(NEBinaryFileLoader& loader)
	{
		for (SuperClass::Iterator* itr = getIterator(0); itr; itr = itr->getNext())
			loader >> itr->getValue();

		return loader;
	}

	NEObject& NEArgumentInterfaceList::clone() const
	{
		return *(new ThisClass(*this));
	}
}