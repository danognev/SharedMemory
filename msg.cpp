#include "msg.h"
#include "memory_worker.h"

void msg::ShowHelp() {
    cout << "\nПомощь" << endl 
	<< "Задача программы: Создавать разделяемую память и производить запись/чтение из разных процессов\n\n"
    << "Использование: [аргумент 1] [значение (опционально)]\n" 
    << "Аргумент 1:\n\t[-c] - создать разделенную память и внести данные "
    << "(требуется значение: строка с данными не более " << memory_worker::SM_SIZE << " символов)"
    << "\n\t[-r] - прочитать содержимое разделенной памяти" 
    << "\n\t[-u] - очистить созданную память." << endl;
}
void msg::IncorrectOptions() {
    cout << "Некорректный ввод аргументов!" << endl;
    ShowHelp();
}