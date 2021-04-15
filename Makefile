#TARGET = rott
TARGET = rott-sw
PSPSDK = $(shell psp-config --pspsdk-path)
PSPBIN = $(shell psp-config --psp-prefix)/bin
SDL_CONFIG = $(PSPBIN)/sdl-config
PSP_EBOOT_ICON = ICON0.PNG
PSP_EBOOT_PIC1 = PIC1.PNG

BUILD_PRX=1
PSP_FW_VERSION = 371
PSP_LARGE_MEMORY = 1


O = o
OBJS = \
	cin_actr.o \
	cin_efct.o \
	cin_evnt.o \
	cin_glob.o \
	cin_main.o \
	cin_util.o \
	dosutil.o \
	engine.o \
	fx_man.o \
	isr.o \
	modexlib.o \
	rt_actor.o \
	rt_battl.o \
	rt_build.o \
	rt_cfg.o \
	rt_crc.o \
	rt_com.o \
	rt_debug.o \
	rt_dmand.o \
	rt_door.o \
	rt_draw.o \
	rt_floor.o \
	rt_game.o \
	rt_in.o \
	rt_main.o \
	rt_map.o \
	rt_menu.o \
	rt_msg.o \
	rt_net.o \
	rt_playr.o \
	rt_rand.o \
	rt_scale.o \
	rt_sound.o \
	rt_spbal.o \
	rt_sqrt.o \
	rt_stat.o \
	rt_state.o \
	rt_str.o \
	rt_swift.o \
	rt_ted.o \
	rt_util.o \
	rt_view.o \
	rt_vid.o \
	rt_err.o \
	scriplib.o \
	w_wad.o \
	watcom.o \
	z_zone.o \
	byteordr.o \
	pspDveManager.o

INCDIR = /usr/local/pspdev/psp/include/libtimidity
#DEFAULT_CFLAGS = $(shell $(SDL_CONFIG) --cflags) -DUSE_SDL=1    -DPLATFORM_UNIX   -DSHAREWARE=0
DEFAULT_CFLAGS = $(shell $(SDL_CONFIG) --cflags) -DUSE_SDL=1    -DPLATFORM_UNIX   -DSHAREWARE=1


MORE_CFLAGS =  -O3

CFLAGS = $(DEFAULT_CFLAGS) $(MORE_CFLAGS)  -G0 -Wall -fno-exceptions  -fsingle-precision-constant -mno-check-zero-division  -funsafe-math-optimizations -fpeel-loops -ffast-math  -fno-exceptions
CXXFLAGS = $(DEFAULT_CFLAGS) $(MORE_CFLAGS) -fno-exceptions

LIBS =   -lSDL_mixer -lvorbisidec $(shell $(SDL_CONFIG) --libs)   -lpsppower -lpspaudiolib -lpspaudio -lpsputility

EXTRA_TARGETS = EBOOT.PBP

include $(PSPSDK)/lib/build.mak
