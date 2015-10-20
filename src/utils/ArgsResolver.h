/*
 * ArgsResolver.h
 *
 *  Created on: Oct 20, 2015
 *      Author: mauruch
 */

#ifndef SRC_UTILS_EXCEPTIONS_ARGSRESOLVER_H_
#define SRC_UTILS_EXCEPTIONS_ARGSRESOLVER_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class ArgsResolver {

private:
	vector<string> params;

public:

	ArgsResolver(){};

	template<typename T, typename ... Args>
	ArgsResolver(T t, Args ... args) {
		func(t, args...);
	}

	template<typename T>
	void func(T t) {
		params.push_back(convertToString(t));
	}

	template<typename T, typename ... Args>
	void func(T t, Args ... args) // recursive variadic function
			{
		params.push_back(convertToString(t));
		func(args...);
	}

	//TODO use a Helper
	template<typename T>
	string convertToString(T t) {
		stringstream convert;
		convert << t;
		return string(convert.str());
	}

	vector<string> getParams() {
		return params;
	}

};

#endif /* SRC_UTILS_EXCEPTIONS_ARGSRESOLVER_H_ */
