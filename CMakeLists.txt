cmake_minimum_required(VERSION 3.10)
project(ToySim)

set(CMAKE_CXX_STANDARD 20)

find_package(LLVM REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS} include)
add_definitions(${LLVM_DEFINITIONS})


# add_library(common STATIC include/helper.hpp)

set(INTERPRETER_SOURCES
    src/interpreter.cpp
    src/commands.cpp
    src/helper.cpp
)

set(JIT_SOURCES
    src/commands.cpp
    src/commands_jit.cpp
    src/jit.cpp
    src/helper.cpp
)


add_executable(toy_interpreter ${INTERPRETER_SOURCES})
add_executable(toy_jit ${JIT_SOURCES})

# Link against the LLVM library
target_link_libraries(toy_jit LLVM-20)
target_compile_options(toy_jit PRIVATE ${LLVM_CXXFLAGS})

target_link_libraries(toy_interpreter LLVM-20)
target_compile_options(toy_interpreter PRIVATE ${LLVM_CXXFLAGS})

    target_compile_options(toy_jit PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        # -Werror
	    -Weffc++
        -Waggressive-loop-optimizations
        -Wc++14-compat
        -Wmissing-declarations
        -Wcast-align -Wcast-qual
        -Wchar-subscripts
        -Wconditionally-supported
        -Wconversion
        -Wctor-dtor-privacy
        -Wempty-body -Wfloat-equal
        -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2
        -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd
        -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self
        -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo
        -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn
        -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override
        -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code
        -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix
        -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast
        -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation
        -fstack-protector -fstrict-overflow -flto-odr-type-merging
        -fno-omit-frame-pointer
        # -Wlarger-than=10000 -Wstack-usage=8192
        -pie -fPIE
        -Werror=vla
        # -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,
        # leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,
        # signed-integer-overflow,undefined,unreachable,vla-bound,vptr
    )

    target_compile_options(toy_interpreter PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        # -Werror
	    -Weffc++
        -Waggressive-loop-optimizations
        -Wc++14-compat
        -Wmissing-declarations
        -Wcast-align -Wcast-qual
        -Wchar-subscripts
        -Wconditionally-supported
        -Wconversion
        -Wctor-dtor-privacy
        -Wempty-body -Wfloat-equal
        -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2
        -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd
        -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self
        -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo
        -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn
        -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override
        -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code
        -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix
        -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast
        -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation
        -fstack-protector -fstrict-overflow -flto-odr-type-merging
        -fno-omit-frame-pointer
        # -Wlarger-than=10000 -Wstack-usage=8192
        -pie -fPIE
        -Werror=vla
        # -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,
        # leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,
        # signed-integer-overflow,undefined,unreachable,vla-bound,vptr
    )
