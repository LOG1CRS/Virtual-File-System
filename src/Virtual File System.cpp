#include <iostream> 
#include <list> 
#include <iterator> 
#include <windows.h>
#include <string>
#include <sstream>
using namespace std; 

void typeCommand();
int splitCommand(string);
int resolveUserOption(string);
void createFunction(string, string, string);
void unmountFunction();
void mountFunction(string);
void loadFunction(string, string);
void downloadFunction(string, string);
void rmFunction(string);
void lsFunction();
void infoFunction();
void detailsFunction(string);

string command_words[5];

int main(){
	
	char iterator_command;
	
	cout<<"Virtual File System Started"<<endl;
	Sleep(1000);
	cout<<"If you have a doubt please type a command: 'manual' to help you"<<endl;
	Sleep(1000);
	
	do{
		cin.clear();
		cin.sync();
		typeCommand();
		cout<<endl;
		Sleep(1000);
		cout<<"Do you want type another command? (y|n)"<<endl;
		cin>>iterator_command;
		
		system("cls");
		
	}while(iterator_command == 'y' || iterator_command == 'Y');
	
	cout<<"Virtual File System Finished"<<endl;
}

void typeCommand(){
	string command; 
	cout<<"Please type a command"<<endl;
	getline(cin, command);
	int num_words = splitCommand(command);
	
	
	switch(resolveUserOption(command_words[0])){
		case 1:
			createFunction(command_words[1], command_words[2], command_words[3]);
			break;
		case 2:
			unmountFunction();
			break;
		case 3:
			mountFunction(command_words[1]);
			break;
		case 4:
			loadFunction(command_words[1], command_words[2]);
			break;
		case 5:
			downloadFunction(command_words[1], command_words[2]);
			break;
		case 6:
			rmFunction(command_words[1]);
			break;
		case 7:
			lsFunction();
			break;
		case 8:
			infoFunction();
			break;
		case 9:
			detailsFunction(command_words[1]);
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
			cout<<"Plase type a valid command, if you have a doubt please type a command: 'manual' to help you"<<endl;
	}
}

int splitCommand(string command){
	istringstream spliter(command); 
	int num_of_words = 0;
	do { 
        string word; 
        spliter >> word; 
  
    	command_words[num_of_words] = word;
    	
  		num_of_words++;
    } while (spliter); 
    
    return num_of_words-1;
}

int resolveUserOption(string option){
	int optionValue;
	
	if(option == "create"){
		optionValue = 1;
	}else if(option == "unmount"){
		optionValue = 2;
	}else if(option == "mount"){
		optionValue = 3;
	}else if(option == "load"){
		optionValue = 4;
	}else if(option == "download"){
		optionValue = 5;
	}else if(option == "rm"){
		optionValue = 6;
	}else if(option == "ls"){
		optionValue = 7;
	}else if(option == "info"){
		optionValue = 8;
	}else if(option == "details"){
		optionValue = 9;
	}else if(option == "manual"){
		optionValue = 10;
	}
	
	return optionValue;
}

void createFunction(string block_name, string block_size, string block_number){
	
	if(block_name == "" || block_size == "" || block_number == ""){
		cout<<"Plase type a valid parameters for this command, if you have a doubt please type a command: 'manual' to help you"<<endl;
		return;
	}
	
	cout<<"create"<<endl;
	cout<<"Block name: "<<block_name<<endl;
	cout<<"Block size: "<<block_size<<endl;
	cout<<"Block divided into: "<<block_number<<endl;
}

void unmountFunction(){
	cout<<"unmount"<<endl;
}

void mountFunction(string block_name){
	
	if(block_name == ""){
		cout<<"Plase type a valid parameters for this command, if you have a doubt please type a command: 'manual' to help you"<<endl;
		return;
	}
	
	cout<<"mount"<<endl;
	cout<<"Block name: "<<block_name<<endl;
}

void loadFunction(string file_path, string file_name){
	
	if(file_name == "" || file_path == ""){
		cout<<"Plase type a valid parameters for this command, if you have a doubt please type a command: 'manual' to help you"<<endl;
		return;
	}
	
	cout<<"load"<<endl;
	cout<<"File path: "<<file_path<<endl;
	cout<<"File name: "<<file_name<<endl;
}

void downloadFunction(string virtual_file_name, string local_file_name){
	
	if(virtual_file_name == "" || local_file_name == ""){
		cout<<"Plase type a valid parameters for this command, if you have a doubt please type a command: 'manual' to help you"<<endl;
		return;
	}
	
	cout<<"download"<<endl;
	cout<<"Virtual file name: "<<virtual_file_name<<endl;
	cout<<"Local file name: "<<local_file_name<<endl;
}

void rmFunction(string file_name){
	
	if(file_name == ""){
		cout<<"Plase type a valid parameters for this command, if you have a doubt please type a command: 'manual' to help you"<<endl;
		return;
	}
	
	cout<<"rm"<<endl;
	cout<<"File name: "<<file_name<<endl;
}

void lsFunction(){
	cout<<"ls"<<endl;
}

void infoFunction(){
	cout<<"info"<<endl;
}

void detailsFunction(string file_name){
	
	if(file_name == ""){
		cout<<"Plase type a valid parameters for this command, if you have a doubt please type a command: 'manual' to help you"<<endl;
		return;
	}
	
	cout<<"details"<<endl;
	cout<<"File name: "<<file_name<<endl;
}








