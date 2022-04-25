default: sp-umbra/help

SPUMBRA_MAKE_PATH := $(lastword $(MAKEFILE_LIST))
SPUMBRA_DIRECTORY := $(dir $(SPUMBRA_MAKE_PATH))

ifeq ($(SPUMBRA_DIRECTORY),./)
SPUMBRA_DIRECTORY :=
endif

#Utilities
SPUMBRA_MAKE_DIRECTORY := $(SPUMBRA_DIRECTORY)make
include $(SPUMBRA_MAKE_DIRECTORY)/sources.mk
include $(SPUMBRA_MAKE_DIRECTORY)/tools.mk
include $(SPUMBRA_MAKE_DIRECTORY)/git.mk
include $(SPUMBRA_MAKE_DIRECTORY)/cpp.mk
include $(SPUMBRA_MAKE_DIRECTORY)/sp-unit.mk

# Source code
include $(SPUMBRA_SOURCE_DIRECTORY)/make.mk
include $(SPUMBRA_TEST_DIRECTORY)/make.mk
# include $(SPUMBRA_EXAMPLE_DIRECTORY)/make.mk

# Main targets
include $(SPUMBRA_MAKE_DIRECTORY)/targets.mk

# Unit testing submake: Must come after targets as the target specifies the output directory
include $(SPUNIT_DIRECTORY)/spunit.mk

#Dependencies
-include $(SPUMBRA_SOURCE_DEPENDENCY_FILES)
-include $(SPUMBRA_TEST_DEPENDENCY_FILES)
-include $(SPUMBRA_EXAMPLE_DEPENDENCY_FILES)