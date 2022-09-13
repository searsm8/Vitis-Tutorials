; ModuleID = '/home/msears/Vitis-Tutorials/AI_Engine_Development/Feature_Tutorials/05-AI-engine-versal-integration/_x/s2mm/s2mm/s2mm/solution/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

%"struct.ap_int<32>" = type { %"struct.ap_int_base<32, true>" }
%"struct.ap_int_base<32, true>" = type { %"struct.ssdm_int<32, true>" }
%"struct.ssdm_int<32, true>" = type { i32 }
%"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>" = type { %"struct.qdma_axis<32, 0, 0, 0>" }
%"struct.qdma_axis<32, 0, 0, 0>" = type { %"struct.ap_int<32>", %"struct.ap_uint<4>", %"struct.ap_uint<1>", %"struct.ap_uint<1>", %"struct.ap_uint<1>", %"struct.ap_uint<1>", %"struct.ap_uint<1>" }
%"struct.ap_uint<4>" = type { %"struct.ap_int_base<4, false>" }
%"struct.ap_int_base<4, false>" = type { %"struct.ssdm_int<4, false>" }
%"struct.ssdm_int<4, false>" = type { i4 }
%"struct.ap_uint<1>" = type { %"struct.ap_int_base<1, false>" }
%"struct.ap_int_base<1, false>" = type { %"struct.ssdm_int<1, false>" }
%"struct.ssdm_int<1, false>" = type { i1 }

; Function Attrs: noinline
define void @apatb_s2mm_ir(%"struct.ap_int<32>"* noalias nocapture nonnull %mem, %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* noalias nocapture nonnull dereferenceable(12) %s, i32 %size) local_unnamed_addr #0 {
entry:
  %mem_copy = alloca %"struct.ap_int<32>", align 512
  %s_copy.data = alloca i32
  %s_copy.keep = alloca i4
  %s_copy.last = alloca i1
  call fastcc void @copy_in(%"struct.ap_int<32>"* nonnull %mem, %"struct.ap_int<32>"* nonnull align 512 %mem_copy, %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* nonnull %s, i32* %s_copy.data, i4* %s_copy.keep, i1* %s_copy.last)
  call void @apatb_s2mm_hw(%"struct.ap_int<32>"* %mem_copy, i32* %s_copy.data, i4* %s_copy.keep, i1* %s_copy.last, i32 %size)
  call void @copy_back(%"struct.ap_int<32>"* %mem, %"struct.ap_int<32>"* %mem_copy, %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %s, i32* %s_copy.data, i4* %s_copy.keep, i1* %s_copy.last)
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_in(%"struct.ap_int<32>"* noalias readonly, %"struct.ap_int<32>"* noalias align 512, %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* noalias, i32* noalias "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.0" %_V_data_V, i4* noalias "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.1" %_V_keep_V, i1* noalias "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.2" %_V_last_V) unnamed_addr #1 {
entry:
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<32>"(%"struct.ap_int<32>"* align 512 %1, %"struct.ap_int<32>"* %0)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"(i32* %_V_data_V, i4* %_V_keep_V, i1* %_V_last_V, %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %2)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @"onebyonecpy_hls.p0struct.ap_int<32>"(%"struct.ap_int<32>"* noalias align 512, %"struct.ap_int<32>"* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq %"struct.ap_int<32>"* %0, null
  %3 = icmp eq %"struct.ap_int<32>"* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  %.0.0.04 = getelementptr %"struct.ap_int<32>", %"struct.ap_int<32>"* %1, i32 0, i32 0, i32 0, i32 0
  %.01.0.05 = getelementptr %"struct.ap_int<32>", %"struct.ap_int<32>"* %0, i32 0, i32 0, i32 0, i32 0
  %5 = load i32, i32* %.0.0.04, align 4
  store i32 %5, i32* %.01.0.05, align 512
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"onebyonecpy_hls.p0class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"(i32* noalias "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.0" %_V_data_V, i4* noalias "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.1" %_V_keep_V, i1* noalias "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.2" %_V_last_V, %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* noalias "fpga.caller.interfaces"="layout_transformed") unnamed_addr #3 {
entry:
  %1 = icmp eq %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %0, null
  %2 = or i1 false, %1
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  call fastcc void @"streamcpy_hls.p0class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"(i32* %_V_data_V, i4* %_V_keep_V, i1* %_V_last_V, %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* nonnull %0)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"(i32* noalias nocapture "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.0" %_V_data_V, i4* noalias nocapture "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.1" %_V_keep_V, i1* noalias nocapture "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.2" %_V_last_V, %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed") unnamed_addr #4 {
entry:
  %1 = alloca %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"
  %2 = alloca %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"
  br label %empty

