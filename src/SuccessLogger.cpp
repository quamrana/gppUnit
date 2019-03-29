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
#include "SuccessLogger.h"

#include "ProjectDescription.h"

namespace gppUnit {
	using std::endl;

	void LoggerAlgorithm::LogToFile(const std::string& fileName, const ProjectDescription* project) {
		if(allowedToProceed(project)) {
			if(fileExists(fileName)) {
				openFileForAppend(fileName);
			} else {
				openFileForWriting(fileName);
				writeHeader(fileName, project);
			}
			writeLog(project);
			closeFile();
		}
	}

	bool FileLogger::fileExists(const std::string& fileName) const {
		std::ifstream ifile;
		ifile.open(fileName.c_str(), std::ios::in);
		bool ret = ifile.is_open();
		ifile.close();
		return ret;
	}
	void FileLogger::openFileForAppend(const std::string& fileName) {
		openFile(fileName, std::ios::out | std::ios::app);
	}
	void FileLogger::openFileForWriting(const std::string& fileName) {
		openFile(fileName, std::ios::out);
	}
	void FileLogger::openFile(const std::string& fileName, std::ios_base::openmode mode) {
		file.open(fileName.c_str(), mode);
	}

	void FileLogger::closeFile() {
		file.close();
	}

	bool SuccessLoggerImplementation::allowedToProceed(const ProjectDescription* project) const {
		return project->hasPassed();
	}
	void SuccessLoggerImplementation::writeHeader(const std::string& fileName, const ProjectDescription* project) {
		getFile() << "'table=1.1" << endl
		          << "'" << fileName << " - Automatically created by gppUnit1.5" << endl
		          << "unittests,name=" << project->name() << endl
		          << "tests,units,date,time,runtime" << endl
		          ;
	}
	void SuccessLoggerImplementation::writeLog(const ProjectDescription* project) {
		getFile() << project->results() << ','
		          << project->classes() << ','
		          << getNow() << ','
		          << project->run_time()
		          << endl;
	}

	bool AllRunsLoggerImplementation::allowedToProceed(const ProjectDescription*) const {
		return true;
	}
	void AllRunsLoggerImplementation::writeHeader(const std::string& fileName, const ProjectDescription* project) {
		getFile() << "'table=1.1" << endl
		          << "'" << fileName << " - Automatically created by gppUnit1.5" << endl
		          << "unittests,name=" << project->name() << endl
		          << "passed,tests,units,date,time,runtime" << endl
		          ;
	}
	void AllRunsLoggerImplementation::writeLog(const ProjectDescription* project) {
		getFile() << project->hasPassed() << ','
		          << project->results() << ','
		          << project->classes() << ','
		          << getNow() << ','
		          << project->run_time()
		          << endl;
	}
}
