
#Alter the build directory based on the target, so as not to mix debug and release object files
SPUMBRA_DEFAULT_DEBUG_TARGETS := 	sp-umbra/debug \
									sp-umbra/default/debug

SPUMBRA_DEFAULT_DEBUG_CLEAN_TARGETS:= $(patsubst %,%/clean,$(SPUMBRA_DEFAULT_DEBUG_TARGETS))

SPUMBRA_DEFAULT_RELEASE_TARGETS := 	sp-umbra \
									sp-umbra/default \
									sp-umbra/release \
									sp-umbra/default/release

SPUMBRA_DEFAULT_RELEASE_CLEAN_TARGETS:= $(patsubst %,%/clean,$(SPUMBRA_DEFAULT_RELEASE_TARGETS))

SPUMBRA_DEFAULT_DEBUG_MODES := $(filter $(SPUMBRA_DEFAULT_DEBUG_TARGETS) $(SPUMBRA_DEFAULT_DEBUG_CLEAN_TARGETS),$(MAKECMDGOALS))
SPUMBRA_DEFAULT_RELEASE_MODES := $(filter $(SPUMBRA_DEFAULT_RELEASE_TARGETS) $(SPUMBRA_DEFAULT_RELEASE_CLEAN_TARGETS),$(MAKECMDGOALS))

ifneq ($(SPUMBRA_DEFAULT_DEBUG_MODES),)
	SPUMBRA_BUILD_DIRECTORY := $(SPUMBRA_BUILD_DIRECTORY)/debug
	SPUMBRA_BINARY_DIRECTORY := $(SPUMBRA_BINARY_DIRECTORY)/debug
endif
ifneq ($(SPUMBRA_DEFAULT_RELEASE_MODES),)
	SPUMBRA_BUILD_DIRECTORY := $(SPUMBRA_BUILD_DIRECTORY)/release
	SPUMBRA_BINARY_DIRECTORY := $(SPUMBRA_BINARY_DIRECTORY)/release
endif

SPUMBRA_OUTPUT_FILES=$(call spumbra_make_output_files,$(SPUMBRA_SOURCE_FILES),$(SPUMBRA_SOURCE_DIRECTORY)/%,$(SPUMBRA_BUILD_DIRECTORY)/source/%)
SPUMBRA_SOURCE_DEPENDENCY_FILES=$(call spumbra_make_dependency_files,$(SPUMBRA_SOURCE_FILES),$(SPUMBRA_SOURCE_DIRECTORY)/%,$(SPUMBRA_BUILD_DIRECTORY)/source/%)
SPUMBRA_SOURCE_DEPENDENCY_FILES+=$(SPUMBRA_DEFAULT_MAIN_DEPENDENCY)

SPUMBRA_DEFAULT_MAIN:=$(SPUMBRA_BUILD_DIRECTORY)/source/main.cpp.o
SPUMBRA_DEFAULT_MAIN_DEPENDENCY:=$(SPUMBRA_BUILD_DIRECTORY)/source/main.cpp.d
SPUMBRA_APPLICATION:=$(SPUMBRA_BINARY_DIRECTORY)/sp-umbra

sp-umbra/debug: sp-umbra/default/debug

sp-umbra/default/debug: SPUMBRA_CPP_FLAGS += $(SPUMBRA_CPP_DEBUG_FLAGS) -DSPUMBRA_DEBUG
sp-umbra/default/debug: $(SPUMBRA_APPLICATION)

sp-umbra: sp-umbra/default/release
sp-umbra/default: sp-umbra/default/release
sp-umbra/release: sp-umbra/default/release

sp-umbra/default/release: SPUMBRA_CPP_FLAGS += $(SPUMBRA_CPP_RELEASE_FLAGS) -DSPUMBRA_RELEASE
sp-umbra/default/release: $(SPUMBRA_APPLICATION)

$(SPUMBRA_APPLICATION): SPUMBRA_INCLUDE += -I$(SPUMBRA_SOURCE_DIRECTORY)
$(SPUMBRA_APPLICATION): $(SPUMBRA_OUTPUT_FILES) $(SPUMBRA_DEFAULT_MAIN)
	$(VERBOSE_FLAG)$(MAKE_DIRECTORY) $(@D)
	$(VERBOSE_FLAG)$(SPUMBRA_CPP) -o $@ $^

sp-umbra/debug/clean: sp-umbra/default/debug/clean

SPUMBRA_DEFAULT_CLEAN_FILES := 	$(SPUMBRA_DEFAULT_APPLICATION) \
								$(SPUMBRA_OUTPUT_FILES) \
								$(SPUMBRA_DEPENDENCY_FILES) \
								$(SPUMBRA_DEFAULT_MAIN) \
								$(SPUMBRA_DEFAULT_MAIN_DEPENDENCY)

sp-umbra/default/debug/clean:
	$(VERBOSE_FLAG)$(REMOVE_FILE) $(SPUMBRA_DEFAULT_CLEAN_FILES)

sp-umbra/clean: sp-umbra/default/release/clean
sp-umbra/default/clean: sp-umbra/default/release/clean
sp-umbra/release/clean: sp-umbra/default/release/clean

sp-umbra/default/release/clean:
	$(VERBOSE_FLAG)$(REMOVE_FILE) $(SPUMBRA_DEFAULT_CLEAN_FILES)