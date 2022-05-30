#pragma once
#include <algorithm>
#include <cctype>
#include <compare>
#include <cstdio>
#include <iostream>
#include <memory>
#include <pthread.h>
#include <utility>
#include <cstdlib>
#include <functional>
#include <vector>
#include <thread>

#include "tethranode.hpp"


 
struct User { // exists temporarily for testing.
	std::string name;
	unsigned short age;
	bool alive;
	std::string email;
	bool permission;
	User( std::string pname, unsigned short page, bool palive, 
		std::string pemail, bool ppermission ) 
	{
		this->name = pname; this->age = page;
		this->alive = palive; this->email = pemail;
		this->permission = ppermission;
	}
};


template <typename T>
class tethralink { 
// PRIVATE
	int length;
	int NUM_THREADS;
	tethra_node<T>* start;
	tethra_node<T>* end;
	std::vector<T> vec;

	void initialize(unsigned int thread_limit_parameter) {
		// for now. 6 is the default number of threads for multithreaded tasks.
		if (thread_limit_parameter == 0) { // aka default.
			this->NUM_THREADS = 6;
		}
		if (thread_limit_parameter > 10) {
			this->NUM_THREADS = 10;
		}
		else {
			this->NUM_THREADS = thread_limit_parameter;
		}
		this->start = nullptr;
		this->end = nullptr;
		this->length = 0;
	}

	std::string capitalize(std::string str) {
		std::vector<char> data(str.begin(), str.end());
		std::transform(data.begin(), data.end(), data.begin(), toupper);
		return std::string(data.begin(), data.end()); // there is some stuff going on right no
	}

	// I should hope to find a way to optomise this sometime.
	tethra_node<T>* get_node(int index) {
		// this has a failsafe to evade seg faults at all costs.
		tethra_node<T>* x;
		if (index < (this->length / 2)) {
			x = this->start;
			for (int i = 0; i < index && i < this->length - 1; i += 1) {
				x = x->delta_node;
			}
		}
		else {
			x = this->end;
			for (int i = this->length; i < index && i > 0; i -= 1) {
				x = x->delta_node;
			}
		}
		return x;
	}

	// I can definitly do this better. 
	// However, this works conceptually for now.
	void remove_node(tethra_node<T>* dead_node) { // possibly causing seg faults.
		if (dead_node->alpha_node == nullptr) {
			if (dead_node->delta_node) {
				this->start = dead_node->delta_node;
			}
		}
		else {
			dead_node->alpha_node->delta_node = dead_node->delta_node;
		}
		if (dead_node->delta_node == nullptr) {
			this->end = dead_node->alpha_node;
		}
		else {
			dead_node->delta_node->alpha_node = dead_node->alpha_node;
		}

		this->length -= 1;
		delete(dead_node);
		data_update();
	}

	// This must be called the every time the data is changed so.
	void data_update() {
		tethra_node<T>* nodeptr = this->start;
		for (int i = 0; i <= (this->length / 2); i++) {
			// do something...
		}
		for (int i = this->length; i > (this->length / 2); i--) {
			// do something...
		}
	}

	static void any_of_thread_handler(std::function<bool(T element)>& lambda, bool* res, tethralink* instance) {
		tethra_node<T>* nodeptr = instance->start;
		while (nodeptr->delta_node) {
			if (lambda(nodeptr->value)) {
				*res = true;
			}
			nodeptr = nodeptr->delta_node;
		}
		if (lambda(nodeptr->value)) {
			*res = true;
		}
	}

// PUBLIC
public:


	tethralink() { // constructor.
		initialize(0);
	}

	tethralink(unsigned int thread_limit_parameter) {
		initialize(thread_limit_parameter);
	}

	tethralink(T* x, unsigned int thread_limit_parameter) {
		initialize(thread_limit_parameter);
		append_array(x);
	}

	int size() {
		return this->length;
	}

