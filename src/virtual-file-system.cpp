/**
 * Virtual File System
 *
 * Developed by André Marco Ruiz Sandoval, Alfredo Emmanuel Garcaa Falcon, Jorge Alejandro Chávez Nuñez
 * Final project for Operating System Course.
 * Professor Miguel Alcaraz Rivera
 *
 */

#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
//#include <windows.h>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <ctime>
//#include <string.h>
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
void printVolume();
string getVolumeString(int);
void getAllVolumeInfo();
void createFreeTable();
int checkAvailableSpace(int);
int checkAvailableDirectory();

//Global variables
string command_words[5];
char *volume;
string allVolumeName;
int blockSize;
int blockNumber;
int freeSpace;
bool createdVolume = false;
int volumeInfoBlockSize = 32;
int volumeInfoBlockSizeNum = 48;
int volumeInfoBlockNumber = 64;
int volumeInfoBlockNumberNum = 80;
int volumeInfoFreeSpace = 96;
int volumeInfoFreeSpaceNum = 112;

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
	cout << "If you have a doubt please type a command: 'manual' to help you. Press enter to continue." << endl;

	//time_t now = time(0);
	// convert now to string form
	//char* dt = ctime(&now);
	//cout << dt << endl;

	do
	{
		//Clear input stream
		cin.clear();
		cin.ignore(10000, '\n');

		//Get user option
		typeCommand();

		cout << endl;
		cout << "Do you want type another command? (y|n)" << endl;
		cin >> iterator_command;

		//Clear
		//system("cls");

	} while (iterator_command == 'y' || iterator_command == 'Y');
	if (createdVolume){
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
	cout << endl;
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
		cout << "Plase type a VALID COMMAND, if you have a doubt please type a command: 'manual' to help you" << endl;
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
		//cout << word << endl;
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
		cout << "Plase type a VALID PARAMETERS for this command, if you have a doubt please type a command: 'manual' to help you." << endl;
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

	if(volume_name.size() > 16){
		cout << "Volume name must be less than 16 characters." << endl;
		return;
	}

	blockSize = stoi(block_size);
	blockNumber = stoi(block_number);
	allVolumeName = volume_name;

	freeSpace = 127484;
	volume = (char*) malloc(blockSize * blockNumber);
	memset(volume, '|', blockSize * blockNumber);
	char validVolume[] = "Valid Virtual File System";
	memcpy(volume, validVolume, strlen(validVolume));

	cout << endl << "Volume created." << endl;
	cout << "Volume name: " << volume_name << endl;
	cout << "Block size: " << blockSize << endl;
	cout << "Block number: " << blockNumber << endl;
	cout << "Volume size: " << strlen(volume) << endl;

	char volumeName[16];
	char volumeNameChar[16];
	string volumeNameString = "Volume name: ";
	strcpy(volumeName, volume_name.c_str());
	strcpy(volumeNameChar, volumeNameString.c_str());
	memcpy(volume+blockSize, volumeNameChar , strlen(volumeNameChar));
	memcpy(volume+blockSize+16, volumeName , strlen(volumeName));

	char blockSizeConverted[16];
	string tempBlockSize = to_string(blockSize);
	strcpy(blockSizeConverted, tempBlockSize.c_str());
	char blockSizeChar[16];
	string blockSizeString = "Block size: ";
	strcpy(blockSizeChar, blockSizeString.c_str());
	memcpy(volume+blockSize+volumeInfoBlockSize, blockSizeChar , strlen(blockSizeChar));
	memcpy(volume+blockSize+volumeInfoBlockSizeNum, blockSizeConverted , strlen(blockSizeConverted));

	char blockNumberConverted[16];
	string tempBlockNumber = to_string(blockNumber);
	strcpy(blockNumberConverted, tempBlockNumber.c_str());
	char blockNumberChar[16];
	string blockNumberString = "Block number: ";
	strcpy(blockNumberChar, blockNumberString.c_str());
	memcpy(volume+blockSize+volumeInfoBlockNumber, blockNumberChar , strlen(blockNumberChar));
	memcpy(volume+blockSize+volumeInfoBlockNumberNum, blockNumberConverted , strlen(blockNumberConverted));

	char freeSpaceConverted[16];
	string tempFreeSpace = to_string(freeSpace);
	strcpy(freeSpaceConverted, tempFreeSpace.c_str());
	char freeSpaceChar[16];
	string freeSpaceString = "Free space: ";
	strcpy(freeSpaceChar, freeSpaceString.c_str());
	memcpy(volume+blockSize+volumeInfoFreeSpace, freeSpaceChar , strlen(freeSpaceChar));
	memcpy(volume+blockSize+volumeInfoFreeSpaceNum, freeSpaceConverted , strlen(freeSpaceConverted));

	createFreeTable();
	createdVolume = true;
	//printVolume();
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
	if(!createdVolume){
		cout << "Volume not created." << endl;
		return;
	}
	char *data;
	data = (char*) malloc(sizeof(volume));
	memcpy(data, volume, sizeof(volume));

	ofstream fout;
	fout.open(allVolumeName + ".loco");
	fout << volume;
	fout.close();
	free(volume);
	createdVolume = false;

	cout << "File saved, called "<< allVolumeName <<".loco" << endl;
}

