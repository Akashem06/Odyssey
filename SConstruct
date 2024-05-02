# SConstruct
import os
# SConstruct
import os

###########################################################
# Common FLAGS for Compilation
###########################################################

common_flags = [
    '-Wall',
    '-Wextra',
    '-Werror',
    '-Isrc',
    '-Iinc',
    '-DTEST'
]

###########################################################
# FLAGS for Compilation
###########################################################

cflags = [
    '-Wno-unused-variable',
    '-Wno-unused-parameter',
    '-Wpointer-arith',
]

cppflags = [
    '-Wno-unused-variable',
    '-Wno-unused-parameter',
    '-Wpointer-arith',
]

###########################################################
# Environment Setup
###########################################################

env = Environment(
    ENV={ 'PATH': os.environ['PATH'] },
    CC='gcc',
    CXX='g++',
    CXXFLAGS=common_flags + cppflags,
    CCFLAGS=common_flags + cflags,
    LIBS=['gmock', 'gtest'],
    LIBPATH=['/usr/src/googletest/lib']
)

###########################################################
# Action Functions
###########################################################

COMMAND = COMMAND_LINE_TARGETS[0] if COMMAND_LINE_TARGETS else ''

if COMMAND == 'build':
    SConscript('scons/build.scons', exports={'env': env})

elif COMMAND == 'test':
    SConscript('scons/test.scons', exports={'env': env})

elif COMMAND == 'clean':
    AlwaysBuild(Command('#/clean', [], 'rm -rf build/*'))

elif COMMAND == 'format' or COMMAND == 'lint':
    SConscript('scons/format_lint.scons', exports={'env': env})

else: # Unknown command
    SConscript('scons/build.scons', exports={'env': env})

###########################################################
# Custom Help Function
###########################################################
    
Help('''
Usage:
  scons [OPTIONS]

Options:
  -h, --help      Show this help message
  --clean         Clean the build directory
  --format        Format the code
  --lint          Run linting on the code
  --build         Build the project
''')