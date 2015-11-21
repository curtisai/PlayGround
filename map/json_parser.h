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
#include "map.h"
//under score is allowed in name



class JsonEntity{
public:
	virtual ~JsonEntity(){}
	
};

class JsonValue : public JsonEntity {
public:
    virtual void push_back(sgdm::StackGuard<JsonValue> element){}
	virtual ~JsonValue(){}
    virtual std::string asString(){return "";}
    virtual int asInt(){return 0;}
    virtual double asDouble(){return 0;}
    virtual JsonValue& getValue(){return *this;}
    virtual std::string getKey(){return "";}
};

class JsonPair : public JsonValue{
  private:
  	sgdm::StackGuard<JsonValue> lhs;
 	sgdm::StackGuard<JsonValue> rhs;
  public:
    JsonPair(sgdm::StackGuard<JsonValue>&& LHS, sgdm::StackGuard<JsonValue>&& RHS): lhs(std::move(LHS)) , rhs(std::move(RHS)){}
  	virtual ~JsonPair(){}
    
    std::string getKey(){
        return lhs->asString();
    }
    JsonValue& getValue(){
        return *rhs;
    }
    
    virtual void push_back(sgdm::StackGuard<JsonValue> element){}
    virtual std::string asString(){return "";}
    virtual int asInt(){return 0;}
    virtual double asDouble(){return 0;}
    
};





class JsonObject : public JsonValue{
	//std::vector<sgdm::StackGuard<JsonEntity>> v;// or JsonPair
  private:
    sgdc::Map<JsonValue, sgdm::StackGuard> v;
    //sgdm::IAllocator<sgdm::StackGuard<JsonEntity>>* alloc;

  public:
    JsonObject(sgdm::IAllocator<sgdm::StackGuard<JsonValue>>* alloc):v(alloc){}
	virtual ~JsonObject(){}
	virtual void push_back(sgdm::StackGuard<JsonValue> newPair){
		v.push(std::move(newPair));
  	}
    JsonValue& operator[](const std::string& key){
        return v[key];
  	}
    

    virtual std::string asString(){return "";}
    virtual int asInt(){return 0;}
    virtual double asDouble(){return 0;}
    virtual JsonValue& getValue(){return *this;}

};


class JsonName : public JsonValue{
  private:
  	std::string nameValue;

  public:
  	JsonName(std::string& newName):nameValue(newName){}
  	virtual ~JsonName(){}
    std::string asString(){
        return nameValue;
    }
    virtual void push_back(sgdm::StackGuard<JsonValue> element){}
    virtual int asInt(){return 0;}
    virtual double asDouble(){return 0;}
    virtual JsonValue& getValue(){return *this;}
};

class JsonInteger : public JsonValue{
  private:
  	int integerValue;
  public:
  	JsonInteger(int newInteger):integerValue(newInteger){}
	virtual ~JsonInteger(){}
    virtual void push_back(sgdm::StackGuard<JsonValue> element){}
    virtual std::string asString(){return "";}
    virtual int asInt(){return integerValue;}
    virtual double asDouble(){return 0;}
    virtual JsonValue& getValue(){return *this;}
};

class JsonDouble : public JsonValue{
  private:
  	double doubleValue;
  public:
  	JsonDouble(double newDouble):doubleValue(newDouble){}
	virtual ~JsonDouble(){}
    virtual void push_back(sgdm::StackGuard<JsonValue> element){}
    virtual std::string asString(){return "";}
    virtual int asInt(){return 0;}
    virtual double asDouble(){return doubleValue;}
    virtual JsonValue& getValue(){return *this;}
};

class JsonArray : public JsonValue{
  private:
  	std::vector<sgdm::StackGuard<JsonValue>> arrayElements;
  public:
  	JsonArray():arrayElements(){}
	void push_back(sgdm::StackGuard<JsonValue> element){
		arrayElements.push_back(std::move(element));
	}
  	virtual ~JsonArray(){
  	}
    virtual std::string asString(){return "";}
    virtual int asInt(){return 0;}
    virtual double asDouble(){return 0;}
    virtual JsonValue& getValue(){return *this;}
};




class JsonParser{
  private:

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
	sgdm::StackGuard<JsonValue> Error(std::string errorMsg){
		std::cout<< errorMsg<<std::endl;
		return std::move(sgdm::StackGuard<JsonValue>());
	}

	//Parsers begins
	sgdm::StackGuard<JsonValue> ParseInteger(){
		sgdm::StackGuard<JsonValue> res(new JsonInteger(inputIntger));
		getNextTok();
		return std::move(res);
	}

	sgdm::StackGuard<JsonValue> ParseDouble(){
		sgdm::StackGuard<JsonValue> res(new JsonDouble(inputDouble));
		getNextTok();
		return std::move(res);
	}

	sgdm::StackGuard<JsonValue> ParseName(){
		sgdm::StackGuard<JsonValue> res(new JsonName(idString));
		getNextTok();
		return std::move(res);
	}

	sgdm::StackGuard<JsonValue> ParseObject(sgdm::IAllocator<sgdm::StackGuard<JsonValue>>* alloc){
		sgdm::StackGuard<JsonValue> resObject(new JsonObject(alloc));
		if(currentTok != '{'){
			return Error("Expecting { at entity beginning");
		}
		else{
			getNextTok();//eat {
			while(currentTok != '}'){
				if(currentTok == ',')
					getNextTok();//eat ,
				resObject->push_back(std::move(ParsePair(alloc)));
			}
			getNextTok(); //eat }
			return std::move(resObject);
		}
	}



	sgdm::StackGuard<JsonValue> ParsePair(sgdm::IAllocator<sgdm::StackGuard<JsonValue>>* alloc){
		sgdm::StackGuard<JsonValue> pairName(new JsonName(idString));
		getNextTok();
		if(currentTok != ':'){
			return Error("Expecting :");
		}
		else{
			getNextTok(); //eat :
			sgdm::StackGuard<JsonValue> pairValue(std::move(ParsePrimary(alloc)));
            return std::move(new JsonPair(std::move(pairName),std::move(pairValue)));
		}
		
	}

	sgdm::StackGuard<JsonValue>  ParseArray(sgdm::IAllocator<sgdm::StackGuard<JsonValue>>* alloc){
		sgdm::StackGuard<JsonValue> array(new JsonArray());
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
				array->push_back(std::move(ParsePrimary(alloc)));
			}	
		}
		getNextTok(); //eat ]
		return std::move(array);

	}

	sgdm::StackGuard<JsonValue>  ParsePrimary(sgdm::IAllocator<sgdm::StackGuard<JsonValue>>* alloc){
		//getNextTok();
		switch(currentTok){
		case tok_endl:
                return std::move(Error("primary fail"));
		case tok_identifier:
			return std::move(ParseName());
		case tok_integer:
			return std::move(ParseInteger());
		case tok_double:
			return std::move(ParseDouble());
		//case '\'':
		//{
		//		getNextTok();
		//		return ParseName();
		//	}
		case '[':
			return std::move(ParseArray(alloc));
		case '{':
			return std::move(ParseObject(alloc));
                default:
                return std::move(Error("error"));
		
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

  	sgdm::StackGuard<JsonValue> Parse(sgdm::IAllocator<sgdm::StackGuard<JsonValue>>* alloc){
		getNextTok();
		/*if (currentTok == '{')    *///error handling needed
        return std::move(ParsePrimary(alloc));
  	}

};







#endif