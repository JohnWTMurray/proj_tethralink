#include <algorithm>
#include <cstring>
#include <functional>
#include <pthread.h>
#include <regex> // yes this is true
#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>
#include "tethralink.hpp"


void meme(std::vector<int>* vecc) {
	std::for_each_n(vecc->begin(), vecc->size(), [](int element) {
		printf("%d\n", element);
	});
}


// application entry point
int main(int argc, char* argv[]) {
	tethralink<std::string> params;
	for (int i = 1; i < argc; i++) {
		params.append(argv[i]);
	}
	params.capitalize_all();
	params.print();
	printf("Telepath\n");

	int arr[] = {1,2,3,4,5,6,7,8,9,10};
	tethralink<int> list;
	list.append(2); list.append(4);
	list.append(8); list.append(16);
	list.append(32); list.append(64);
	// for (int i = 0; i < 500; i++) {
	// 	list.append(i);
	// }

	std::function<bool(int element)> lambda = [](int element) {
		return (element > 100);
	};


	printf(list.any_of(lambda) ? "TRUE\n" : "FALSE\n");
	list.print();

	// list.append_array(arr, sizeof(arr) / sizeof(*arr));


	// printf(list.any_of(lambda) ? "TRUE\n" : "FALSE\n");

	// list.print();

	return 0;
}
