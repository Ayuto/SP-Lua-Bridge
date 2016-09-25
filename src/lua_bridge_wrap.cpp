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
// Lua Bridge
#include "lua_bridge_helpers.h"

// GMod
#include "LuaBase.h"
#include "Types.h"
#include "Interface.h"
#include "UserData.h"

using namespace GarrysMod::Lua;
using namespace GarrysMod::Lua::Type;



// ============================================================================
// >> Expose the lua_bridge module
// ============================================================================
void expose_lua_base();
void expose_special();
void expose_lua_type();
void expose_lua_state();
void expose_user_data();


BOOST_PYTHON_MODULE(_lua_bridge)
{
    // Initialize converters
    InitConverters();
    
    // Expose classes
    expose_lua_base();
    expose_special();
    expose_lua_type();
    expose_lua_state();
    expose_user_data();
}


// ============================================================================
// >> Expose LuaBase class
// ============================================================================
void expose_lua_base()
{
    class_<ILuaBase, boost::noncopyable> LuaBase("LuaBase", no_init);
    
    LuaBase.def(
        "top",
        &ILuaBase::Top
    );
    
    LuaBase.def(
        "push",
        &ILuaBase::Push
    );
    
    LuaBase.def(
        "pop",
        &ILuaBase::Pop,
        (arg("amount")=1)
    );
    
    LuaBase.def(
        "get_table",
        &ILuaBase::GetTable
    );
    
    LuaBase.def(
        "get_field",
        &ILuaBase::GetField
    );
    
    LuaBase.def(
        "set_field",
        &ILuaBase::SetField
    );
    
    LuaBase.def(
        "create_table",
        &ILuaBase::CreateTable
    );
    
    LuaBase.def(
        "set_table",
        &ILuaBase::SetTable
    );
    
    LuaBase.def(
        "set_meta_table",
        &ILuaBase::SetMetaTable
    );
    
    LuaBase.def(
        "get_meta_table",
        &ILuaBase::GetMetaTable
    );
    
    LuaBase.def(
        "call",
        &ILuaBase::Call
    );
    
    LuaBase.def(
        "pcall",
        &ILuaBase::PCall
    );
    
    LuaBase.def(
        "equal",
        &ILuaBase::Equal
    );
    
    LuaBase.def(
        "raw_equal",
        &ILuaBase::RawEqual
    );
    
    LuaBase.def(
        "insert",
        &ILuaBase::Insert
    );
    
    LuaBase.def(
        "remove",
        &ILuaBase::Remove
    );
    
    LuaBase.def(
        "next",
        &ILuaBase::Next
    );
    
    LuaBase.def(
        "new_user_data",
        &ILuaBase::NewUserdata,
        return_value_policy<return_by_value>()
    );
    
    LuaBase.def(
        "throw_error",
        &ILuaBase::ThrowError
    );
    
    LuaBase.def(
        "check_type",
        &ILuaBase::CheckType
    );
    
    LuaBase.def(
        "arg_error",
        &ILuaBase::ArgError
    );
    
    LuaBase.def(
        "raw_get",
        &ILuaBase::RawGet
    );
    
    LuaBase.def(
        "raw_set",
        &ILuaBase::RawSet
    );
    
    LuaBase.def(
        "get_string",
        &ILuaBase::GetString,
        (arg("stack_pos")=-1)
    );
    
    LuaBase.def(
        "get_number",
        &ILuaBase::GetNumber,
        (arg("stack_pos")=-1)
    );
    
    LuaBase.def(
        "get_bool",
        &ILuaBase::GetBool,
        (arg("stack_pos")=-1)
    );
    
    /*
    LuaBase.def(
        "get_cfunction",
        &ILuaBase::GetCFunction,
        (arg("stack_pos")=-1)
    );
    */
    
    LuaBase.def(
        "get_user_data",
        &ILuaBase::GetUserdata,
        (arg("stack_pos")=-1),
        return_by_value_policy()
    );
    
    LuaBase.def(
        "push_nil",
        &ILuaBase::PushNil
    );
    
    LuaBase.def(
        "push_string",
        &ILuaBase::PushString,
        (arg("value"), arg("length")=0)
    );
    
    LuaBase.def(
        "push_number",
        &ILuaBase::PushNumber
    );
    
    LuaBase.def(
        "push_bool",
        &ILuaBase::PushBool
    );
    
    /*
    LuaBase.def(
        "push_cfunction",
        &ILuaBase::PushCFunction
    );
    
    LuaBase.def(
        "push_cclosure",
        &ILuaBase::PushCClosure
    );
    */
    
    LuaBase.def(
        "push_user_data",
        &ILuaBase::PushUserdata
    );
    
    LuaBase.def(
        "create_reference",
        &ILuaBase::ReferenceCreate
    );
    
    LuaBase.def(
        "free_reference",
        &ILuaBase::ReferenceFree
    );
    
    LuaBase.def(
        "push_reference",
        &ILuaBase::ReferencePush
    );
    
    LuaBase.def(
        "push_special",
        &ILuaBase::PushSpecial
    );
    
    LuaBase.def(
        "is_type",
        &ILuaBase::IsType
    );
    
    LuaBase.def(
        "get_type",
        &ILuaBase::GetType
    );
    
    LuaBase.def(
        "get_type_name",
        &ILuaBase::GetTypeName
    );
    
    LuaBase.def(
        "create_meta_table_type",
        &ILuaBase::CreateMetaTableType
    );
    
    LuaBase.def(
        "check_string",
        &ILuaBase::CheckString,
        (arg("stack_position")=-1)
    );
    
    LuaBase.def(
        "check_number",
        &ILuaBase::CheckNumber,
        (arg("stack_position")=-1)
    );
    
    LuaBase ADD_OBJ(ILuaBase);
}