/**
 * mountVolume function
 *
 * This function loads a previously saved file system into memory,
 *
 * @param block name
 */
void mountVolume(string file_name)
{
	if (file_name == "")
	{
		cout << "Plase type a VALID PARAMETERS for this command, if you have a doubt please type a command: 'manual' to help you." << endl;
		return;
	}

	if(createdVolume){
		cout << "Volume already mounted." << endl;
		return;
	}

	//cout << "mount" << endl;
	//cout << "File name: " << file_name << endl;

	std::ifstream is (file_name, std::ifstream::binary);
	if (is) {
		// get length of file:
		is.seekg (0, is.end);
		int length = is.tellg();
		is.seekg (0, is.beg);

		char * buffer = new char [length];

		std::cout << "Reading " << length << " characters... " << endl;
		// read data as a block:
		is.read (buffer,length);

		if (is){
			std::cout << "All characters read successfully." << endl;
			char validVolume[] = "Valid Virtual File System";
			char *checkVolume;
			checkVolume = (char*) malloc(sizeof(validVolume));
			for(int i = 0; i < strlen(validVolume); i++)
				checkVolume[i]=buffer[i];
			if(strcmp(checkVolume, validVolume) == 0){
				cout << "Valid volume. Proceeding to copy" << endl;
				volume = (char*) malloc(length);
				memcpy(volume, buffer, length);
				getAllVolumeInfo();
				allVolumeName = file_name;
				cout << "Volume name: " << allVolumeName << endl;
				cout << "Block size: " << blockSize << endl;
				cout << "Block number: " << blockNumber << endl;
				cout << "Free space: " << freeSpace << endl;
				createdVolume = true;
				//printVolume();
			} else{
				cout << "File system invalid." << endl;
				return;
			}
		} else {
			cout << "Error: only " << is.gcount() << " could be read";
		}
		is.close();

		// ...buffer contains the entire file...

		delete[] buffer;
	}
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

	if(!createdVolume){
		cout << "Volume not created." << endl;
		return;
	}

	//cout << "load" << endl;
	//cout << "File path: " << file_path << endl;
	//cout << "File name: " << file_name << endl;

	if(file_name.size() > 16){
		cout << "File name must be less than 16 characters." << endl;
		return;
	}

	//cin.clear();
	//cin.ignore(10000, '\n');
	//cout.flush();
	std::ifstream is(file_path, std::ifstream::binary);
	//char *temp;
	//temp = (char*) malloc(length);
	//std::ifstream is(file_path);     // open file
	//char c;
	//while (is.get(c))          // loop getting single characters
	//	std::cout << c;
	//is.close();
	//int length = is.tellg();
	//char *temp;
	//temp = (char*) malloc(10);
	//memset(temp, '|', 10);
	//cout << "Size of temp: " << length << endl;
	//char c;
	//int cntr = 0;
	//while(is.get(c)){
	//	cout << c;
	//	temp[cntr] = c;
	//	cntr++;
	//}
	//cout << temp << endl;
	//cout << "Reading " << length << " characters... " << endl;
	// read data as a block:
	//memcpy(volume+5, temp, strlen(temp)-1);
	//for(int i = 0; i < strlen(volume); i++)
	//	cout << volume[i];
	//is.close();
	if (is) {
		// get length of file:
		is.seekg (0, is.end);
		int length = is.tellg();
		is.seekg (0, is.beg);

		//char temp;
		//temp = (char*) malloc(length);
		//cout << "Size of temp: " << length << endl;
		//char c;
		//int cntr = 0;
		//while(is.get(c)){
		//	temp[cntr] = c;
		//	cntr++;
		//}
		//cout << temp << endl;
		char * buffer = new char [length];
		cout << "Reading " << length << " characters... " << endl;
		// read data as a block:
		//memcpy(volume, temp, strlen(temp));
		//for(int i = 0; i < strlen(volume); i++)
		//	cout << volume[i];
		is.read (buffer, length);

		if (is){
			cout << "All characters read successfully." << endl;
			/*char c;
			int cntr = 0;
			while(is.get(c)){
				temp[cntr] = c;
				cntr++;
			}
			cout << temp << endl;
			memcpy(volume, temp, strlen(temp));
			for(int i = 0; i < strlen(volume); i++)
				cout << volume[i];*/
			int startWriting = checkAvailableSpace(length);
			if(startWriting == -1)
				return;
			memcpy(volume+(blockSize*35)+(startWriting*blockSize), buffer, length);
			cout << "Start writing: " << startWriting << endl;
			int directoryIndex = checkAvailableDirectory();
			if(directoryIndex == -1)
				return;
			cout << "Directory index: " << directoryIndex << endl;
			char name[16];
			//string blockSizeString = "Block size: ";
			strcpy(name, file_name.c_str());
			cout << name << endl;
			memcpy(volume+directoryIndex, name, strlen(name));

			char id[6];
			//char blockSizeConverted[16];
			string tempId = to_string(directoryIndex);
			strcpy(id, tempId.c_str());
			cout << id << endl;
			memcpy(volume+directoryIndex+16, id, strlen(id));

			char size[6];
			//char blockSizeConverted[16];
			string tempLength = to_string(length);
			strcpy(size, tempLength.c_str());
			cout << size << endl;
			memcpy(volume+directoryIndex+22, size, strlen(size));

			time_t now = time(0);
			// convert now to string form
			char* date = ctime(&now);
			cout << date << endl;
			memcpy(volume+directoryIndex+28, date, strlen(date)-1);

			char start[6];
			//char blockSizeConverted[16];
			string tempStart = to_string(startWriting);
			strcpy(start, tempStart.c_str());
			cout << start << endl;
			memcpy(volume+directoryIndex+58, start, strlen(start));
		} else
			cout << "Error: only " << is.gcount() << " could be read" << endl;
		is.close();

		// ...buffer contains the entire file...

		delete[] buffer;
	} else{
		cout << "Cannot load file." << endl;
	}
	printVolume();
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
		cout << "Plase type a VALID PARAMETERS for this command, if you have a doubt please type a command: 'manual' to help you " << endl;
		return;
	}

	//cout << "download" << endl;
	//cout << "Virtual file name: " << virtual_file_name << endl;
	//cout << "Local file name: " << local_file_name << endl;
	int increment = 64;
	char file[16];
	memset(file, 0, 16);
	int cntr= 0;
	int startDel;
	bool finded = false;
	//cout << "Files in volume:" << endl;
	for(int i = blockSize*2; i < blockSize*3; i += increment){
		if(volume[i] != '|'){
			for(int j = i; j < strlen(volume); j++){
				if(volume[j] == '|'){
					break;
				} else{
					file[cntr] = volume[j];
					cntr++;
				}
			}
			cntr = 0;
			if(strcmp(file, virtual_file_name.c_str()) == 0){
				//strcpy(blockSizeChar, blockSizeString.c_str());
				cout << "File found." << endl;
				startDel = i;
				finded = true;
			}
			//cout << file << endl;
			memset(file, 0, 16);
		}
	}
	if(!finded){
		cout << "File not found." << endl;
	} else {
		//char* deleteFile;
		//deleteFile = (char*) malloc(64);
		//memset(deleteFile, '|', 64);
		//memcpy(volume+startDel, deleteFile, 64);
		//printVolume();

		cntr = 0;
		char* sizeFile;
		sizeFile = (char*) malloc(6);
		memset(sizeFile, 0, 6);
		for(int i = startDel+22; i < strlen(volume); i++){
			if(volume[i] == '|'){
				break;
			} else{
				sizeFile[cntr] = volume[i];
				cntr++;
			}
		}
		//cout << "File size: " << sizeFile << endl;
		int size = atoi(sizeFile);
		//cout << size << endl;

		cntr = 0;
		char* blockFile;
		blockFile = (char*) malloc(6);
		memset(blockFile, 0, 6);
		for(int i = startDel+58; i < strlen(volume); i++){
			if(volume[i] == '|'){
				break;
			} else{
				blockFile[cntr] = volume[i];
				cntr++;
			}
		}
		//cout << "FCB: " << blockFile << endl;
		int fcb = atoi(blockFile);
		//cout << fcb << endl;

		char* toDownload;
		toDownload = (char*) malloc(size);
		memcpy(toDownload, volume+(blockSize*35)+(fcb*blockSize), size);
		//memcpy(volume+(blockSize*));
		//cout << toDownload << endl;

		ofstream fout;
		fout.open(local_file_name);
		fout << toDownload;
		fout.close();
		//free(volume);
		//createdVolume = false;

		cout << "File saved, called "<< local_file_name << endl;
	}
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
		cout << "Plase type a VALID PARAMETERS for this command, if you have a doubt please type a command: 'manual' to help you." << endl;
		return;
	}

	//cout << "rm" << endl;
	//cout << "File name: " << file_name << endl;
	int increment = 64;
	char file[16];
	memset(file, 0, 16);
	int cntr= 0;
	int startDel;
	bool finded = false;
	cout << "Files in volume:" << endl;
	for(int i = blockSize*2; i < blockSize*3; i += increment){
		if(volume[i] != '|'){
			for(int j = i; j < strlen(volume); j++){
				if(volume[j] == '|'){
					break;
				} else{
					file[cntr] = volume[j];
					cntr++;
				}
			}
			cntr = 0;
			if(strcmp(file, file_name.c_str()) == 0){
				//strcpy(blockSizeChar, blockSizeString.c_str());
				cout << "File found and deleted." << endl;
				startDel = i;
				finded = true;
			}
			//cout << file << endl;
			memset(file, 0, 16);
		}
	}
	if(!finded){
		cout << "File not found." << endl;
	} else {
		char* deleteFile;
		deleteFile = (char*) malloc(64);
		memset(deleteFile, '|', 64);
		memcpy(volume+startDel, deleteFile, 64);
		printVolume();
	}
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
	//cout << "ls" << endl;
	int increment = 64;
	char file[16];
	memset(file, 0, 16);
	int cntr= 0;
	cout << "Files in volume:" << endl;
	for(int i = blockSize*2; i < blockSize*3; i += increment){
		if(volume[i] != '|'){
			for(int j = i; j < strlen(volume); j++){
				if(volume[j] == '|'){
					break;
				} else{
					file[cntr] = volume[j];
					cntr++;
				}
			}
			cntr = 0;
			cout << file << endl;
			memset(file, 0, 16);
		}
	}
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
	if(!createdVolume){
		cout << "Volume not created." << endl;
		return;
	}
	cout << "Volume info." << endl;
	cout << "Volume name: " << allVolumeName << endl;
	cout << "Block size: " << blockSize << endl;
	cout << "Block number: " << blockNumber << endl;
	cout << "Volume size: " << strlen(volume) << endl;
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
		cout << "Plase type a VALID PARAMETERS for this command, if you have a doubt please type a command: 'manual' to help you." << endl;
		return;
	}

	//cout << "details" << endl;
	//cout << "File name: " << file_name << endl;

	int increment = 64;
	char file[16];
	memset(file, 0, 16);
	int cntr= 0;
	int startDel;
	bool finded = false;
	//cout << "Files in volume:" << endl;
	for(int i = blockSize*2; i < blockSize*3; i += increment){
		if(volume[i] != '|'){
			for(int j = i; j < strlen(volume); j++){
				if(volume[j] == '|'){
					break;
				} else{
					file[cntr] = volume[j];
					cntr++;
				}
			}
			cntr = 0;
			if(strcmp(file, file_name.c_str()) == 0){
				//strcpy(blockSizeChar, blockSizeString.c_str());
				cout << "File found." << endl;
				startDel = i;
				finded = true;
			}
			//cout << file << endl;
			memset(file, 0, 16);
		}
	}
	if(!finded){
		cout << "File not found." << endl;
	} else {
		cntr = 0;
		char* nameFile;
		nameFile = (char*) malloc(16);
		memset(nameFile, 0, 16);
		for(int i = startDel; i < strlen(volume); i++){
			if(volume[i] == '|'){
				break;
			} else{
				nameFile[cntr] = volume[i];
				cntr++;
			}
		}
		cout << "File name: " << nameFile << endl;
		cntr = 0;

		char* idFile;
		idFile = (char*) malloc(6);
		memset(idFile, 0, 6);
		for(int i = startDel+16; i < strlen(volume); i++){
			if(volume[i] == '|'){
				break;
			} else{
				idFile[cntr] = volume[i];
				cntr++;
			}
		}
		cout << "ID: " << idFile << endl;
		cntr = 0;

		char* sizeFile;
		sizeFile = (char*) malloc(6);
		memset(sizeFile, 0, 6);
		for(int i = startDel+22; i < strlen(volume); i++){
			if(volume[i] == '|'){
				break;
			} else{
				sizeFile[cntr] = volume[i];
				cntr++;
			}
		}
		cout << "File size: " << sizeFile << endl;
		cntr = 0;

		char* dateFile;
		dateFile = (char*) malloc(30);
		memset(dateFile, 0, 30);
		for(int i = startDel+28; i < strlen(volume); i++){
			if(volume[i] == '|'){
				break;
			} else{
				dateFile[cntr] = volume[i];
				cntr++;
			}
		}
		cout << "File date: " << dateFile << endl;
		cntr = 0;

		char* blockFile;
		blockFile = (char*) malloc(6);
		memset(blockFile, 0, 6);
		for(int i = startDel+58; i < strlen(volume); i++){
			if(volume[i] == '|'){
				break;
			} else{
				blockFile[cntr] = volume[i];
				cntr++;
			}
		}
		cout << "FCB: " << blockFile << endl;
	}
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

