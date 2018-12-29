#pragma once

namespace wrd
{
	template <typename T>
	class _TGet {
	public:
		static T& get(T& expr) {
			return store() = expr;
		}
		static T& store() {
			static T inner;
			return inner;
		}
	};
	template <typename T>
	class _TGet<T*> {
	public:
	   static T* get(T* trg) {
		   return *store() = trg;
	   }
	   static T** store() {
		   static T* inner;
		   return &inner;
	   }
	};
}
