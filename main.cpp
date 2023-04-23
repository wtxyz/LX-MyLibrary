#include "pch.h"
#include <iostream>
#include <string>
#include "console.h"

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
	MENU_7,
	MENU_8,
	MENU_65535 = 65535
};

struct BookItem {
	char ISBN[14] = { 0 };// ISBN 
	char name[256] = { 0 }; // 书名
	float price = 0.0; // 价格
	int capacity = 0;
	BookItem* next = nullptr;
	BookItem* front = nullptr;
};

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
void deleteItemByISBN(BookItem* list, const char* ISBN) {
	BookItem* pDeleteCursor = list;
	while (pDeleteCursor != nullptr) {
		if (strcmp(pDeleteCursor->ISBN, ISBN) == 0) {
			Console::setColor(RedFore);
			std::cout << pDeleteCursor->name << " 已被删除!" << std::endl;
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
			list->capacity = list->capacity - 1;
			delete pDeleteCursor;
			break;
		}
		pDeleteCursor = pDeleteCursor->next;
	}
}

// 查找指定元素，返回指定Item指针
BookItem* findItemByISBN(const char* ISBN, const BookItem* list) {

	BookItem* pSearchCursor = (BookItem*)list;

	BookItem* pResult = nullptr;

	while (pSearchCursor != nullptr) {
		if (strcmp(pSearchCursor->ISBN, ISBN) == 0) {
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

// 获取当前菜单
int getMenuId() {
	int menuId = 0;
	Console::setColor(BlueFore);
	std::cout << "请选择服务的种类：  " << std::endl;
	//std::cout << "\t65535、从文本读取数据。" << std::endl;
	std::cout << "\t1、图书信息表的创建和输出。" << std::endl;
	std::cout << "\t2、按照图书价格进行升序排序，并且输出排序后的图书信息。" << std::endl;
	std::cout << "\t3、查找给定图书中价格最贵的图书。" << std::endl;
	std::cout << "\t4、找到指定位置的最喜欢的图书，并输出图书信息。" << std::endl;
	std::cout << "\t5、按照指定的位置，将新购买的图书插入到指定的位置。" << std::endl;
	std::cout << "\t6、输出当前顺序表。" << std::endl;
	std::cout << "\t7、修改指定ISBN的书籍。" << std::endl;
	std::cout << "\t8、删除指定ISBN的书籍。" << std::endl;
	std::cout << "\t0.保留文件并退出系统" << std::endl;
	Console::setColor(YellowFore);
	std::cout << "请选择: ";
	std::cin >> menuId;
	Console::setColor();
	return menuId;
}

// 显示数据表
void showTable(const BookItem* list, bool includEmptyHead = true) {
	Console::setColor(LimeFore);
	printf("\t\t%24s %24s %24s\n", "ISBN", "名称", "价格");
	const BookItem* pTemp = includEmptyHead ? list->next : list;
	if (pTemp == nullptr) {
		Console::setColor(RedFore);
		std::cout << "书籍数据列表为空！" << std::endl;
		Console::setColor();
		return;
	}
	Console::setColor(AquaFore);
	while (pTemp != nullptr) {
		printf("\t\t%24s %24s %24.2f\n", pTemp->ISBN, pTemp->name, pTemp->price);
		pTemp = pTemp->next;
	}
	Console::setColor();
}

// 查找价格最高的书籍
BookItem* findHighestPrice(const BookItem* list) {
	// [x] <-> [A] <-> [B] .....
	BookItem* pCursor = list->next;
	BookItem* result = pCursor;
	while (pCursor != nullptr) {
		if (pCursor->price > result->price) {
			result = pCursor;
		}
		pCursor = pCursor->next;
	}// while
	return result;
}

BookItem* cloneTo(const BookItem* item) {
	BookItem* it = new BookItem;
	strcpy(it->ISBN, item->ISBN);
	strcpy(it->name, item->name);
	it->next = nullptr;
	it->front = nullptr;
	it->price = item->price;
	it->capacity = 1;
	return it;
}


// 查找指定位置的书籍
BookItem* findBookByIndex(const BookItem* list, int index) {
	BookItem* pCursor = list->next;

	if (index > list->capacity) {
		Console::setColor(RedFore);
		std::cout << "索引超出了最大长度!" << std::endl << std::endl;
		Console::setColor();
		return nullptr;
	}

	while (index--) {
		pCursor = pCursor->next;
	}

	return pCursor;
}


// 从文件中读取数据
void readBooksInfoFromFile(BookItem* list, int* itemCount) {
	FILE* fp = fopen("books.txt", "r");
	char contents[1024] = { 0 };
	BookItem* pCursor = list;
	int count = 0;
	while (fgets(contents, 1024, fp)) {
		char* p = contents;
		char* strTokens = strtok(contents, ",");
		int idx = 0;
		BookItem* item = new BookItem;
		while (strTokens) {
			int currentIdx = idx % 3;
			switch (currentIdx) {
			case 0: {
				strcpy(item->ISBN, strTokens);
				break;
			}
			case 1: {
				strcpy(item->name, strTokens);
				break;
			}
			case 2: {
				item->price = atof(strTokens);
				break;
			}
			default:
				break;
			}
			idx++;
			strTokens = strtok(nullptr, ",");
		}
		// while token
		item->next = NULL;
		item->front = pCursor;
		pCursor->next = item;
		pCursor = item;
		memset(contents, 0, 1024);
		count++;
	}// while
	list->capacity = count;
	*itemCount = count;
}



// 排序链表
void sortBooks(BookItem* list, int itemCount) {
	BookItem* pBook = list;
	for (int i = 0; i < itemCount; i++) {
		pBook = list->next;
		for (int j = 0; j < itemCount - 1; j++) {
			if (pBook != nullptr && pBook->next != nullptr) {
				if (pBook->price > pBook->next->price) {
					BookItem* PA = pBook;
					BookItem* PB = pBook->next;
					PB->front = PA->front;
					PB->front->next = PB;
					// [A]----
					PA->next = PB->next;
					if (PA->next)
						PA->next->front = PA;
					PA->front = PB;
					PB->next = PA;
					pBook = PA;
				}
				else {
					pBook = pBook->next;
				}
			}

		}
	}
}


int main() {

	Console::setColor(GreenFore);
	std::cout << "**************************************************************" << std::endl;
	std::cout << "******************** 欢迎使用图书馆管理系统v1.0 **************" << std::endl;
	std::cout << "******************** @Author ";
	Console::setColor(FuchsiaFore);
	std::cout << "Xing Liu";
	Console::setColor(GreenFore);
	std::cout << "*************************" << std::endl;
	std::cout << "******************** @Date 2023/04/24 ************************" << std::endl;
	std::cout << "**************************************************************" << std::endl;
	Console::setColor();

	BookItem* pBooks = new BookItem;// 原始指针

	BookItem pBooksArray[32];

	// 从文件中读取数据到内存中
	int itemCount = 0;
	int menuId = 0;

	while (1) {
		menuId = getMenuId();

		switch (menuId)
		{
		case MenuID::MENU_0: {
			// 推出系统
			return 0;
			break;
		}
		case MenuID::MENU_1: {
			// 输入内容
			readBooksInfoFromFile(pBooks, &itemCount);
			std::cout << "我已经读取" << itemCount << "个数据到链表中!\n" << std::endl;
			break;
		}
		case MenuID::MENU_2: {
			// 按照图书价格进行排序
			sortBooks(pBooks, itemCount);
			showTable(pBooks);
			break;
		}
		case MenuID::MENU_3: {
			// 找最贵的书籍
			BookItem* result = findHighestPrice(pBooks);
			if (result != nullptr) {
				std::cout << "最贵的图书为：" << result->name << std::endl << std::endl;
			}
			break;
		}
		case MenuID::MENU_4: {
			// 找到最喜欢的书籍（指定位置），并输出图书信息
			int position = 0;
			std::cout << "您指定的位置是: ";
			std::cin >> position;
			BookItem* item = cloneTo(findBookByIndex(pBooks, position));
			if (item != nullptr) {
				showTable(item, false);
			}
			delete item;
			break;
		}
		case MenuID::MENU_5: {
			// 插入图书到指定位置
			int position = 0;
			char ISBN[256] = { 0 };
			char name[256] = { 0 };
			float price = 0.0;

			std::cout << "请输入你要插入的位置: ";
			std::cin >> position;
			std::cout << "请输入图书的ISBN: ";
			std::cin >> ISBN;
			std::cout << "请输入图书的书名: ";
			std::cin >> name;
			std::cout << "请输入图书的价格: ";
			std::cin >> price;

			BookItem* replacedItem = findBookByIndex(pBooks, position);
			// ---[x] <--> [A]......
			BookItem* item = new BookItem;
			strcpy(item->ISBN, ISBN);
			strcpy(item->name, name);
			item->price = price;

			item->front = replacedItem->front;
			replacedItem->front->next = item;

			item->next = replacedItem;
			replacedItem->front = item;
			pBooks->capacity = pBooks->capacity + 1;

			showTable(pBooks);

			break;
		}
		case MenuID::MENU_6: {
			// 输出当前数据表
			showTable(pBooks);
			break;
		}
		case MenuID::MENU_7: {
			// 修改指定ISBN的书籍价格和书名等
			char ISBN[256] = { 0 };
			char name[256] = { 0 };
			float price = 0.0;
			std::cout << "请输入要修改的ISBN:";
			std::cin >> ISBN;
			BookItem* item = findItemByISBN(ISBN, pBooks);
			if (item == nullptr) {
				Console::setColor(RedFore);
				std::cout << "没有找到指定ISBN的图书" << std::endl << std::endl;
				Console::setColor();
				break;
			}
			std::cout << "请输入图书新的ISBN: ";
			std::cin >> ISBN;
			std::cout << "请输入图书新的书名: ";
			std::cin >> name;
			std::cout << "请输入图书新的价格: ";
			std::cin >> price;
			strcpy(item->ISBN, ISBN);
			strcpy(item->name, name);
			item->price = price;
			showTable(pBooks);
			break;
		}
		case MenuID::MENU_8: {
			// 按照指定ISBN 删除信息
			char ISBN[256] = { 0 };
			std::cout << "请输入要删除的ISBN:";
			std::cin >> ISBN;
			deleteItemByISBN(pBooks, ISBN);
			showTable(pBooks);
			break;
		}
		case MenuID::MENU_65535: {
			// 从文本读取数据
			readBooksInfoFromFile(pBooks, &itemCount);
			std::cout << "我已经读取" << itemCount << "个数据到链表中!\n" << std::endl;
			break;
		}
		default:
			break;
		}
	}// while(1)

	return 0;
}

