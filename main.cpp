#include "daScript/daScript.h"
#include "daScript/das_common.h"

int main() {
    auto guard = das::daScriptEnvironmentGuard();
    das::TextPrinter tout;
    NEED_MODULE(Module_BuiltIn)
    das::ModuleGroup dummyGroup;
    auto program = compileDaScript("hello.das",das::make_smart<das::FsFileAccess>(),tout,dummyGroup,{});
    auto pctx = das::SimulateWithErrReport(program, tout);
    auto fnVec = pctx->findFunctions("main");
    pctx->evalWithCatch(fnVec.back(), nullptr);
}
