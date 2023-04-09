#include "process.h"

void process::Process(char *text) {
	auto pid = fork();
	if(pid == -1) {
		perror("При порождении процесса произошла ошибка!");
		return;
	}
	else if(pid > 0) {
		wait(0);
		mw::ReadSharedMemory();
	}
	else {
		if(!mw::CreateSharedMemory())
			return;
		cout << "PID: " << getpid() << " | Memory Allocation: [" << static_cast<void*>(mw::getAddress()) << " " 
        << static_cast<void*>(mw::getAddress()+ mw::SM_SIZE) << "]" << endl;
		mw::WriteInSharedMemory(text);
		mw::CloseMemory();
		exit(0);
	}
}