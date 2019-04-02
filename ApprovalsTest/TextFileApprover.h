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
#pragma once
#include "ApprovalNamer.h"

#include <vector>

namespace gppUnit {
	class TextFileApprover {
	public:
		TextFileApprover(const std::string& data, ApprovalNamer& n): namer(n), actual(makeBoundedContents(data)) {}
		bool verify();
		virtual ~TextFileApprover() {}
		static std::string makeBoundedContents(const std::string&);

	private:
		bool actualAndApprovedMatch();

		std::string getApprovedContents();
		void writeReceived();
		void removeReceived();

		ApprovalNamer& namer;
		const std::string actual;		// received
		std::string approvedContents;

		virtual std::string getFileContents(const std::string& filename) const;
		virtual void makeFileWithContents(const std::string& filename, const std::string& contents) const;
		virtual void remove(const std::string& filename)const;
		void reportToUser() const;
		void ensureApprovedFile() const;
		virtual void startDiff(const std::string& lhsFilename, const std::string& rhsFilename) const;

		static void launch(const std::vector<std::string>& argv);
	};
}
