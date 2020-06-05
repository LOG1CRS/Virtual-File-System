#include <iostream>
#include <list>
#include <iterator>
//#include <windows.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
using namespace std;

//Functions declarations
void typeCommand();
int splitCommand(string);
int resolveUserOption(string);
void createVolume(string, string, string);
void unmountVolume();
void mountVolume(string);
void loadFile(string, string);
void downloadFile(string, string);
void rmFile(string);
void lsFiles();
void info();
void details(string);
bool isNumber(string);

//Global variables
string command_words[5];


/**
 * Main function
 *
 * in this function the code starts,
 * It is in charge of introducing the user and maintaining the loop,
 * so that the user can add all the commands he wants without finishing the program.
 */
int main(){

	char iterator_command;

	cout<<"Virtual File System Started"<<endl;
	//sleep(10);
	cout<<"If you have a doubt please type a command: 'manual' to help you. Press enter to continue." << endl;
	//sleep(10);

	do{
		//Clear input stream
		cin.clear();
		cin.ignore(10000,'\n');

		//Get user option
		typeCommand();

		//Ask if the user wants type another command
		//sleep(10);
		cout << endl;
		cout << "Do you want type another command? (y|n)"<<endl;
		cin >> iterator_command;

		//Clear
		//system("cls");

	} while(iterator_command == 'y' || iterator_command == 'Y');

	//Finish program
	cout<<"Virtual File System Finished"<<endl;
	return 0;
}

void typeCommand(){
	string command;
	cout << "Please type a command" << endl;
	getline(cin, command);
	int num_words = splitCommand(command);

	switch(resolveUserOption(command_words[0])){
		case 1:
			createVolume(command_words[1], command_words[2], command_words[3]);
			break;
		case 2:
			unmountVolume();
			break;
		case 3:
			mountVolume(command_words[1]);
			break;
		case 4:
			loadFile(command_words[1], command_words[2]);
			break;
		case 5:
			downloadFile(command_words[1], command_words[2]);
			break;
		case 6:
			rmFile(command_words[1]);
			break;
		case 7:
			lsFiles();
			break;
		case 8:
			info();
			break;
		case 9:
			details(command_words[1]);
			break;
		case 10:
			cout<<"The commands you can use: "<<endl;
			cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
			cout<<"Command: create *name* *blockSize* *numberOfBlocks*"<<endl;
			cout<<"Details: 'create' Loads the virtual file system into memory. If it doesn't exist" <<endl<< "create a new one. Block sizes can be 128, 256, 512, or 1024 bytes. The maximum size of the created volume is 1GB."<<endl;
			cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
			cout<<"Command: unmount"<<endl;
			cout<<"Details: 'unmount' Saves virtual file system to specified file on hard drive"<<endl;
			cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
			cout<<"Command: mount *name*"<<endl;
			cout<<"Details: 'mount' Loads a previously saved file system into memory."<<endl;
			cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
			cout<<"Command: load *./original.txt copy.txt "<<endl;
			cout<<"Details: 'load' Loads a file to the virtual file system from the local hard drive"<<endl;
			cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
			cout<<"Command: download copy.txt newCopy.txt"<<endl;
			cout<<"Details: 'download' Downloads a file from the virtual file system to the local hard drive"<<endl;
			cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
			cout<<"Command: rm archivo.txt "<<endl;
			cout<<"Details: 'rm' deletes a file from the virtual file system"<<endl;
			cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
			cout<<"Command: details *file.txt*"<<endl;
			cout<<"Details: 'details' Shows the details of how a file is saved, " <<endl<< "including the number of blocks it uses and the list of blocks where it is saved."<<endl;
			cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
			cout<<"Command: ls"<<endl;
			cout<<"Details: 'ls' Lists the files"<<endl;
			cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
			cout<<"Command: info"<<endl;
			cout<<"Details: 'info' Gives system information, including volume size, used space, and free space."<<endl;
			cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
			break;
		default:
			cout<<"Plase type a VALID COMMAND, if you have a doubt please type a command: 'manual' to help you"<<endl;
	}
}


