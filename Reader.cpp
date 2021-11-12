#include <iostream>
#include "SharedObject.h"


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
	Shared<MyShared> shared("sharedMemory");//a space called sharedMemeory which is also named as sharedMemeory is storing Share object with type as <MyShared>

	while(true){
		if(shared->sharedRunning==true){
			std::cout<<"ThreadID: "<<shared->sharedThreadId<<" ReportID: "<<shared->sharedReportId<<" Delay: "<<shared->sharedDelay<<std::endl;
			sleep(2);
		}else{
			break;
		}
	}
}
