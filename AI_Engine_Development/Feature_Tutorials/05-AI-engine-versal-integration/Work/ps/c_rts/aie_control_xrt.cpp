#include <iostream>
#include "adf/new_frontend/adf.h"
#include "adf/adf_api/X86SimConfig.h"


/************************** Graph Configurations  *****************************/

  adf::X86SimGraphConfig GraphConfigurations[] = {
  // {id, name, runForIter, x86SimPtr}
    {0, "clipgraph", -1, nullptr},
  };
  const int NUM_GRAPH = 1;

/************************** PLIO Configurations  *****************************/

  adf::X86SimPLIOConfig PLIOConfigurations[] = {
  //{id, name, loginal_name}
    {0, "clipgraph.in", "DataIn1"},
    {1, "clipgraph.out", "DataOut1"},
  };
  const int NUM_PLIO = 2;


/************************** ADF API initializer *****************************/

  class InitializeAIEControlXRT
  {
  public:
    InitializeAIEControlXRT()
    {
      std::cout<<"Initializing ADF API..."<<std::endl;
      adf::initializeX86SimConfigurations(GraphConfigurations, NUM_GRAPH,
                                    nullptr, 0,
                                    nullptr, 0,
                                    PLIOConfigurations, NUM_PLIO,
                                    nullptr, 0);
    }
  } initAIEControlXRT;



#if !defined(__CDO__)

// Kernel Stub Definition
  void classifier(input_stream<cint16> *,output_window<int> *) { /* Stub */ } 
  void fir_27t_sym_hb_2i(input_window<cint16> *,output_window<cint16> *) { /* Stub */ } 
  void polar_clip(input_stream<cint16> *,output_stream<cint16> *) { /* Stub */ } 
#endif
