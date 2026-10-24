include $(APPDIR)/Make.defs
PROGNAME = $(CONFIG_GAMES_T2GEN_PROGNAME)
PRIORITY = $(CONFIG_GAMES_T2GEN_PRIORITY)
STACKSIZE = $(CONFIG_GAMES_T2GEN_STACKSIZE)
MODULE = $(CONFIG_GAMES_T2GEN)
MAINSRC = src/t2gen_main.c
ifeq ($(CONFIG_GAMES_T2GEN_MUSASHI),y)
CSRCS = src/t2gen_musashi.c src/t2gen_vdp.c src/t2gen_render.c src/musashi/m68kcpu.c src/musashi/m68kops.c
CFLAGS += -I$(APPDIR)/games/t2gen/src/musashi
else
CSRCS = src/t2gen_boot.c
endif
include $(APPDIR)/Application.mk
