#pragma once
#include <string>

namespace r3c {

struct TranspileOptions {
  std::string input_path;
  std::string out_dir = "build/out";
  bool emit_asm = false;
  bool emit_rust = false;
};

class Transpiler {
public:
  int run(const TranspileOptions& opt);

private:
  int ensure_out_dir(const std::string& outdir);
  int write_text(const std::string& path, const std::string& content);
  std::string toy_rust_stub();
  std::string toy_linux_x64_nasm();
};

} // namespace r3c