SPUMBRA_GIT_HASH := $(shell git rev-parse HEAD)
SPUMBRA_GIT_HASH_FILE := sp-umbra.git-hash.txt
ifeq ($(wildcard $(SPUMBRA_GIT_HASH_FILE)),) #Empty, i.e. does not exist
	SPUMBRA_GIT_PREVIOUS_HASH :=
else 
	SPUMBRA_GIT_PREVIOUS_HASH := $(shell cat $(SPUMBRA_GIT_HASH_FILE))
endif

ifeq ($(SPUMBRA_GIT_HASH),$(SPUMBRA_GIT_PREVIOUS_HASH))
$(SPUMBRA_GIT_HASH_FILE): 
else
$(SPUMBRA_GIT_HASH_FILE):
	@echo $(SPUMBRA_GIT_HASH) > $@

.PHONY: $(SPUMBRA_GIT_HASH_FILE)
endif