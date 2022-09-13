#include "systemc.h"
#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <map>
#include <thread>
#include "me_native.h"
#include "adf/new_frontend/adf.h"
#include "adf/x86sim/x86sim.h"
#include "adf/buffer_port/buffer_port.h"
#include "adf/adf_api/X86SimConfig.h"
// adf::headers of all kernels
#include "include.h"

////// Kernel function Wrapper declarations //////
void b2_kernel_wrapper(x86sim::stream_internal *, window_internal *);
void b0_kernel_wrapper(window_internal *, window_internal *);
void b1_kernel_wrapper(x86sim::stream_internal *, x86sim::stream_internal *);

////// Class kernel dtor wrapper extern declaration //////

////// Class kernel ctor wrapper extern declaration //////

////// Kernel Inits extern declaration //////

namespace {
} // namespace
namespace x86sim
{

////// Kernel Classes //////

class Kernel_b0_fir_27t_sym_hb_2i : public IMEKernel
{
public: 
    Kernel_b0_fir_27t_sym_hb_2i(ISimulator *sim, std::string label)
    : IMEKernel(sim, label)
    {
    }

protected: 
    virtual void invokeKernel() override
    {
        b0_kernel_wrapper(
          ((IWindowConnector*) input(0)) -> readWindow(),
          ((IWindowConnector*) output(0)) -> writeWindow()
        );
    }
};

class Kernel_b1_polar_clip : public IMEKernel
{
public: 
    Kernel_b1_polar_clip(ISimulator *sim, std::string label)
    : IMEKernel(sim, label)
    {
    }

protected: 
    virtual void invokeKernel() override
    {
        b1_kernel_wrapper(
          ((IStreamConnector*) input(0)) -> stream(),
          ((IStreamConnector*) output(0)) -> stream()
        );
    }
};

class Kernel_b2_classifier : public IMEKernel
{
public: 
    Kernel_b2_classifier(ISimulator *sim, std::string label)
    : IMEKernel(sim, label)
    {
    }

protected: 
    virtual void invokeKernel() override
    {
        b2_kernel_wrapper(
          ((IStreamConnector*) input(0)) -> stream(),
          ((IWindowConnector*) output(0)) -> writeWindow()
        );
    }
};

////// Set Initial Value for input async RTP //////

static void initValue(IRtpConnector* rtp, int8_t* val, size_t bytes)
{
    updateRtp(val, bytes,rtp);
}

ISimulator *createSimulator(ISimulator::Kind kind)
{
    ISimulatorConfig simConfig = {};
    simConfig._enableProgress = true;
    simConfig._enableEventTrace = std::getenv("X86SIM_EVENT_TRACE_ON");
    simConfig._enableEventTracePrint = std::getenv("X86SIM_EVENT_TRACE_PRINT_ON");
    simConfig._enableSnapshots = std::getenv("X86SIM_SNAPSHOTS_ON");
    simConfig._simTimeout = 0;
    simConfig._plWaitTime = 0;
    simConfig._meKernelIters = 0;

    if (ISimulator::Kind::kBasic == kind)
    {
        auto simParams = createSimParams();
        simParams -> meKernelIters = -1 /* aiecompiler argument value */ ;
        if (!simParams -> populate())
            std::exit(EXIT_FAILURE);
        simConfig._simTimeout = simParams->simTimeout;
        simConfig._plWaitTime = simParams->plWaitTime;
        simConfig._meKernelIters = simParams->meKernelIters;
        simConfig._enableStopOnDeadlock = std::getenv("X86SIM_STOP_ON_DEADLOCK");
        simConfig._enableHandShakeWithExtTb = std::getenv("X86SIM_HANDSHAKE_EXT_TB");
        simConfig._socketIO = false;
        if (auto env = std::getenv("PACKAGEDIR"))
            simConfig._optionsFile = env + std::string("/options/x86sim.options");
    }
    if (ISimulator::Kind::kSwemu == kind)
    {
        simConfig._meKernelIters = -1;
        if (auto optionFilePath = std::getenv("X86SIM_OPTIONSPATH"))
            simConfig._optionsFile = optionFilePath ;
    }
    if (simConfig._simTimeout == 0)
        if (auto val = std::getenv("X86SIM_TIMEOUT"))
            simConfig._simTimeout = std::atoi(val);

    if (!(simConfig._optionsFile).empty())
        ISimulatorOptions::processFile(simConfig);

    if (auto inputDir = std::getenv("INPUTDIR"))
        simConfig._inputDir = inputDir;
    if (auto outputDir = std::getenv("OUTPUTDIR"))
        simConfig._outputDir = outputDir;
    if ((simConfig._inputDir).empty())
        simConfig._inputDir = ".";
    if ((simConfig._outputDir).empty())
        simConfig._outputDir = "./x86simulator_output";

    ISimulator *sim = SimulatorFactory::simulator(simConfig, kind);
    IBasicSimulator *basicSim = dynamic_cast<IBasicSimulator*>(sim);
    ISwemuSimulator *swemuSim = dynamic_cast<ISwemuSimulator*>(sim);
    IXmcSimulator *xmcSim = dynamic_cast<IXmcSimulator*>(sim);
    IWindowConnector *wcon_i3_po0_i0_pi0
        = ConnectorFactory::windowConnector(sim, "wcon_i3_po0_i0_pi0", 512, 64, nullptr, nullptr, false);
    sim -> addConnectorMetaData(
        {wcon_i3_po0_i0_pi0, "window", "cint16", "clipgraph.in.out[0]", "clipgraph.interpolator.in[0]", "out", "in", 1, 1});
    IWindowConnector *wcon_i2_po0_i4_pi0
        = ConnectorFactory::windowConnector(sim, "wcon_i2_po0_i4_pi0", 1024, 0, nullptr, nullptr, false);
    sim -> addConnectorMetaData(
        {wcon_i2_po0_i4_pi0, "window", "int32", "clipgraph.classify.out[0]", "clipgraph.out.in[0]", "out", "in", 1, 1});
    IWindowConnector *wcon_i0_po0_i0_po0
        = ConnectorFactory::windowConnector(sim, "wcon_i0_po0_i0_po0", 1024, 0, nullptr, nullptr, false);
    sim -> addConnectorMetaData(
        {wcon_i0_po0_i0_po0, "window", "cint16", "clipgraph.interpolator.out[0]", "", "out", "", 1, 0});
    IStreamConnector *scon_i1_pi0_i1_pi0
        = ConnectorFactory::streamConnector(sim, "scon_i1_pi0_i1_pi0");
    sim -> addConnectorMetaData(
        {scon_i1_pi0_i1_pi0, "stream", "cint16", "clipgraph.clip.in[0]", "clipgraph.clip.in[0]", "in", "in", 0, 1});
    IStreamConnector *scon_i1_po0_i2_pi0
        = ConnectorFactory::streamConnector(sim, "scon_i1_po0_i2_pi0");
    sim -> addConnectorMetaData(
        {scon_i1_po0_i2_pi0, "stream", "cint16", "clipgraph.clip.out[0]", "clipgraph.classify.in[0]", "out", "in", 1, 1});
    INode *winbrdcst_i0_po0
         = NodeFactory::windowBroadcaster(sim, "winbrdcst_i0_po0", wcon_i0_po0_i0_po0);
    winbrdcst_i0_po0 -> addOutput(scon_i1_pi0_i1_pi0);

    // Graph configs
    // {id, name, test-iterations, x86SimPtr}
    DFGraph *gr_clipgraph = new DFGraph(sim);
    sim->addGraphConfig({ 0, "clipgraph", -1, gr_clipgraph});
    Kernel_b0_fir_27t_sym_hb_2i *ker_i0
        = new Kernel_b0_fir_27t_sym_hb_2i(sim, "ker_i0");
    gr_clipgraph -> addKernel(ker_i0);
    ker_i0 -> addInput(wcon_i3_po0_i0_pi0);
    ker_i0 -> addOutput(wcon_i0_po0_i0_po0);
    sim -> addNodeMetaData({ker_i0, "clipgraph.interpolator", {
        {wcon_i0_po0_i0_po0, {"out[0]"}}
        , {wcon_i3_po0_i0_pi0, {"in[0]"}}
    }});

    Kernel_b1_polar_clip *ker_i1
        = new Kernel_b1_polar_clip(sim, "ker_i1");
    gr_clipgraph -> addKernel(ker_i1);
    ker_i1 -> addInput(scon_i1_pi0_i1_pi0);
    ker_i1 -> addOutput(scon_i1_po0_i2_pi0);
    sim -> addNodeMetaData({ker_i1, "clipgraph.clip", {
        {scon_i1_pi0_i1_pi0, {"in[0]"}}
        , {scon_i1_po0_i2_pi0, {"out[0]"}}
    }});

    Kernel_b2_classifier *ker_i2
        = new Kernel_b2_classifier(sim, "ker_i2");
    gr_clipgraph -> addKernel(ker_i2);
    ker_i2 -> addInput(scon_i1_po0_i2_pi0);
    ker_i2 -> addOutput(wcon_i2_po0_i4_pi0);
    sim -> addNodeMetaData({ker_i2, "clipgraph.classify", {
        {scon_i1_po0_i2_pi0, {"in[0]"}}
        , {wcon_i2_po0_i4_pi0, {"out[0]"}}
    }});

    if (basicSim)
    {
        INode *platformIn_i3
            = NodeFactory::fileReader
            (sim, "platformIn_i3",
            simConfig._inputDir + "/data/input.txt", 
            false, CINT16, 4, false);
        platformIn_i3 -> addOutput(wcon_i3_po0_i0_pi0);

        INode *platformOut_i4
            = NodeFactory::fileWriter
            (sim, "platformOut_i4",
            simConfig._outputDir + "/data/output.txt", 
            false, INT32, 4, false);
        platformOut_i4 -> addInput(wcon_i2_po0_i4_pi0);


        auto configs = basicSim->getConfig();
        adf::initializeX86SimConfigurations(
            std::get<0>(configs),
            std::get<1>(configs),
            std::get<2>(configs),
            std::get<3>(configs),
            std::get<4>(configs),
            std::get<5>(configs),
            std::get<6>(configs),
            std::get<7>(configs),
            std::get<8>(configs),
            std::get<9>(configs));
    }
    if (swemuSim)
    {
        IPlatformStreamNode *platformIn_i3
            = NodeFactory::streamReader(sim, "platformIn_i3", false);
        swemuSim->registerHlsStreamNode(platformIn_i3, "DataIn1");
        platformIn_i3 -> addOutput(wcon_i3_po0_i0_pi0);

        IPlatformStreamNode *platformOut_i4
            = NodeFactory::streamWriter(sim, "platformOut_i4", false);
        swemuSim->registerHlsStreamNode(platformOut_i4, "DataOut1");
        platformOut_i4 -> addInput(wcon_i2_po0_i4_pi0);

    }
    if (xmcSim)
    {
        IPlatformBuffer * bufplatformIn_i3
            = PlatformBufferFactory::inputBuffer(sim, "bufplatformIn_i3", 32768);
        INode *platformIn_i3
            = NodeFactory::bufferReader(sim, "platformIn_i3", bufplatformIn_i3, 4, 4);
        platformIn_i3 -> addOutput(wcon_i3_po0_i0_pi0);

        IPlatformBuffer * bufplatformOut_i4
            = PlatformBufferFactory::outputBuffer(sim, "bufplatformOut_i4", 32768);
        INode *platformOut_i4
            = NodeFactory::bufferWriter(sim, "platformOut_i4", bufplatformOut_i4, 4, 4);
        platformOut_i4 -> addInput(wcon_i2_po0_i4_pi0);

    }
    if ( !xmcSim)
    {
        sim->start();
    }
    return sim;
}

void *createBasicSimulatorInstance()
{
    static auto  g_sim = std::unique_ptr<ISimulator>
        (createSimulator(ISimulator::Kind::kBasic));
    return g_sim.get();
}

void *createSwemuSimulatorInstance()
{
    static auto  g_sim = std::unique_ptr<ISimulator>
        (createSimulator(ISimulator::Kind::kSwemu));
    return dynamic_cast<x86sim::ISwemuSimulator*>(g_sim.get());
}

void *createXmcSimulator()
{
    auto sim = createSimulator(ISimulator::Kind::kXmcGraph);
    return dynamic_cast<x86sim::IXmcSimulator*>(sim);
}

}  //end of x86Sim namespace


#include "adf/x86sim/symbolVisibility.h"
#include "adf/x86sim/x86simSwemuIfc.hpp"

