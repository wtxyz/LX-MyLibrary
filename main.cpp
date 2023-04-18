#include "pch.h"
#include <iostream>
#include <string>
#include "console.h"
// We Now use C++ to write a system of Library.

#define USE_LINKED_LIST 1 // Store the data by list.( 0 means array style storage.)

typedef enum Status {
	STATUS_OK,
	STATUS_ERROR
};

struct BookItem {
	char ISBN[14] = { 0 };// ISBN 
	char name[256] = { 0 }; // 书名
	float price = 0.0; // 价格
	BookItem* next = nullptr;
	BookItem* front = nullptr;
};

/*
	[x]->[A]->[B]->[C]  ....
*/

void print_list(BookItem* targetList) {
	// 此处不使用头
	// [x] -> [A] -> [B]....
	BookItem* pTemp = targetList;
	if (pTemp == nullptr) {
		Console::setColor(FuchsiaFore);
		std::cout << "printf_list: The list was empty." << std::endl;
		Console::setColor();
		return;
	}
	while (pTemp != nullptr) {
		std::cout << "ISBN: " << pTemp->ISBN << std::endl;
		std::cout << "Name: " << pTemp->name << std::endl;
		std::cout << "Price: " << pTemp->price << std::endl;
		pTemp = pTemp->next;
		std::cout << std::endl;
	}
}

void destroy(BookItem* list) {
	BookItem* pCursor = list;
	// 删除所有当前节点及其后面的所有数据
	while (pCursor != nullptr) {
		BookItem* tempNext = pCursor->next;
		delete pCursor;
		pCursor = tempNext;
	}
	list->next = nullptr;
}

// delete
void delete_item_by_ISBN(BookItem* listNode, const char* ISBN) {
	BookItem* pDeleteCursor = listNode;
	while (pDeleteCursor != nullptr) {
		if (strcmp(pDeleteCursor->ISBN, ISBN) == 0) {
			Console::setColor(YellowFore);
			std::cout << pDeleteCursor->name << " will be deleted." << std::endl;
			Console::setColor();
			// [x] -> [A] -> [B(ISBN=0601)] -> [C]....
			BookItem* pTemp = pDeleteCursor;
			// 边界检查
			if (pTemp->next != nullptr) {
				// the last element.
				pTemp->front->next = pTemp->next;
				pTemp->next->front = pTemp->front;
			}
			else {
				pTemp->front->next = nullptr;
			}
			delete pDeleteCursor;
			break;
		}
		pDeleteCursor = pDeleteCursor->next;
	}
}


int main() {

	Console::setColor(GreenFore);
	std::cout << "\n\t********************************" << std::endl;
	std::cout << "\t** Welcome to Library system. **" << std::endl;
	std::cout << "\t********************************" << std::endl;
	Console::setColor();

	// [x] <=== pBooks
	BookItem* pBooks = new BookItem;// 原始指针

	// [x] <=== pCursor
	BookItem* pCursor = pBooks;

	BookItem* pInsertCursor = pBooks->next;
	char input_insert[1000] = { 0 };
	std::cout << "Please input ISBN Name Price:";
	char ISBN[20] = { 0 };
	char name[30] = { 0 };
	float price = 0.0;
	scanf("%s %s %f", &ISBN, &name, &price);

	BookItem* pnew = new BookItem;
	strcpy(pnew->ISBN, ISBN);
	strcpy(pnew->name, name);
	pnew->price = price;
	pnew->next = nullptr;
	pnew->front = pCursor;
	pCursor->next = pnew;

	print_list(pBooks->next);


	//************************ 查找（按照ISBN）START*******************************************

	if (0) {
		BookItem* pSearchCursor = pBooks->next;
		char input[1000] = { 0 };
		std::cout << "Please input ISBN : ";
		scanf("%s", input);
		// [x]->[A]->[B]->[C]....
		while (pSearchCursor != nullptr) {
			if (strcmp(pSearchCursor->ISBN, input) == 0) {
				std::cout << "Found: " << pSearchCursor->name << " " << "$" << pSearchCursor->price << std::endl;
			}
			pSearchCursor = pSearchCursor->next;
		}//while
	}

	//************************ 查找（按照ISBN）END ********************************************


	//************************ 删除（按照ISBN）START*******************************************
	if (0) {
		char input_delete[1000] = { 0 };
		Console::setColor(RedFore);
		std::cout << "Please input ISBN to DELETE! : ";
		Console::setColor();
		scanf("%s", input_delete);
		delete_item_by_ISBN(pBooks->next, input_delete);

		Console::setColor(RedFore);
		std::cout << "Please input ISBN to DELETE! : ";
		Console::setColor();
		scanf("%s", input_delete);
		delete_item_by_ISBN(pBooks->next, input_delete);
	}


	//************************ 删除（按照ISBN）END*******************************************


	//************************ 修改（按照ISBN）START*******************************************
	// 找到ISBN -> 修改价格
	char input_modify[100] = { 0 };
	Console::setColor(FuchsiaFore);
	std::cout << "Please input ISBN to find the Book: ";
	Console::setColor();
	std::cin >> input_modify;
	BookItem* pModifyCursor = pBooks;
	while (pModifyCursor != nullptr) {
		if (strcmp(pModifyCursor->ISBN, input_modify) == 0) {
			Console::setColor(YellowFore);
			std::cout << "Please input anew price for " << pModifyCursor->name << ": ";
			Console::setColor();
			float new_price = 0.0;
			scanf("%f", &new_price);
			pModifyCursor->price = new_price;
		}

		pModifyCursor = pModifyCursor->next;
	}


	//************************ 修改（按照ISBN）END*******************************************

	print_list(pBooks->next);

	return 0;
}

