/*
 * v8config.hpp
 *
 *  Created on: Aug 4, 2011
 *      Author: andrew
 */
#pragma once
#include <string>
#include <v8.h>

#include "../engine/config.hpp"

using namespace std;
using namespace v8;


class V8Config : public Config {

public:
	V8Config();
	virtual void setFileSystem(PFileSystem fileSystem);
	virtual PFileSystem getFileSystem();
	virtual void load(string jsonFileName);
	virtual int getInt(const char* category,const char* name);
	virtual string getString(const char* category,const char* name);
	virtual ~V8Config(){
		// Dispose the persistent context.
		context.Dispose();
	}
private:
	void parseConfig(Handle<Value> config);
	Handle<Object> getObjectParameter(Handle<Object> element,const char* key);
	Handle<Integer> getIntegerParameter(Handle<Object> element,const char* key);
	Handle<String> getStringParameter(Handle<Object> element,const char* key);
	Handle<Value> getKeyHandle(Handle<Object> element,const char* key);
	Handle<Object> rootObject;
	Persistent<Context> context;
	HandleScope handle_scope;
	PFileSystem fileSystem;

};

