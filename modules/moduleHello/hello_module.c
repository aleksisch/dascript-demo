#include "daScript/daScriptC.h"
#include <stdio.h>

vec4f hello_from_c_module( das_context * ctx, das_node * node, vec4f * args ) {
    return das_result_string("Hello from c module!");
}

#ifdef _MSC_VER
    #define DAS_EXPORT_DLL __declspec(dllexport)
#else
    #define DAS_EXPORT_DLL __attribute__((visibility("default")))
#endif
#define EXPORT_API DAS_EXPORT_DLL

EXPORT_API das_module * register_dyn_Module_Hello() {
    das_module * mod = das_module_create ("HelloModule");
    das_module_group * lib = das_modulegroup_make();
    das_module_bind_interop_function(mod, lib, &hello_from_c_module, "hello_from_c_module", "hello_from_c_module", SIDEEFFECTS_modifyExternal, "s ");
    das_modulegroup_release(lib);
    return mod;
}
