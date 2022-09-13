#
# Set debug=yes for compiling code with -O0
#
ifeq ($(debug),)
 debug := no
endif
ifeq ($(filter $(debug),yes no),)
 $(error Invalid value '$(debug)' in 'debug=$(debug)', use 'yes' or 'no')
endif
$(info debug=$(debug))
#
# Set debug_lib_x86sim=yes for linking against lnx64.g/libx86sim.so
#
ifeq ($(debug_lib_x86sim),)
 debug_lib_x86sim := no
endif
ifeq ($(filter $(debug_lib_x86sim),yes no),)
 $(error Invalid value '$(debug_lib_x86sim)' in 'debug_lib_x86sim=$(debug_lib_x86sim)', use 'yes' or 'no')
endif
$(info debug_lib_x86sim=$(debug_lib_x86sim))
#
# Set address_sanitizer=yes to detect out of bound memory access in kernel code
# Set ASAN_SYMBOLIZER_PATH=${XILINX_VITIS_AIETOOLS}/lnx64.o/tools/clang/bin/llvm-symbolizer
# to get a better stack trace.
#
ifeq ($(address_sanitizer),)
 address_sanitizer := no
endif
ifeq ($(filter $(address_sanitizer),yes no),)
 $(error Invalid value '$(address_sanitizer)' in 'address_sanitizer=$(address_sanitizer)', use 'yes' or 'no')
endif
$(info address_sanitizer=$(address_sanitizer))

ifeq ($(XILINX_VITIS_AIETOOLS),)
XILINX_VITIS_AIETOOLS:=${XILINX_VITIS}/aietools
endif

ifeq ($(address_sanitizer),yes)
 ASAN_CFLAGS := -fsanitize=address
 ASAN_LFLAGS := -L${XILINX_VITIS_AIETOOLS}/lnx64.o/tools/clang/lib/clang/12.0.0/lib/linux/ -lclang_rt.asan-x86_64
 ASAN_SUPPORT_FLAGS := -ldl 
endif

CFLAGS := -g -std=c++17
CFLAGS += -D__X86SIM__ -D__PTHREAD_API__
CFLAGS +=  -DHLS_STREAM_THREAD_SAFE
CFLAGS += -fvisibility=hidden
ifeq ($(debug),yes)
  CFLAGS +=  -g -O0
endif
CFLAGS += -D__AIEARCH__=1
CFLAGS += -DAIE_OPTION_SCALAR_FLOAT_ON_VECTOR

CFLAGS += -I ../..
CFLAGS += -I ${XILINX_VITIS_AIETOOLS}/include
CFLAGS += -I ${XILINX_VITIS_AIETOOLS}/data/osci_systemc/include
CFLAGS += -I ${XILINX_HLS}/include
CFLAGS += -I ${XILINX_VITIS_AIETOOLS}/tps/boost_1_72_0
CFLAGS += -I /proj/xbuilds/SWIP/2022.1_0420_0327/installs/lin64/Vitis/2022.1/aietools/include
CFLAGS += -I ../.././aie
CFLAGS += -I ../.././data
CFLAGS += -I ../.././aie/kernels
CFLAGS += -I ../.././

me_DIR := $(XILINX_VITIS_AIETOOLS)/data/versal_prod/lib
CHESSDIR := $(XILINX_VITIS_AIETOOLS)/tps/lnx64/target/chessdir
AIE_CFLAGS := -I $(me_DIR)
AIE_CFLAGS += -I $(CHESSDIR)
AIE_CFLAGS += -I $(XILINX_VITIS_AIETOOLS)/data/osci_systemc/include
AIE_CFLAGS += -I $(me_DIR)/designware/DWFC_fp/include
AIE_CFLAGS += -I $(me_DIR)/designware/DWFC_fp_multifunc/include
AIE_CFLAGS += -I $(me_DIR)/designware/dwfc_multifunc/include

ifeq ($(debug_lib_x86sim),yes)
EXT_LIB_X86SIM := g
else
EXT_LIB_X86SIM := o
endif
LFLAGS := -lx86simStreamApiAIE1 -lx86sim -Wl,-R${XILINX_VITIS_AIETOOLS}/lib/lnx64.$(EXT_LIB_X86SIM)
LFLAGS += -Wl,-R${XILINX_VITIS_AIETOOLS}/tps/lnx64/gcc/lib64

DEPFLAGS = -MT $@ -MMD -MP -MF $(<F).Td
POSTCOMPILE = @mv -f $(<F).Td $(<F).d && touch $@

all:	sim.out libsim.so libxmcsim.so
vmc:	libxmcsim.so wrap_graph.cpp.d

wrap_graph.cpp.d: wrap_graph.cpp
	g++ -fPIC -E -MT wrap_graph.cpp.o -M -MM -MP -MF $(<F).d $(CFLAGS) $(AIE_CFLAGS) wrap_graph.cpp

wrap_graph.cpp.o: wrap_graph.cpp wrap_graph.cpp.d
	g++ -fPIC -c -o wrap_graph.cpp.o $(DEPFLAGS) $(CFLAGS) $(AIE_CFLAGS) wrap_graph.cpp
	$(POSTCOMPILE)

