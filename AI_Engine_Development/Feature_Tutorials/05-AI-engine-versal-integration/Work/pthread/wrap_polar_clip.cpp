#include "adf.h"
#include "../.././aie/kernels/polar_clip.cpp"
void b1_kernel_wrapper(x86sim::stream_internal * arg0, x86sim::stream_internal * arg1)
{
  auto _arg0 = (input_stream_cint16 *)(arg0);
  auto _arg1 = (output_stream_cint16 *)(arg1);
  return polar_clip(_arg0, _arg1);
}
