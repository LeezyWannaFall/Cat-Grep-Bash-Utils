# SimpleBash Utils

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Make](https://img.shields.io/badge/Make-003366?style=for-the-badge&logo=cmake&logoColor=white)
![Unit Tests](https://img.shields.io/badge/Unit_Tests-Passing-success?style=for-the-badge)

Реализация базовых консольных утилит UNIX: cat и grep.

## Описание

Проект содержит собственную реализацию двух классических UNIX-утилит:
- `cat` - утилита для чтения и конкатенации файлов
- `grep` - утилита для поиска шаблонов в тексте

## Утилита cat

### Использование

bash
./s21_cat [ОПЦИИ] [ФАЙЛ]...

### Поддерживаемые опции
- `-b` (number-nonblank) - нумерует только непустые строки
- `-e` (end-of-line) - отображает символы конца строки как $
- `-n` (number) - нумерует все выходные строки
- `-s` (squeeze-blank) - сжимает несколько смежных пустых строк
- `-t` (tabs) - отображает табуляции как ^I

## Утилита grep

### Использование

bash
./s21_grep [ОПЦИИ] ШАБЛОН [ФАЙЛ]...

### Поддерживаемые опции
- `-e ШАБЛОН` - использует ШАБЛОН для поиска
- `-i` - игнорирует различия регистра
- `-v` - выводит несовпадающие строки
- `-c` - выводит только количество совпадающих строк
- `-l` - выводит только имена файлов с совпадениями
- `-n` - выводит номер строки перед каждой строкой
- `-h` - выводит совпадающие строки без имени файла
- `-s` - подавляет сообщения об ошибках
## Сборка

Для сборки каждой утилиты используйте make в соответствующей директории:

```bash
cd cat && make
cd grep && make
```

## Примеры использования

### cat
```bash
./s21_cat -b file.txt
./s21_cat -n -s file1.txt file2.txt
```

### grep
```bash
./s21_grep pattern file.txt
./s21_grep -i -n "search text" *.txt
```

## Тестирование

Каждая утилита содержит набор тестов. Для запуска тестов используйте:
```bash
make test
```