PthreadSim.cpp.o: PthreadSim.cpp PthreadSim.cpp.d
	g++ -fPIC -c -o PthreadSim.cpp.o $(DEPFLAGS) $(CFLAGS) $(AIE_CFLAGS) PthreadSim.cpp
	$(POSTCOMPILE)

PthreadSimBasic.cpp.o: PthreadSimBasic.cpp PthreadSimBasic.cpp.d
	g++ -fPIC -c -o PthreadSimBasic.cpp.o $(DEPFLAGS) $(CFLAGS) PthreadSimBasic.cpp
	$(POSTCOMPILE)

PthreadSimSwemu.cpp.o: PthreadSimSwemu.cpp PthreadSimSwemu.cpp.d
	g++ -fPIC -c -o PthreadSimSwemu.cpp.o $(DEPFLAGS) $(CFLAGS) PthreadSimSwemu.cpp
	$(POSTCOMPILE)

PthreadSimXmc.cpp.o: PthreadSimXmc.cpp PthreadSimXmc.cpp.d
	g++ -fPIC -c -o PthreadSimXmc.cpp.o $(DEPFLAGS) $(CFLAGS) PthreadSimXmc.cpp
	$(POSTCOMPILE)

wrap_hb27_2i.cc.o:	 wrap_hb27_2i.cc wrap_hb27_2i.cc.d
	aie_clang++ -fPIC -c -o wrap_hb27_2i.cc.o -D__AIENGINE__ -D__AIEARCH__=1 \
$(DEPFLAGS) $(CFLAGS) $(ASAN_CFLAGS) $(MY_KERNEL_CFLAGS) -std=c++2a -stdlib=libc++ wrap_hb27_2i.cc
	$(POSTCOMPILE)

wrap_polar_clip.cpp.o:	 wrap_polar_clip.cpp wrap_polar_clip.cpp.d
	aie_clang++ -fPIC -c -o wrap_polar_clip.cpp.o -D__AIENGINE__ -D__AIEARCH__=1 \
$(DEPFLAGS) $(CFLAGS) $(ASAN_CFLAGS) $(MY_KERNEL_CFLAGS) -std=c++2a -stdlib=libc++ wrap_polar_clip.cpp
	$(POSTCOMPILE)

wrap_classify.cc.o:	 wrap_classify.cc wrap_classify.cc.d
	aie_clang++ -fPIC -c -o wrap_classify.cc.o -D__AIENGINE__ -D__AIEARCH__=1 \
$(DEPFLAGS) $(CFLAGS) $(ASAN_CFLAGS) $(MY_KERNEL_CFLAGS) -std=c++2a -stdlib=libc++ wrap_classify.cc
	$(POSTCOMPILE)

aie_kernels_obj.o: wrap_hb27_2i.cc.o wrap_polar_clip.cpp.o wrap_classify.cc.o
	ld -o aie_kernels_obj.o -r wrap_hb27_2i.cc.o wrap_polar_clip.cpp.o wrap_classify.cc.o -L${XILINX_VITIS_AIETOOLS}/lib/lnx64.o -lc++ -lc++abi ${ASAN_LFLAGS} ${MY_KERNEL_LFLAGS}

sim.out: aie_kernels_obj.o  PthreadSimBasic.cpp.o PthreadSim.cpp.o wrap_graph.cpp.o
	aie_g++ -o sim.out -D__AIEARCH__=1 aie_kernels_obj.o  PthreadSimBasic.cpp.o PthreadSim.cpp.o wrap_graph.cpp.o -lpthread -ladf_api_x86sim -lx86simSocketUtil ${LFLAGS} ${ASAN_SUPPORT_FLAGS}

libsim.so: aie_kernels_obj.o  PthreadSimSwemu.cpp.o PthreadSim.cpp.o
	aie_g++ -shared -o libsim.so -D__AIEARCH__=1 aie_kernels_obj.o  PthreadSimSwemu.cpp.o PthreadSim.cpp.o -lc++ -lpthread -ladf_api_x86sim -lx86simDummySocketUtil ${LFLAGS} ${ASAN_SUPPORT_FLAGS}

libxmcsim.so: aie_kernels_obj.o  PthreadSimXmc.cpp.o PthreadSim.cpp.o
	aie_g++ -shared -o libxmcsim.so -D__AIEARCH__=1 aie_kernels_obj.o  PthreadSimXmc.cpp.o PthreadSim.cpp.o -lc++ -lpthread -ladf_api_x86sim -lx86simDummySocketUtil ${LFLAGS} ${ASAN_SUPPORT_FLAGS}

clean: 
	rm -f  wrap_hb27_2i.cc.o wrap_polar_clip.cpp.o wrap_classify.cc.o aie_kernels_obj.o PthreadSim.cpp.o PthreadSimBasic.cpp.o PthreadSimSwemu.cpp.o wrap_graph.cpp.o sim.out  libsim.so

%.d: ;
.PRECIOUS: %.d

include  $(wildcard wrap_graph.cpp.d) $(wildcard PthreadSim.cpp.d) $(wildcard PthreadSimBasic.cpp.d) $(wildcard PthreadSimSwemu.cpp.d) $(wildcard PthreadSimXmc.cpp.d) $(wildcard wrap_hb27_2i.cc.d) $(wildcard wrap_polar_clip.cpp.d) $(wildcard wrap_classify.cc.d)
