ifeq ($(SPUMBRA_OVERRIDE_CPP),)
SPUMBRA_CPP = g++ -std=c++17
else
SPUMBRA_CPP = $(SPUMBRA_OVERRIDE_CPP)
endif

SPUMBRA_CPP_DEBUG_FLAGS ?= -g3 -O0
SPUMBRA_CPP_RELEASE_FLAGS ?= -g0 -O3
SPUMBRA_CPP_FLAGS ?= -Wall -Werror -Wextra
#Place a target for building an output (.o) file based on a C++ (.cpp) file
# parameter 1 = source directory
# parameter 2 =  output directory
# Example usage: $(call spunit_make_build_cpp_target,src,build/src)
define spumbra_make_build_cpp_target
	$(eval $(call _spumbra_make_build_cpp_target,$(1),$(2),$(3)))
endef
define _spumbra_make_build_cpp_target
$(2)/%.cpp.o: $(1)/%.cpp
	@$$(MAKE_DIRECTORY) $$(@D)
	$$(VERBOSE_FLAG)$$(SPUMBRA_CPP) $$(SPUMBRA_CPP_FLAGS) $$(SPUMBRA_INCLUDE) -MMD -MP -MT $$@ -MF $(2)/$$*.cpp.d -c $$< -o $$@ $(3)
endef
