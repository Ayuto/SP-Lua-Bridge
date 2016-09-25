/**
* =============================================================================
* lua_bridge
* Copyright(C) 2016 Ayuto. All rights reserved.
* =============================================================================
*
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License, version 3.0, as published by the
* Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
* details.
*
* You should have received a copy of the GNU General Public License along with
* this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef _LUA_BRIDGE_HELPERS
#define _LUA_BRIDGE_HELPERS

// ============================================================================
// >> INCLUDES
// ============================================================================
#include "boost/python.hpp"
using namespace boost::python;

#include "LuaBase.h"
using namespace GarrysMod::Lua;


// ============================================================================
// >> DEFINITIONS
// ============================================================================
#ifndef GMMODULE
#define GMMODULE
#endif


// ============================================================================
// >> EXTERNALS
// ============================================================================
extern void InitConverters();


// ============================================================================
// >> TYPEDEFS
// ============================================================================
typedef return_value_policy<return_by_value> return_by_value_policy;
typedef return_value_policy<reference_existing_object> reference_existing_object_policy;


// ============================================================================
// >> ADD_OBJ
// ============================================================================
template<class T>
T* __obj__(void* pPtr)
{
	return (T *) pPtr;
}

// Use this macro to add this class to make_object()
#define ADD_OBJ(classname) \
	.def("_obj", \
		&__obj__<classname>, \
		reference_existing_object_policy() \
	).staticmethod("_obj")


#endif // _LUA_BRIDGE_HELPERS