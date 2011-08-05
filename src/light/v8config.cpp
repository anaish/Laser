#include <glog/logging.h>
#include <v8.h>
#include "v8config.hpp"

using namespace v8;

/**
A V8 implementation of the Config interface.
**/
V8Config :: V8Config(){

}

/**
Loads the config from JSON files
**/
void V8Config::load(){

	LOG(ERROR) << "Loading configuration";

	//Create the handle scope
	HandleScope handle_scope;

	//create the context
	Persistent<Context> context = Context::New();

	// Enter the created context for compiling and
	// running the script.
	Context::Scope context_scope(context);

	  // Create a string containing the JavaScript source code.
	Handle<String> source = String::New("'Test' + ', JavaScript'");

	// Compile the source code.
	Handle<Script> script = Script::Compile(source);

	// Run the script to get the result.
	Handle<Value> result = script->Run();

	// Dispose the persistent context.
	context.Dispose();

	// Convert the result to an ASCII string and print it.
	String::AsciiValue ascii(result);

	LOG(ERROR) << *ascii;

}
