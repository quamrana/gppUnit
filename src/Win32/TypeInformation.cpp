#include "TypeInformation.h"

namespace gppUnit{
	void replaceAll(std::string& name, char oldChar, char newChar){
		std::string::size_type index=0;
		goto from;
		while(index!=std::string::npos){
			name.replace(index,1,1,newChar);
from:
			index=name.find(oldChar,index);
		}
	}
	void quotesToParentheses(std::string& name){
		replaceAll(name,'`','(');
		replaceAll(name,'\'',')');
	}
	std::string demangleTypeName(const std::string& name){
		std::string result=name;
		//name.replace(
		if (result.length()>6) {
			quotesToParentheses(result);
			return result.substr(6);
		}
		return result;
	}
}
