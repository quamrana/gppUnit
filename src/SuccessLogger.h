/*
Copyright (c) 2011 Andrew Wall

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef SUCCESSLOGGER_H_C727B3A4_81E2_472C_98A4_C3088B4A7023
#define SUCCESSLOGGER_H_C727B3A4_81E2_472C_98A4_C3088B4A7023

#include "Notification.h"

#include <fstream>

namespace gppUnit {
	class ProjectDescription;

	class FileLoggerInterface {
	protected:
		virtual ~FileLoggerInterface() {}
	public:
		virtual void LogToFile(const std::string& fileName, const ProjectDescription* project) = 0;
	};

	class FileLoggerNotification: public Notification {
		std::string fileName;
		FileLoggerInterface& fileLogger;
		const ProjectDescription* proj;
		void StartProject(const ProjectDescription& desc) { proj = &desc; }
	public:
		FileLoggerNotification(const std::string& fileName,
		                       FileLoggerInterface& fileLogger): fileName(fileName),
			fileLogger(fileLogger),
			proj(0)
		{}
		void EndProject() {
			fileLogger.LogToFile(fileName, proj);
		}
	};

	class SuccessLoggerAlgorithm: public FileLoggerInterface {
		virtual void LogToFile(const std::string& fileName, const ProjectDescription* project);

		virtual bool fileExists(const std::string& fileName) = 0;
		virtual void openFileForAppend(const std::string& fileName) = 0;
		virtual void openFileForWriting(const std::string& fileName) = 0;
		virtual void writeHeader(const std::string& fileName, const ProjectDescription* project) = 0;
		virtual void writeLog(const ProjectDescription* project) = 0;
		virtual void closeFile() = 0;
	};

	// TODO:  SuccessLogger is not tested!!
	class SuccessLogger: public SuccessLoggerAlgorithm {
		std::ofstream file;
		virtual bool fileExists(const std::string& fileName);
		virtual void openFileForAppend(const std::string& fileName);
		virtual void openFileForWriting(const std::string& fileName);
		virtual void writeHeader(const std::string& fileName, const ProjectDescription* project);
		virtual void writeLog(const ProjectDescription* project);
		virtual void closeFile();
	};

	const char* getNow(void);
}
#endif // SUCCESSLOGGER_H_C727B3A4_81E2_472C_98A4_C3088B4A7023
