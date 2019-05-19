//
// Created by a.kiryanenko on 2019-05-17.
//

#include <iostream>
#include "../libspu/structure.hpp"
#include "Simulator.h"

using namespace std;
using namespace SPU;

int main() {
  Simulator simulator;
  auto &baseStructure = (BaseStructure&) simulator;
  Structure<string> str1({
                             { "one",    5 },
                             { "two",    7 },
                             { "three", 10 }
                         }, baseStructure);

  value_t val = { 50, 123 };
  str1.insert({
                  { "one",    27 },
                  { "two",    10 },
                  { "three",  30 }
              }, val);

  pair_t pair = str1.search({
                                { "one",    27 },
                                { "two",    10 },
                                { "three",  30 }
                            });

  unsigned int val0 = pair.value[0];
  unsigned int val1 = pair.value[1];

  cout << "Found: " << val0 << " " << val1 << endl;
  cout << "Full pair is " << to_string(pair) << endl;

  int b = (BitFlow&) pair.value;
  cout << "Value " << b;
}