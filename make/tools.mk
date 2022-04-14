# Command line tools abstraction

ifeq ($(QUIET),)
	VERBOSE_FLAG:=
else
	VERBOSE_FLAG:=@
endif

MAKE_DIRECTORY:=mkdir -p
REMOVE_FILE:=rm -f
REMOVE_DIRECTORY:=rm -rf
