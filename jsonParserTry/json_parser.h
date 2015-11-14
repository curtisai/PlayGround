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
#include "stack_guard.h"
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
  	std::vector<sgdm::StackGuard<JsonEntity>> arrayElements;
  public:
  	JsonArray():arrayElements(){}
	void push_back(sgdm::StackGuard<JsonEntity> element){
		arrayElements.push_back(element);
	}
  	virtual ~JsonArray(){
  		/*
  		for(unsigned int i = 0; i < arrayElements.size(); i++){
  			if(arrayElements[i] != nullptr)
  				delete arrayElements[i];
  		}
  		*/
  	}
};

class JsonPair : public JsonValue{
  private:
  	sgdm::StackGuard<JsonEntity> lhs;
  	sgdm::StackGuard<JsonEntity> rhs;
  public:
  	JsonPair(sgdm::StackGuard<JsonEntity>&& LHS, sgdm::StackGuard<JsonEntity>&& RHS) : lhs(LHS) , rhs(RHS){}
  	virtual ~JsonPair(){
  		/*
  		if(lhs != nullptr)
  			delete lhs;
  		if(rhs != nullptr)
  			delete rhs;
  			*/
  	}
};


class JsonParser{
  private:
  	//StackGuard<JsonEntity> parseResult;

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
	sgdm::StackGuard<JsonEntity> Error(std::string errorMsg){
		std::cout<< errorMsg<<std::endl;
		return std::move(sgdm::StackGuard<JsonEntity>());
	}

	//Parsers begins
	sgdm::StackGuard<JsonEntity> ParseInteger(){
		//JsonInteger* res = new JsonInteger(inputIntger);
		sgdm::StackGuard<JsonEntity> res(new JsonInteger(inputIntger));
		getNextTok();
		return std::move(res);
	}

	sgdm::StackGuard<JsonEntity> ParseDouble(){
		sgdm::StackGuard<JsonEntity> res(new JsonDouble(inputDouble));
		getNextTok();
		return std::move(res);
	}

	sgdm::StackGuard<JsonEntity> ParseName(){
		sgdm::StackGuard<JsonEntity> res(new JsonName(idString));
		getNextTok();
		return std::move(res);
	}

	sgdm::StackGuard<JsonEntity> ParseObject(){
		sgdm::StackGuard<JsonEntity> resObject(new JsonObject());
		if(currentTok != '{'){
			//delete resObject;
			return Error("Expecting { at entity beginning");
		}
		else{
			getNextTok();//eat {
			while(currentTok != '}'){
				if(currentTok == ',')
					getNextTok();//eat ,
				resObject->push_back(ParsePair());
			}
			getNextTok(); //eat }
			return std::move(resObject);
		}
	}



	sgdm::StackGuard<JsonEntity> ParsePair(){
		//JsonName* pairName;
		//JsonValue* pairValue;
		sgdm::StackGuard<JsonEntity> pairName(new JsonName(idString));
		getNextTok();
		if(currentTok != ':'){
			//delete pairName;
			return Error("Expecting :");
		}
		else{
			getNextTok(); //eat :
			sgdm::StackGuard<JsonEntity> pairValue(ParsePrimary());
		}
		return std::move(new JsonPair(std::move(pairName),std::move(pairValue)));
	}

	sgdm::StackGuard<JsonEntity>  ParseArray(){
		sgdm::StackGuard<JsonEntity> array(new JsonArray());
		if(currentTok != '['){
			//delete array;
			return Error("Expecting new");
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
		return std::move(array);

	}

	sgdm::StackGuard<JsonEntity>  ParsePrimary(){
		//getNextTok();
		switch(currentTok){
		case tok_endl:
			return Error("primary fail");
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
  		//parseResult = NULL;
		lastChar = ' ';
  	}

  	~JsonParser(){
  		//if(parseResult != NULL)
  			//delete parseResult;
  	}

  	void Parse(){
		getNextTok();
		/*if (currentTok == '{')    *///error handling needed
			sgdm::StackGuard<JsonEntity> parseResult(ParsePrimary());
  	}

};







#endif