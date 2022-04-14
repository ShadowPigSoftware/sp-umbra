include $(SPUMBRA_MAKE_DIRECTORY)/targets/help.mk
include $(SPUMBRA_MAKE_DIRECTORY)/targets/default.mk
include $(SPUMBRA_MAKE_DIRECTORY)/targets/test.mk
include $(SPUMBRA_MAKE_DIRECTORY)/targets/examples.mk

#Now that the build directory has been overriden by the targets,
#we can specify the cpp object file targets
$(call spumbra_make_build_cpp_target,$(SPUMBRA_SOURCE_DIRECTORY),$(SPUMBRA_BUILD_DIRECTORY)/source)
$(call spumbra_make_build_cpp_target,$(SPUMBRA_TEST_DIRECTORY),$(SPUMBRA_BUILD_DIRECTORY)/test)
$(call spumbra_make_build_cpp_target,$(SPUMBRA_EXAMPLES_DIRECTORY),$(SPUMBRA_BUILD_DIRECTORY)/examples)