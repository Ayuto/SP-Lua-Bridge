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

// ============================================================================
// >> INCLUDES
// ============================================================================
#include "boost/python.hpp"
using namespace boost::python;


// ============================================================================
// >> CONVERTERS
// ============================================================================
struct void_ptr_to_python
{
    void_ptr_to_python()
    {
        to_python_converter< void*, void_ptr_to_python >();
    }

    static PyObject* convert(void* pPtr)
    {
        static object Pointer = import("memory").attr("Pointer");
        return incref(Pointer((unsigned long) pPtr).ptr());
    }
};

struct void_ptr_from_python
{
    void_ptr_from_python()
    {
        boost::python::converter::registry::insert(
            &convert,
            boost::python::type_id<void>()
        );
    }

    static void* convert(PyObject* pObj)
    {
        object obj = object(handle<>(borrowed(pObj)));
        unsigned long ulAddr = extract<unsigned long>(obj.attr("address"));
        return (void *) ulAddr;
    }
};


// ============================================================================
// >> FUNCTIONS
// ============================================================================
void InitConverters()
{
	void_ptr_to_python();
	void_ptr_from_python();
}