/**
 * printVolume function
 *
 * This function checks if the parameter its a number.
 *
 */
void printVolume(){
	if(createdVolume){
		for (int i = 0; i < strlen(volume); i++)
        		cout << volume[i];
		cout << endl;
	}
}

/**
 * getVolumeString function
 *
 * This function return a string from volume given start position
 *
 * @param start position
 */
string getVolumeString(int start){
	char *info;
	string returnString;
	int cntr = 0;
	info = (char*) malloc(blockSize);
	for(int i = start + 16; i < strlen(volume); i++){
		if(volume[i] == '|'){
			break;
		} else{
			info[cntr] = volume[i];
			cntr++;
		}
	}
	returnString = info;
	return returnString;
}

/**
 * getAllVolumeInfo function
 *
 * This function gets volume info
 *
 * @param start position
 */
void getAllVolumeInfo(){
	char *getVolumeName;
	char *getBlockSize;
	char *getBlockNumber;
	char *getFreeSpace;
	int cntr = 0;
	getVolumeName = (char*) malloc(16);
	getBlockSize = (char*) malloc(16);
	getBlockNumber = (char*) malloc(16);
	getFreeSpace = (char*) malloc(16);
	for(int i = 4096 + 16; i < strlen(volume); i++){
		if(volume[i] == '|'){
			break;
		} else{
			getVolumeName[cntr] = volume[i];
			cntr++;
		}
	}
	cntr = 0;
	for(int i = 4096 + volumeInfoBlockSizeNum; i < strlen(volume); i++){
		if(volume[i] == '|'){
			break;
		} else{
			getBlockSize[cntr] = volume[i];
			cntr++;
		}
	}
	cntr = 0;
	for(int i = 4096 + volumeInfoBlockNumberNum; i < strlen(volume); i++){
		if(volume[i] == '|'){
			break;
		} else{
			getBlockNumber[cntr] = volume[i];
			cntr++;
		}
	}
	cntr = 0;
	for(int i = 4096 + volumeInfoFreeSpaceNum; i < strlen(volume); i++){
		if(volume[i] == '|'){
			break;
		} else{
			getFreeSpace[cntr] = volume[i];
			cntr++;
		}
	}
	cntr = 0;
	//allVolumeName = getVolumeName;
	blockSize = atoi(getBlockSize);
	blockNumber = atoi(getBlockNumber);
	freeSpace = atoi(getFreeSpace);
}


