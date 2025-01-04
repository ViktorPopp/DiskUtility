# Disk Utility
This project is a simple disk performance testing application written in C++20. It measures the read and write speeds of a specified disk by writing and reading a test file of a user-defined size.

## Features
* Prompt user for disk letter, data size, caching option, and iteration count.
* Validate the specified disk.
* Perform disk write and read tests.
* Display average write and read speeds.

## Requirements
* Windows operating system
* C++20 compatible compiler
* Visual Studio IDE (recommended)

## Building the Project
1.	Open the project in Visual Studio.
2.	Build the project by selecting Build > Build Solution from the menu ot by pressing `Crtl+Shift+B`.

## Example Usage
```
Enter the disk letter (e.g., C): D
Enter the size of data to write (in MB): 1024
Enable caching? (y/n): n
Enter the number of iterations: 6

Warm-up run 1
Writing 1024 MB to disk...
Time taken for write: 0.469393 seconds
Write speed: 2181.54 MB/s
Reading 1024 MB from disk...
Time taken for read: 0.334193 seconds
Read speed: 3064.1 MB/s
Test file deleted.

...

Final Results:
Average Write Speed: 2170.76 MB/s
Average Read Speed: 3104.65 MB/s
```

## Architecture
* [main.cpp](DiskUtilityCLI/main.cpp): Entry point of the application.
* [Application.h](DiskUtilityCLI/Application.h): Header file for the Application class.
* [Application.cpp](DiskUtilityCLI/Application.cpp): Implementation of the Application class and all of the testing functions.

## License
This project is licensed under the MIT License. See the [LICENSE.txt](LICENSE.ttx) file for more details.

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request with your changes.

## Contact
For any issues, please open an issue on the GitHub repository. For questions please open an discussion.
