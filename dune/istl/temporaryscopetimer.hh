#ifndef DUNE_ISTL_TEMPORARYSCOPETIMER_HH
#define DUNE_ISTL_TEMPORARYSCOPETIMER_HH
#include <chrono>
#include <fstream>
#include <string>
#include <execution>
#include <algorithm>

#include <execution>
#include <algorithm>
#include <ranges>

namespace Dune::util {

struct TimeScope {
  int line;
  std::string file;
  std::string function;
  std::chrono::high_resolution_clock::time_point start;
  std::string basename;

  TimeScope(const char* n, int l, const char* f, const char* func)
    : basename(n), line(l), file(f), function(func), start(std::chrono::high_resolution_clock::now())
  {}


  ~TimeScope() {
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::string base = file.substr(file.find_last_of("/\\") + 1);
    std::string filename = base + "_" + function + "_" + std::to_string(line) + ".txt";
    std::ofstream out(filename, std::ios_base::app);
    out << diff.count() << "\n";
  }
};
}

#define TIME_SCOPE(name) ::Dune::util::TimeScope temporarytimer(name, __LINE__, __FILE__, __func__)

#endif // DUNE_ISTL_TEMPORARYSCOPETIMER_HH