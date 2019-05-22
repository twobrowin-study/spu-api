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

struct Point {
  float x;
  float y;
  float z;
};

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



  str1.insert({
                  { "one",    3 },
                  { "two",    3 },
                  { "three",  3 }
              }, 1.123);
  pair = str1.search({
                         { "one",    3 },
                         { "two",    3 },
                         { "three",  3 }
                     });
  double fval = (BitFlow&) pair.value;
  cout << "Double value: " << fval << endl;


  string string1 = "This string stored at hash map. In SPU stored id for a string";
  BaseExternValue extern_val = HashMapExternValue<string>(string1);
  str1.insert({
                  { "one",    1 },
                  { "two",    1 },
                  { "three",  1 }
              }, extern_val);
  pair = str1.search({
                         { "one",    1 },
                         { "two",    1 },
                         { "three",  1 }
                     });
  string res_str = (HashMapExternValue<string>) pair.value;
  cout << res_str << endl;

  /// C помощью HashMapExternValue можно хранить любые структуры.
  /// Операторы << и >> делают тоже, что и методы set и get
  Point p = {1.5, 2.3, 3.7};
  HashMapExternValue<Point> point_ext;
  point_ext << p;
  str1.insert({
                  { "one",   2 },
                  { "two",   2 },
                  { "three", 2 }
              }, point_ext);
  pair = str1.search({
                               { "one",    2 },
                               { "two",    2 },
                               { "three",  2 }
                           });
  if (pair.status == OK) {
    point_ext << pair;
    Point p_res;
    point_ext >> p;
    cout << "Point struct X=" << p.x << " Y=" << p.y << " Z=" << p.z << endl;
  }


  /// Ecли объявлен SPU_SIMULATOR, то необязательно указывать симулятор в конструкторе Structure
#ifdef SPU_SIMULATOR
  Structure<> str2;
  str2.insert(2, 120);
  str2.insert(1, 10);
  str2.insert(5, 50);
  str2.insert(4, 40);

  pair = str2.search(2);
  long long val2 = (BitFlow&) pair.value;
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