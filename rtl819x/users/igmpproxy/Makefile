ifeq ($(wildcard $(DIR_LINUX)/.config),)
DIR_LINUX_KERNEL = $(DIR_ROOT)/linux-2.6.30
else
DIR_LINUX_KERNEL = $(DIR_LINUX)
endif
CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
LD = $(CROSS_COMPILE)gcc
COPT = -Os

ifeq ($(KERNEL_VER),linux-2.6.30) 
CFLAGS +=-I$(DIR_LINUX_KERNEL)/include -DCONFIG_DEFAULTS_KERNEL_2_6 -D__BIG_ENDIAN_BITFIELD -DCONFIG_CPU_BIG_ENDIAN -DCONFIG_QUERIER_SELECTION $(COPT)
endif
ifeq ($(KERNEL_VER),linux-3.10) 
CFLAGS +=-I$(DIR_LINUX_KERNEL)/include/uapi -DCONFIG_DEFAULTS_KERNEL_2_6 -D__BIG_ENDIAN_BITFIELD -DCONFIG_CPU_BIG_ENDIAN -DCONFIG_QUERIER_SELECTION $(COPT)
endif
ifeq ($(KERNEL_VER),linux-2.6.36.x)
CFLAGS +=-I$(DIR_LINUX_KERNEL)/include/uapi -DCONFIG_DEFAULTS_KERNEL_2_6 -D__BIG_ENDIAN_BITFIELD -DCONFIG_CPU_BIG_ENDIAN -DCONFIG_QUERIER_SELECTION $(COPT)
endif
#CFLAGS=-I -Os -DCONFIG_DEFAULTS_KERNEL_2_6 -D__BIG_ENDIAN_BITFIELD -DCONFIG_CPU_BIG_ENDIAN

CFLAGS += $(EXTRA_CFLAGS)
EXEC = igmpproxy
OBJS = mroute-api.o lib.o ifvc.o syslog.o timeout.o main.o

ifeq ($(CONFIG_IGMPPROXY_MULTIWAN),y)
CFLAGS += -DCONFIG_IGMPPROXY_MULTIWAN
endif

ifeq ($(CONFIG_ISP_IGMPPROXY_MULTIWAN),y)
CFLAGS += -DCONFIG_ISP_IGMPPROXY_MULTIWAN
endif

ifeq ($(CONFIG_IGMPV3_SUPPORT),y)
CFLAGS += -DCONFIG_IGMPV3_SUPPORT
OBJS   += igmpv3.o
DEPH   += igmpproxy.h
endif
all: BUILT_TIME $(EXEC)


$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $(INCLUDE) -o $@ $(OBJS) $(LDLIBS$(LDLIBS-$(@)))

romfs:
	$(ROMFSINST) /bin/$(EXEC)

clean:
	-rm -f $(EXEC) *.elf *.o *.bak built_time

BUILT_TIME:
	@echo  \#define BUILT_TIME \"`TZ=UTC date -u "+%Y.%m.%d-%H:%M%z" `\" > ./built_time	
