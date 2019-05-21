//
// Created by a.kiryanenko on 2019-05-17.
//

#include <iostream>
#include "../libspu/structure.hpp"
#include "../libspu/extern_value.h"
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


  string string1 = "This string stored at hash map. In SPU stored id for a string";
  BaseExternValue extern_val = HashMapExternValue<string>(string1);
  str1.insert({
                  { "one",    27 },
                  { "two",    10 },
                  { "three",  30 }
              }, extern_val);


  /// Ecли объявлен SPU_SIMULATOR, то необязательно указывать симулятор в конструкторе Structure
#ifdef SPU_SIMULATOR
  Structure<> str2;
  str2.insert(2, 120);
  str2.insert(1, 10);
  str2.insert(5, 50);
  str2.insert(4, 40);

  pair = str2.search(2);
  int val2 = (BitFlow&) pair.value;
  cout << "Value for struct 2: " << val2 << endl;

  pair_t min = str2.min();
  pair_t max = str2.max();
  cout << "Min: <" <<  to_string(min) << "> Max: <" << to_string(max) << ">" << endl;

  pair_t next = str2.next(1);
  pair_t prev = str2.prev(5);
  cout << "Next: <" <<  to_string(next) << "> Prev: <" << to_string(prev) << ">" << endl;

  pair_t nsm = str2.nsm(3);
  pair_t ngr = str2.ngr(3);
  cout << "NSM: <" <<  to_string(nsm) << "> NGR: <" << to_string(ngr) << ">" << endl;
#endif
}