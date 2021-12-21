#include <chrono>
#include <cmath>
#include <iostream>

#define LOOPS 1'000'000'000

using namespace std;

long log() {
  long a = 0;
  for (size_t i = 1; i < LOOPS; ++i) {
    a += floor(log10(i)) + 1;
  }
  return a;
}

long div() {
  long a = 0;
  for (size_t i = 1; i < LOOPS; ++i) {
    long x = 0;
    for (size_t j = i; j > 0; j /= 10) {
      ++x;
    }
    a += x;
  }
  return a;
}

void benchmark(long (*f)(), string name) {
  auto t1 = chrono::high_resolution_clock::now();
  long a = (*f)();
  auto t2 = chrono::high_resolution_clock::now();
  auto dur = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
  cout << name << " takes " << dur << "ms - " << a << endl;
}

int main() {
  benchmark(log, "log");
  benchmark(div, "div");
}
