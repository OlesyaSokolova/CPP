# Счетчик слов

Напишите программу, которая будет принимать в качестве аргумента имя текстового файла, и выводить CSV файл (http://ru.wikipedia.org/wiki/CSV) с колонками:
1. Слово.
2. Частота.
3. Частота (в %).
CSV файл должен быть упорядочен по убыванию частоты, то есть самые частые слова
должны идти в начале. Разделителями считать все символы кроме букв и цифр.


Аргументы командной строки программы:  
> word_count.exe input.txt output.csv  

Требования к программе:  

1. Для работы со строками используйте класс стандартной библиотеки std::string (см. http://www.cplusplus.com/reference/string/string/)   

2. Работа с файлами должна осуществляться с помощью классов стандартной библиотеки из модуля fstream (http://www.cplusplus.com/reference/fstream/)  

3. Строки из файла должны зачитываться с помошью метода std::getline (см. http://www.cplusplus.com/reference/string/string/getline/)  

4. Сохраняйте зачитанные строки в контейнере стандартной библиотеки std::list (http://www.cplusplus.com/reference/list/list/), std::map (http://www.cplusplus.com/reference/map/map/)  
