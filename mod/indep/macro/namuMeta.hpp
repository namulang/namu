#pragma once

#include "overload.hpp"
#include "forEach.hpp"

// world universal DECL macro:
//  WRD_DECL is generalized API used to describe the metadata of
//  class in namu.
//  WRD_DECL can be used to define detailed metadata about a class by chaining sub-command sets.
//  with WRD macro, I can clarify that those INIT_META, VISIT are should be after of WRD macro.
//  and limit the scope of availbility.
//  these macros which are available only inside of WRD macro are called to sub-commands.
//
// Usage:
//  use WRD_DECL macro at declaration of your class.
//
//  class Foo {
//      WRD_DECL(cmd1(arg1, arg2, ...), cmd2(arg1, arg2, ...), ...)
//
//  public:
//      ...and your codes...
//  };

#define _ON_EACH_DECL(cmd) __WRD__DECL_##cmd
#define WRD(...) WRD_EACH(_ON_EACH_DECL, __VA_ARGS__)
