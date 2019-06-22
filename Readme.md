ПРОГРАММНЫЙ ИНТЕРФЕЙС ПРОЦЕССОРА С НАБОРОМ КОМАНД ДИСКРЕТНОЙ МАТЕМАТИКИ
=======================================================================


## Материалы по установке SDK Baikal находятся [тут](https://www.baikalelectronics.ru/products/T1/)
## Инструкция по подключению:
1. Собрать [образы ядра драйвера leonhard](https://www.baikalelectronics.ru/upload/Stuff/Baikal_Electronics-SDK_seminar-221118%20%281%29.pdf).
2. Запустить скрипт $BAIKAL_SDK_PATH/usr/scripts/build-boot-img.sh bfkx -a
3. Скачать [API Level0](https://bmstu.codes/twobrowin/spu-api).
4. Изменить в скрипте cp_images_to_srv.sh путь к Baikal SDK и имя пользователя на сервере. Запустить скрипт cp_images_to_srv.sh
5. Подключиться к Baikal с сервера 195.19.32.95 (доступ по ssh доступен всем).
6. На сервере понадобятся две консоли: /dev/ttyACM0 (управляющая) и /dev/ttyUSB0 (linux shell).
7. Подключиться к управляющей консоли: minicom -D /dev/ttyACM0
8. Запустить Baikal систему: power on
9. В консоли /dev/ttyUSB0 выбрать пункт 7 меню (загрузка по tftp). В итоге ваш кастомный образ из папки /tftp/ будет загружен в систему.
10. После загрузки Linux копировать выданные скриптом cp_images_to_srv.sh в консоль Baikal shell (minicom -D /dev/ttyUSB0). Запустить команды. В итогу в вашей ~/ директории будут записаны драйвер leonhard, и текстовый код. Далее можно начать тестирование вашего приложения.



РЕФЕРАТ
=======

МИКРОПРОЦЕССОРНЫЕ СИСТЕМЫ, 
ПРОЦЕССОР ОБРАБОТКИ СТРУКТУР, 
ПРОЦЕССОР С НАБОРОМ КОМАНД ДИСКРЕТНОЙ МАТЕМАТИКИ, 
ПРОГРАММНЫЙ ИНТЕРФЕЙС, 
СИСТЕМНОЕ ПРОГРАММИРОВАНИЕ.

Настоящая работа посвящена разработке программного интерфейса
процессора с набором команд дискретной математики (процессора обработки
структур, далее СП). Программный интерфейс предназначен для включения в
разрабатываемое программное обеспечение с использованием
вычислительной мощности СП.

Программный интерфейс состоит из драйвера СП для ОС GNU/Linux и
библиотеки СП. Драйвер предоставляет интерфейс передачи команд
процессора обработки структур на основе символьного файла посредством
системной шины PCI. Библиотека СП обеспечивает упрощение передачи
управляющих команд драйверу и основывается на объектном подходе к
рассмотрению структур СП.

Отличительной особенностью библиотеки СП является наличие
системы классов, обеспечивающей возможность разметки данных на
именованные поля. Данные рассматриваются как набор разрядов и могут
представлять как ключ, так и значение структуры СП.


СОДЕРЖАНИЕ
==========


ВВЕДЕНИЕ
========

Современные вычислительные машины обладают не только
достоинствами, вытекающими из принципов унификации и универсальности,
но и рядом недостатков. В качестве основного обрабатывающего блока ЭВМ
выступает арифметико-логическое устройство [1]. Вместе с тем, при решении
практических задач используется существенно большее количество
математических операций, включая операции над множествами в дискретной
математике.

В МГТУ им. Н.Э. Баумана проведен полный цикл создания
принципиально новой универсальной вычислительной системы, начиная от
создания принципов и моделей и заканчивая созданием опытного образца,
проведения тестов и испытаний [2]. Разработано принципиально новое
вычислительное устройство: Процессор с набором команд дискретной
математики (Процессор обработки структур, далее СП), реализующее набор
команд дискретной математики высокого уровня над множествами и
структурами данных. Новая архитектура позволяет более эффективно
решать задачи дискретной оптимизации, основанные на моделях множеств,
графов, и отношений.

Включение вычислительных ресурсов СП в разрабатываемое ПО
выполняется посредством программного интерфейса (далее ПИ). Для
программиста ПИ представляет собой библиотеку СП, обеспечивающую
передачу команд и операндов СП, получение результатов выполнения
операций.

Существующая версия ПИ СП требует знаний системного
программирования СП для использования. Такая версия ПИ не позволяет
вовлекать новых разработчиков, что приводит к проблеме развития СП.

Алгоритмы, разработанные специально для СП, опираются на ширину
ключа для поиска записей в памяти СП и определяют составные поля
представления ключа. Существующая версия ПИ предоставляет функции
разбиения данных на поля комплексными манипуляциями усвоения сдвигов в
поразрядном представлении данных.

К разрабатываемой версии ПИ предъявляются следующие основные
требования:
1. рассмотрение структур СП как объектов;
2. выполнение разбиения данных на поля в объектной модели;
3. выработка метода расширения количества хранимых структур СП;
4. выработка метода потоковой обработки команд СП и выполнение
системной поддержки (уровня драйвера СП) ПИ на основаниях
ассемблера СП.



# 1 Основные характеристики микроархитектуры СП

Процессор с набором команд дискретной математики (процессор
обработки структур, СП) представляет собой вычислительный модуль, работа
которого основана на хранении данных вида ключ-значения и их
объединении в структуры [11]. Структуры СП представляют собой наборы
данных ключ-значение. Процессор способен выполнять действия над
структурами, соответствующие основным операциям дискретной математики
над множествами. Среди этих операций: добавление, удаление, поиск (в том
числе поиск наиболее похожего), а также операции над несколькими
структурами (пересечение, сложение, вычитание).

Структуры данных с формальной точки зрения представляет собой совокупность
двух сущностей: информационную составляющую о значениях полей данных и структурную 
составляющую, учитывающую отношения данных. Такая двойственность
позволяет разделить процесс обработки структур данных на два потока вычислений:
во-первых, поток обработки структурной составляющей и, во-вторых, поток обработки
информационной части. В связи с этим в вычислительной системе может быть два
параллельно работающих микропроцессора: это специальный микропроцессор, который
обрабатывает реляционную (структурную) часть структур данных, в то время как 
универсальный CPU выполняет вычисления над информационной составляющей структур.


![Рисунок 1 ― Архитектура вычислительной системы с несколькими потоками команд и 
одним потоком данных](docs/MISD_architecture.png)

Рисунок 1 ― Архитектура вычислительной системы с несколькими потоками команд и 
одним потоком данных


На рисунке 2 представлена микроархитектура реализации СП под
названием Leonhard. В [2] приведено исчерпывающее описание блоков
микроархитектуры СП, даны принципы работы. Настоящая работа
рассматривает эту архитектуру как «чёрный ящик».


![Рисунок 2 ― Микроархитектура микропроцессора Leonhard](docs/Leonhard_architecture.png)

Рисунок 2 ― Микроархитектура микропроцессора Leonhard


Для ускорения поиска и обработки всего набора команд микропроцессор Leonhard
x64 использует внутренне представление множеств в виде B+дерева, для которого
возможна параллельная обработка нескольких вершин дерева как на промежуточных
уровнях, используемых для поиска, так и на нижнем уровне, хранящем непосредственно
ключи и значения. В связи с этим любая операция над структурой начинается с поиска
информации в B+дереве, а заканчивается обработкой так называемых листьев дерева
(вершин нижнего уровня).



# 2 Набор команд дискретном математики

Микропроцессор Leonhard x64 хранит информацию о множествах в виде неперекрывающихся 
B+ деревьев. Последняя версия набора команд Leonhard x64 была расширена
двумя новыми инструкциями (NSM и NGR) для обеспечения требований некоторых
алгоритмов. Каждая инструкция набора включает до трех операндов (таблица 1.1):

Таблица 1 - Формат данных Leonhard x64

| Структура | Ключ    | Значение |
| --------- | ------- | -------- |
| 3 бита    | 64 бита | 64 бита  |


Набор команд состоит из 20 высокоуровневых кодов операций, перечисленных ниже.
- **Search (SRCH)** выполняет поиск значения, связанного с ключом.
- **Insert (INS)** вставляет пару ключ-значение в структуру. SPU обновляет значение,
если указанный ключ уже находится в структуре.
- **Операция Delete (DEL)** выполняет поиск указанного ключа и удаляет его из
структуры данных.
- **Neighbors (NSM, NGR)** выполняют поиск соседнего ключа, который меньше (или
больше) заданного и возвращает его значение. Операции могут быть использованы
для эвристических вычислений, где интерполяция данных используется вместо
точных вычислений (например, кластеризация или агрегация).
- **Maximum /minimum (MAX, MIN)** ищут первый или последний ключи в структуре данных.
- **Операция Cardinality (CNT)** определяет количество ключей, хранящихся в структуре.
- **Команды AND, OR, NOT** выполняют объединения, пересечения и дополнения в
двух структурах данных.
- **Срезы (LS, GR, LSEQ, GREQ)** извлекают подмножество одной структуры данных в другую.
- **Переход к следующему или предыдущему (NEXT, PREV)** находят соседний
(следующий или предыдущий) ключ в структуре данных относительно переданного
ключа. В связи с тем, что исходный ключ должен обязательно присутствовать в
структуре данных, операции NEXT/PREV отличаются от NSM/NGR.
- **Удаление структуры (DELS)** очищает все ресурсы, используемые заданной структурой.
- **Команда Squeeze (SQ)** дефрагментирует блоки памяти DSM, используемые структурой.
- **Команда Jump (JT)** указывает SPU код ветвления, который должен быть
синхронизирован с CPU (команда доступна только в режиме MISD).

Микропроцессор реализован на базе микросхемы ПЛИС XC6VLX240T-1FFG1156,
входящей в состав отладочной платы ML605

Таблица 2 - Параметры Leonhard x64

| Параметр                                                       | Значение    |
| -------------------------------------------------------------- | ----------- |
| Максимальный размер команды в локальной памяти команд СП (LCM) | 144 бит     |
| Максимальный размер команды из ЦП                              | 160 бит     |
| Максимальный размер результата из СП в ЦП                      | 64 бит      |
| Количество разрядов поля ключа                                 | 64 бит      |
| Количество разрядов поля значения                              | 64 бит      |
| Расположение байт в памяти                                     | Младший байт по младшему адресу |
| Размер внешней памяти структур                                 | 4 ГБайта    |
| Максимальное количество ключей в структуре                     | 100 663 296 |
| Кратность вершины B+ дерева                                    | 8           |
| Количество ключей на нижнем уровне дерева                      | 6           |
| Максимальное количество хранимых структур                      | 7           |

