#include "memory_worker.h"

using mw = memory_worker;

const string mw::SM_NAME = "MY_MEMORY";
const int32_t mw::SM_SIZE = 100;
int mw::shm;
char *mw::address;

char* mw::getAddress() { return address; }
bool mw::CreateSharedMemory() {
	shm = shm_open(SM_NAME.c_str(),O_CREAT|O_RDWR,0777);
	if(shm == -1) {
		perror("Произошла ошибка при создании разделенной памяти!");
		return false;
	}
	if(ftruncate(shm,SM_SIZE+1) == -1) {
		perror("При установлении размера произошла ошибка!");
		return false;
	}
	address = static_cast<char*>(mmap(0,SM_SIZE+1,PROT_WRITE|PROT_READ,MAP_SHARED,shm,0));
	if(address == (char*)(-1)) {
		perror("Ошибка при разметке памяти!");
		return false;
	}
    else return true;
}
void mw::WriteInSharedMemory(char *text) {
	if(strlen(text) > SM_SIZE)
		perror("Введенная строка слишком длинная!");
	else {
		memcpy(address, text, SM_SIZE+1);
		address[SM_SIZE] = '\0';
		cout << "PID: " << getpid() << " | Записано: " << text << endl;
	}
}
void mw::ReadSharedMemory() {
	auto shm = shm_open(SM_NAME.c_str(),O_RDONLY,0777);
	auto address = (char*)mmap(0,SM_SIZE+1,PROT_READ,MAP_SHARED,shm,0);
	if(shm == -1) {
		perror("Произошла ошибка при чтении разделенной памяти!");
		return;
	}
	cout << "PID: " << getpid() << " | Прочитано: " << address << " | [" << (void*)address << " " <<
	(void*)(address + strlen(address)) << "]" << endl;
	CloseMemory();
}
void mw::CloseMemory() {
    munmap(address,SM_SIZE+1);
	close(shm);
}
void mw::SharedMemoryUnlink() {
    if(shm_unlink(SM_NAME.c_str()) == -1)
		perror("Возникла ошибка при удалении");
	else
		cout << "Успешно удалено!" << endl;
}