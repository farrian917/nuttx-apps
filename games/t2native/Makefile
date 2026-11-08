include $(APPDIR)/Make.defs
PROGNAME = $(CONFIG_GAMES_T2NATIVE_PROGNAME)
PRIORITY = $(CONFIG_GAMES_T2NATIVE_PRIORITY)
STACKSIZE = $(CONFIG_GAMES_T2NATIVE_STACKSIZE)
MODULE = $(CONFIG_GAMES_T2NATIVE)
MAINSRC = src/main.c
CSRCS = src/intro_assets.c src/game_assets.c
# Original VDP snapshot playback speed. 25 = four times slower than 60Hz.
CFLAGS += -DT2_INTRO_SPEED_PERCENT=25
include $(APPDIR)/Application.mk
