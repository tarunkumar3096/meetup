#include <stdio.h>
#include <stdlib.h>

struct list {
	int data;
	struct list *next;
} *src_list;

void add_beg(struct list *queue, int data)
{
	struct list *temp;

	temp = (struct list *)malloc(sizeof(struct list));
	temp->data = data;
	if (queue == NULL)
		temp->next = NULL;
	else
		temp->next = queue;
	
       src_list = temp;
}

//void 
void remove_beg(struct list *queue)
{

	if (queue == NULL)
		return;

	src_list = queue->next;

	return;
}

void remove_end(struct list *queue)
{
	struct list *prev = queue;

	if (queue == NULL)
		return;

	while (queue->next != NULL) {
		prev = queue;
		queue = queue->next;
	}

	prev->next = NULL;
}
	
struct list *search(struct list *queue, int data)
{
	struct list *temp = queue;

	if (queue == NULL)
		return;

	while (!(temp == NULL) && (temp->data != data)) {
		temp = temp->next;
	}
	if (!temp)
		return NULL;
	return temp;
}

void remove_mid(struct list *queue, int data)
{
	struct list *temp;
	struct list *prev = queue; 

	temp = search(queue, data);
	if (temp) {
		printf("in\n");
		while (temp != queue) {
			prev = queue;
			queue = queue->next;
		}
		prev->next = temp->next;
	}
	else
		return;
}

void add_node(int data)
{
	//printf("data = %d\n", data);
	struct list *queue;
	struct list *head = src_list;
	queue = (struct list *)malloc(sizeof(struct list));
	queue->data = data;
	queue->next = NULL;

	if (src_list == NULL) {
		src_list = queue;
	} else {
		while (head->next != NULL)
			head = head->next;
		head->next = queue;
	}
	printf("%d\n", queue->data);

	

}

void display(struct list *queue)
{
	//printf("%x\n", &queue);
	struct list *temp = queue;
	//queue =  (struct list *)malloc(sizeof(struct list));
	//printf("%x\n", &queue);
	if (temp == NULL)
		return;
	
	while (temp) {
		//printf("hello\n");
		printf("%d-->", temp->data);
		temp = temp->next;
	}
	printf("NULL\n");
}
	
	

int main()
{
	struct list *find;
	int a = 50;
	printf("in\n");
	printf("%x\n", &src_list);
	add_node(a);
	display(src_list);
	printf("%d\n", &src_list->data);

	printf("in\n");
	add_node(49);
	add_node(48);
	add_node(47);
	add_node(46);
	display(src_list);
	add_beg(src_list, 55);
	display(src_list);
	add_beg(src_list, 2354);
	display(src_list);	
	remove_mid(src_list, 40);
	printf("mid deletion:\n");
	display(src_list);
	remove_beg(src_list);
	display(src_list);
	remove_end(src_list);
	display(src_list);
	remove_end(src_list);
	display(src_list);
	find = search(src_list, 49);
	display(find);
	free(src_list);
	return 0;
}
	
