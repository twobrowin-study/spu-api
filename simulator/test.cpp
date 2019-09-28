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
  double x;
  double y;
  double z;
};

struct Point2D {
  float x;
  float y;
};

int main() {
  BaseStructure *baseStructure = new Simulator;
  // Создание структуры struct1 с аргументами ключа: "one", "two", "three" и их размерами в битах
  Structure<string> struct1({
                             { "one",    5 },
                             { "two",    7 },
                             { "three", 10 }
                         }, baseStructure);

  value_t val = { 50, 123 };
  struct1.insert({
                  { "one",    27 },
                  { "two",    10 },
                  { "three",  30 }
              }, val);

  pair_t pair = struct1.search({
                                { "one",    27 },
                                { "two",    10 },
                                { "three",  30 }
                            });

  unsigned int val0 = pair.value[0];
  unsigned int val1 = pair.value[1];

  cout << "Found: " << val0 << " " << val1 << endl;
  cout << "Full pair is " << to_string(pair) << endl;


  // Вставка пары ключ-значение, где
  // ключ: {"one": 3, "two": 3, "three": 3}
  // значение: 1.123
  struct1.insert({
                  { "one",    3 },
                  { "two",    3 },
                  { "three",  3 }
              }, 1.123);

  // Получить значение для ключа {"one": 3, "two": 3, "three": 3}
  pair = struct1.search({
                         { "one",    3 },
                         { "two",    3 },
                         { "three",  3 }
                     });
  if (pair.status == OK) {
    // value является парой двух 32-рязрядных чисел
    unsigned int val0 = pair.value[0];
    unsigned int val1 = pair.value[1];
    cout << "Found: " << val0 << " " << val1 << endl;
    cout << "Full pair is " << to_string(pair) << endl;
    // Также можно обратно получить исходное значение
    double dval = (BitFlow&) pair.value;
    cout << "Found double: " << dval << endl;
  }


  /// C помощью HashMapExternValue можно сохранять структуры любого размера.
  string string1 = "This string stored at hash map. In SPU stored id for a string";
  BaseExternValue extern_val = HashMapExternValue<string>(string1);
  struct1.insert({
                  { "one",    1 },
                  { "two",    1 },
                  { "three",  1 }
              }, extern_val);
  pair = struct1.search({
                         { "one",    1 },
                         { "two",    1 },
                         { "three",  1 }
                     });
  string res_str = (HashMapExternValue<string>) pair.value;
  cout << res_str << endl;

  Point p = {1.5, 2.3, 3.7};
  HashMapExternValue<Point> point_ext;
  /// Операторы << и >> делают тоже, что и методы set и get
  point_ext << p;
  struct1.insert({
                  { "one",   2 },
                  { "two",   2 },
                  { "three", 2 }
              }, point_ext);
  pair = struct1.search({
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



  // Пример демонстрации работы со структурой с шаблонным типом `void`.
  // ------------------------------------------------------------------

  Point2D point = {3.14, 2.7};

  // Создание структуры struct2 без определения агрументов ключа
  Structure<> struct2;

  // Можно вставлять любые структуры данных, размер которых меньше 8 байт
  struct2.insert(123, 120);
  struct2.insert("abc", 10.123);
  struct2.insert(5.321, 50);
  struct2.insert(8, point);

  // И соответсвенно даставать
  pair = struct2.search(123);
  int val123 = (BitFlow&) pair.value;
  cout << "Found 123: " << val123 << endl;
  pair = struct2.search("abc");
  double valabc = (BitFlow&) pair.value;
  cout << "Found 'abc': " << valabc << endl;
  pair = struct2.search(5.321);
  int val5321 = (BitFlow&) pair.value;
  cout << "Found 5.321: " << val5321 << endl;
  pair = struct2.search(8);
  Point2D valpoint = (BitFlow&) pair.value;
  cout << "Found 8: " << valpoint.x << ' ' << valpoint.y << endl;



  /// Ecли объявлен SPU_SIMULATOR, то необязательно указывать симулятор в конструкторе Structure
#ifdef SPU_SIMULATOR
  Structure<> struct3;
  struct3.insert(2, 120);
  struct3.insert(1, 10);
  struct3.insert(5, 50);
  struct3.insert(4, 40);

  pair = struct3.search(2);
  long long val2 = (BitFlow&) pair.value;
  cout << "Value for struct 2: " << val2 << endl;

  /// Получить пару ключ-значение с минимальным ключом в структуре
  pair_t min = struct3.min();     //=> 1: 10
  /// Получить пару ключ-значение с максимальным ключом в структуре
  pair_t max = struct3.max();     //=> 5: 50
  cout << "Min: <" <<  to_string(min) << "> Max: <" << to_string(max) << ">" << endl;

  /// Получить следующую пару ключ-значение
  pair_t next = struct3.next(1);  //=> 2: 120
  /// Получить предыдущую пару ключ-значение
  pair_t prev = struct3.prev(5);  //=> 4: 40
  cout << "Next: <" <<  to_string(next) << "> Prev: <" << to_string(prev) << ">" << endl;

  /// Получить ближайшую пару ключ-значение у которой ключ меньше заданного
  pair_t nsm = struct3.nsm(3);    //=> 2: 120
  /// Получить ближайшую пару ключ-значение у которой ключ больше заданного
  pair_t ngr = struct3.ngr(3);    //=> 4: 40
  cout << "NSM: <" <<  to_string(nsm) << "> NGR: <" << to_string(ngr) << ">" << endl;
#endif
}