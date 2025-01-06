#pragma once

#include <string>
#include <vector>

namespace Disk
{
	namespace Benchmark
	{
		bool isDiskValid(const std::string & diskLetter);
		bool promptDiskLetter(std::string & diskLetter);
		bool promptDataSize(size_t & dataSizeMB);
		bool promptUseCaching(bool& useCaching);
		bool promptIterationCount(int& iterationCount);
		void performDiskTests(const std::string & diskLetter, size_t dataSizeMB, bool useCaching, int iterationCount);
		double testWriteSpeed(const std::string & filePath, std::vector<char>&buffer, size_t dataSizeMB, bool useCaching);
		double testReadSpeed(const std::string & filePath, std::vector<char>&buffer, size_t dataSizeMB, bool useCaching);
		void cleanUpTestFile(const std::string & filePath);
		void displayFinalResults(const std::vector<double>&writeSpeeds, const std::vector<double>&readSpeeds);
	}
}