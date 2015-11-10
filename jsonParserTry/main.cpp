#include "json_parser.h"

int main(){
	JsonParser myParser("{'schema': {'intoTheJungle' : 123 , 'highSchool' : 0.01} , 'description' : 'schemry' , 'required' : [ 'storage' , 'sand' , {'theWorld' : 'onceAgain' } ] }");
	//JsonParser myParser("{'required': [ 'storage' , 'sand' , {'theWorld' : 'onceAgain' } ]}");
	myParser.Parse();




	return 0;
}