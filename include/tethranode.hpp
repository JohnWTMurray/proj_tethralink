#pragma once
#include <iostream>
#include <functional>

// WARNING: if you're trying to create an instance of this struct stop.
// This exists only as a tool for 'tethralink'.
// To use this technology properly, create an instance of tethralink
// tethralink<type> instance; or
// tethralink<type>* instance = new tethralink();
template <typename T> 
struct tethra_node {
	tethra_node<T>* alpha_node;
	tethra_node<T>* delta_node; 
	T value;

	tethra_node() { // default constructor
		// do nothing. this is the constructor that is actually called
	}

	// this exists because I might want to give 'tethra_node' more roles and tasks
	// to declutter 'tethralink'. however for the time being it is unuded.
	tethra_node(tethra_node<T>* alpha_node, tethra_node<T>* dead_node, T value) {
		if (alpha_node == nullptr || delta_node == nullptr) {
			printf("invalid nodes\n"); 
			~tethra_node();
			return; // error;
		}
		this->alpha_node = alpha_node;
		this->dead_node = dead_node;
		this->value = value;
	}

	~tethra_node() {

	}
};
