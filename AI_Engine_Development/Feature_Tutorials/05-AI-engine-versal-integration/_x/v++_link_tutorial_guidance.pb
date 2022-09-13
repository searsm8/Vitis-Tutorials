
ù

v++_link_tutorial$edf29cd3-01a5-45d9-b023-231b06dda0edˆv++  -l -t sw_emu --platform /proj/xbuilds/SWIP/2022.1_0420_0327/installs/lin64/Vitis/2022.1/base_platforms/xilinx_vck190_base_202210_1/xilinx_vck190_base_202210_1.xpfm s2mm.xo mm2s.xo libadf.a --save-temps -g --config system.cfg -o tutorial.xsa *ô"î/home/msears/Vitis-Tutorials/AI_Engine_Development/Feature_Tutorials/05-AI-engine-versal-integration/_x/reports/link/v++_link_tutorial_guidance.html2ä"Ö/home/msears/Vitis-Tutorials/AI_Engine_Development/Feature_Tutorials/05-AI-engine-versal-integration/_x/v++_link_tutorial_guidance.pbBø

system.cfg∞# ¬© Copyright 2020 Xilinx, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

[connectivity]
nk=mm2s:1:mm2s
nk=s2mm:1:s2mm
sc=mm2s.s:ai_engine_0.DataIn1
sc=ai_engine_0.DataOut1:s2mm.s