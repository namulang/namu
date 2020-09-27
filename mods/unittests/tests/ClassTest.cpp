#include "../TestManager.hpp"

WRD_TEST_START(ClassTest)
	//	basic:
	{
		TClass<Thing> cls;
		T( ! cls.isTemplate())
		T(cls.isADT())
		const Classes& subs = cls.getSubs();
		T(subs.isExist())
		T(subs.getLen())
		T(subs.getSize())
		T( ! cls.instance().isBind())
		const Classes& sups = cls.getSupers();
		T(sups.isExist())
		T(sups.getLen() == 0)
		T(sups.getSize() == 0)
		T(cls == cls.getSuper())

		TClass<Instance> ins;
		T(ins.isSub(cls))
		T(ins.isSubCls(cls))
		T(ins.getSuper().isExist())
		T(ins.getSuper() == cls)
		TStrong<TClass<Instance> > cloned = ins.clone();
		T(cloned.isExist())
		T(cloned.isBind())
		T(*cloned == ins)
		//TODO: cls.getLeafs().isExist())
		// TODO: checks TClass<Instance> is one of subs using has() or check() API on Container.
	}

	//	super & sub:
	{
		TClass<Thing> thg;
		const Classes& subs = thg.getSubs();
		T(subs.isExist())
		T(subs.getLen() > 0)
		for(int n=0; n < subs.getLen() ;n++)
		{
			const Node& e = subs[n];
			T(e.isExist())
			const Class& c = e.down<Class>();
			T(c.isExist())
			T(e.getSuper() == thg)
		}
	}
	return "";
WRD_TEST_END(ClassTest)
