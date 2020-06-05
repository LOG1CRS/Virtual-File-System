/**
 * Virtual File System
 *
 * Developed by André Marco Ruiz Sandoval, Alfredo Emmanuel García Falcon, Jorge Alejandro Chávez Nuñez
 * Final project for Operating System Course.
 * Professor Miguel Alcaraz Rivera
 *
 */

#include <iostream>
#include <list>
#include <iterator>
//#include <windows.h>
#include <string>
#include <cstring>
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
char *volume;

/**
 * Main function
 *
 * in this function the code starts,
 * It is in charge of introducing the user and maintaining the loop,
 * so that the user can add all the commands he wants without finishing the program.
 */
int main()
{

	char iterator_command;

	cout << "Virtual File System Started" << endl;
	//sleep(10);
	cout << "If you have a doubt please type a command: 'manual' to help you. Press enter to continue." << endl;
	//sleep(10);

	do
	{
		//Clear input stream
		cin.clear();
		cin.ignore(10000, '\n');

		//Get user option
		typeCommand();

		//Ask if the user wants type another command
		//sleep(10);
		cout << endl;
		cout << "Do you want type another command? (y|n)" << endl;
		cin >> iterator_command;

		//Clear
		//system("cls");

	} while (iterator_command == 'y' || iterator_command == 'Y');
	if (strlen(volume) > 0){
		free(volume);
		cout << "Memory released" << endl;
	}

	//Finish program
	cout << "Virtual File System Finished" << endl;
	return 0;
}

/**
 * typeCommand function
 *
 * This function gets the command and calls a command according to the command entered,
 * switch statement calls resolveUseroption to gets an integer to calls a specific function.
 */
void typeCommand()
{
	string command;
	cout << "Please type a command" << endl;
	getline(cin, command);
	int num_words = splitCommand(command);

	switch (resolveUserOption(command_words[0]))
	{
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
		cout << "The commands you can use: " << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Command: create *name* *blockSize* *numberOfBlocks*" << endl;
		cout << "Details: 'create' Loads the virtual file system into memory. If it doesn't exist" << endl
			 << "create a new one. Block sizes can be 128, 256, 512, or 1024 bytes. The maximum size of the created volume is 1GB." << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Command: unmount" << endl;
		cout << "Details: 'unmount' Saves virtual file system to specified file on hard drive" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Command: mount *name*" << endl;
		cout << "Details: 'mount' Loads a previously saved file system into memory." << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Command: load *./original.txt copy.txt " << endl;
		cout << "Details: 'load' Loads a file to the virtual file system from the local hard drive" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Command: download copy.txt newCopy.txt" << endl;
		cout << "Details: 'download' Downloads a file from the virtual file system to the local hard drive" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Command: rm archivo.txt " << endl;
		cout << "Details: 'rm' deletes a file from the virtual file system" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Command: details *file.txt*" << endl;
		cout << "Details: 'details' Shows the details of how a file is saved, " << endl
			 << "including the number of blocks it uses and the list of blocks where it is saved." << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Command: ls" << endl;
		cout << "Details: 'ls' Lists the files" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Command: info" << endl;
		cout << "Details: 'info' Gives system information, including volume size, used space, and free space." << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
		break;
	default:
		cout << "Please type a VALID COMMAND, if you have a doubt please type a command: 'manual' to help you" << endl;
	}
}

/**
 * splitCommand function
 *
 * This function divides the entered command into words,
 * istringstream divides the command according spaces.
 *
 * @param the command entered
 * @return the number of word divided
 */
int splitCommand(string command)
{
	istringstream spliter(command);
	int num_of_words = 0;
	do
	{
		string word;
		spliter >> word;
		cout << word << endl;
		command_words[num_of_words] = word;
		num_of_words++;
	} while (spliter);

	return num_of_words - 1;
}

/**
 * resolveUserOption function
 *
 * This function return the integer value of the entered command.
 *
 * @param the first word of the command
 * @return the integer value of the command
 */
int resolveUserOption(string option)
{
	int optionValue;

	if (option == "create")
	{
		optionValue = 1;
	}
	else if (option == "unmount")
	{
		optionValue = 2;
	}
	else if (option == "mount")
	{
		optionValue = 3;
	}
	else if (option == "load")
	{
		optionValue = 4;
	}
	else if (option == "download")
	{
		optionValue = 5;
	}
	else if (option == "rm")
	{
		optionValue = 6;
	}
	else if (option == "ls")
	{
		optionValue = 7;
	}
	else if (option == "info")
	{
		optionValue = 8;
	}
	else if (option == "details")
	{
		optionValue = 9;
	}
	else if (option == "manual")
	{
		optionValue = 10;
	}

	return optionValue;
}

