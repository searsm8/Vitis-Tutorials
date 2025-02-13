// © Copyright 2021–2022 Xilinx, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

// FFTrows_graph FFT point size...
#define FFT_ROW_TP_POINT_SIZE MAT_COLS
// FFTcols_graph FFT point size...
#define FFT_COL_TP_POINT_SIZE MAT_ROWS

// 1 (FFT) or 0 (IFFT)...
#define FFT_2D_TP_FFT_NIFFT 1
// 0 Bit Shift before output, will have to change based on input...
#define FFT_2D_TP_SHIFT 0
// FFT divided over 1 FFT Kernel...
#define FFT_2D_TP_CASC_LEN 1
// Dynamic FFT Point Size is disabled...
#define FFT_2D_TP_DYN_PT_SIZE 0

// TP_WINDOW_VSIZE for FFTrows_graph...
#define FFT_ROW_TP_WINDOW_VSIZE MAT_COLS

// TP_WINDOW_VSIZE for FFTcols_graph
// Increasing the "TP__WINDOW _VSIZE" so that the ping-pong overhead is less
// Assigning it as MAT_COLS instead of MAT_ROWS...
#define FFT_COL_TP_WINDOW_VSIZE MAT_COLS

////////////////////////////////////////////////////////
// FFT_2D Datatype related Macros
// Datatype can be:
// cint16 (Default) or cfloat...
// 0=cint16(Default)
// 1=cfloat
#if FFT_2D_DT == 0

   // Input data type...
   #define FFT_2D_TT_DATA cint16
   // Twiddle Factor data type...
   #define FFT_2D_TT_TWIDDLE cint16
   
   // FFTrows_graph I/O WINDOW BUFF SIZE IN BYTES...
   #define FFT_ROW_WINDOW_BUFF_SIZE (FFT_ROW_TP_WINDOW_VSIZE * 4)
   // FFTcols_graph I/O WINDOW BUFF SIZE IN BYTES...
   #define FFT_COL_WINDOW_BUFF_SIZE (FFT_COL_TP_WINDOW_VSIZE * 4)
   
#elif FFT_2D_DT == 1

   // Input data type...
   #define FFT_2D_TT_DATA cfloat
   // Twiddle Factor data type...
   #define FFT_2D_TT_TWIDDLE cfloat
   
   // FFTrows_graph I/O WINDOW BUFF SIZE IN BYTES...
   #define FFT_ROW_WINDOW_BUFF_SIZE (FFT_ROW_TP_WINDOW_VSIZE * 8)
   // FFTcols_graph I/O WINDOW BUFF SIZE IN BYTES...
   #define FFT_COL_WINDOW_BUFF_SIZE (FFT_COL_TP_WINDOW_VSIZE * 8)
   
#endif

#include "adf.h"
#include "fft_ifft_dit_1ch_graph.hpp"

using namespace adf;
namespace dsplib = xf::dsp::aie;

extern uint8_t fftCols_grInsts, fftRows_grInsts;

class FFTrows_graph: public graph
{
   public:
   	std::vector<input_plio> row_in;
   	std::vector<output_plio> row_out;
      
   	// Constructor - with Rowise FFT graph class initialization...
   	//FFTrows_graph(): row_in(FFT2D_INSTS), row_out(FFT2D_INSTS) {
   	FFTrows_graph(): row_in(1), row_out(1) {

         dsplib::fft::dit_1ch::fft_ifft_dit_1ch_graph<FFT_2D_TT_DATA, FFT_2D_TT_TWIDDLE, FFT_ROW_TP_POINT_SIZE,
         FFT_2D_TP_FFT_NIFFT, FFT_2D_TP_SHIFT, FFT_2D_TP_CASC_LEN, FFT_2D_TP_DYN_PT_SIZE, FFT_ROW_TP_WINDOW_VSIZE> FFTrow_gr; //[FFT2D_INSTS];
         
         //for(int fftRows_grInsts = 0; fftRows_grInsts < FFT2D_INSTS; ++fftRows_grInsts) {

            //adf::kernel *FFTrow_gr_kernels = FFTrow_gr[fftRows_grInsts].getKernels();
            runtime<ratio>(*FFTrow_gr.getKernels()) = 0.8;
            
            std::string rows_plioIn_str = "DataIn" + std::to_string(fftRows_grInsts*2) ;
            const char *rows_plioIn = rows_plioIn_str.c_str();
            
            std::string rows_In_file_str = "input" + std::to_string(0) + ".txt";
            const char *rows_In_file = rows_In_file_str.c_str();

            row_in[0] = input_plio::create(rows_plioIn, plio_128_bits, rows_In_file);
            //row_in[fftRows_grInsts] = input_plio::create(rows_plioIn, plio_128_bits, rows_In_file);

            std::string rows_plioOut_str = "DataOut" + std::to_string(fftRows_grInsts*2) ;
            const char *rows_plioOut = rows_plioOut_str.c_str();
            
            std::string rows_Out_file_str = "data/output" + std::to_string(fftRows_grInsts*2) + ".txt";
            const char *rows_Out_file = rows_Out_file_str.c_str();
            
            row_out[0] = output_plio::create(rows_plioOut, plio_128_bits, rows_Out_file);
            //row_out[fftRows_grInsts] = output_plio::create(rows_plioOut, plio_128_bits, rows_Out_file);

            //adf::runtime<ratio>(FFTrow_gr_kernels[fftRows_grInsts]) = 0.8;

            adf::connect< window<FFT_ROW_WINDOW_BUFF_SIZE> > (row_in[0].out[0],  FFTrow_gr.in[0]);
            adf::connect< window<FFT_ROW_WINDOW_BUFF_SIZE> > (FFTrow_gr.out[0], row_out[0].in[0]);
            //adf::connect< window<FFT_ROW_WINDOW_BUFF_SIZE> > (row_in[fftRows_grInsts].out[0],   FFTrow_gr[fftRows_grInsts].in[0]);
            //adf::connect< window<FFT_ROW_WINDOW_BUFF_SIZE> > (FFTrow_gr[fftRows_grInsts].out[0], row_out[fftRows_grInsts].in[0]);
            ++fftRows_grInsts;
   	    //}
      }
};

