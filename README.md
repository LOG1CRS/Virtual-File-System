# Virtual-File-System
Virtual File System made with c++

## Getting Started
You can clone or download the project and run it with a C++ compiler.

### Commands for Virtual File System
 - Command: **create <name> <blockSize> <numberOfBlocks>**
 	 - Details: 'create' Loads the virtual file system into memory. If it doesn't exist create a new one. Block sizes can be 128, 256, 512, or 1024 bytes. The maximum size of the created volume is 1GB.
 - Command: **unmount**
 	 - Details: 'unmount' Saves virtual file system to specified file on hard drive.
 - Command: **mount <name>**
 	 - Details: 'mount' Loads a previously saved file system into memory.
 - Command: **load <*./original.txt> <copy.txt>**
 	 - Details: 'load' Loads a file to the virtual file system from the local hard drive.
 - Command: **download <copy.txt> <newCopy.txt>**
 	 - Details: 'download' Downloads a file from the virtual file system to the local hard drive.
 - Command: **rm <file.txt>**
 	 - Details: 'rm' deletes a file from the virtual file system.
 - Command:  **details <file.txt>**
 	 - Details: 'details' Shows the details of how a file is saved including the number of blocks it uses and the list of blocks where it is saved.
 - Command: **ls**
 	 - Details: 'ls' Lists the files.
 - Command: **info**
 	 - Details: 'info' Gives system information, including volume size, used space, and free space.
   
## Built With

* C++ 11
* Bash command line

## Contributing

Contributions are closed.

## Authors

* **Alfredo Emmanuel García Falcon** - *Student* - [AcesTerra](https://github.com/AcesTerra)
* **André Marco Ruiz Sandoval** - *Student* - [LOG1CRS](https://github.com/LOG1CRS)
* **Jorge Alejandro Chávez Nuñez** - *Student* - [ChavezJan](https://github.com/ChavezJan)

## License

This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/LOG1CRS/Virtual-File-System/blob/master/LICENSE) file for more details.

## What did we learned from this project?

* How file systems works.
* how malloc function works
