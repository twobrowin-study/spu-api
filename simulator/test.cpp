//
// Created by a.kiryanenko on 2019-05-17.
//

#include <iostream>
#include "../libspu/structure.hpp"
#include "Simulator.h"

/// Объявление SPU_SIMULATOR определяет использовать ли симулятор SPU по умолчанию
#define SPU_SIMULATOR

using namespace std;
using namespace SPU;

int main() {
  BaseStructure *baseStructure = new Simulator;
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
  cout << "Value " << b << endl;


  /// Ecли объявлен SPU_SIMULATOR, то необязательно указывать симулятор в конструкторе Structure
#ifdef SPU_SIMULATOR
  Structure<> str2;
  str2.insert(2, 3);
  pair = str2.search(2);
  int val2 = (BitFlow&) pair.value;
  cout << "Value for struct 2: " << val2 << endl;
#endif
}