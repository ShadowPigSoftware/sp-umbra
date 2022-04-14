SPUMBRA_SOURCE_DIRECTORY = $(SPUMBRA_DIRECTORY)source
SPUMBRA_INCLUDE_DIRECTORY = $(SPUMBRA_DIRECTORY)include
SPUMBRA_EXAMPLES_DIRECTORY = $(SPUMBRA_DIRECTORY)examples
SPUMBRA_TEST_DIRECTORY = $(SPUMBRA_DIRECTORY)test
SPUMBRA_BUILD_DIRECTORY = $(SPUMBRA_DIRECTORY)build
SPUMBRA_BINARY_DIRECTORY = $(SPUMBRA_DIRECTORY)bin

SPUMBRA_SOURCE_FILES =
SPUMBRA_EXAMPLE_SOURCE_FILES = 
SPUMBRA_TEST_SOURCE_FILES = 
SPUMBRA_INCLUDE=-I$(SPUMBRA_INCLUDE_DIRECTORY)
# construct the output (.o) files from a list of C++ (.cpp)
# parameter 1 = Source Files
# parameter 2 = input pattern, excluding the extension, e.g. src/%
# parameter 3 = output pattern, exclusing the extension, e.g. build/src/%
# Example usage $(call spumbra_make_output_files, $(SOURCE_FILES), src/%, build/src/%)
define spumbra_make_output_files
$(patsubst $(2).cpp,$(3).cpp.o,$(1))
endef

# construct the dependency (.d) files from a list of C++ (.cpp)
# parameter 1 = Source Files
# parameter 2 = input pattern, excluding the extension, e.g. src/%
# parameter 3 = output pattern, exclusing the extension, e.g. build/src/%
# Example usage $(call spumbra_make_dependency_files, $(SOURCE_FILES), src/%, build/src/%)
define spumbra_make_dependency_files
$(patsubst $(2).cpp,$(3).cpp.d,$(1))
endef