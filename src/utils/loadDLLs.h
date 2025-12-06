
#ifdef __cplusplus
extern "C" 
{
#endif
#include "../../Sgp4Prop/SampleCode/C/DriverExamples/services/DllMainDll_Service.h"
#include "../../Sgp4Prop/SampleCode/C/DriverExamples/services/TimeFuncDll_Service.h"
#include "../../Sgp4Prop/SampleCode/C/DriverExamples/wrappers/DllMainDll.h"
#include "../../Sgp4Prop/SampleCode/C/DriverExamples/wrappers/TimeFuncDll.h"
#include "../../Sgp4Prop/SampleCode/C/DriverExamples/wrappers/TleDll.h"
#include "../../Sgp4Prop/SampleCode/C/DriverExamples/wrappers/Sgp4PropDll.h"
#include "../../Sgp4Prop/SampleCode/C/DriverExamples/wrappers/EnvConstDll.h"
#include "../../Sgp4Prop/SampleCode/C/DriverExamples/wrappers/AstroFuncDll.h"
#ifdef __cplusplus
}
#endif

namespace utils{
void  LoadAstroStdDlls();
void  FreeAstroStdDlls();
}