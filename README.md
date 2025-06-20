# Live Ocean Simulation

**Live Ocean Simulation** — это консольная игра-симуляция экосистемы океана с водорослями, травоядными и хищниками. Вся визуализация реализована через библиотеку [PDCurses](https://pdcurses.org/).

## Скриншот

```
A — водоросли  
H — травоядные рыбы  
P — хищники  
~ — пустая вода/песок  
```

## Сборка

### Требования

- g++ (C++17)
- [CMake](https://cmake.org/) (опционально)
- Библиотека **PDCurses** (уже собрана и лежит в папке `lib/`)

### Сборка через CMake (рекомендуется)

```sh
git clone https://github.com/yourname/ocean.git
cd ocean
mkdir build
cd build
cmake ..
cmake --build .
```

### Сборка вручную через g++

```sh
g++ -std=c++17 -Iinclude -Llib \
    src/main.cpp src/entity.cpp src/ocean.cpp src/algae.cpp src/herbivore.cpp src/predator.cpp \
    -lpdcurses -o ocean.exe
```

> **Примечание:**  
> Путь к библиотеке `libpdcurses.a` — `lib/libpdcurses.a`.  
> Заголовочные файлы PDCurses уже подключены через `include/curses.h`.

## Запуск

```sh
./ocean.exe
```

Для выхода из симуляции нажмите `q`.

## Структура проекта

```
include/         — заголовочные файлы (включая curses.h)
lib/             — собранная статическая библиотека pdcurses (libpdcurses.a)
src/             — исходники симуляции
CMakeLists.txt   — файл сборки CMake
```

## Лицензия

MIT или ваша лицензия.

---

**Удачной симуляции!**
