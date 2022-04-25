SPUMBRA_CORE_SOURCE_FILES := 		$(SPUMBRA_SOURCE_DIRECTORY)/core/utf32_character_class.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/core/utf32_character_traits.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/core/utf32_string.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/core/utf32_string_position_iterator.cpp


SPUMBRA_FILESYSTEM_SOURCE_FILES := 	$(SPUMBRA_SOURCE_DIRECTORY)/filesystem/file.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/filesystem/filesystem.cpp

SPUMBRA_TRANSLATION_SOURCE_FILES := $(SPUMBRA_SOURCE_DIRECTORY)/translation/error/translation_error.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/translation/utf8_to_utf32_translation_phase.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/translation/string_literal_translation_phase.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/translation/preprocessor_sequence/preprocessor_sequence_translation_phase.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/translation/preprocessor_sequence/pstp_state_base.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/translation/preprocessor_sequence/pstp_state_normal.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/translation/preprocessor_sequence/pstp_state_first_dollar.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/translation/preprocessor_sequence/pstp_state_second_dollar.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/translation/preprocessor_sequence/pstp_state_declaration_block.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/translation/preprocessor_sequence/pstp_state_usage_block.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/translation/preprocessor_lexer/preprocessor_lexer_translation_phase.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/translation/preprocessor_lexer/pltp_block_type.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/translation/preprocessor_lexer/pltp_block.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/translation/preprocessor_lexer/pltp_preprocessor_declaration_block.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/translation/lexer/lexer_token_type.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/translation/lexer/lexer_token.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/translation/lexer/alpha_lexer.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/translation/lexer/whitespace_lexer.cpp \
									$(SPUMBRA_SOURCE_DIRECTORY)/translation/lexer/symbol_lexer.cpp

SPUMBRA_SOURCE_FILES += $(SPUMBRA_CORE_SOURCE_FILES) \
						$(SPUMBRA_FILESYSTEM_SOURCE_FILES) \
						$(SPUMBRA_TRANSLATION_SOURCE_FILES)