empty:                                            ; preds = %push, %entry
  %3 = bitcast %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %0 to i8*
  %4 = call i1 @fpga_fifo_not_empty_12(i8* %3)
  br i1 %4, label %push, label %ret

push:                                             ; preds = %empty
  %5 = bitcast %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %2 to i8*
  %6 = bitcast %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %0 to i8*
  call void @fpga_fifo_pop_12(i8* %5, i8* %6)
  %7 = load volatile %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>", %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %2
  store %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>" %7, %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %1
  %8 = getelementptr inbounds %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>", %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %1, i32 0, i32 0, i32 0
  %9 = bitcast %"struct.ap_int<32>"* %8 to i32*
  %10 = bitcast i32* %9 to i8*
  %11 = bitcast i32* %_V_data_V to i8*
  call void @fpga_fifo_push_4(i8* %10, i8* %11)
  %12 = getelementptr inbounds %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>", %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %1, i32 0, i32 0, i32 1
  %13 = bitcast %"struct.ap_uint<4>"* %12 to i4*
  %14 = bitcast i4* %13 to i8*
  %15 = bitcast i4* %_V_keep_V to i8*
  call void @fpga_fifo_push_1(i8* %14, i8* %15)
  %16 = getelementptr inbounds %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>", %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %1, i32 0, i32 0, i32 4
  %17 = bitcast %"struct.ap_uint<1>"* %16 to i1*
  %18 = bitcast i1* %17 to i8*
  %19 = bitcast i1* %_V_last_V to i8*
  call void @fpga_fifo_push_1(i8* %18, i8* %19)
  br label %empty, !llvm.loop !5

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_out(%"struct.ap_int<32>"* noalias, %"struct.ap_int<32>"* noalias readonly align 512, %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* noalias, i32* noalias "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.0" %_V_data_V, i4* noalias "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.1" %_V_keep_V, i1* noalias "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.2" %_V_last_V) unnamed_addr #5 {
entry:
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<32>"(%"struct.ap_int<32>"* %0, %"struct.ap_int<32>"* align 512 %1)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>.4"(%"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %2, i32* %_V_data_V, i4* %_V_keep_V, i1* %_V_last_V)
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"onebyonecpy_hls.p0class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>.4"(%"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* noalias align 512 "fpga.caller.interfaces"="layout_transformed", i32* noalias "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.0" %_V_data_V, i4* noalias "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1" %_V_keep_V, i1* noalias "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.2" %_V_last_V) unnamed_addr #3 {
entry:
  %1 = icmp eq %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %0, null
  %2 = or i1 %1, false
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  call fastcc void @"streamcpy_hls.p0class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>.7"(%"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* nonnull align 512 %0, i32* %_V_data_V, i4* %_V_keep_V, i1* %_V_last_V)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>.7"(%"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed", i32* noalias nocapture "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.0" %_V_data_V, i4* noalias nocapture "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1" %_V_keep_V, i1* noalias nocapture "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.2" %_V_last_V) unnamed_addr #4 {
entry:
  %1 = alloca %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"
  %2 = alloca i32
  %3 = alloca i4
  %4 = alloca i1
  br label %empty

empty:                                            ; preds = %push, %entry
  %5 = bitcast i32* %_V_data_V to i8*
  %6 = call i1 @fpga_fifo_not_empty_4(i8* %5)
  br i1 %6, label %push, label %ret

push:                                             ; preds = %empty
  %7 = bitcast i32* %2 to i8*
  %8 = bitcast i32* %_V_data_V to i8*
  call void @fpga_fifo_pop_4(i8* %7, i8* %8)
  %9 = load volatile i32, i32* %2
  %10 = getelementptr inbounds %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>", %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %1, i32 0, i32 0, i32 0
  %11 = bitcast %"struct.ap_int<32>"* %10 to i32*
  store i32 %9, i32* %11
  %12 = bitcast i4* %3 to i8*
  %13 = bitcast i4* %_V_keep_V to i8*
  call void @fpga_fifo_pop_1(i8* %12, i8* %13)
  %14 = bitcast i4* %3 to i8*
  %15 = load i8, i8* %14
  %16 = trunc i8 %15 to i4
  %17 = getelementptr inbounds %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>", %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %1, i32 0, i32 0, i32 1
  %18 = bitcast %"struct.ap_uint<4>"* %17 to i4*
  store i4 %16, i4* %18
  %19 = bitcast i1* %4 to i8*
  %20 = bitcast i1* %_V_last_V to i8*
  call void @fpga_fifo_pop_1(i8* %19, i8* %20)
  %21 = bitcast i1* %4 to i8*
  %22 = load i8, i8* %21
  %23 = trunc i8 %22 to i1
  %24 = getelementptr inbounds %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>", %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %1, i32 0, i32 0, i32 4
  %25 = bitcast %"struct.ap_uint<1>"* %24 to i1*
  store i1 %23, i1* %25
  %26 = bitcast %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %1 to i8*
  %27 = bitcast %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %0 to i8*
  call void @fpga_fifo_push_12(i8* %26, i8* %27)
  br label %empty, !llvm.loop !5

ret:                                              ; preds = %empty
  ret void
}

declare void @apatb_s2mm_hw(%"struct.ap_int<32>"*, i32*, i4*, i1*, i32)

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_back(%"struct.ap_int<32>"* noalias, %"struct.ap_int<32>"* noalias readonly align 512, %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* noalias, i32* noalias "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.0" %_V_data_V, i4* noalias "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.1" %_V_keep_V, i1* noalias "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.2" %_V_last_V) unnamed_addr #5 {
entry:
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<32>"(%"struct.ap_int<32>"* %0, %"struct.ap_int<32>"* align 512 %1)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>.4"(%"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %2, i32* %_V_data_V, i4* %_V_keep_V, i1* %_V_last_V)
  ret void
}

define void @s2mm_hw_stub_wrapper(%"struct.ap_int<32>"*, i32*, i4*, i1*, i32) #6 {
entry:
  %5 = alloca %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"
  call void @copy_out(%"struct.ap_int<32>"* null, %"struct.ap_int<32>"* %0, %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %5, i32* %1, i4* %2, i1* %3)
  call void @s2mm_hw_stub(%"struct.ap_int<32>"* %0, %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %5, i32 %4)
  call void @copy_in(%"struct.ap_int<32>"* null, %"struct.ap_int<32>"* %0, %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"* %5, i32* %1, i4* %2, i1* %3)
  ret void
}

declare void @s2mm_hw_stub(%"struct.ap_int<32>"*, %"class.hls::stream<qdma_axis<32, 0, 0, 0>, 0>"*, i32)

declare i1 @fpga_fifo_not_empty_12(i8*)

declare i1 @fpga_fifo_not_empty_4(i8*)

declare void @fpga_fifo_pop_12(i8*, i8*)

declare void @fpga_fifo_pop_4(i8*, i8*)

declare void @fpga_fifo_pop_1(i8*, i8*)

declare void @fpga_fifo_push_12(i8*, i8*)

declare void @fpga_fifo_push_4(i8*, i8*)

declare void @fpga_fifo_push_1(i8*, i8*)

attributes #0 = { noinline "fpga.wrapper.func"="wrapper" }
attributes #1 = { argmemonly noinline "fpga.wrapper.func"="copyin" }
attributes #2 = { argmemonly noinline norecurse "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #3 = { argmemonly noinline "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #4 = { argmemonly noinline "fpga.wrapper.func"="streamcpy_hls" }
attributes #5 = { argmemonly noinline "fpga.wrapper.func"="copyout" }
attributes #6 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.rotate.disable"}