/**
 * createFreeTable function
 *
 * This function creates the table of available spaces.
 *
 * @param
 */
void createFreeTable(){
	char *freeTable;
	freeTable = (char*) malloc(blockSize*32);
	memset(freeTable, 'a', blockSize*32);
	int freeStart = blockSize*3;
	memcpy(volume+freeStart, freeTable, blockSize*32);
}

/**
 * checkAvailableSpace function
 *
 * This function checks for available space for file.
 *
 * @param size of file
 *
 */
int checkAvailableSpace(int fileSize){
	int neededSpaces = (fileSize / blockSize) + 1;
	cout << "Spaces needed for your file: " << neededSpaces << endl;
	bool isFree = false;
	int availableCntr = 0;
	int freeCntr = 0;
	int startWriting;
	while(!isFree){
		if(volume[(blockSize*3) + availableCntr] == 'a'){
			freeCntr++;
			if(freeCntr == neededSpaces){
				startWriting = availableCntr - neededSpaces + 1;
				isFree = true;
				char *getFreeSpace;
				getFreeSpace = (char*) malloc(16);
				int cntr = 0;
				for(int i = blockSize + volumeInfoFreeSpaceNum; i < strlen(volume); i++){
					if(volume[i] == '|'){
						break;
					} else{
						getFreeSpace[cntr] = volume[i];
						cntr++;
					}
				}
				//string fS = getVolumeString(volumeInfoFreeSpace);
				int tempSpace = atoi(getFreeSpace);
				cout << "Taken out free space" << endl;
				tempSpace = tempSpace - neededSpaces;
				char f[16];
				string fS = to_string(tempSpace);
				//string blockSizeString = "Block size: ";
				strcpy(f, fS.c_str());
				cout << "Free space: " << f << endl;
				memcpy(volume+blockSize+volumeInfoFreeSpaceNum, f, strlen(f));
				//printVolume();
			}
		}
		if(volume[(blockSize*3) + availableCntr] == 'o')
			freeCntr = 0;
		if(availableCntr == 131072){
			cout << "Not enough space for your file" << endl;
			return -1;
		}
		availableCntr++;
	}
	for(int i = blockSize*3+startWriting; i < blockSize*3+startWriting+neededSpaces; i++)
		volume[i] = 'o';
	//printVolume();
	return startWriting;
}

/**
 * checkAvailableDirectory function
 *
 * This function checks for available directory space for file.
 *
 * @param
 *
 */
int checkAvailableDirectory(){
	int increment = 64;
	for(int i = blockSize*2; i < blockSize*3; i += increment){
		if(volume[i] == '|')
			return i;
	}
	cout << "Not enough space in directory for your file." << endl;
	return -1;
}
