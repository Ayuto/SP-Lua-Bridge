# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python
import memory

from core import PLATFORM

# Lua Bridge
from lua_bridge._lua_bridge import *


# =============================================================================
# >> ALL DEFINITION
# =============================================================================
__all__ = (
    'LuaBase',
    'Special',
    'LuaType',
    'LuaState',
    'UserData'
    'lua',
    'push',
    'get',
    'call'
)


# =============================================================================
# >> CONSTANTS
# =============================================================================
# Control whether debug messages are enabled or not
DEBUG = False


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# TODO: Move this into an *.ini file
server = memory.find_binary('server')

if PLATFORM == 'windows':
    pLua = server.find_pointer(
        b'\x55\x8B\xEC\x6A\x01\xE8\x2A\x2A\x2A\x2A\x83\xC4\x04\x84\xC0\x74'
        b'\x2A\x83\x3D\x2A\x2A\x2A\x2A\x00\x74\x2A\x56\x8B\x75\x08\x83\x3E\x02',
        84, 2)
else:
    pLua = server.find_pointer('g_Lua', level=1)

lua = memory.make_object(LuaBase, pLua)


# =============================================================================
# >> FUNCTIONS
# =============================================================================
def debug(*args, **kwargs):
    """Print a message if debugging is enabled."""
    # TODO: Use logging
    if DEBUG:
        print(*args, **kwargs)


def push(value):
    """Push a value onto the stack.

    :param value:
        Value to push.
    """
    if value is None:
        debug('lua.push_nil()')
        lua.push_nil()
    elif isinstance(value, str):
        debug('lua.push_string(\'{}\')'.format(value))
        lua.push_string(value)
    elif isinstance(value, int):
        debug('lua.push_number(\'{}\')'.format(value))
        lua.push_number(value)
    elif isinstance(value, bool):
        debug('lua.push_bool(\'{}\')'.format(value))
        lua.push_bool(value)
    else:
        raise NotImplementedError


def get(stack_pos=-1):
    """Retrieve a value from the stack.

    :param int stack_pos:
        Position of the value on the stack.
    :return:
        The value in its appropriate type.
    """
    lua_type = LuaType.values[lua.get_type(stack_pos)]

    if lua_type == LuaType.STRING:
        debug('lua.get_string({})'.format(stack_pos))
        return lua.get_string(stack_pos)
    elif lua_type == LuaType.NUMBER:
        debug('lua.get_number({})'.format(stack_pos))
        return lua.get_number(stack_pos)
    elif lua_type == LuaType.BOOL:
        debug('lua.get_bool({})'.format(stack_pos))
        return lua.get_bool(stack_pos)
    else:
        raise NotImplementedError


def call(func_path, args, results=0):
    """Call a function or module function.

    :param func_path:
        A function name or list/tuple that defines the path to the function
        (e.g. a module function).
    :param args:
        A string a list/tuple that contains the arguments for the function
        call.
    :param int results:
        Number of results returned by the function.

    Example #1:

    Call ``print('Hello!')``.

    .. code:: python

        call('print', 'Hello!')


    Example #2:

    Call ``team.GetName(0)`` and print its return value.

    .. code:: python

        print(call(
            ['team', 'GetName'], # function path
            0, # Team 0/Unassigned
            1) # GetName() has one return value
        )
    """
    # Validate function path
    if isinstance(func_path, str):
        func_path = [func_path]
    elif not isinstance(func_path, (tuple, list)):
        raise TypeError('"func_path" must be str, list or tuple.')
    elif not func_path:
        raise ValueError('"func_path" must not be empty.')

    # Prepare arguments
    if not isinstance(args, (list, tuple)):
        args = [args]

    debug('lua.push_special(Special.GLOBAL)')
    lua.push_special(Special.GLOBAL)

    # Retrieve the function
    for path_element in func_path:
        debug('lua.get_field(-1, \'{}\')'.format(path_element))
        lua.get_field(-1, path_element)

    # Push arguments
    for arg in args:
        push(arg)

    # Do the call
    debug('lua.call({}, {})'.format(len(args), results))
    lua.call(len(args), results)

    # Retrieve results
    result = []
    for index in range(results):
        result.append(get(~index))

    # Clean-up stack
    debug('lua.pop({})'.format(len(func_path) + results))
    lua.pop(len(func_path) + results)

    # Finish the call
    if not result:
        return None

    return tuple(result)
