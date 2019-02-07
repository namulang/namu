#pragma once

namespace wrd
{
	template <typename T>
	class _TGet {
	public:
		static T& set(T& expr) { return *store() = &expr, get(); }
		static T& get() { return **store(); }
		static T** store() {
			static T* inner = 0;
			return &inner;
		}
	};
	template <typename T>
	class _TGet<T*> {
	public:
	   static T* set(T* trg) { return *store() = trg; }
	   static T* get() { return *store(); }
	   static T** store() {
		   static T* inner = 0;
		   return &inner;
	   }
	};
	template <typename T>
	class _TGet<T&> {
	public:
		static T& set(T& expr) { return *store() = &expr, get(); }
		static T& get() { return **store(); }
		static T** store() {
			static T* inner = 0;
			return &inner;
		}
	};
}
