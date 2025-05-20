CXX := clang++
CXXFLAGS := -std=c++23 -pedantic -Wall -Wextra -Wpedantic -Wcast-align -Wconversion -Wsign-conversion -Wdouble-promotion
CPPFLAGS := -I.

# https://github.com/cpp-best-practices/cppbestpractices/blob/master/02-Use_the_Tools_Available.md
CXXFLAGS += -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wunused -Woverloaded-virtual -Wformat=2 -Wimplicit-fallthrough

# https://stackoverflow.com/questions/2408038/what-does-wall-in-g-wall-test-cpp-o-test-do
CXXFLAGS += -Wcast-qual -Wpointer-arith -Wfloat-equal

# https://clang.llvm.org/docs/AddressSanitizer.html
CXXFLAGS += -fsanitize=address -O1 -fno-omit-frame-pointer -fno-optimize-sibling-calls

# https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
CXXFLAGS += -fsanitize=undefined,float-divide-by-zero,local-bounds,vptr,integer,nullability -fno-sanitize-recover=all

# https://clang.llvm.org/docs/SanitizerSpecialCaseList.html
CXXFLAGS += -fsanitize-ignorelist=ignorelist.txt

LINK.o := $(LINK.cc)

CPPFLAGS += -MMD -MP

.PHONY: dependencies
dependencies:
	@$(CXX) $(CPPFLAGS) -MMD -MF - $(SOURCE)

INCLUDE := $(shell find . | grep '\.d$$')
-include $(INCLUDE)
