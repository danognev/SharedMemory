# Обучающее задание с SharedMemory и процессами
### В рамках обучения в it школе НТЦ Протей

Цель задания: создать разделенную память, записать в неё данные и попробовать прочесть из другого процесса.
Разработанная программа имеет следующий функционал: 
1. Консольный пользовательский интерфейс с выводом информационного сообщения и меню.
2. Возможность создать разделенную память и записать данные (строка).
3. Прочитать данные из разделенной памяти (в случае отсутствия разделенной памяти - сообщение с ошибкой).
4. Удалить разделенную память.

###### Описание функций программы
    void ShowMenu() noexcept;
Функция с выводом пунктов меню в консоль через cout

    void UserChoice();
Обработчик пунктов меню. Используется перечисление eMenuVariants для соответствующих пунктов.

    void Process();
Работа с процессами. Дочерний процесс создается при помощи системного вызова fork(). Дочерний процесс создает разделенную память функцией CreateSharedMemory и просит пользователя занести данные (строку) в размере не превышающем значение макроса SM_SIZE.

    char* CreateSharedMemory(int& shm);
Создает разделенную память. В качестве аргумента принимает ссылку на файловый дескриптор. В случае успешного создания возвращает адрес. В случае возникновения ошибок - выводится сообщение и функция возвращает -1.

    void WriteInSharedMemory(char*);
Функция, записывающая данные в разделенную память. Выводит сообщение и просит пользователя внести с клавиатуры данные (строку) размером не более SM_SIZE (без учета нуль-терминатора). В случае превышения размера при вводе строки - из буфера будет взята строка размером SM_SIZE+1 (с учетом нуль-терминатора).

    void ReadSharedMemory();
Производит чтение из разделенной памяти. В случае возникновения ошибки при чтении - вывод сообщения.