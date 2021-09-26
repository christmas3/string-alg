# Алгоритмы поиска подстроки в строке

- Алгоритм Бойера-Мура
- Алгоритм Кнута-Морриса-Пратта

# Зависимости сборки

* c++11
* cmake
* gtest

# Сборка cmake

``` shell
mkdir ../build
cd ../build
cmake ..
cmake --build .
```

## Запуск тестов

```shell 
./graph --gtest_filter=StringSuit.BmTest
```

# Docker

```shell
docker build -t testing .
docker run -it testing sh
/src/testing/build/testing
```
