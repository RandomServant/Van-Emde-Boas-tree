# van Emde Boas tree
- ФИО - Борик Роман Дмитриевич
- Вуз - ДВФУ
- Направление - Б9121-09.03.03пикд
- Год - 2022
- Алгоритм - Дерево ван Эмде Боаса

Вступление
===============
**Дерево ван Эмде Боаса (van Emde Boas tree)** — ассоциативный массив, 
который позволяет хранить целые числа в диапазоне [0; U), где U = k^2,
и осуществлять над ними все соответствующие дереву поиска операции.

Главная особенность этой структуры — выполнение всех операций за время O(log(log(U))) 
независимо от количества хранящихся в ней элементов.

Минусом данной структуры данных будет являться что для слишком больших U дерево ван Эмде Боаса 
будет занимать большее количество памяти (грубая оценка — O(U)).

Использование
===============
**Деревья ван Эмде Боаса** можно использовать, где угодно вместо обычного бинарного дерева поиска, 
если ключи в дереве поиска являются целыми числами в некотором фиксированном диапазоне. Таким образом, для приложений, 
где вам нужно найти целое число в наборе, наиболее близком к некоторому другому целому, 
использование **vEB-дерева** потенциально может быть быстрее, чем использование простого 
**сбалансированного двоичного дерева поиска**.

Поддерживаемые операции
===============
- `Insert(x)` — Вставка числа `x` в дерево.
- `RemoveVEB(x)` — Удаление числа `x`.
- `minimumVEB()`, `maximumVEB()` — Нахождение минимума и максимума в дереве.
- `Find(x)` — Поиск числа `x` в дереве.
- `SuccessorVEB(x)` — Поиск следующего числа после `x`, которое содержится в дереве.
- `PredecessorVEB(x)` — Поиск предшествующего `x` числа.

Структура
===============
Атрибуты узла дерева ван Эмбде Боаса
------------------
- `universeSize` - число элементов, хранящееся в дереве, корнем которого является текущий узел
- `minimum` - минимальное значение дерева, корнем которого является данный узел
- `maximum` - максимальное значение дерева, корнем которого является данный узел
- `summary` - вспомогательное дерево, хранящее информацию о детях текущего узла
- `cluster` - массив, хранящий указатели на детей узла

Вспомогательные функции
-------------------
- `High(x)` — число, указывающее номер кластера `х`
- `Low(x)` — число, указывающее позицию `х` в его кластере
- `GenerateIndex(x, y)` — число, соответствующее номеру элемента `х`

Реализация
===================
Структура
------------------
### Атрибуты
```c++
int universeSize;
int minimum;
int maximum;
Van_Emde_Boas_Tree* summary;
vector<Van_Emde_Boas_Tree*> clusters;
```
### Конструктор
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
### Вспомогательные функции
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
Поддерживаемые операции
------------------
### minimumVEB и maximumVEB
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

### Find
- В любой точке нашего поиска, если ключ является минимальным или максимальным для дерева, что означает, что ключ присутствует, тогда верните `true`.
- Если мы достигнем базового варианта, но приведенное выше условие равно `false`, то ключ не должен присутствовать в дереве, поэтому верните `true`.
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
### Insert
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
### SuccessorVEB
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
### PredecessorVEB
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
### RemoveVEB
Предполагается, что ключ уже присутствует в дереве.

- Сначала мы проверяем, присутствует ли только один ключ, затем присваиваем максимуму и минимуму дерева значение `null`, чтобы удалить ключ.
- **Базовый случай:** если размер юниверса дерева равен двум, то после того, как приведенное выше условие наличия только одного ключа равно false, в дереве присутствует ровно два ключа (после того, как приведенное выше условие окажется ложным), поэтому удалите ключ запроса, присвоив максимуму и минимуму дерева значение еще один ключ, присутствующий в дереве.
- **Рекурсивный случай:***
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
Список литературы
=================
1. https://neerc.ifmo.ru/wiki/index.php?title=Дерево_ван_Эмде_Боаса
2. https://habr.com/ru/post/125499/
3. https://en.wikipedia.org/wiki/Van_Emde_Boas_tree#References
4. https://www.geeksforgeeks.org/van-emde-boas-tree-set-1-basics-and-construction/
5. https://github.com/YAKOVLENKO/DZ
