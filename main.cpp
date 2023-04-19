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

typedef enum MenuID {
	MENU_0,
	MENU_1,
	MENU_2,
	MENU_3,
	MENU_4,
	MENU_5,
	MENU_6,
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

// 查找指定元素，返回指定Item指针
const BookItem* findItemByISBN(const char* ISBN, const BookItem* list) {

	BookItem* pSearchCursor = (BookItem*)list;

	BookItem* pResult = nullptr;

	char input[1000] = { 0 };

	std::cout << "Please input ISBN : ";

	scanf("%s", input);
	// [x]->[A]->[B]->[C]....
	while (pSearchCursor != nullptr) {
		if (strcmp(pSearchCursor->ISBN, input) == 0) {
			Console::setColor(FuchsiaFore);
			std::cout << "Found: " << pSearchCursor->name << " " << "$" << pSearchCursor->price << std::endl;
			Console::setColor();
			pResult = pSearchCursor;
			break;
		}
		pSearchCursor = pSearchCursor->next;
	}//while

	return pResult;

}


void showMenu(int* menuId) {
	Console::setColor(BlueFore);
	std::cout << "请选择服务的种类：  " << std::endl;
	std::cout << "\t1、图书信息表的创建和输出。" << std::endl;
	std::cout << "\t2、按照图书价格进行升序排序，并且输出排序后的图书信息。" << std::endl;
	std::cout << "\t3、查找给定图书中价格最贵的图书。" << std::endl;
	std::cout << "\t4、找到指定位置的最喜欢的图书，并输出图书信息。" << std::endl;
	std::cout << "\t5、按照指定的位置，将新购买的图书插入到指定的位置。" << std::endl;
	std::cout << "\t6、输出当前顺序表。" << std::endl;
	std::cout << "\t0.保留文件并退出系统" << std::endl;
	Console::setColor(PurpleFore);
	std::cout << "请选择: ";
	std::cin >> *menuId;
	Console::setColor();
}


void showTable(const BookItem* items) {
	Console::setColor(LimeFore);
	printf("\t\t%24s %24s %24s\n", "ISBN", "名称", "价格");
	const BookItem* pTemp = items;
	if (pTemp == nullptr) {
		Console::setColor(RedFore);
		std::cout << "printf_list: The list was empty." << std::endl;
		Console::setColor();
		return;
	}
	Console::setColor(AquaFore);
	while (pTemp != nullptr) {
		printf("\t\t%24s %24s %24f\n", pTemp->ISBN, pTemp->name, pTemp->price);
		pTemp = pTemp->next;
	}
	Console::setColor();
}


int main() {

	Console::setColor(GreenFore);
	std::cout << "*************************************************************" << std::endl;
	std::cout << "******************** Welcome to Library system. *************" << std::endl;
	std::cout << "*************************************************************" << std::endl;
	Console::setColor();

	int currentMenuId = 0;

	showMenu(&currentMenuId);

	//std::cout << currentMenuId;
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

	showTable(pBooks->next);


	return 0;


	// [x] <=== pBooks
	//BookItem* pBooks = new BookItem;// 原始指针

	//// [x] <=== pCursor
	//BookItem* pCursor = pBooks;

	//BookItem* pInsertCursor = pBooks->next;
	//char input_insert[1000] = { 0 };
	//std::cout << "Please input ISBN Name Price:";
	//char ISBN[20] = { 0 };
	//char name[30] = { 0 };
	//float price = 0.0;
	//scanf("%s %s %f", &ISBN, &name, &price);

	//BookItem* pnew = new BookItem;
	//strcpy(pnew->ISBN, ISBN);
	//strcpy(pnew->name, name);
	//pnew->price = price;
	//pnew->next = nullptr;
	//pnew->front = pCursor;
	//pCursor->next = pnew;

	print_list(pBooks->next);

	const BookItem* item = findItemByISBN("1234", pBooks);
	if (item != nullptr) {
		printf("Found: %s\n", item->name);
	}
	else {
		printf("Not Found!\n");
	}


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
	if (0) {
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
	}


	return 0;
}

