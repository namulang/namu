#pragma once

namespace NE
{
	//    the Adam class:
	//        the most ancestor of whole classes which are exposed to the World framework.
	//        with existance of Adam, the World can construct the unified hierarchy tree
	//        on NEClassManager.
	//        Adam have 2 children. NEObject and NEUnknown.
	//
	//        NEObject:    
	//            These're reachable descestors from World framework.
	//            Can be instantiated(only if ConcreteClass), know that its Super-class
	//            is, whether it's class template and if so, what it's Trait class, and
	//            so on. Users can fully access with World RTTI functions.
	//            Generally, World will identify what is derived class from NEObject
	//            with 2 ways.            
	//
	//            from built-in classes:
	//                All built-in classes from world frameworks are fetched to NEClass
	//                Manager when it initialize.
	//
	//            from Package fetching:
	//                on initialize Kernel object, ModuleManager try to find and fetch
	//                package whose name is finished with extension ".dll".
	//                while on it, all fetched meta classes are enrolled to hierarchy
	//                tree of NEClassManager.
	//
	//        Unknown:
	//            if World framework think that given classtype isn't belonged to World
	//            frameworks, make it classfied to be derived from Unknown.
	//            In fact, all decestors of unknown aren't reachable by World RTTI.
	//            it means, World doesn't guarranty that which is super class,
	//            whether it's a sort of ADT of Unknowns.
	//            Only limited RTTI will be supported.
	//
	//        To enroll hierarchy tree of ClassManager as World component:
	//            If you want to add your class which isn't belonged to world framework,
	//            there are 3 conditions.
	//        
	//                1.    specify which is Super class of yours with "typedef" keyword.
	//                2.    specify Meta class such as above.
	//                3.    make sure that yours are decestor of NEObject.
	//                    Of course, there is no need to be a direct child of NEObject.
	//
	//            for instance,
	//                class YourADTClass : public NEModule // cond#3. NEModule is one of decestor of NEObject.
	//                {
	//                public:
	//                    typedef NEModule Super; // cond#1
	//                    typedef NETInterface<YourADTClass> MetaClass; // cond#2. if yours are a concrete class, please use NETConcreteClass instead of.
	//                }
	//            if your class doesn't satisfy with all 3 conditions, your one will be classfied to NEUnkown.
	class NE_DLL NEAdam {};
}