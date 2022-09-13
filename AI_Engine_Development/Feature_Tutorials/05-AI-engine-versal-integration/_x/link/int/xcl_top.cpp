#include "libspir_types.h"
#include "hls_stream.h"
#include "xcl_top_defines.h"
#include "ap_axi_sdata.h"
#include "xcl_top_datamovers.h"
#define EXPORT_PIPE_SYMBOLS 1
#include "cpu_pipes.h"
#undef EXPORT_PIPE_SYMBOLS
#include "xcl_half.h"
#include <cstddef>
#include <vector>
#include <complex>
#include <pthread.h>
using namespace std;

extern "C" {

void mm2s(size_t mem, size_t s, unsigned int size);

static pthread_mutex_t __xlnx_cl_mm2s_mutex = PTHREAD_MUTEX_INITIALIZER;
void __stub____xlnx_cl_mm2s(char **argv) {
  void **args = (void **)argv;
  size_t mem = *((size_t*)args[0+1]);
  size_t s = *((size_t*)args[1+1]);
  unsigned int size = *((unsigned int*)args[2+1]);
 //  pthread_mutex_lock(&__xlnx_cl_mm2s_mutex);
  mm2s(mem, s, size);
 //   pthread_mutex_unlock(&__xlnx_cl_mm2s_mutex);
}
void s2mm(size_t mem, size_t s, unsigned int size);

static pthread_mutex_t __xlnx_cl_s2mm_mutex = PTHREAD_MUTEX_INITIALIZER;
void __stub____xlnx_cl_s2mm(char **argv) {
  void **args = (void **)argv;
  size_t mem = *((size_t*)args[0+1]);
  size_t s = *((size_t*)args[1+1]);
  unsigned int size = *((unsigned int*)args[2+1]);
 //  pthread_mutex_lock(&__xlnx_cl_s2mm_mutex);
  s2mm(mem, s, size);
 //   pthread_mutex_unlock(&__xlnx_cl_s2mm_mutex);
}

typedef qdma_axis<32, 0, 0, 0> __xlnx_cl_struct_type_0;
__XLNX_DEFINE_STREAM_FUNCS__(mm2s, Hecb4be88, __xlnx_cl_struct_type_0) 

typedef qdma_axis<32, 0, 0, 0> __xlnx_cl_struct_type_1;
__XLNX_DEFINE_STREAM_FUNCS__(s2mm, Hecb4be88, __xlnx_cl_struct_type_1) 
}
