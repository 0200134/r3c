#include "stdlib.hpp"

std::string injectStdLib() {
    return R"(
pub fn r3c_stdlib_info() {
    println!("[r3c-stdlib] ready: core utilities linked.");
}

pub fn r3c_sum(a: i32, b: i32) -> i32 {
    a + b
}

pub fn r3c_hello() {
    println!("Hello from r3c stdlib!");
}
)";
}
