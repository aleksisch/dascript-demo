options gen2
require Hello/hello_module
require HelloModule

[export]
def main() {
    print("Hello world!\n")

    // Das module
    print("{hello_from_das()}\n")
    // C++ module
    print("{hello_from_cpp_module()}\n")
}