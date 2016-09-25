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
)


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# TODO: Move this into a file
server = memory.find_binary('server')

if PLATFORM == 'windows':
    pLua = server.find_pointer(
        b'\x55\x8B\xEC\x6A\x01\xE8\x2A\x2A\x2A\x2A\x83\xC4\x04\x84\xC0\x74'
        b'\x2A\x83\x3D\x2A\x2A\x2A\x2A\x00\x74\x2A\x56\x8B\x75\x08\x83\x3E\x02',
        84, 2)
else:
    pLua = server.find_pointer('g_Lua', level=1)

lua = memory.make_object(LuaBase, pLua)
