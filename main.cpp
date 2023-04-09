#include <iostream>
#include <unistd.h>
#include "msg.h"
#include "process.h"

using namespace std;
using mw = memory_worker;

int main(int argc, char **argv) {
	int result;
	if(argc == 1)
		msg::IncorrectOptions();
	else {
		while((result = getopt(argc,argv, "ruc:")) != -1) {
				switch(result) {
					case 'c': {
						process::Process(argv[argc-1]);
						break;
					}
					case 'r': {
						mw::ReadSharedMemory();
						break;
					}
					case 'u': {
						mw::SharedMemoryUnlink();
						break;
					}
					case '?': {
						msg::IncorrectOptions();
						break;
					}
				}
			}
	}
	return 0;
}