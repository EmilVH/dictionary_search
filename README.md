# dictionary_search
 ***Что это?***
 Небольшое приложение, позволяющее искать слова по подстроке в англиском словаре с очень высокой эффективностью\
 ***Идея реализации***\
 Слова в англиском языке чаще всего не очень длинные, а значит у них не очень много различных суффиксов, а поскольку словарь не менятся можно провести
 значительный предподсчёт заранее, а при запуске выводить ответ быстро.\
 ***Решение***
 1. Запишем строки такого вида: суффикс слова + разделитель + оставшийся префикс
 2. Затем отсортируем их и запишем в файл
 3. Тогда при получении запроса на поиск, мы можем двоичным поиском найти индексы границ между которым префиксы слов (уже заранее преобразованных) соответствуют запросу
 4. Тогда все слова из этого промежутка подходят, остаётся лишь сделать обратное преобразование к преобразованию в п.1 и вывести количество слов
 ***Плюсы и минусы***
 + \+ Двоичный поиск занимает не более 60 прыжков по файлу, слова выводятся за размер результата
 + \+ Словарь не хранится в оперативной памяти
 - \- Словарь после предподсчета занимает в несколько раз больше места, чем стандартный словарь
 
