# composed by kroko

## ============================================================================
## EDIT SECTION

## --------------------------------
# MUST: Change /usr/lib/mali to /path/where/your/libMali.so resides
MALIINCLIBDIR		= /usr/lib/mali

# For dynamic linking hopefully you have already added it to ldconfig, right? :)
# Fyi, it can be done by issuing:
# Echo "/usr/lib/mali" > /etc/ld.so.conf.d/mali.conf && ldconfig
# you can check if ldconfig sees libMali bay issuing:
# ldconfig -v | grep libMali

## --------------------------------
# MUST: change /usr/include/mali to /path/where/your/fbdev/headers/(EGL|GLES|GLES2|KHR) reside
# double check that those are fbdev not wayland/x11 headers!
MALIINCHEADERDIR	= /usr/include/mali

## --------------------------------
# if you wish, change GCC ARM options (well, if you use this makefile on other than armv7-a, you should)
FLAGS_ARCH = -mabi=aapcs-linux -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -mfpu=neon-vfpv4 -mfp16-format=ieee -marm -mtp=auto

# set flags empty for gcc to autodetect (g++ -mcpu=native -Q --help=target)
# FLAGS_ARCH = 

## --------------------------------
# if you wish change optimization flags
# don't care about size just execution time for production and compile time for develop
# FLAGS_OPT	= -O3 # production, optimize for execution time
FLAGS_OPT	= -O0 # develop, optimize for compile time

## ============================================================================
## CONSTANT SECTION
# probably no need to edit anything below for this demo
# g++ (Debian 6.3.0-18+deb9u1) 6.3.0 20170516

## --------------------------------
DEPENDENCIES_HEADER_DIR_QUOTE = ../../dependencies/shared/hela/hela/include ../../dependencies/shared/hela/food/spdlog/include
DODE_HEADER_DIR_QUOTE = ../../code/include

## --------------------------------
# cat /proc/cpuinfo gives
# ARMv7 Processor rev 5 (v7l)
# Features	: half thumb fastmult vfp edsp neon vfpv3 tls vfpv4 idiva idivt vfpd32 lpae evtstrm
# CPU part	: 0xc07

# these sources claim H3 is armv7-a
# http://linux-sunxi.org/H3
# https://en.wikipedia.org/wiki/ARM_Cortex-A7
# https://en.wikipedia.org/wiki/Allwinner_Technology#H-Series_2
# 0xc07 also leads to armv7-a
# https://en.wikipedia.org/wiki/Comparison_of_ARMv7-A_cores
# http://linux-sunxi.org/images/4/4b/Allwinner_H3_Datasheet_V1.2.pdf
# g++ -mcpu=native -Q --help=target disagrees to everything
# fak mī
# anyways, specify armv7-a in -march
# -march=name[+extensions] are poor here, use -mfpu flag

FLAGS_OTHER	= -std=c++14 -Wall -Wextra

## --------------------------------
CXX				= g++
LDFLAGS			= -lGLESv2 -lEGL -lm -pthread
CPPFLAGS_ALL		= $(FLAGS_OPT) $(FLAGS_ARCH) $(FLAGS_OTHER) $(addprefix -iquote,$(DEPENDENCIES_HEADER_DIR_QUOTE)) $(addprefix -iquote,$(DODE_HEADER_DIR_QUOTE))
MACROS	= HELA_LINUX_ARM_FBDEV_MALI_ALLWINNER

SRCDIRCODE			= ../../code/src/
SRCDIRHELA			= ../../dependencies/shared/hela/hela/src/
OBJDIR			= Makeobjects/
BINDIR			= ./
TARGET			= gl-test

# Nasty recursive inclusion of everything
# But then we would have to wrap all that is not within embedded-linux-fbdev-mali-allwinner-mali-utgard in defines
SRC				= $(wildcard $(addsuffix *.cpp,$(SRCDIRCODE))) $(shell find $(SRCDIRHELA) -type f -not -path "*/desktop-*" -name "*.cpp")
VPATH			= $(SRCDIRCODE) $(shell find $(SRCDIRHELA) -maxdepth 100 -type d -not -path "*/desktop-*")

OBJ				= $(addprefix $(OBJDIR), $(patsubst %.cpp, %.o, $(notdir $(SRC))))

$(TARGET) : $(OBJ) copyassets
	$(CXX) $(LDFLAGS) $(addprefix -L,$(MALIINCLIBDIR)) -o $(BINDIR)$@ $(OBJ)

$(OBJDIR)%.o : %.cpp $(OBJDIR)
	$(CXX) $(CPPFLAGS_ALL) $(addprefix -I,$(MALIINCHEADERDIR)) $(addprefix -D,$(MACROS)) -c -o $@ $<

$(OBJDIR):
	mkdir -p $@

copyassets :
	mkdir -p ./assets
	rsync -rupE ../../code/assets/ ./assets

clean :
	-rm -rf $(BINDIR)$(TARGET)
	-rm -rf $(OBJDIR)
	-rm -rf assets/
