
#include <iostream>
#include <string>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <fstream>

using namespace std;

int main() {

	cout << "DO NOT RUN THIS PROGRAM AS ROOT!" << endl;
	for(;;){
		cout << endl;
		cout << "Cars or Birds" << endl;
		cout << "(0) Cars" << endl;
		cout << "(1) Birds " << endl;
		cout << "(2) exit " << endl;
		int choice = 0;
		char* filename = new char[256];
		cin >> choice;
		
		if (choice == 2)
			exit(0);
		char* no = new char[10];
		char* ea = new char[10];
		char* so = new char[10];
		char* we = new char[10];

		char* portions = new char[10];
		char* babies = new char[10];
		char* feedings = new char[10];

		switch (choice) {
			case 0:
				cout << endl << "enter cars at N roadway: ";
				cin >> no ; 
				cout << endl << "enter cars at E roadway: ";
				cin >> ea;
				cout << endl << "enter cars at S roadway: ";
				cin >> so;
				cout << endl << "enter cars at W roadway: ";
				cin >> we;
				break;
			case 1:
				cout << endl << "enter portions: ";
				cin >> portions ; 
				cout << endl << "enter babies: ";
				cin >> babies; 
				cout << endl << "enter feedings: ";
				cin >> feedings;
				break;
		}
		char* programName = new char[256];
		char* pathname = new char[256];
		switch (choice) {
			case 0:
				pathname = "cars/cars";
				programName = "cars";
				break;
			case 1:
				pathname = "birds/birds";
				programName = "birds";
				break;
			default:
				cout << "Please choose a proper option." << endl;
				break;	
		}
		/*string s1 = string( string(no)+" "+string(ea)+" "+string(so)+" "+string(we) );
		string s2 = string( string(portions)+" "+string(babies)+" "+string(feedings) );
		
		char *carArgs = new char[256];
		char *birdArgs = new char[256];
		
		int length1 = s1.copy(carArgs, s1.length(), 0);
		int length2 = s2.copy(birdArgs, s2.length(), 0);
		
		carArgs[length1] = '\0';
		birdArgs[length2] = '\0';*/
		char *birdArgs[4] = { portions, babies, feedings, (char*)0 };
		char *carArgs[5] = { no, ea, so, we, (char*)0 };
		
		char *cmd[] = { programName, (char*)0 };
		
		/*if (choice == 0){
			char *cmd[] = { programName, carArgs, (char*)0};
		}
		if (choice == 1){
			char *cmd[] = { programName, portions,babies,feedings, (char*)0};
		}*/
		int ret =0;
		pid_t child_pid = fork();
		int status, ch_stat;
		if( child_pid < 0) 
			cout << "error forking!" << endl;
		if( child_pid == 0){ //child
			cout << pathname << " " << *cmd << " "  << endl;
			if(choice == 0)
				execv("cars/cars", carArgs);
			if(choice == 1)
				execv("birds/birds", birdArgs);
			if( ret == -1 )
				cerr << "error execing.." << endl;
		}
		else { //parent
			while( (status=wait(&ch_stat)) != child_pid ) {
				if( status < 0 && errno == ECHILD) 
					break;
				errno = 0;
			}
		}
	
	}
	return 0;
}
