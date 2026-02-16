options gen2
options log_aot
module hello_module_cpp

// Avoid inline
var x = "Hello from"

def hello_das_cpp_mod() {
    // This will be aotted
    return x + " das!"
}