class FFTcols_graph: public graph
{
   public:
   	std::vector<input_plio> col_in;
   	std::vector<output_plio> col_out;
   
   	// Constructor - with Colwise FFT graph class initialization...
   	//FFTcols_graph(): col_in(FFT2D_INSTS), col_out(FFT2D_INSTS)
   	FFTcols_graph(): col_in(1), col_out(1)
      {
         dsplib::fft::dit_1ch::fft_ifft_dit_1ch_graph<FFT_2D_TT_DATA, FFT_2D_TT_TWIDDLE, FFT_COL_TP_POINT_SIZE,
         FFT_2D_TP_FFT_NIFFT, FFT_2D_TP_SHIFT, FFT_2D_TP_CASC_LEN, FFT_2D_TP_DYN_PT_SIZE, FFT_COL_TP_WINDOW_VSIZE> FFTcol_gr; //[FFT2D_INSTS];

         //for(int fftCols_grInsts = 0; fftCols_grInsts < FFT2D_INSTS; ++fftCols_grInsts) {

            //adf::kernel *FFTcol_gr_kernels = FFTcol_gr[fftCols_grInsts].getKernels(); 
            runtime<ratio>(*FFTcol_gr.getKernels()) = 0.8;

            std::string cols_plioIn_str = "DataIn" + std::to_string(fftCols_grInsts*2 + 1) ;
            const char *cols_plioIn = cols_plioIn_str.c_str();
            
            std::string cols_In_file_str = "input" + std::to_string(1) + ".txt";
            const char *cols_In_file = cols_In_file_str.c_str();

            col_in[0] = input_plio::create(cols_plioIn, plio_128_bits, cols_In_file);
            //col_in[fftCols_grInsts] = input_plio::create(cols_plioIn, plio_128_bits, cols_In_file);

            std::string cols_plioOut_str = "DataOut" + std::to_string(fftCols_grInsts*2 + 1) ;
            const char *cols_plioOut = cols_plioOut_str.c_str();
            
            std::string cols_Out_file_str = "data/output" + std::to_string(fftCols_grInsts*2 + 1) + ".txt";
            const char *cols_Out_file = cols_Out_file_str.c_str();
            
            col_out[0] = output_plio::create(cols_plioOut, plio_128_bits, cols_Out_file);
            //col_out[fftCols_grInsts] = output_plio::create(cols_plioOut, plio_128_bits, cols_Out_file);

            //adf::runtime<ratio>(FFTcol_gr_kernels[fftCols_grInsts]) = 0.8;

            adf::connect< window<FFT_COL_WINDOW_BUFF_SIZE> > (col_in[0].out[0],   FFTcol_gr.in[0]);
            adf::connect< window<FFT_COL_WINDOW_BUFF_SIZE> > (FFTcol_gr.out[0], col_out[0].in[0]);
            //adf::connect< window<FFT_COL_WINDOW_BUFF_SIZE> > (col_in[fftCols_grInsts].out[0],   FFTcol_gr[fftCols_grInsts].in[0]);
            //adf::connect< window<FFT_COL_WINDOW_BUFF_SIZE> > (FFTcol_gr[fftCols_grInsts].out[0], col_out[fftCols_grInsts].in[0]);
            ++fftCols_grInsts;
   	    //}
   	}
};

class FFT2D_graph: public graph
{
   public:
   	FFTrows_graph fft_rows[FFT2D_INSTS];
      FFTcols_graph fft_cols[FFT2D_INSTS];
};
