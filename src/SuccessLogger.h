/*
Copyright (c) 2011-2019 Andrew Wall

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
		void StartProject(const ProjectDescription& desc) override { proj = &desc; }
		void EndProject() override { fileLogger.LogToFile(fileName, proj); }
	public:
		FileLoggerNotification(const std::string& fileName,
		                       FileLoggerInterface& fileLogger): fileName(fileName),
			fileLogger(fileLogger),
			proj(0)
		{}
	};

	const char* getNow(void);

	class LoggerAlgorithm: public FileLoggerInterface {
		virtual void LogToFile(const std::string& fileName, const ProjectDescription* project) override;

	protected:
		virtual bool allowedToProceed(const ProjectDescription* project) const = 0;
		virtual bool fileExists(const std::string& fileName) const = 0;
		virtual void openFileForAppend(const std::string& fileName) = 0;
		virtual void openFileForWriting(const std::string& fileName) = 0;
		virtual void writeHeader(const std::string& fileName, const ProjectDescription* project) = 0;
		virtual void writeLog(const ProjectDescription* project) = 0;
		virtual void closeFile() = 0;
		virtual std::ostream& getFile() = 0;
		virtual const char* getNow() { return gppUnit::getNow(); }
	};

	// TODO:  Classes below here are not tested!!
	class FileLogger: public virtual LoggerAlgorithm {
		bool fileExists(const std::string& fileName) const override;
		void openFileForAppend(const std::string& fileName) override;
		void openFileForWriting(const std::string& fileName) override;
		void closeFile() override;
		std::ostream& getFile() override { return file; }
		std::ofstream file;

		virtual void openFile(const std::string& fileName, std::ios_base::openmode mode);
	};

	class SuccessLoggerImplementation: public virtual LoggerAlgorithm {
		virtual bool allowedToProceed(const ProjectDescription* project) const override;
		virtual void writeHeader(const std::string& fileName, const ProjectDescription* project) override;
		virtual void writeLog(const ProjectDescription* project) override;
	};

	class AllRunsLoggerImplementation: public virtual LoggerAlgorithm {
		virtual bool allowedToProceed(const ProjectDescription* project) const override;
		virtual void writeHeader(const std::string& fileName, const ProjectDescription* project) override;
		virtual void writeLog(const ProjectDescription* project) override;
	};
	class SuccessLogger: public FileLogger, SuccessLoggerImplementation {};
	class AllRunsLogger: public FileLogger, AllRunsLoggerImplementation {};

}
#endif // SUCCESSLOGGER_H_C727B3A4_81E2_472C_98A4_C3088B4A7023
