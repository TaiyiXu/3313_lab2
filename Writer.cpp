#include <iostream>
#include "SharedObject.h"
#include "thread.h"
#include <string>


struct MyShared{
	int sharedDelay;// for tracking how many secs was passed 
	int sharedThreadID; // Each new thread will have an unique id to represent its identity. 
	int sharedReportID;// to count how many time this thread has repeated the message.
	bool sharedRunning;//bool condition to whether the thread is still running

};

class WriterThread : public Thread{//creating thread for the writer 
	public:
		int delay;
		int threadID;
		int reportID=1;
		bool flag;

		WriterThread(int in, int threadid):Thread(8*1000){//write thread method
			this->delay=in;
			this->threadID=threadid;
		}

		virtual long ThreadMain(void)override{
			
			Shared<MyShared>sharedMemory("sharedMemory");
			
			while(true)
			{	//when user type yes, new thread should  be created and replaced the conetent with newest user enters.
				sharedMemory->sharedThreadID=threadID;
				sharedMemory->sharedReportID=reportID;
				sharedMemory->sharedDelay=delay;
				reportID++;
				sleep(delay);

				if(flag){ // if the flag is false, the thread is ended and should be terminated.
					break;
				}
			}
		}
		
};


int main(void)
{
	std::string threadDelay;//for user to input new delay of reports
	std::string userInput;//for user to input new msg.
	int numThread=1;//the first thread should be generated at the begging, the number of thread should be accumulated whenever new threads are created 


	std::cout << "I am a Writer" << std::endl;


	WriterThread*thread;//creating a new object taht represents the writer class


	Shared<MyShared> shared("sharedMemory", true); //This is the owner of sharedMamory, when the condition= true, writer are allowed to change the property of shared object
	
	shared->sharedRunning=true;//Setting the sharedRunning state to be true, which means shared object can still be used by thread. 



	while(true){
		std::cout<<"do you want to create another writer thread? Enter yes or no: "<<std::endl;
		std::cin>>userInput;
		std::cin.clear();

		if (userInput=="y")
		{
			std::cout<<"Please enter a delay time for this thread"<< std::endl;
			std::cin>>threadDelay;
			std::cin.clear();
			int delay = atoi(threadDelay.c_str());//converting the string to int.

			thread = new WriterThread(delay,numThread);//creating a new thread with
			numThread++; //count the number of thread after creating a new thread
		}
		else if(userInput=="n")
		{
			if(numThread-1!=0){
				shared->sharedRunning=false;//check if there are thread spawn, if so, diable the ability for thread to access to shared object
				break;
			}
			else{
				break;
			}
		}
		else
		{
			std::cout<<"Invalid input entered:"<<std::endl;
		}
	}	
		
	if(numThread-1!=0){// if numthread is not equal to 0, it mean threads were spanwed and need to be terminated.
		thread->flag= true;
		delete thread;
	}

	return 0;
	
}




