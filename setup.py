# =============================================================================
# >> IMPORTS
# =============================================================================
# Python
import os

from distutils.core import Extension
from distutils.core import setup


# =============================================================================
# >> PROJECT SOURCES
# =============================================================================
SOURCES = [
    'src/lua_bridge_wrap.cpp',
    'src/lua_bridge_converters.cpp',
]


# =============================================================================
# >> EXTRA INCLUDES
# =============================================================================
INCLUDE_DIRS = [
    'src/thirdparty/boost',
    'src/thirdparty/gmod-module-base/include',
]


# =============================================================================
# >> LIBRARY SEARCH DIRECTORIES
# =============================================================================
LIBRARY_DIRS = [
    'src/thirdparty/boost/lib',
]


# =============================================================================
# >> LIBRARY NAMES
# =============================================================================
# Windows
if os.name == 'nt':
    LIBRARIES = [
        'libboost_python-vc140-mt-1_61',
    ]

# Linux
else:
    LIBRARIES = [
        'boost_python',
    ]


# =============================================================================
# >> COMPILER FLAGS
# =============================================================================
COMPILER_FLAGS = [
]


# =============================================================================
# >> LINKER FLAGS
# =============================================================================
if os.name == 'nt':
    LINKER_FLAGS = [
    ]
else:
    LINKER_FLAGS = [
        '-static-libgcc',
        '-static-libstdc++',
    ]


# =============================================================================
# >> MACROS
# =============================================================================
MACROS = [
    ('BOOST_PYTHON_STATIC_LIB', ''),
]


# =============================================================================
# >> MAIN
# =============================================================================
def main():
    setup(
        name='lua_bridge',
        ext_modules=[
            Extension(
                'lua_bridge._lua_bridge',
                sources=SOURCES,
                library_dirs=LIBRARY_DIRS,
                libraries=LIBRARIES,
                include_dirs=INCLUDE_DIRS,
                extra_compile_args=COMPILER_FLAGS,
                extra_link_args=LINKER_FLAGS,
                define_macros=MACROS
            ),
        ],
        packages=['lua_bridge']
    )

if __name__ == '__main__':
    main()