	void append(T element) {
		tethra_node<T>* nodeptr = new tethra_node<T>;
		nodeptr->value = element;
		this->length += 1;
		if (start == nullptr) {
			start = nodeptr;
			end = nodeptr;
		}
		else {
			nodeptr->alpha_node = this->end;
			this->end->delta_node = nodeptr;
			this->end = nodeptr;
		}
		data_update();
	}

	// for regular arrays.
	void append_array(T* x, int length) {
		for (int i = 0; i < length; i++) { 
			tethra_node<T>* nodeptr = new tethra_node<T>;
			nodeptr->value = x[i];
			this->length += 1;
			if (start == nullptr) {
				start = nodeptr;
				end = nodeptr;
			}
			else {
				nodeptr->alpha_node = this->end;
				this->end->delta_node = nodeptr;
				this->end = nodeptr;
			}
		}
		data_update();
	}

	// for null terminated array pointers (not good practice. Will likely only confuse users)
	void append_array(T* x) { // accepts a pointer as an argument
		for (int i = 0; x[i]; i++) { 
			append(x[i]);
		}
	}

	T get(int index) {
		return get_node(index)->value;
	}

	void remove(int index) {
		remove_node(get_node(index));
	}

	// incomplete method
	void for_each(std::function<void(T element)>& lambda) {
		tethra_node<T>* nodeptr = this->start;
		while (nodeptr->delta_node) {
			lambda(nodeptr->value);
			nodeptr = nodeptr->delta_node;
		}
		lambda(nodeptr->value);
	}


	bool any_of(std::function<bool(T element)>& lambda) {

		bool res = false;
		// if (this->length > 99 && this->NUM_THREADS > 1) { 
		// 	std::thread* threads[this->NUM_THREADS];
		// 	int startpoint = 0;
		// 	for (int i = 0; i < this->NUM_THREADS; i++) {
		// 		threads[i] = new std::thread(any_of_thread_handler, lambda, &res, this);
		// 	}
		// 	for (int i = 0; i < this->NUM_THREADS; i++) {
		// 		threads[i]->join();
		// 		delete( threads[i] );
		// 	}
		// }
		// else {
		// 	// just use one thread.
		// 	return any_of_thread_handler(lambda, &res, this);
		// }
		// causing some issues
		return res;

	}

	bool all_of(std::function<bool(T element)>& lambda) {
		return false;
	}

	// lambda function must be of return type 'bool'
	// filter method is causing shit loads of problems.
	void filter(std::function<bool(T element)>& lambda) {
		if (this->length > 0) {
			tethra_node<T>* nodeptr = this->start;
			if (!lambda(nodeptr->value)) {
				std::cout << "filter: " << nodeptr->value << std::endl;
				remove_node(nodeptr);
			}

			while (nodeptr->delta_node) {
				nodeptr = nodeptr->delta_node;
				std::cout << "filter: " << nodeptr->value << std::endl;
				if (!lambda(nodeptr->value) && nodeptr->delta_node) { // weird hack
					remove_node(nodeptr);
				}
			}
		}
	}

	void print() { // causing seg faults.
		tethra_node<T>* x = this->start;
		std::cout << x->value << std::endl;

		if (this->start != nullptr) {
			while (x->delta_node) {
				x = x->delta_node;
				std::cout << x->value << std::endl;
			}
		}

		// delete(x); // !!! issue. bad idea!
	}

	// only availbie with type 'std::string'
	void capitalize_all() requires std::same_as<T, std::string> {
		if (this->start != nullptr) {
			tethra_node<T>* x = this->start;
			x->value = capitalize(x->value);
			while (x->delta_node) {
				x = x->delta_node;
				x->value = capitalize(x->value);
			}
		}
	}

	T* get_array() { // remember to implement some async stuff for this later 
		T* arr = (T*)std::malloc(sizeof(T) * this->length);

		tethra_node<T>* x = this->start;
		int i = 0;
		arr[i] = x->value;
		while (x->delta_node) {
			i++;
			x = x->delta_node;
			arr[i] = x->value;
		}
		// arr[i + 1] = NULL;
		return arr; /* */
	}

	~tethralink() { // deconstructor
		delete(this->start);
		delete(this->end);
	}
};
