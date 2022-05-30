#include "tethralink.hpp"


// Private







// Private
// ----------------------------------------------------------------------------
// Public


/*

tethralink::tethralink() { // constructor
	this->start = nullptr;
	this->end = nullptr;
	this->length = 0;
}


void tethralink::append(int element) { 
	tethra_node* x = new tethra_node();
	x->value = element;
	this->length += 1;
	if (start == nullptr) {
		start = x;
		end = x;
	}
	else {
		x->alpha_node = this->end;
		this->end->delta_node = x;
		this->end = x;
	}
}

int tethralink::get(int index) {
	return 0; // hmm...
}

void tethralink::print() {
	tethra_node* x = this->start;
	printf("%d\n", x->value);

	while (x->delta_node) {
		x = x->delta_node;
		printf("%d\n", x->value);
	}
	// delete(x); // !!! issue. bad idea!
}

int* tethralink::get_array() {
	int* arr = (int*)malloc(sizeof(int) * this->length);

	tethra_node* x = this->start;
	int i = 0; 
	arr[i] = x->value;
	while (x->delta_node) {
		i++;
		x = x->delta_node;
		arr[i] = x->value;
	}
	// arr[i + 1] = NULL;
	return arr;
}

tethralink::~tethralink() {
	// std::cout << "destructor gadget" << std::endl;
}

*/