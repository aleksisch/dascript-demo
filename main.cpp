#include "daScript/ast/dyn_modules.h"
#include "daScript/daScript.h"

int main() {
    das::TextPrinter tout;
    auto faccess = das::smart_ptr<das::FsFileAccess>(new das::FsFileAccess);

    NEED_ALL_DEFAULT_MODULES
    das::require_dynamic_modules(faccess, das::getDasRoot(), "./", tout);
    das::Module::Initialize();

    das::ModuleGroup dummyGroup;
    das::CodeOfPolicies policies;                        // compiler setup

    // Enables AOT linking.
    policies.aot = true;
    // If some functions have changed do not fail.
    policies.fail_on_no_aot = false;

    auto program = compileDaScript("hello.das",faccess,tout,dummyGroup,policies);
    if (program->failed()) {
        for ( auto & err : program->errors ) {
            tout << reportError(err.at, err.what, err.extra, err.fixme, err.cerr);
        }
        tout << "File `hello.das` not found.\n";
        return -1;
    }
    das::Context pctx(program->getContextStackSize());
    if ( !program->simulate(pctx, tout) ) {
        tout << "failed to simulate\n";
        for ( auto & err : program->errors ) {
            tout << reportError(err.at, err.what, err.extra, err.fixme, err.cerr);
        }
        return -1;
    }
    auto fnVec = pctx.findFunctions("main");
    if (fnVec.empty()) {
        tout << "Function `main` not found.\n";
        return -1;
    }
    pctx.evalWithCatch(fnVec.back(), nullptr);

    das::Module::Shutdown();
}
