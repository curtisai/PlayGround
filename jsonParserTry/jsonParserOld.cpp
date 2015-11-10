#include <string>

class JsonEntity{
  public:
	~JsonEntity();
};

class JsonPair : public JsonEntity{
  private:
};

class JsonIdentifier : public JsonEntity{
  private:
  	std::string idStr;
  public:
  	JsonIdentifier(const std::string& newStr) : idStr(newStr){}

};

class JsonValue : public JsonEntity{};

class JsonArray : public JsonValue{
  private:
  	JsonEntity* arrayElements;
  public:
  	JsonArray(JsonEntity* newArray){
  		arrayElements = newArray;
  	}
};

class JsonInteger : public JsonValue{
  private:
  	int intVal;
  public:
  	JsonInteger(int newVal) : intVal(newVal){}

};

class JsonDouble : public JsonValue{
  private:
  	double doubleVal;
  public:
  	JsonDouble(double newVal) : doubleVal(newVal){}
};

class JsonParser{
  private:
	enum token{
		tok_eof = -1,
		tok_identifier = -2,
		tok_integer = -3,
		tok_double = -4,
		tok_error = -100
	};
	std::string& inputString;
	int strIndex;
	static std::string identifierStr;
	static int integerVal;
	static double doubleVal;

	char getNext(){
		strIndex++;
		return inputString[strIndex];
	}
	int getTok(){
		bool isInteger = true;
		int lastChar = ' ';
		while(isspace(lastChar)){
			lastChar = getChar();
		}//eat all white space

		if(isalpha(lastChar)){ //if(lastChar == '"'){  //is syntax checking should be done on 
		       //higher level
	           //	lastChar = getChar();
			identifierStr = lastChar;
			lastChar = getChar();
			while(isalnum(lastChar)){
				identifierStr += lastChar;
			}
			return tok_identifier;
			//else
			//	return tok_error; // " should come in pair
		}
		if(isdigit(lastChar) || lastChar == '.' || lastChar == '-'){
			std::string numberString;
			if(lastChar == '.')
				isInteger = false;
			numberString = lastChar;
			lastChar = getChar();
			while(isdigit(lastChar)|| lastChar == '.'){
				if(lastChar == '.' && isInteger == false)
				    return tok_error;  //multiple . co-existing
				if(lastChar == '.')
					isInteger = false;
				numberString += lastChar;
				lastChar = getChar();
			}
			if(isInteger == true){
				integerVal = std::stoi(numberString);
				return tok_integer;
			}
			else{
				doubleVal = std::stod(numberString);
				return tok_double;
			}
		}
		if(lastChar == EOF)
			return tok_eof;

		int thisChar = lastChar;
		lastChar = getChar();
		return thisChar;
	}
  public:
  	JsonParser(const std::string& theString):inputString(theString){
  		strIndex = 0;
  	}
};