// ============================================================================
// >> Expose Special enum
// ============================================================================
void expose_special()
{
    enum_<Special> _Special("Special");
    
    _Special.value("GLOBAL", SPECIAL_GLOB);
    _Special.value("ENVIRONMENT", SPECIAL_ENV);
    _Special.value("REGISTRY", SPECIAL_REG);
}


// ============================================================================
// >> Expose LuaType enum
// ============================================================================
void expose_lua_type()
{
    enum_<LuaType> _Special("LuaType");
    
    _Special.value("INVALID", INVALID);
    _Special.value("NIL", NIL);
    _Special.value("BOOL", BOOL);
    _Special.value("LIGHTUSERDATA", LIGHTUSERDATA);
    _Special.value("NUMBER", NUMBER);
    _Special.value("STRING", STRING);
    _Special.value("TABLE", TABLE);
    _Special.value("FUNCTION", FUNCTION);
    _Special.value("USERDATA", USERDATA);
    _Special.value("THREAD", THREAD);
    
    // UserData
    _Special.value("ENTITY", ENTITY);
    _Special.value("VECTOR", VECTOR);
    _Special.value("ANGLE", ANGLE);
    _Special.value("PHYSOBJ", PHYSOBJ);
    _Special.value("SAVE", SAVE);
    _Special.value("RESTORE", RESTORE);
    _Special.value("DAMAGEINFO", DAMAGEINFO);
    _Special.value("EFFECTDATA", EFFECTDATA);
    _Special.value("MOVEDATA", MOVEDATA);
    _Special.value("RECIPIENTFILTER", RECIPIENTFILTER);
    _Special.value("USERCMD", USERCMD);
    _Special.value("SCRIPTEDVEHICLE", SCRIPTEDVEHICLE);
    
    // Client Only
    _Special.value("MATERIAL", MATERIAL);
    _Special.value("PANEL", PANEL);
    _Special.value("PARTICLE", PARTICLE);
    _Special.value("PARTICLEEMITTER", PARTICLEEMITTER);
    _Special.value("TEXTURE", TEXTURE);
    _Special.value("USERMSG", USERMSG);
    
    _Special.value("CONVAR", CONVAR);
    _Special.value("IMESH", IMESH);
    _Special.value("MATRIX", MATRIX);
    _Special.value("SOUND", SOUND);
    _Special.value("PIXELVISHANDLE", PIXELVISHANDLE);
    _Special.value("DLIGHT", DLIGHT);
    _Special.value("VIDEO", VIDEO);
    _Special.value("FILE", GarrysMod::Lua::Type::FILE);
}


// ============================================================================
// >> Expose lua_State class
// ============================================================================
void expose_lua_state()
{
    class_<lua_State, boost::noncopyable> State("LuaState", no_init);
    
    State.def_readwrite(
        "lua_base",
        &lua_State::luabase
    );
}


// ============================================================================
// >> Expose UserData class
// ============================================================================
void expose_user_data()
{
    class_<UserData> _UserData("UserData");
    
    _UserData.def_readwrite(
        "data",
        &UserData::data
    );
    
    _UserData.def_readwrite(
        "type",
        &UserData::type
    );
}