int splitCommand(string command){
	istringstream spliter(command);
	int num_of_words = 0;
	do {
		string word;
        	spliter >> word;
		cout << word << endl;
    		command_words[num_of_words] = word;
		num_of_words++;
	} while (spliter);

    return num_of_words-1;
}

int resolveUserOption(string option){
	int optionValue;

	if(option == "create"){
		optionValue = 1;
	} else if(option == "unmount"){
		optionValue = 2;
	} else if(option == "mount"){
		optionValue = 3;
	} else if(option == "load"){
		optionValue = 4;
	} else if(option == "download"){
		optionValue = 5;
	} else if(option == "rm"){
		optionValue = 6;
	} else if(option == "ls"){
		optionValue = 7;
	} else if(option == "info"){
		optionValue = 8;
	} else if(option == "details"){
		optionValue = 9;
	} else if(option == "manual"){
		optionValue = 10;
	}

	return optionValue;
}

void createVolume(string volume_name, string block_size, string block_number){

	if(volume_name == "" || block_size == "" || block_number == ""){
		cout << "Plase type a VALID PARAMETERS for this command, if you have a doubt please type a command: 'manual' to help you." << endl;
		return;
	}

	bool validSize = isNumber(block_size);
	bool validBlock = isNumber(block_number);

	if(!validBlock){
		cout << "Invalid block. It must be a number." << endl;
		return;
	}

	if(!validSize){
		cout << "Invalid size. It must be a number." << endl;
		return;
	}

	int blockSize = stoi(block_size);
	int blockNumber = stoi(block_number);

	cout << "create" << endl;
	cout << "Block name: " << volume_name << endl;
	cout << "Block size: " << blockSize << endl;
	cout << "Block number: " << blockNumber << endl;
}

void unmountVolume(){
	cout << "unmount" << endl;
}

void mountVolume(string block_name){

	if(block_name == ""){
		cout << "Plase type a VALID PARAMETERS for this command, if you have a doubt please type a command: 'manual' to help you."<<endl;
		return;
	}

	cout<<"mount"<<endl;
	cout<<"Block name: "<<block_name<<endl;
}

void loadFile(string file_path, string file_name){

	if(file_name == "" || file_path == ""){
		cout << "Plase type a VALID PARAMETERS for this command, if you have a doubt please type a command: 'manual' to help you."<<endl;
		return;
	}

	cout<<"load"<<endl;
	cout<<"File path: "<<file_path<<endl;
	cout<<"File name: "<<file_name<<endl;
}

void downloadFile(string virtual_file_name, string local_file_name){

	if(virtual_file_name == "" || local_file_name == ""){
		cout<<"Plase type a VALID PARAMETERS for this command, if you have a doubt please type a command: 'manual' to help you "<<endl;
		return;
	}

	cout<<"download"<<endl;
	cout<<"Virtual file name: "<<virtual_file_name<<endl;
	cout<<"Local file name: "<<local_file_name<<endl;
}

void rmFile(string file_name){

	if(file_name == ""){
		cout<<"Plase type a VALID PARAMETERS for this command, if you have a doubt please type a command: 'manual' to help you."<<endl;
		return;
	}

	cout<<"rm"<<endl;
	cout<<"File name: "<<file_name<<endl;
}

void lsFiles(){
	cout<<"ls"<<endl;
}

void info(){
	cout<<"info"<<endl;
}

void details(string file_name){

	if(file_name == ""){
		cout<<"Plase type a VALID PARAMETERS for this command, if you have a doubt please type a command: 'manual' to help you."<<endl;
		return;
	}

	cout<<"details"<<endl;
	cout<<"File name: "<<file_name<<endl;
}

bool isNumber(string s) {
	//return !s.empty() && find_if(s.begin(), s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end();
	//return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}
