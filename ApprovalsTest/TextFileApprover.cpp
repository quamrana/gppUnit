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
#include "TextFileApprover.h"

#include <fstream>
#include <vector>
#include <numeric>
#include <sstream>

namespace gppUnit {
	bool TextFileApprover::verify() {
		if(actualAndApprovedMatch()) {
			return true;
		}
		writeReceived();
		reportToUser();
		return actualAndApprovedMatch();
	}
	bool TextFileApprover::actualAndApprovedMatch() {
		approvedContents = getApprovedContents();
		if(actual == approvedContents) {
			removeReceived();
			return true;
		}
		return false;
	}

	std::string TextFileApprover::getApprovedContents() { return getFileContents(namer.getApprovedFilename()); }
	void TextFileApprover::writeReceived() {
		makeFileWithContents(namer.getReceivedFilename(), actual);
	}
	void TextFileApprover::removeReceived() { remove(namer.getReceivedFilename()); }

	void TextFileApprover::reportToUser() const {
		ensureApprovedFile();
		startDiff(namer.getReceivedFilename(), namer.getApprovedFilename());
	}
	void TextFileApprover::ensureApprovedFile() const {
		if(approvedContents.length() == 0) {   // When string is empty, we don't know whether the file actually exists or not.
			makeFileWithContents(namer.getApprovedFilename(), "");
		}
	}


	// Implementations:

	std::string getFileContentsWithoutDelimiters(const std::string& filename);
	std::string TextFileApprover::getFileContents(const std::string& filename) const {
		/*
		std::ifstream ifs(filename, std::ios::in | std::ios::binary | std::ios::ate);
		if(!ifs.good()) { return ""; }

		auto fileSize = static_cast<int>(ifs.tellg());
		ifs.seekg(0, std::ios::beg);

		std::vector<char> bytes(fileSize);
		ifs.read(bytes.data(), fileSize);

		return std::string(bytes.data(), fileSize);
		*/
		return getFileContentsWithoutDelimiters(filename);
	}
	void TextFileApprover::makeFileWithContents(const std::string& filename, const std::string& contents) const {
		std::ofstream file(filename);
		file << contents;
	}

	void TextFileApprover::remove(const std::string& filename)const { std::remove(filename.c_str()); }
	void TextFileApprover::startDiff(const std::string& lhsFilename, const std::string& rhsFilename) const {
		//"C:\Program Files\TortoiseHg\lib"
		//std::string mergeProgram = "C:\\Program Files\\TortoiseHg\\lib\\TortoiseMerge.exe";
		std::string mergeProgram = "D:\\Program Files\\Tortoise\\TortoiseMerge.exe";
		auto argv = { mergeProgram, lhsFilename, rhsFilename };
		launch(argv);
	}
	void TextFileApprover::launch(const std::vector<std::string>& argv) {
		//if (!exists(argv.front())) {
		//	return;
		//}

		std::string command = std::accumulate(argv.begin(), argv.end(), std::string(""), [](std::string total, std::string next_part) {return total + " " + "\"" + next_part + "\""; });
		std::string startCommand = "start \"\" /W" + command;
		system(startCommand.c_str());
	}

	std::string TextFileApprover::makeBoundedContents(const std::string& contents) {
		static std::string bounds = "\n--\n";
		std::stringstream out;
		out << bounds << contents << bounds;
		return out.str();
	}
	std::string getFileContentsWithoutDelimiters(const std::string& filename) {
		std::ifstream ifs(filename, std::ios::in | std::ios::ate);
		if(!ifs.good()) { return ""; }

		auto fileSize = static_cast<int>(ifs.tellg());
		ifs.seekg(0, std::ios::beg);

		std::string ret;
		ret.reserve(fileSize);

		std::string str;
		// Read the next line from File until it reaches the end.
		while(std::getline(ifs, str)) {
			ret += str + '\n';
		}
		return ret;
	}
}
