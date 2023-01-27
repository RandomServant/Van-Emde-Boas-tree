![Fefu_logo](https://github.com/RandomServant/Van-Emde-Boas-tree/blob/master/Images/DVFU_Logo.png)
## Федеральное агентство по образованию РФ
## Дальневосточный федеральный университет
## ИНСТИТУТ МАТЕМАТИКИ И КОМПЬЮТЕРНЫХ ТЕХНОЛОГИЙ
## Департамент математического и компьютерного моделирования
# Дерево ван Эмде Боаса
## Доклад
### Студента гр. Б9121-09.03.03пикд
### Борика Р. Д.
### Руководитель
### Кленин А. С.
### г. Владивосток 2023


--------------------------
Содержание <a name="Содержание"></a>
===============
- [Содержание](#содержание-)
- [Глоссарий](#глоссарий-)
- [Формальная постановка задачи](#формальная-постановка-задачи-)
- [1. Вступление](#1-вступление-)
- [2. Использование](#2-использование-)
- [3. История](#3-история-)
- [4. Ограничения](#4-ограничения-)
- [5. Поддерживаемые операции](#5-поддерживаемые-операции-)
- [6. Реализация](#6-реализация-)
  - [6.1.Структура](#61-структура-)
    - [6.1.1. Атрибуты](#611-атрибуты-узла-дерева-ван-эмде-боаса-)
    - [6.1.2 Конструктор](#612-конструктор-)
    - [6.1.3. Вспомогательные функции](#613-вспомогательные-функции-)
  - [6.2. Поддерживаемые операции](#62-поддерживаемые-операции-)
    - [6.2.1. MinimumVEB и MaximumVEB](#621-minimumveb-и-maximumveb-)
    - [6.2.2. Find](#622--find-)
    - [6.2.3. Insert](#623-insert-)
    - [6.2.4. SuccessorVEB](#624-successorveb-)
    - [6.2.5. PredecessorVEB](#625-predecessorveb-)
    - [6.2.6. RemoveVEB](#626-removeveb-)
- [7. Тестирование](#7-тестирование-)
  - [7.1. Запуск](#71-запуск-)
  - [7.2. Требования](#72-требования-)
    - [7.2.1. Пример](#ПримерТ)
  - [7.3. Заполнение файлов .in](#73-заполнение-файлов-in-)
    - [7.3.1. Сокращение команд](#731-сокращение-команд-)
    - [7.3.2. Пример](#732-пример-)
  - [7.4 Заполнение файлов .ans](#74-заполнение-файлов-ans-)
    - [7.4.1. Пример](#741-пример-)
  - [7.5. Вывод в файл .out](#75-вывод-в-файл-out-)
    - [7.5.1. Пример](#751-пример-)
  - [7.6. Генератор тестов](#76-генератор-тестов-)
- [8. Проверка производительности](#8-проверка-производительности-)
  - [8.1. Итоги](#81-итоги-)
- [9. Список литературы](#9-список-литературы-)
      
----------------------------
Глоссарий <a name="Глоссарий"></a>
===============
- `vEB дерево` - дерево ван Эмде Боаса.
- `Ассоциативный массив` - абстрактный тип данных, позволяющий хранить пары вида «(ключ, значение)».
- `null` - в данной реализации за `null` принимается значение `-1`.
-----------------------------
Формальная постановка задачи <a name="Формальнаяпостановказадачи"></a>
=============== 
1. Изучить алгоритм "дерево ван Эмде Боаса" и описать его в форме научного доклада
2. Реализовать алгоритм "дерево ван Эмде Боаса" со всеми присущими
ему операциями: минимум, максимум, вставка, удаление, поиск следующего, поиск предыдущего, поиск элемента.
3. Выполнить исследование на производительность сравнением с другими древовидными структурами данных.
4. Результат работы выложить на github.

---------------------
1\. Вступление <a name="Вступление"></a>
===============
**Дерево ван Эмде Боаса (van Emde Boas tree)** — ассоциативный массив, 
который позволяет хранить целые числа в диапазоне `[0; U)`, где `U` положительное целое число вида $2^k$, 
здесь `U` является размером дерева Ван Эмде Боаса, а `k` является максимальным количеством бит в числе.
Дерево позволяет осуществлять над числами все соответствующие дереву поиска операции.

Главное достоинство этой структуры — выполнение всех операций за время `O(log(log(U)))`
независимо от количества хранящихся в ней элементов.

Недостатком этой структуры данных является, что для слишком больших `U`, дерево ван Эмде Боаса
будет занимать большое количество памяти (грубая оценка — `O(U)`). [[2]](#9-список-литературы-)

----------------------------------------
2\. Использование <a name="Использование"></a>
===============
**Деревья ван Эмде Боаса** можно использовать где угодно, вместо обычного бинарного дерева поиска, 
если ключи в дереве поиска являются целыми числами в некотором фиксированном диапазоне. Таким образом, для приложений, 
где вам нужно найти целое число в наборе, наиболее близком к некоторому другому целому, 
использование **vEB-дерева** потенциально может быть быстрее, чем использование простого 
**бинарного дерева поиска**. [[4]](#9-список-литературы-)

Кроме этого очевидного использования **vEB-дерева**, его можно использовать для следующего:

1. **Сортировка последовательности** за `O(n*log(log(U)))` </br>
Для этого нам необходимо вставить элементы, которые необходимо отсортировать, в дерево и запомнить минимальное значение и в цикле вызвать функцию `SuccessorVEB` (поиск следующего числа в дереве, подробнее про функцию далее) 
от него с увеличением числа `x = SuccessorVEB(x + 1)`.
2. **Алгоритм Дейкстры** </br>
Так как с использованием двоичной кучи этот алгоритм работает за `O(E*Log(V))`, где `E` - количество ребер между вершинами,
`V` - количество вершин в графе. Если же вместо кучи использовать дерево Ван Эмде Боаса, то итоговая асимптотика снизится 
до `O(E*log(log(U)))` [[2]](#9-список-литературы-)

---------------------
3\. История <a name="История"></a>
===============
VEB дерево было изобретено командой во главе с голландским ученым-компьютерщиком Питером ван Эмде Боасом в 1975 году.
[[3]](#9-список-литературы-)

-------------------
4\. Ограничения <a name="Данные"></a>
===============
Алгоритм дерева ван Эмде Боаса требует корректности входных данных.
Он не гарантирует корректного удаления несуществующего элемента.
Размер дерева должен являться степенью двойки.

---------------------------------------
5\. Поддерживаемые операции <a name="Поддерживаемыеоперации"></a>
===============
- `Insert(x)` — Вставка числа `x` в дерево.
- `RemoveVEB(x)` — Удаление числа `x`.
- `MinimumVEB()`, `MaximumVEB()` — Нахождение минимума и максимума в дереве.
- `Find(x)` — Поиск числа `x` в дереве.
- `SuccessorVEB(x)` — Поиск следующего числа после `x`, которое содержится в дереве.
- `PredecessorVEB(x)` — Поиск предшествующего `x` числа.
[[2][4]](#9-список-литературы-)

| Insert             | RemoveVEB          | MinimumVEB | MaximumVEB | Find               | SuccessorVEB       | PredecessorVEB     |
|--------------------|--------------------|------------|------------|--------------------|--------------------|--------------------|
| $$O(log(log(U)))$$ | $$O(log(log(U)))$$ | $$O(1)$$   | $$O(1)$$   | $$O(log(log(U)))$$ | $$O(log(log(U)))$$ | $$O(log(log(U)))$$ |

---------------------------------------
6\. Реализация <a name="Реализация"></a>
===================
Исходный код можно найти [здесь](https://github.com/RandomServant/Van-Emde-Boas-tree/tree/master/vEB%20Tree).

6\.1. Структура <a name="СтруктураР"></a>
------------------
### 6\.1.1. Атрибуты узла дерева ван Эмде Боаса <a name="АтрибутыР"></a>

- `universeSize` - число элементов, хранящееся в дереве, корнем которого является текущий узел
- `minimum` - минимальное значение дерева, корнем которого является данный узел
- `maximum` - максимальное значение дерева, корнем которого является данный узел
- `summary` - вспомогательное дерево, хранящее информацию о детях текущего узла
- `cluster` - массив, хранящий указатели на детей узла
```c++
int universeSize;
int minimum;
int maximum;
VanEmdeBoasTree* summary;
VanEmdeBoasTree** clusters;
```

-------------------
| ![Рис. 1: Дерево ван Эмде Боаса размерностью 16, содержащее числа {2, 3, 4, 5, 7, 14, 15}](https://github.com/RandomServant/Van-Emde-Boas-tree/blob/master/Images/vEB_Struct.png) |
|:--:|
| Рис. 1: Дерево ван Эмде Боаса размерностью 16, содержащее числа {2, 3, 4, 5, 7, 14, 15} |

--------------------
| ![Рис. 2: Summary хранит информацию о заполненности или пустоте детей текущего узла](https://github.com/RandomServant/Van-Emde-Boas-tree/blob/master/Images/Summary.png) |
|:--:|
| Рис. 2: Summary хранит информацию о заполненности или пустоте детей текущего узла |

------------------------------------
### 6\.1.2. Конструктор <a name="Конструктор"></a>
```c++
VanEmdeBoasTree(int size) {
    universeSize = size;
    minimum = null;
    maximum = null;

    if(size <= 2) {
        summary = nullptr;
        clusters = new VanEmdeBoasTree*[0];
    }
    else {
        int sizeOfNewClusters = ceil(sqrt(size));

        summary = new VanEmdeBoasTree(sizeOfNewClusters);

        clusters = new VanEmdeBoasTree*[sizeOfNewClusters];

        for (int i = 0; i < sizeOfNewClusters; ++i) {
            clusters[i] = new VanEmdeBoasTree(ceil(sqrt(size)));
        }
    }
}
```
### 6\.1.3. Вспомогательные функции <a name="ВспомогательныефункцииР"></a>

- `High(x)` — число, указывающее номер кластера ключа `х`
- `Low(x)` — число, указывающее позицию `х` в его кластере
- `GenerateIndex(x, y)` — число, указывающее позицию ключа, полученную из его позиции в кластере `y` и его индекса кластера `x`
```c++
int High(int x)
    {
        int div = ceil(sqrt(universeSize));
        return x / div;
    }
```
```c++
int Low(int x)
    {
        int mod = ceil(sqrt(universeSize));
        return x % mod;
    }
```
```c++
int GenerateIndex(int x, int y)
    {
        int ru = ceil(sqrt(universeSize));
        return x * ru + y;
    }
```
6\.2. Поддерживаемые операции <a name="ПоддерживаемыеоперацииР"></a>
------------------
### 6\.2.1. MinimumVEB и MaximumVEB <a name="minmax"></a>
Дерево Ван Эмде Боаса хранит минимум и максимум в качестве своих атрибутов, 
поэтому мы можем вернуть его значение, если оно присутствует, и `null` в противном случае.
```c++
int MinimumVEB() {
    return minimum;
}

int MaximumVEB() {
    return maximum;
}
```

### 6\.2.2.  Find <a name="Find"></a>
- В любой точке нашего поиска, если ключ является минимальным или максимальным для дерева, что означает, что ключ присутствует, тогда верните `true`.
- Если мы достигнем базового случая, но приведенное выше условие равно `false`, то ключ не должен присутствовать в дереве, поэтому верните `true`.
- В противном случае рекурсивно вызовите функцию над кластером ключа, т.е. `[High(key)]` и его положение в кластере, т. е. `[Low(key)]`.
- Здесь мы разрешаем `universeSize` принимать любую степень 2, так что, если возникает ситуация, в которой `universeSize` меньше значения ключа, тогда возвращайте `false`.
```c++
bool Find(int key) {
        if (universeSize < key) {
            return false;
        }
        if (minimum == key || maximum == key) {
            return true;
        }
        else {
            if (universeSize == 2) {
                return false;
            }
            else {
                return clusters[High(key)]->Find(Low(key));
            }
        }
    }
```
### 6\.2.3. Insert <a name="Insert"></a>
1. Если в дереве нет ключей, то просто назначьте ключу минимум и максимум дерева.
2. В противном случае мы углубимся в дерево и сделаем следующее:
     - Если ключ, который мы хотим вставить, меньше текущего минимума дерева, то мы меняем местами оба значения, потому что новый ключ будет реальным минимумом дерева, а ключ, который уже был на месте минимума, будет использоваться для дальнейшего процесса.
Эту концепцию можно рассматривать как ленивое размножение в дереве Ван Эмде Боаса. Потому что это старое минимальное значение действительно является минимумом одного из кластеров рекурсивной структуры Ван Эмде Боаса. Так что на самом деле мы не углубляемся в структуру до тех пор, пока не возникнет такая необходимость.
     - Если мы не находимся в базовом случае, это означает, что размер вселенной дерева больше 2, тогда:
Если кластер дерева `[High(key)]` пуст, то мы рекурсивно вызываем `Insert` поверх `summary` и, поскольку мы выполняем ленивое распространение, мы просто присваиваем ключу минимальное и максимальное значение и останавливаем рекурсию.
В противном случае мы вызываем `Insert` над кластером, в котором присутствует ключ.
3. Аналогично, мы проверяем значение `maximum` и устанавливаем ключ как `maximum`, если он больше текущего максимума.

```c++
void Insert(int key) {
        if(minimum == -1) {
            minimum = key;
            maximum = key;
        }
        else {
            if(key < minimum)
                swap(key, minimum);

            if(universeSize > 2) {
                if(clusters[High(key)]->MinimumVEB() == -1) {
                    summary->Insert(High(key));
                    clusters[High(key)]->minimum = Low(key);
                    clusters[High(key)]->maximum = Low(key);
                }
                else {
                    clusters[High(key)]->Insert(Low(key));
                }
            }

            if (key > maximum) {
                maximum = key;
            }
        }
    }
```
### 6\.2.4. SuccessorVEB <a name="SuccessorVEB"></a>
- **Базовый случай**: Если размер дерева `universeSize` равен 2, то если ключ запроса равен 0, а ключ - 1 присутствует в дереве, то верните 1, так как он будет преемником. В противном случае верните значение `null`.
- Если ключ меньше минимального, то мы можем легко сказать, что минимум будет преемником ключа запроса.
- **Рекурсивный случай**:
    - Сначала мы ищем преемника в кластере, в котором присутствует ключ.
    - Если мы найдем какого-либо преемника в кластере, то сгенерируем его индекс и вернем его.
    - В противном случае выполните поиск следующего кластера, в котором присутствует хотя бы один ключ, и верните минимальный индекс этого кластера.
```c++
int SuccessorVEB(int key) {
        if(universeSize == 2) {
            if(key == 0 && maximum == 1)
                return 1;
            else
                return -1;
        }
        else if (minimum != -1 && key < minimum){
            return minimum;
        }
        else {
            int maxElementInCluster = clusters[High(key)]->MaximumVEB();
            int offset, successorCluster;

            if (maxElementInCluster != -1 && Low(key) < maxElementInCluster) {
                offset = clusters[High(key)]->SuccessorVEB(Low(key));
                return GenerateIndex(High(key), offset);
            }

            else {
                successorCluster = summary->SuccessorVEB(High(key));

                if (successorCluster == -1) {
                    return -1;
                }
                else {
                    offset = clusters[successorCluster]->MinimumVEB();
                    return GenerateIndex(successorCluster, offset);
                }
            }
        }
    }
```
### 6\.2.5. PredecessorVEB <a name="PredecessorVEB"></a>
- **Базовый случай:** Если размер `universeSize` дерева равен 2, то если ключ запроса равен 1, а ключ-0 присутствует в дереве, то верните 0, так как он будет предшественником. В противном случае верните значение `null`.
- Если ключ больше максимального, то мы можем легко сказать, что maximum будет предшественником ключа запроса.
- **Рекурсивный случай:**
    - Сначала мы ищем предшественника в кластере, в котором присутствует ключ.
    - Если мы найдем какой-либо предшественник в кластере, то сгенерируем его индекс и вернем его.
    - В противном случае выполните поиск предыдущего кластера, в котором присутствует хотя бы один ключ, в сводке. Если какой-либо кластер присутствует, то верните индекс максимума этого кластера.
    - Если кластера с этим свойством нет, то посмотрите, является ли из-за ленивого распространения минимум дерева (в котором присутствует кластер) меньше ключа, если да, то верните минимум, в противном случае верните `null`.
```c++
int PredecessorVEB(int key) {
        if (universeSize == 2) {
            if (key == 1 && minimum == 0)
                return 0;
            else
                return -1;
        }
        else if (maximum != -1 && key > maximum) {

            return maximum;
        }
        else {
            int minInCluster = clusters[High(key)]->MinimumVEB();
            int offset{ 0 }, pred_cluster{ 0 };

            if (minInCluster != -1 && Low(key) > minInCluster) {
                offset = clusters[High(key)]->PredecessorVEB(Low(key));

                return GenerateIndex(High(key), offset);
            }
            else {
                pred_cluster = summary->PredecessorVEB(High(key));

                if (pred_cluster == -1) {
                    if (minimum != -1 && key > minimum) {
                        return minimum;
                    } else
                        return -1;
                }
                else {
                    offset = clusters[pred_cluster]->MaximumVEB();

                    return GenerateIndex(pred_cluster, offset);
                }
            }
        }
    }
```
### 6\.2.6. RemoveVEB <a name="RemoveVEB"></a>
Предполагается, что ключ уже присутствует в дереве.

- Сначала мы проверяем, присутствует ли только один ключ, затем присваиваем максимуму и минимуму дерева значение `null`, чтобы удалить ключ.
- **Базовый случай:** если размер `universeSize` дерева равен двум, то после того, как приведенное выше условие наличия только одного ключа равно false, в дереве присутствует ровно два ключа (после того, как приведенное выше условие окажется ложным), поэтому удалите ключ запроса, присвоив максимуму и минимуму дерева значение еще один ключ, присутствующий в дереве.
- **Рекурсивный случай:**
    - Если ключ является минимумом дерева, то найдите следующий минимум дерева и назначьте его как минимум дерева и удалите ключ запроса.
    - Теперь ключ запроса отсутствует в дереве. Нам придется изменить остальную часть структуры в дереве, чтобы полностью исключить ключ:
    - Если минимум кластера ключа запроса равен `null`, то мы также удалим его из сводки. Кроме того, если ключ является максимумом дерева, то мы найдем новый максимум и назначим его как максимум дерева.
    - В противном случае, если ключ является максимальным для дерева, найдите новый максимум и назначьте его как максимум дерева.
```c++
void RemoveVEB(int key) {
        if (maximum == minimum) {
            minimum = -1;
            maximum = -1;
        }
        else if (universeSize == 2) {
            if (key == 0) {
                minimum = 1;
            }
            else {
                minimum = 0;
            }
            maximum = minimum;
        }
        else {
            if (key == minimum) {
                int first_cluster = summary->MinimumVEB();

                key = GenerateIndex(first_cluster, clusters[first_cluster]->MinimumVEB());
                minimum = key;
            }

            clusters[High(key)]->RemoveVEB(Low(key));

            if (clusters[High(key)]->MinimumVEB() == -1) {
                summary->RemoveVEB(High(key));

                if (key == maximum) {
                    int maxInSummary = summary->MaximumVEB();

                    if (maxInSummary == -1) {
                        maximum = minimum;
                    }
                    else {
                        maximum = GenerateIndex(maxInSummary, clusters[maxInSummary]->MaximumVEB());
                    }
                }
            }
            else if (key == maximum) {
                maximum = GenerateIndex(High(key), clusters[High(key)]->MaximumVEB());
            }
        }
    }
```
[[4]](#9-список-литературы-)

------------------------
7\. Тестирование <a name="Тестирование"></a>
=================
Исходный код можно найти [здесь](https://github.com/RandomServant/Van-Emde-Boas-tree/tree/master/Testing).

7\.1 Запуск <a name="Запуск"></a>
--------------
```c++
Testing *test = new Testing(/*Путь к папке с файлами*/, /*Количество файлов*/);
test->StartTests();
```
7\.2. Требования <a name="Требования"></a>
--------------
- Папка с файлами должна содержать файлы с расширениями `.in`, `.ans`.
- Количество файлов должно быть одинаковым для разных расширений файлов.
- Файлы должны названы натуральными числами
### 7.2.1 Пример <a name="ПримерТ"></a>
```
1.in
1.ans
2.in
2.ans
...
16.in
16.ans
```

7\.3. Заполнение файлов .in <a name=".in"></a>
--------------
- На первой строке указывается размер **vEB дерева**.
- Далее на каждой строке указываются сокращенные версии команд и, если требуется, ключ.
- На последней строке файла ставится символ `e` для завершения считывания.

### 7.3.1. Сокращение команд <a name="Сокращениекоманд"></a>
- `f` - функция `Find` (через пробел указывается ключ, ожидается вывод 1 или 0).
- `i` - функция `Insert` (через пробел указывается ключ).
- `r` - функция `RemoveVEB` (через пробел указывается ключ).
- `s` - функция `SuccessorVEB` (через пробел указывается ключ, ожидается вывод числа).
- `p` - функция `PredecessorVEB` (через пробел указывается ключ, ожидается вывод числа).
- `u` - функция `MaximumVEB` (ожидается вывод числа).
- `d` - функция `MinimumVEB` (ожидается вывод числа).

### 7.3.2. Пример <a name="Пример.in"></a>
```
16
f 10
i 2
r 2
s 8
p 4
u
d
e
```
7\.4. Заполнение файлов .ans <a name=".ans"></a>
--------------
Поочередно на каждой строке заполняется ожидаемый вывод.

### 7.4.1. Пример <a name="Пример.ans"></a>
```
0
-1
-1
2
-1
```
7\.5. Вывод в файл .out <a name=".out"></a>
--------------
- На каждой строке выводится число, результат работы функции 
из файла `.in` с таким же названием.
- Через пробел от числа выводится или `OK`, если фактический вывод
совпадает с ожидаемым, или `Error`, если вывод не совпадает.
- Ещё через пробел выводится название функции и через знак `-` время её выполнения (если функция не предполагает вывод данных, то название функции и время выполнения выводится на новой строке).

### 7.5.1. Пример <a name="Пример.out"></a>
```
0 OK Find - 1200ns
Insert - 900ns
RemoveVEB - 800ns
-1 OK SuccessorVEB - 1000ns
-1 OK PredecessorVEB - 1000ns
-1 Error
-1 OK
```

7\.6. Генератор тестов <a name="Генератортестов"></a>
---------------
Создан для проверки производительности.
Создаёт указанное количество фалов в указанной папке.
```c++
Testing *test = new Testing(/*Путь к папке с файлами*/, /*Количество файлов*/);

test->StartGeneratingAndTestingVEB(/*Тестируемая операция*/, /*true или false*/); // Для vEB дерева 
test->StartGeneratingAndTestingSET(/*Тестируемая операция*/, /*true или false*/); // Для ordered set
test->StartGeneratingAndTestingUNSET(/*Тестируемая операция*/, /*true или false*/); // Для unordered set
```

Примечание: <br> 
- **Тестируемая операция** - параметр, принимающий сокращенные команды (смотрите п. [7.3.1.](#Сокращениекоманд))
- **true или false** - значение, которое обозначает генерировать выборку для тестов в случайном порядке или нет. 

---------------------
8\. Проверка производительности <a name="Производительность"></a>
===================
Для сравнения использовались контейнеры `std::set` и `std::unordered_set` стандартной библиотеки шаблонов `STL`
и аналогичные **vEB дереву** функции.

Каждая операция тестировалась 1 млн. раз, а после высчитывалось среднее время её работы.
- Операция `Find` тестировалась при полностью заполненном дереве.
- Операции `SuccessorVEB` и `PredecessorVEB` также тестировались при полностью заполненном дереве.
- Операция `Insert` тестировалась совместно с операцией `RemoveVEB`, где операция `Insert` полностью заполняла дерево,
а после операция `RemoveVEB` полностью очищала его.
- Все операции выполнялись с одним и тем же набором случайных значений. Набор случайных значений сгенерирован
с помощью алгоритма перестановки [Фишера-Йетса](https://github.com/RandomServant/Van-Emde-Boas-tree/tree/master/FisherYatesShuffle). [[7]](#9-список-литературы-)

Графики построены с помощью языка программирования `Python` и библиотеки `matplotlib`.

-----------------
| ![Рис. 3: График Find](https://github.com/RandomServant/Van-Emde-Boas-tree/blob/master/Images/Charts/Find_r.png) |
|:--:|
| *Рис. 3: График операции Find* |

-----------------
| ![Рис. 4: График Insert](https://github.com/RandomServant/Van-Emde-Boas-tree/blob/master/Images/Charts/Insert_r.png) |
|:--:|
| *Рис. 4: График операции Insert* |

-----------------
| ![Рис. 5: График SuccessorVEB](https://github.com/RandomServant/Van-Emde-Boas-tree/blob/master/Images/Charts/Successor.png) |
|:--:|
| *Рис. 5: График операции SuccessorVEB* |

-----------------
| ![Рис. 6: График PredecessorVEB](https://github.com/RandomServant/Van-Emde-Boas-tree/blob/master/Images/Charts/Predecessor.png) |
|:--:|
| *Рис. 6: График операции PredecessorVEB* |

-----------------
| ![Рис. 7: График RemoveVEB](https://github.com/RandomServant/Van-Emde-Boas-tree/blob/master/Images/Charts/Remove_r.png) |
|:--:|
| *Рис. 7: График операции RemoveVEB* |

-----------------
8.1. Итоги <a name="Итогипроверки"></a>
-----------------
По результатам проверки видно, что функции `Successor` и `Predecessor` **vEB дерева** 
проигрывают в производительности аналогичным функциям контейнера `std::set` из библиотеки `STL`.
Так же видно, что алгоритм **vEB дерева** обгоняет по скорости стандартные контейнеры, кроме 
случаев с большими числами. В них `std::unordered_set` обгоняет алгоритм дерева ван Эмде Боаса.

Структура показывает заявленную асимптотику, что делает ее очень эффективной в плане скорости, но главный её
минус, как и было оговорено в начале, большое потребление памяти.

------------------------
9\. Список литературы <a name="Списоклитературы"></a>
=================
1. https://neerc.ifmo.ru/wiki/index.php?title=Дерево_ван_Эмде_Боаса
2. https://habr.com/ru/post/125499/
3. https://en.wikipedia.org/wiki/Van_Emde_Boas_tree#References
4. https://www.geeksforgeeks.org/van-emde-boas-tree-set-1-basics-and-construction/
5. https://github.com/YAKOVLENKO/DZ
6. https://ru.frwiki.wiki/wiki/Arbre_de_Van_Emde_Boas#Structure
7. https://vscode.ru/prog-lessons/kak-peremeshat-massiv-ili-spisok.html