/**
 * createVolume function
 *
 * This function loads the virtual file system into memory,
 *
 * @param block name
 * @param block size
 * @param block number
 */
void createVolume(string volume_name, string block_size, string block_number)
{

	if (volume_name == "" || block_size == "" || block_number == "")
	{
		cout << "Please type a VALID PARAMETERS for this command, if you have a doubt please type a command: 'manual' to help you." << endl;
		return;
	}

	bool validSize = isNumber(block_size);
	bool validBlock = isNumber(block_number);

	if (!validBlock)
	{
		cout << "Invalid block. It must be a number." << endl;
		return;
	}

	if (!validSize)
	{
		cout << "Invalid size. It must be a number." << endl;
		return;
	}

	int blockSize = stoi(block_size);
	int blockNumber = stoi(block_number);

	volume = (char*) malloc(blockSize * blockNumber);
	memset(volume, '|', blockSize * blockNumber);
	for (int i = 0; i < strlen(volume); i++)
        	cout << volume[i] << " ";

	cout << "create" << endl;
	cout << "Block name: " << volume_name << endl;
	cout << "Block size: " << blockSize << endl;
	cout << "Block number: " << blockNumber << endl;
	cout << "Volume size: " << strlen(volume);
}

/**
 * unmountVolume function
 *
 * This function saves virtual file system to specified file on hard drive,
 *
 *
 */
void unmountVolume()
{
	cout << "unmount" << endl;
}

/**
 * mountVolume function
 *
 * This function loads a previously saved file system into memory,
 *
 * @param block name
 */
void mountVolume(string block_name)
{

	if (block_name == "")
	{
		cout << "Please type a VALID PARAMETERS for this command, if you have a doubt please type a command: 'manual' to help you." << endl;
		return;
	}

	cout << "mount" << endl;
	cout << "Block name: " << block_name << endl;
}

/**
 * loadFile function
 *
 * This function loads a file to the virtual file system from the local hard drive,
 *
 * @param file path
 * @param file name
 */
void loadFile(string file_path, string file_name)
{

	if (file_name == "" || file_path == "")
	{
		cout << "Plase type a VALID PARAMETERS for this command, if you have a doubt please type a command: 'manual' to help you." << endl;
		return;
	}

	cout << "load" << endl;
	cout << "File path: " << file_path << endl;
	cout << "File name: " << file_name << endl;
}

/**
 * downloadFile function
 *
 * This function downloads a file from the virtual file system to the local hard drive,
 *
 * @param virtual file name
 * @param local file name
 */
void downloadFile(string virtual_file_name, string local_file_name)
{

	if (virtual_file_name == "" || local_file_name == "")
	{
		cout << "Please type a VALID PARAMETERS for this command, if you have a doubt please type a command: 'manual' to help you " << endl;
		return;
	}

	cout << "download" << endl;
	cout << "Virtual file name: " << virtual_file_name << endl;
	cout << "Local file name: " << local_file_name << endl;
}

/**
 * rmFile function
 *
 * This function deletes a file from virtual file system,
 *
 * @param file name
 */
void rmFile(string file_name)
{

	if (file_name == "")
	{
		cout << "Please type a VALID PARAMETERS for this command, if you have a doubt please type a command: 'manual' to help you." << endl;
		return;
	}

	cout << "rm" << endl;
	cout << "File name: " << file_name << endl;
}

/**
 * lsFile function
 *
 * This function lists the files,
 *
 *
 */
void lsFiles()
{
	cout << "ls" << endl;
}

/**
 * info function
 *
 * This function gives system information, including volume size, used space, and free space,
 *
 *
 */
void info()
{
	cout << "info" << endl;
}

/**
 * details function
 *
 * This function shows the details of how a file is saved, the number of blocks it uses and the list of blocks where it is saved,
 *
 * @param file name
 */
void details(string file_name)
{

	if (file_name == "")
	{
		cout << "Please type a VALID PARAMETERS for this command, if you have a doubt please type a command: 'manual' to help you." << endl;
		return;
	}

	cout << "details" << endl;
	cout << "File name: " << file_name << endl;
}

/**
 * isNumber function
 *
 * This function checks if the parameter its a number.
 *
 * @param command parameter 
 */
bool isNumber(string parameter)
{
	//return !s.empty() && find_if(s.begin(), s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end();
	//return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
	std::string::const_iterator it = parameter.begin();
	while (it != parameter.end() && std::isdigit(*it))
		++it;
	return !parameter.empty() && it == parameter.end();
}
