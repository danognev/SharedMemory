#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits>
#include <string.h>

using namespace std;

#define SM_SIZE 100
#define SM_NAME "MY_MEMORY"

enum eMenuVariants { Create = 1, Read ,Unlink, Exit };

void ShowMenu() noexcept;
void UserChoice();
void Process();
char* CreateSharedMemory(int&);
void WriteInSharedMemory(char*);
void ReadSharedMemory();

int main() {
	cout << "Программа написана Огневым Даниилом" << endl 
	<< "Задача программы: Создавать разделяемую память и производить запись/чтение из разных процессов" << endl;
	ShowMenu();
	UserChoice();
	return 0;
}

void Process() {
	int shm;
	char *address = nullptr;
	auto pid = fork();
	if(pid == -1) {
		perror("При порождении процесса произошла ошибка!");
		return;
	}
	else if(pid > 0) {
		wait(0);
		ReadSharedMemory();
	}
	else {
		address = CreateSharedMemory(shm);
		if(address == (char*)(-1))
			return;
		cout << "PID: " << getpid() << " | Memory Allocation: [" << (void*)address << " " << (void*)(address+ SM_SIZE) << "]" << endl;
		WriteInSharedMemory(address);
		munmap(address,SM_SIZE);
    	close(shm);
		exit(0);
	}
}
void ReadSharedMemory() {
	auto shm = shm_open(SM_NAME,O_RDONLY,0777);
	auto address = (char*)mmap(0,SM_SIZE+1,PROT_READ,MAP_SHARED,shm,0);
	if(shm == -1) {
		perror("Произошла ошибка при чтении разделенной памяти!");
		return;
	}
	cout << "PID: " << getpid() << " | Прочитано: " << address << " | [" << (void*)address << " " <<
	(void*)(address + strlen(address)) << "]" << endl;
	munmap(address,SM_SIZE+1);
	close(shm);
}
void WriteInSharedMemory(char *address) {
	char *text = new char[SM_SIZE+1];
	cout << "Введите текст, который хотите внести в память. Не более: " << SM_SIZE << " символов!" << endl;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.getline(text, SM_SIZE+1);
	memcpy(address, text, SM_SIZE+1);
	cout << "PID: " << getpid() << " | Записано: " << text << endl;
	delete[] text;
}
char* CreateSharedMemory(int &shm) {
	char* address;
	shm = shm_open(SM_NAME,O_CREAT|O_RDWR,0777);
	if(shm == -1) {
		perror("Произошла ошибка при создании разделенной памяти!");
		return (char*)(-1);
	}
	if(ftruncate(shm,SM_SIZE+1) == -1) {
		perror("При установлении размера произошла ошибка!");
		return (char*)(-1);
	}
	address = (char*)mmap(0,SM_SIZE+1,PROT_WRITE|PROT_READ,MAP_SHARED,shm,0);
	if(address == (char*)(-1)) {
		perror("Ошибка при разметке памяти!");
		return (char*)(-1);
	}
	else 
		return address;

}
void UserChoice() {
	int variant;
	cout << "Ввод: ";
	try {
		cin >> variant;
		switch(variant) {
			case Create: {
				Process();
				ShowMenu();
				UserChoice();
				break;
			}
			case Read: {
				ReadSharedMemory();
				ShowMenu();
				UserChoice();
				break;
			}
			case Unlink: {
				shm_unlink(SM_NAME);
				cout << "Успешно удалено!" << endl;
				ShowMenu();
				UserChoice();
				break;
			}
			case Exit: {
				break;
			}
			default: {
				throw exception();
			}
		}
	}
	catch(...) {
		cout << "Некорректный ввод! Попробуйте ещё раз" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		UserChoice();
	}
}


void ShowMenu() noexcept {
	cout << "\n\nЧто вы хотите сделать?" << endl 
	<< "1. Создать разделяемую память и процесс, затем внести данные" << endl
	<< "2. Прочитать содержимое разделенной памяти" << endl
	<< "3. Очистить созданную память" << endl 
	<< "4. Выйти из программы" << endl;
}