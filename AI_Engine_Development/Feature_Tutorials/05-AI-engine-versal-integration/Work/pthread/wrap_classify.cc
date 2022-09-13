#include "adf.h"
#include "../.././aie/kernels/classifiers/classify.cc"
void b2_kernel_wrapper(x86sim::stream_internal * arg0, window_internal * arg1)
{
  auto _arg0 = (input_stream_cint16 *)(arg0);
  auto _arg1 = get_output_window_int32(arg1);
  return classifier(_arg0, _arg1);
}
