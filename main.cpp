#include "daScript/daScript.h"
#include "daScript/das_common.h"

int main() {
    NEED_MODULE(Module_BuiltIn)
    das::Module::Initialize();

    das::TextPrinter tout;
    das::ModuleGroup dummyGroup;
    auto program = compileDaScript("hello.das",das::make_smart<das::FsFileAccess>(),tout,dummyGroup,{});
    if (program->failed()) {
        printf("File `hello.das` not found.\n");
        return -1;
    }
    auto pctx = das::SimulateWithErrReport(program, tout);
    if (!pctx) {
        printf("Failed to simulate `hello.das`.\n");
        return -1;
    }
    auto fnVec = pctx->findFunctions("main");
    if (fnVec.empty()) {
        printf("Function `main` not found.\n");
        return -1;
    }
    pctx->evalWithCatch(fnVec.back(), nullptr);

    das::Module::Shutdown();
}
