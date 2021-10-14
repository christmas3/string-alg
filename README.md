# Алгоритмы поиска подстроки в строке

- Алгоритм Бойера-Мура
- Алгоритм Кнута-Морриса-Пратта
- Алгоритм сжатия Rle
- Алгоритм сжатия RleAdvanced
- Программа для сжатия и распаковки файлов с помощью алгоритмов Rle и RleAdvanced

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

# Запуск тестов

```shell
cd ./test 
./archive_fileTest
```

# Запуск программы

```shell 
./archive_file [-1|-2] filename         - архивация filename в filename.arch. Параметры -1 - алгоритм Rle; -2 - алгоритм RleAdvanced
./archive_file [-1|-2] -d filename.arch - разархивация filename.arch в filename
```

# Docker

```shell
docker build -t testing .
docker run -it testing sh
/src/testing/build/testing
```
