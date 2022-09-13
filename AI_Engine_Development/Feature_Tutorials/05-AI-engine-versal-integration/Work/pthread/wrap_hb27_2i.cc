#include "adf.h"
#include "../.././aie/kernels/interpolators/hb27_2i.cc"
void b0_kernel_wrapper(window_internal * arg0, window_internal * arg1)
{
  auto _arg0 = get_input_window_cint16(arg0);
  auto _arg1 = get_output_window_cint16(arg1);
  return fir_27t_sym_hb_2i(_arg0, _arg1);
}
