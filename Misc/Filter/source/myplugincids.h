//------------------------------------------------------------------------
// Copyright(c) 2023 My Plug-in Company.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace MyCompanyName {
//------------------------------------------------------------------------
static const Steinberg::FUID kFilterProcessorUID (0xD4E36DF8, 0x9DB15ACA, 0xAF029CAB, 0x0E8D676E);
static const Steinberg::FUID kFilterControllerUID (0x9C6756E9, 0x6B695CB9, 0xB5BFA44A, 0x759FDC59);

#define FilterVST3Category "Fx"

enum FilterParams : Steinberg::Vst::ParamID
{
    kParamGainId = 102, // should be a unique id...
    kParamCutOffId = 103,
};

//------------------------------------------------------------------------
} // namespace MyCompanyName
