SPUMBRA_TEST_UNIT_FILES = 		$(SPUMBRA_TEST_DIRECTORY)/unit/utf8_to_utf32_translation_phase.unit.cpp \
								$(SPUMBRA_TEST_DIRECTORY)/unit/string_literal_translation_phase.unit.cpp \
								$(SPUMBRA_TEST_DIRECTORY)/unit/preprocessor_sequence_translation_phase.unit.cpp \
								$(SPUMBRA_TEST_DIRECTORY)/unit/preprocessor_lexer_translation_phase.unit.cpp


SPUMBRA_TEST_DOUBLE_FILES = 	$(SPUMBRA_TEST_DIRECTORY)/test-doubles/fake_file_system.cpp \
								$(SPUMBRA_TEST_DIRECTORY)/test-doubles/fake_file.cpp

SPUMBRA_TEST_UTILITY_FILES = 	$(SPUMBRA_TEST_DIRECTORY)/utility/test_character_sequence.cpp

SPUMBRA_TEST_SOURCE_FILES += $(SPUMBRA_TEST_UNIT_FILES) $(SPUMBRA_TEST_DOUBLE_FILES) $(SPUMBRA_TEST_UTILITY_FILES)