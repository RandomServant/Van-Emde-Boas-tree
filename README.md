# van Emde Boas tree
- ФИО - Борик Роман Дмитриевич
- Вуз - ДВФУ
- Направление - Б9121-09.03.03пикд
- Год - 2022
- Алгоритм - Дерево ван Эмде Боаса

--------------------------
Содержание <a name="Содержание"></a>
===============
- [Содержание](#Содержание)
- [Глоссарий](#Глоссарий)
- [Формальная постановка задачи](#Формальнаяпостановказадачи)
- [Вступление](#Вступление)
- [Использование](#Использование)
- [Поддерживаемые операции](#Поддерживаемыеоперации)
- [Структура](#Структура)
  - [Атрибуты узла дерева ван Эмбде Боаса](#Атрибуты)
  - [Вспомогательные функции](#Вспомогательныефункции)
- [Реализация](#Реализация)
  - [Структура](#СтруктураР)
    - [Атрибуты](#АтрибутыР)
    - [Вспомогательные функции](#ВспомогательныефункцииР)
    - [Конструктор](#Конструктор)
  - [Поддерживаемые операции](#ПоддерживаемыеоперацииР)
    - [minimumVEB и maximumVEB](#minmax)
    - [Find](#Find)
    - [Insert](#Insert)
    - [SuccessorVEB](#SuccessorVEB)
    - [PredecessorVEB](#PredecessorVEB)
    - [RemoveVEB](#RemoveVEB)
- [Тестирование](#Тестирование)
  - [Запуск](#Запуск)
  - [Требования](#Требования)
    - [Пример](#ПримерТ)
  - [Заполнение файлов .in](#.in)
    - [Сокращение команд](#Сокращениекоманд)
    - [Пример](#Пример.in)
  - [Заполнение файлов .ans](#.ans)
    - [Пример](#Пример.ans)
  - [Вывод в файл .out](#.out)
    - [Пример](#Пример.out)
- [Список литературы](#Списоклитературы)
      
----------------------------
Глоссарий <a name="Глоссарий"></a>
===============
- `vEB дерево` - Дерево ван Эмде Боаса
- `Ассоциативный массив` - абстрактный тип данных, позволяющий хранить пары вида «(ключ, значение)»
-----------------------------

Формальная постановка задачи <a name="Формальнаяпостановказадачи"></a>
===============
Исследовать и реализовать алгоритм "Дерево ван Эмбде Боасса" со всеми присущими
ему операциями: минимум, максимум, вставка, удаление, поиск следующего, поиск предыдущего, поиск элемента. 

---------------------
Вступление <a name="Вступление"></a>
===============
**Дерево ван Эмде Боаса (van Emde Boas tree)** — ассоциативный массив, 
который позволяет хранить целые числа в диапазоне `[0; U)`, где `U` положительное целое число вида `2^k`, 
здесь `U` является размером дерева Ван Эмде Боасса.
Дерево позволяет осуществлять над числами все соответствующие дереву поиска операции.

Главное достоинство этой структуры — выполнение всех операций за время `O(log(log(U)))`
независимо от количества хранящихся в ней элементов.

Недостатком этой структуры данных являеться, что для слишком больших `U`, дерево ван Эмде Боаса 
будет занимать большое количество памяти (грубая оценка — `O(U)`).

----------------------------------------
Использование <a name="Использование"></a>
===============
**Деревья ван Эмде Боаса** можно использовать, где угодно вместо обычного бинарного дерева поиска, 
если ключи в дереве поиска являются целыми числами в некотором фиксированном диапазоне. Таким образом, для приложений, 
где вам нужно найти целое число в наборе, наиболее близком к некоторому другому целому, 
использование **vEB-дерева** потенциально может быть быстрее, чем использование простого 
**сбалансированного двоичного дерева поиска**.

---------------------------------------
Поддерживаемые операции <a name="Поддерживаемыеоперации"></a>
===============
- `Insert(x)` — Вставка числа `x` в дерево.
- `RemoveVEB(x)` — Удаление числа `x`.
- `minimumVEB()`, `maximumVEB()` — Нахождение минимума и максимума в дереве.
- `Find(x)` — Поиск числа `x` в дереве.
- `SuccessorVEB(x)` — Поиск следующего числа после `x`, которое содержится в дереве.
- `PredecessorVEB(x)` — Поиск предшествующего `x` числа.
--------------------------------------------------------
Структура <a name="Структура"></a>
===============
Атрибуты узла дерева ван Эмбде Боаса <a name="Атрибуты"></a>
------------------
- `universeSize` - число элементов, хранящееся в дереве, корнем которого является текущий узел
- `minimum` - минимальное значение дерева, корнем которого является данный узел
- `maximum` - максимальное значение дерева, корнем которого является данный узел
- `summary` - вспомогательное дерево, хранящее информацию о детях текущего узла
- `cluster` - массив, хранящий указатели на детей узла

![Рис. 1: Дерево ван Эмбде Боаса размерностью 16, содержащее числа {2, 3, 4, 5, 7, 14, 15}](https://github.com/RandomServant/Van-Emde-Boas-tree/blob/master/Images/vEB_Struct.png)

Вспомогательные функции <a name="Вспомогательныефункции"></a>
-------------------
- `High(x)` — число, указывающее номер кластера ключа `х`
- `Low(x)` — число, указывающее позицию `х` в его кластере
- `GenerateIndex(x, y)` — число, соответствующее номеру элемента `х`
---------------------------------------
Реализация <a name="Реализация"></a>
===================
Исходный код можно найти здесь.

Структура <a name="СтруктураР"></a>
------------------
### Атрибуты <a name="АтрибутыР"></a>
```c++
int universeSize;
int minimum;
int maximum;
Van_Emde_Boas_Tree* summary;
vector<Van_Emde_Boas_Tree*> clusters;
```
### Конструктор <a name="Конструктор"></a>
```c++
Van_Emde_Boas_Tree(int size) {
        universeSize = size;
        minimum = -1;
        maximum = -1;

        if(size <= 2) {
            summary = nullptr;
            clusters = vector<Van_Emde_Boas_Tree*>(0);
        }
        else {
            int sizeOfNewClusters = ceil(sqrt(size));

            summary = new Van_Emde_Boas_Tree(sizeOfNewClusters);

            clusters = vector<Van_Emde_Boas_Tree*>(sizeOfNewClusters);

            for (int i = 0; i < sizeOfNewClusters; ++i) {
                clusters[i] = new Van_Emde_Boas_Tree(ceil(sqrt(size)));
            }
        }
    }
```
### Вспомогательные функции <a name="ВспомогательныефункцииР"></a>
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
Поддерживаемые операции <a name="ПоддерживаемыеоперацииР"></a>
------------------
### minimumVEB и maximumVEB <a name="minmax"></a>
Дерево Ван Эмде Боаса хранит минимум и максимум в качестве своих атрибутов, 
поэтому мы можем вернуть его значение, если оно присутствует, и `null` в противном случае.
```c++
int minimumVEB() {
    return minimum;
}

int maximumVEB() {
    return maximum;
}
```

### Find <a name="Find"></a>
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
### Insert <a name="Insert"></a>
1. Если в дереве нет ключей, то просто назначьте ключу минимум и максимум дерева.
2. В противном случае мы углубимся в дерево и сделаем следующее:
     - Если ключ, который мы хотим вставить, меньше текущего минимума дерева, то мы меняем местами оба значения, потому что новый ключ будет реальным минимумом дерева, а ключ, который уже был на месте минимума, будет использоваться для дальнейшего процесса.
Эту концепцию можно рассматривать как ленивое размножение в дереве Ван Эмде Боаса. Потому что это старое минимальное значение действительно является минимумом одного из кластеров рекурсивной структуры Ван Эмде Боаса. Так что на самом деле мы не углубляемся в структуру до тех пор, пока не возникнет такая необходимость.
     - Если мы не находимся в базовом случае, это означает, что размер вселенной дерева больше 2, тогда :
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
                if(clusters[High(key)]->minimumVEB() == -1) {
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
### SuccessorVEB <a name="SuccessorVEB"></a>
- **Базовый случай**: Если размер дерева равен 2, то если ключ запроса равен 0, а ключ - 1 присутствует в дереве, то верните 1, так как он будет преемником. В противном случае верните значение `null`.
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
            int maxElementInCluster = clusters[High(key)]->maximumVEB();
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
                    offset = clusters[successorCluster]->minimumVEB();
                    return GenerateIndex(successorCluster, offset);
                }
            }
        }
    }
```
### PredecessorVEB <a name="PredecessorVEB"></a>
- **Базовый случай:** Если размер дерева равен 2, то если ключ запроса равен 1, а ключ-0 присутствует в дереве, то верните 0, так как он будет предшественником. В противном случае верните значение `null`.
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
            int minInCluster = clusters[High(key)]->minimumVEB();
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
                    offset = clusters[pred_cluster]->maximumVEB();

                    return GenerateIndex(pred_cluster, offset);
                }
            }
        }
    }
```
### RemoveVEB <a name="RemoveVEB"></a>
Предполагается, что ключ уже присутствует в дереве.

- Сначала мы проверяем, присутствует ли только один ключ, затем присваиваем максимуму и минимуму дерева значение `null`, чтобы удалить ключ.
- **Базовый случай:** если размер юниверса дерева равен двум, то после того, как приведенное выше условие наличия только одного ключа равно false, в дереве присутствует ровно два ключа (после того, как приведенное выше условие окажется ложным), поэтому удалите ключ запроса, присвоив максимуму и минимуму дерева значение еще один ключ, присутствующий в дереве.
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
                int first_cluster = summary->minimumVEB();

                key = GenerateIndex(first_cluster, clusters[first_cluster]->minimumVEB());
                minimum = key;
            }

            clusters[High(key)]->RemoveVEB(Low(key));

            if (clusters[High(key)]->minimumVEB() == -1) {
                summary->RemoveVEB(High(key));

                if (key == maximum) {
                    int maxInSummary = summary->maximumVEB();

                    if (maxInSummary == -1) {
                        maximum = minimum;
                    }
                    else {
                        maximum = GenerateIndex(maxInSummary, clusters[maxInSummary]->maximumVEB());
                    }
                }
            }
            else if (key == maximum) {
                maximum = GenerateIndex(High(key), clusters[High(key)]->maximumVEB());
            }
        }
    }
```
------------------------
Тестирование <a name="Тестирование"></a>
=================
Исходный код можно найти здесь.

Запуск <a name="Запуск"></a>
--------------
```c++
Testing *test = new Testing(/*Путь к папке с файлами*/, /*Количество файлов*/);
test->StartTests();
```
Требования <a name="Требования"></a>
--------------
- Папка с файлами должна содержать файлы с расширениями `.in`, `.out`, `.ans`.
- Количество файлов должно быть одинаковым для разных расширений файлов.
- Файлы должны названы натуральными числами
### Пример <a name="ПримерТ"></a>
```
1.in
1.out
1.ans
2.in
2.out
2.ans
...
16.in
16.out
16.ans
```

Заполнение файлов .in <a name=".in"></a>
--------------
- На первой строке указывается размер vEB дерева.
- Далее на кажной строке указываются сокращенные версии команд и, если требуется, ключ.
- На последней строке файла ставится символ `e` для завершения считывания.

### Сокращение команд <a name="Сокращениекоманд"></a>
- `f` - функция Find (через пробел указывается ключ, ожидавется вывод 1 или 0).
- `i` - функция Insert. (через пробел указывается ключ)
- `r` - функция RemoveVEB. (через пробел указывается ключ)
- `s` - функция SuccessorVEB (через пробел указывается ключ, ожидавется вывод числа).
- `p` - функция PredecessorVEB (через пробел указывается ключ, ожидавется вывод числа).
- `u` - функция maximumVEB (ожидавется вывод числа).
- `d` - функция minimumVEB (ожидавется вывод числа).

### Пример <a name="Пример.in"></a>
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
Заполнение файлов .ans <a name=".ans"></a>
--------------
Поочередно на каждой строке заполняется ожидаемый вывод.

### Пример <a name="Пример.ans"></a>
```
0
-1
-1
2
-1
```
Вывод в файл .out <a name=".out"></a>
--------------
- На каждой строке выводится число, результат работы функции 
из файла `.in` с таким же названием.
- Через пробел от числа выводится или `Coincidence`, если фактический вывод
совпадает с ожидаемым, или `Error`, если вывод не совпадает.

### Пример <a name="Пример.out"></a>
```
0 Coincidence
-1 Coincidence
-1 Coincidence
-1 Error
-1 Coincidence
```

------------------------
Список литературы <a name="Списоклитературы"></a>
=================
1. https://neerc.ifmo.ru/wiki/index.php?title=Дерево_ван_Эмде_Боаса
2. https://habr.com/ru/post/125499/
3. https://en.wikipedia.org/wiki/Van_Emde_Boas_tree#References
4. https://www.geeksforgeeks.org/van-emde-boas-tree-set-1-basics-and-construction/
5. https://github.com/YAKOVLENKO/DZ
