//json_parser.h
#ifndef JSON_PARSER_H_
#define JSON_PARSER_H_
//all token should be eaten before leaving the parse function
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
#include <memory>
#include <cstddef>
#include <iostream>
//under score is allowed in name

class JsonPair;

class JsonEntity{
public:
	virtual ~JsonEntity(){}
};

class JsonValue : public JsonEntity {
public:
	virtual ~JsonValue(){}
};

class JsonObject : public JsonValue{
	std::vector<JsonPair*> v;// or JsonPair
  public:
  	JsonObject() :v(){}
	virtual ~JsonObject(){}
	void push_back(JsonPair* newPair){
		v.push_back(newPair);
  	}


	JsonPair* operator[](int index){
		return v[index];
  	}

};


class JsonName : public JsonValue{
  private:
  	std::string nameValue;

  public:
  	JsonName(std::string& newName):nameValue(newName){}
  	virtual ~JsonName(){}
};

class JsonInteger : public JsonValue{
  private:
  	int integerValue;
  public:
  	JsonInteger(int newInteger):integerValue(newInteger){}
	virtual ~JsonInteger(){}
};

class JsonDouble : public JsonValue{
  private:
  	double doubleValue;
  public:
  	JsonDouble(double newDouble):doubleValue(newDouble){}
	virtual ~JsonDouble(){}
};

class JsonArray : public JsonValue{
  private:
  	std::vector<JsonValue*> arrayElements;
  public:
  	JsonArray():arrayElements(){}
	void push_back(JsonValue* element){
		arrayElements.push_back(element);
	}
  	virtual ~JsonArray(){
  		for(unsigned int i = 0; i < arrayElements.size(); i++){
  			if(arrayElements[i] != NULL)
  				delete arrayElements[i];
  		}
  	}
};

class JsonPair : public JsonValue{
  private:
  	JsonName* lhs;
  	JsonValue* rhs;
  public:
  	JsonPair(JsonName* LHS, JsonValue* RHS) : lhs(LHS) , rhs(RHS){}
  	virtual ~JsonPair(){
  		if(lhs != NULL)
  			delete lhs;
  		if(rhs != NULL)
  			delete rhs;
  	}
};


class JsonParser{
  private:
  	JsonEntity* parseResult;

  	//tokens
	enum elementToken{
		tok_endl = -1,
		tok_identifier = -2,
		tok_integer = -3,
		tok_double = -4,

		tok_error = -5
	};

	//element buffer
	char lastChar;
	std::string idString;
	int inputIntger;
	double inputDouble;

	std::string stringToParse;
	unsigned indexCount;

	char getChar(){
		if(indexCount < stringToParse.size()){
			indexCount++;
			return stringToParse[indexCount - 1];
		}
		else
			return EOF;
	}

	int getTok(){

		
 		while(isspace(lastChar)){
			lastChar = getChar();
		}


		//read entire string to the idString
		if(lastChar == '\''){
			lastChar = getChar();
			if(isalpha(lastChar)){
				idString = lastChar;
				while(isalnum(lastChar = getChar())||lastChar == '_'){
					idString += lastChar;
				}
				if(lastChar == '\''){
					lastChar = getChar();
					return tok_identifier;
				}
				else
					return tok_error;
			}
		}

		

		//read entire number and save it accordingly
		if(isdigit(lastChar) || lastChar == '.'){
			std::string numberString(1, lastChar);
			bool isInteger = true;
			if(lastChar == '.')
				isInteger = false;
			lastChar = getChar();
			while(isdigit(lastChar) || lastChar == '.'){
				if(lastChar == '.' && isInteger == false)
					return tok_error;
				if (lastChar == '.')
					isInteger = false;
				numberString += lastChar;
				lastChar = getChar();
			}
			if(isInteger){
				inputIntger = std::stoi(numberString);
				return tok_integer;
			}
			else{
				inputDouble = std::stod(numberString);
				return tok_double;
			}

	
		}

		if(lastChar == EOF)
			return tok_endl;

		int thisChar = lastChar;
		lastChar = getChar();
		return thisChar;

	}

	//token buffer

	int currentTok;

	int getNextTok(){
		return currentTok = getTok();
	}

	//helper function for error handling
	JsonEntity* Error(std::string errorMsg){
		std::cout<< errorMsg<<std::endl;
		return NULL;
	}

	//Parsers begins
	JsonInteger* ParseInteger(){
		JsonInteger* res = new JsonInteger(inputIntger);
		getNextTok();
		return res;
	}

	JsonDouble* ParseDouble(){
		JsonDouble* res = new JsonDouble(inputDouble);
		getNextTok();
		return res;
	}

	JsonName* ParseName(){
		JsonName* res = new JsonName(idString);
		getNextTok();
		return res;
	}

	JsonValue* ParseObject(){
		JsonObject* resObject = new JsonObject();
		if(currentTok != '{'){
			delete resObject;
			return (JsonValue*)Error("Expecting { at entity beginning");
		}
		else{
			getNextTok();//eat {
			while(currentTok != '}'){
				if(currentTok == ',')
					getNextTok();//eat ,
				resObject->push_back(ParsePair());
			}
			getNextTok(); //eat }
			return resObject;
		}
	}



	JsonPair* ParsePair(){
		JsonName* pairName;
		JsonValue* pairValue;
		pairName = new JsonName(idString);
		getNextTok();
		if(currentTok != ':'){
			delete pairName;
			return (JsonPair*)Error("Expecting :");
		}
		else{
			getNextTok(); //eat :
			pairValue = ParsePrimary();
		}
		return new JsonPair(pairName, pairValue);
	}

	JsonArray* ParseArray(){
		JsonArray* array = new JsonArray();
		if(currentTok != '['){
			delete array;
			return (JsonArray*)Error("Expecting new");
		}
		getNextTok();
		while(currentTok != ']'){
			if (currentTok == ','){
				getNextTok();
				continue;
			}
			else {
				array->push_back(ParsePrimary());
			}	
		}
		getNextTok(); //eat ]
		return array;

	}

	JsonValue* ParsePrimary(){
		//getNextTok();
		switch(currentTok){
		case tok_endl:
			return NULL;
		case tok_identifier:
			return ParseName();
		case tok_integer:
			return ParseInteger();
		case tok_double:
			return ParseDouble();
		//case '\'':
		//{
		//		getNextTok();
		//		return ParseName();
		//	}
		case '[':
			return ParseArray();
		case '{':
			return ParseObject();
		
		}
	}

  public:
  	JsonParser(const std::string& input):stringToParse(input),idString(){
  		indexCount = 0;
  		inputDouble = 0;
  		inputIntger =0;
  		parseResult = NULL;
		lastChar = ' ';
  	}

  	~JsonParser(){
  		if(parseResult != NULL)
  			delete parseResult;
  	}

  	void Parse(){
		getNextTok();
		/*if (currentTok == '{')    *///error handling needed
			parseResult =  ParsePrimary();
  	}

};







#endif