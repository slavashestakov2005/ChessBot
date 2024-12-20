# Шахматный бот
Курсовой проект за второй курс, шахматный бот для шахмат со сложной очередью.


## Сложная очередь, целевые правила
+ Начальная расстановка фигур практически любая.
+ Пешки не могут стоять на горизонталях 1 и 8, могут превращаться в королей.
+ Количество фигур не отграничено, может быть 5 чёрных слонов и 4 белых короля.
+ Шахов и патов нет.
+ Взятие на проходе есть, можно только следующим ходом.
+ Рокировка возможна, если К и Л на своих местах.
+ Цель: съесть $k$ королей соперника.


## Короткая документация
+ Список названий фигур расположен ниже. Белые фигуры строчными буквами, чёрные - заглавными.

| Русс.  | Англ.  | Короткое |
|--------|--------|----------|
| пешка  | pawn   | p        |
| ладья  | rook   | r        |
| конь   | knight | n        |
| слон   | bishop | b        |
| король | king   | k        |
| ферзь  | queen  | q        |

+ Координаты: пара $(x, y)$, в диапазоне $0 \leq x, y \leq 7$, где $x$ - вертикаль (abcdefgh), $y$ горизонталь (12345678).


## Полезные статьи
+ [Habr - несложные шахматы](https://habr.com/ru/companies/skillbox/articles/437524/);
+ [Habr - разработка шахматной программы](https://habr.com/ru/articles/329528/);
+ [Habr - шахматы на C++](https://habr.com/ru/articles/682122/);
