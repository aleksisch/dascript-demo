#include "daScript/misc/platform.h"

#include "daScript/ast/ast.h"
#include "daScript/ast/ast_interop.h"
#include "daScript/ast/ast_typefactory_bind.h"
#include "daScript/ast/ast_handle.h"
#include "daScript/daScriptModule.h"
#include "daScript/simulate/bind_enum.h"



// function, which we are going to expose to daScript
const char *hello_from_cpp_module (const char *name, das::Context *ctx, das::LineInfoArg * at ) {
    return ctx->allocateString(das::string("Hello from cpp, ") + name + "!", at);
}

// To link AOT to a module you should reference it's AotListBase
// So linker will not omit it.
namespace das {
    extern AotListBase impl_aot_hello_module_cpp;
}

// making custom builtin module
class Module_HelloCPP : public das::Module {
public:
    Module_HelloCPP() : Module("HelloCPP") {
        das::ModuleLibrary lib(this);
        lib.addBuiltInModule();
        // adding constant to the module
        das::addExtern<DAS_BIND_FUN(hello_from_cpp_module)>(*this, lib,
            "hello_from_cpp_module",das::SideEffects::none, "hello_from_cpp_module");

        *das::ModuleKarma += reinterpret_cast<uintptr_t>(&das::impl_aot_hello_module_cpp);
    }
};


REGISTER_DYN_MODULE(Module_HelloCPP,Module_HelloCPP);
REGISTER_MODULE(Module_HelloCPP);
