// Array representation according to Wikipedia article but starts from 0 index.
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int codigo;
    int cantidad;
    int total;
    char nombre_producto[31];
} util;

typedef struct {
	int size;
	int count;
	util* heaparr;
} heap;

int size, count;
int initial_size = 4;

void heap_init(heap *h){
	h->count = 0;
	h->size = initial_size;
	h->heaparr = (util *) malloc(sizeof(util));
	if(!h->heaparr) {
		printf("Error allocatinga memory...\n");
		exit(-1);
	}

}

int heap_size(heap *h){
	return h->size;
}

void max_heapify(util* data, int loc, int count) {
	int left, right, largest, temp;
	left = 2*(loc) + 1;
	right = left + 1;
	largest = loc;
	

	if (left <= count && data[left].total > data[largest].total) {
		largest = left;
	} 
	if (right <= count && data[right].total > data[largest].total) {
		largest = right;
	} 
	
	if(largest != loc) {
		temp = data[loc].total;
		data[loc] = data[largest];
		data[largest].total = temp;
		max_heapify(data, largest, count);
	}

}

void heap_push(heap *h, util value){
	int index, parent;
 
	// Resize the heap if it is too small to hold all the data
	if (h->count == h->size){
		h->size += 1;
		h->heaparr = realloc(h->heaparr, sizeof(util) * h->size);
		if (!h->heaparr) exit(-1); // Exit if the memory allocation fails
	}
 	
 	index = h->count++; // First insert at last of array

 	// Find out where to put the element and put it
	for(;index; index = parent){
		parent = (index - 1) / 2;
		if (h->heaparr[parent].total >= value.total) break;
		h->heaparr[index].total = h->heaparr[parent].total;
	}
	h->heaparr[index].total = value.total;
}

void heap_display(heap *h) {
	for(int i = 0; i < h->count; ++i) {
		//printf("|%d|", h->heaparr[i]);
		printf("%d %s %d %d\n", 
			   h->heaparr[i].codigo, 
			   h->heaparr[i].nombre_producto, 
			   h->heaparr[i].cantidad, 
			   h->heaparr[i].total
			);
	}
	return;
}


util heap_getMax(heap *h){
	util removed;
	int temp = h->heaparr[--h->count].total;
 	
	
	if ((h->count <= (h->size + 2)) && (h->size > initial_size)){
		h->size -= 1;
		h->heaparr = realloc(h->heaparr, sizeof(util) * h->size);
		if (!h->heaparr) exit(-1); // Exit if the memory allocation fails
	}
 	removed = h->heaparr[0];
 	h->heaparr[0].total = temp;
 	max_heapify(h->heaparr, 0, h->count);
 	return removed;
}

