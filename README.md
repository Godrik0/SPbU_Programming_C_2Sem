---
# Task 1
Даны два двумерных целочисленных динамических массива. Проверить, правда ли что они совпадают. Массивы считаются совпадающими если для пары (A1, A2) и для пары (A2, A1)  верно следующее: каждому столбцу (или строке, как трактовать, смотря) массива T1 соответствует ровно один столбец (строка) в массиве T2 содержащий те же элементы, пусть и в произвольном порядке. Примеры:  

A1 = {{1, 2}, {2,1}} A2 = {{2, 1}, {1, 2}} совпадают  
A1 = {{1, 2}, {2,1}} A2 = {{2}, {1, 2}} не совпадают  
A1 = {{1, 2, 3}, {2,1}} A2 = {{3, 2, 1}, {2, 1}, {2, 1}} не совпадают  


  ---

# Task 2  
Подвеской называется структура получаемая следующим образом. На вход подаются два числа (start, end). Далее запускается процедура генерации. При проходе по диапазону она подвешивает “внизу” список всех уникальных делителей данного числа. Далее, она повторяет данную процедуру для новой последовательности, но уже подвешивает “справа”. Единички игнорируются.
  Минимизация перекрытия: последнее число получает преимущество, то есть, в примере пятерка перезаписала бы двойку, если бы та занимала много места.


Пример: (1, 10):
```
1-2-3-4-5-6-7-8-9-10
      |   |   | | |
      2   2   2 3 2
          |   |   |
          3   4-2 5
```
