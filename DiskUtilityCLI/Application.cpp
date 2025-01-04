#include "Application.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <windows.h>
#include <numeric>
#include <memory>
#include <system_error>

void Application::run() {
    std::string diskLetter;
    size_t dataSizeMB;
    bool useCaching;
    int iterationCount;

    if (!promptDiskLetter(diskLetter)) {
        return;
    }

    if (!promptDataSize(dataSizeMB)) {
        return;
    }

    if (!promptUseCaching(useCaching)) {
        return;
    }

    if (!promptIterationCount(iterationCount)) {
        return;
    }

    performDiskTests(diskLetter, dataSizeMB, useCaching, iterationCount);
}

bool Application::isDiskValid(const std::string& diskLetter) {
    std::string path = diskLetter + ":\\";
    DWORD attributes = GetFileAttributesA(path.c_str());
    if (attributes == INVALID_FILE_ATTRIBUTES) {
        return false;
    }
    return (attributes & FILE_ATTRIBUTE_DIRECTORY);
}

bool Application::promptDiskLetter(std::string& diskLetter) {
    std::cout << "Enter the disk letter (e.g., C): ";
    std::cin >> diskLetter;

    if (!isDiskValid(diskLetter)) {
        std::cerr << "Error: The specified disk is not valid or accessible.\n";
        return false;
    }

    return true;
}

bool Application::promptDataSize(size_t& dataSizeMB) {
    std::cout << "Enter the size of data to write (in MB): ";
    std::cin >> dataSizeMB;

    if (dataSizeMB == 0) {
        std::cerr << "Error: Data size must be greater than 0.\n";
        return false;
    }

    if (dataSizeMB > 8192) {
        char choice;
        std::cerr << "Warning: Large data size may take a long time to write/read.\n" << "Do you want to continue? (y/n): ";
        std::cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            return false;
        }
    }

    return true;
}

bool Application::promptUseCaching(bool& useCaching) {
    char choice;
    std::cout << "Enable caching? (y/n): ";
    std::cin >> choice;

    useCaching = (choice == 'y' || choice == 'Y');
    return true;
}

bool Application::promptIterationCount(int& iterationCount) {
    std::cout << "Enter the number of iterations: ";
    std::cin >> iterationCount;

    if (iterationCount <= 0) {
        std::cerr << "Error: Iteration count must be greater than 0.\n";
        return false;
    }

    return true;
}

void Application::performDiskTests(const std::string& diskLetter, size_t dataSizeMB, bool useCaching, int iterationCount) {
    const size_t dataSizeBytes = dataSizeMB * 1024 * 1024;
    std::vector<char> buffer(1024 * 1024 * 4, '\0');
    std::string filePath = diskLetter + ":\\DiskUtilsTestFile.dat";

    std::vector<double> writeSpeeds, readSpeeds;

    // Warm-up runs
    for (int i = 0; i < 2; ++i) {
		std::cout << "\nWarm-up run " << i + 1 << "\n";
        testWriteSpeed(filePath, buffer, dataSizeMB, useCaching);
        testReadSpeed(filePath, buffer, dataSizeMB, useCaching);
        cleanUpTestFile(filePath);
    }

    for (int iteration = 1; iteration <= iterationCount; ++iteration) {
        std::cout << "\nIteration " << iteration << ":\n";

        double writeSpeed = testWriteSpeed(filePath, buffer, dataSizeMB, useCaching);
        if (writeSpeed > 0) writeSpeeds.push_back(writeSpeed);

        double readSpeed = testReadSpeed(filePath, buffer, dataSizeMB, useCaching);
        if (readSpeed > 0) readSpeeds.push_back(readSpeed);

        cleanUpTestFile(filePath);
    }

    displayFinalResults(writeSpeeds, readSpeeds);
}

double Application::testWriteSpeed(const std::string& filePath, std::vector<char>& buffer, size_t dataSizeMB, bool useCaching) {
    HANDLE hFile = CreateFileA(
        filePath.c_str(),
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        useCaching ? FILE_ATTRIBUTE_NORMAL : FILE_FLAG_NO_BUFFERING,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Unable to open file for writing. " << std::system_category().message(GetLastError()) << std::endl;
        return -1;
    }

    std::cout << "Writing " << dataSizeMB << " MB to disk..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    size_t bufferSize = buffer.size();
    for (size_t i = 0; i < dataSizeMB * 1024 / (bufferSize / 1024); ++i) {
        DWORD bytesWritten;
        if (!WriteFile(hFile, buffer.data(), bufferSize, &bytesWritten, NULL) || bytesWritten != bufferSize) {
            std::cerr << "Error: WriteFile failed. " << std::system_category().message(GetLastError()) << std::endl;
            CloseHandle(hFile);
            return -1;
        }
    }

    FlushFileBuffers(hFile); // Ensure data is written to disk
    auto end = std::chrono::high_resolution_clock::now();
    CloseHandle(hFile);

    std::chrono::duration<double> elapsed = end - start;
    double writeSpeed = dataSizeMB / elapsed.count();

    std::cout << "Time taken for write: " << elapsed.count() << " seconds\n";
    std::cout << "Write speed: " << writeSpeed << " MB/s\n";

    return writeSpeed;
}

double Application::testReadSpeed(const std::string& filePath, std::vector<char>& buffer, size_t dataSizeMB, bool useCaching) {
    HANDLE hFile = CreateFileA(
        filePath.c_str(),
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        useCaching ? FILE_ATTRIBUTE_NORMAL : FILE_FLAG_NO_BUFFERING,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Unable to open file for reading. " << std::system_category().message(GetLastError()) << std::endl;
        return -1;
    }

    std::cout << "Reading " << dataSizeMB << " MB from disk..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    size_t bufferSize = buffer.size();
    DWORD bytesRead;
    while (ReadFile(hFile, buffer.data(), bufferSize, &bytesRead, NULL) && bytesRead == bufferSize) {}

    auto end = std::chrono::high_resolution_clock::now();
    CloseHandle(hFile);

    std::chrono::duration<double> elapsed = end - start;
    double readSpeed = dataSizeMB / elapsed.count();

    std::cout << "Time taken for read: " << elapsed.count() << " seconds\n";
    std::cout << "Read speed: " << readSpeed << " MB/s\n";

    return readSpeed;
}

void Application::cleanUpTestFile(const std::string& filePath) {
    if (std::remove(filePath.c_str()) != 0) {
        std::cerr << "Warning: Unable to delete test file.\n";
    }
    else {
        std::cout << "Test file deleted.\n";
    }
}

void Application::displayFinalResults(const std::vector<double>& writeSpeeds, const std::vector<double>& readSpeeds) {
    double avgWriteSpeed = std::accumulate(writeSpeeds.begin(), writeSpeeds.end(), 0.0) / writeSpeeds.size();
    double avgReadSpeed = std::accumulate(readSpeeds.begin(), readSpeeds.end(), 0.0) / readSpeeds.size();

    std::cout << "\nFinal Results:\n";
    std::cout << "Average Write Speed: " << avgWriteSpeed << " MB/s\n";
    std::cout << "Average Read Speed: " << avgReadSpeed << " MB/s\n";
}
