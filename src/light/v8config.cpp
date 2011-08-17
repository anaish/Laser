#include <glog/logging.h>
#include <v8.h>
#include <string>
#include <cassert>

#include "v8config.hpp"
#include "defaultfilesystem.hpp"

using namespace v8;
using namespace std;

/**
A V8 implementation of the Config interface.
**/
V8Config :: V8Config(){

}


/**
Loads the config from JSON files
**/
void V8Config::load(string json){

	LOG(ERROR) << "Loading configuration";

	//create the context
	context = Context::New();

	// Enter the created context for compiling and
	// running the script.
	Context::Scope context_scope(context);

	// Create a string containing the JavaScript source code.
	string evalStart("eval(");
	string evalEnd(");");
	string evalJson = evalStart + json + evalEnd;
	Handle<String> source = String::New(evalJson.c_str());

	// Compile the source code.
	Handle<Script> script = Script::Compile(source);

	// Run the script to get the result.
	Handle<Value> result = script->Run();
	parseConfig(result);


	// Convert the result to an ASCII string and print it.
	String::AsciiValue ascii(result);

	LOG(ERROR) << *ascii;

}

string V8Config::getString(const char* category,const char* name){

	Handle<Object> categoryObject = getObjectParameter(rootObject,category);
	Handle<String> stringParam = getStringParameter(categoryObject,name);
	String::AsciiValue ascii(stringParam);
	string s = *ascii;
	return s;

}

int V8Config::getInt(const char* category,const char* name){

	Handle<Object> categoryObject = getObjectParameter(rootObject,category);
	return getIntegerParameter(categoryObject,name)->IntegerValue();

}

/**
 * Parses and validates the configuration
 */
void V8Config::parseConfig(Handle<Value> result){

	assert(result->IsObject());
	rootObject = result->ToObject();

}

/**
 * Gets the handle for a specific key
 */
Handle<Value> V8Config::getKeyHandle(Handle<Object> element,const char* key){

	Handle<String> handleKey = String::New(key);
	Handle<Value> handleValue = element->Get(handleKey);
	return handleValue;

}


/**
 * Gets an object parameter from the json config as an object
 */
Handle<Object> V8Config::getObjectParameter(Handle<Object> element,const char* key){

	Handle<Value> handleValue = getKeyHandle(element,key);
	assert(handleValue->IsObject());
	return handleValue->ToObject();

}

/**
 * Gets an object parameter from the json config as an Integer
 */

Handle<Integer> V8Config::getIntegerParameter(Handle<Object> element,const char* key){

	Handle<Value> handleValue = getKeyHandle(element,key);
	assert(handleValue->IsNumber());
	return handleValue->ToInteger();

}

/**
 * Gets an object parameter from the json config as a String
 */

Handle<String> V8Config::getStringParameter(Handle<Object> element,const char* key){

	Handle<Value> handleValue = getKeyHandle(element,key);
	assert(handleValue->IsString());
	return handleValue->ToString();

}

