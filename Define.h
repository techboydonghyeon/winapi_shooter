#pragma once

/*
½Ì±ÛÅæ ¸ÅÅ©·Î ÇÔ¼ö
*/
#define SINGLETON_H(className)\
private:\
className(){}\
~className() {}\
public:\
className(const className&) = delete; \
void operator=(const className&) = delete;\
static void CreateInstance(){ \
if(!instance) instance = new className;\
}\
void ReleaseInstance(){\
if(instance) delete instance; instance = nullptr;\
}\

#define SINGLETON_S(className)\
className* className::instance = nullptr;
