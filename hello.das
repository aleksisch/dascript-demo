options gen2
require Hello/hello_module
require Hello/hello_module_cpp
require HelloModule
require HelloCPP

// Will print what was aotted and what wasn't
options log_aot

[export]
def main() {
    print("Hello world!\n")

    // Das module
    print("{hello_from_das()}\n")
    // C module
    print("{hello_from_c_module()}\n")
    // C++ module
    print("{hello_from_cpp_module("Daslang")}\n")
    print("{hello_das_cpp_mod()}\n")
}
