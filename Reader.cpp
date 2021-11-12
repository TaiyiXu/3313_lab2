#include <iostream>
#include "SharedObject.h"
#include "Semaphore.h"


struct MyShared
{
	int sharedDelay;
	int sharedThreadId;
	int sharedReportId;
	bool sharedRunning;
};

int main(void)
{
	std::cout << "I am a reader" << std::endl;

	Semaphore readerSem("readerSemaphore");
	Shared<MyShared> shared("sharedMemory");//a space called sharedMemeory which is also named as sharedMemeory is storing Share object with type as <MyShared>

	while(true){
		if(shared->sharedRunning==true){
			readerSem.Wait();// only when Signal() is triggered, then readerSem then allow the share object to be accessed by the reader
			std::cout<<"ThreadID: "<<shared->sharedThreadId<<" ReportID: "<<shared->sharedReportId<<" Delay: "<<shared->sharedDelay<<std::endl;

		}else{
			break;
		}
	}
}
