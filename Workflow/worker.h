#pragma once
#include <fstream>
#include <iostream>
#include "Consts.h"
#include <optional>
using namespace consts;
namespace workflow
{
	class  Worker
	{
	public:
		Worker(const std::optional <string_list>& parameters);
		virtual ~Worker();
		virtual void validate(const std::optional <string_list>& data) const = 0;
		virtual std::optional <string_list> doSomeWork(const std::optional <string_list>& data)  const= 0;
	protected:
		std::optional <string_list> parameters_;
	};

	class Readfile : public Worker
	{//input - none; output - txt
	public:
		Readfile(const std::optional <string_list>& parameters);
		void validate(const std::optional <string_list>& data) const;
		std::optional <string_list> doSomeWork(const std::optional <string_list>& data) const;
	};

	class Writefile : public Worker
	{//input - txt; output - none 
	public:
		Writefile(const std::optional <string_list>& parameters);
		void validate(const std::optional <string_list>& data) const;
		std::optional <string_list> doSomeWork(const std::optional <string_list>& data) const;
	};

	class Grep : public Worker
	{//input - txt; output - txt  
	public:
		Grep(const std::optional <string_list>& parameters);
		void validate(const std::optional <string_list>& data) const;
		std::optional <string_list> doSomeWork(const std::optional <string_list>& data) const;
	};

	class Sort : public Worker
	{//input - txt; output - txt
	public:
		Sort(const std::optional <string_list>& parameters);
		void validate(const std::optional <string_list>& data) const;
		std::optional <string_list> doSomeWork(const std::optional <string_list>& data) const;
	};

	class Replace : public Worker
	{//input - txt; output - txt  
	public:
		Replace(const std::optional <string_list>& parameters);
		void validate(const std::optional <string_list>& data) const;
		std::optional <string_list> doSomeWork(const std::optional <string_list>& data) const;
	};

	class Dump : public Worker
	{ //input - txt; output - txt  
	public:
		Dump(const std::optional <string_list>& parameters);
		void validate(const std::optional <string_list>& data) const;
		std::optional <string_list> doSomeWork(const std::optional <string_list>& data) const;
	};

Worker* workerFactory(const string_list& parameters);
}