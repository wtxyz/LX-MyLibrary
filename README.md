## MyLibrary代码说明

MyLibrary为C++语言实现的简单存储图书范例，该范例使用了双链表实现，双链表的头结点不进行数据存储，仅作链表索引。


#### 双链表
双链表为一种链式存储，和单链表相比仅仅多了一个指向前向元素的指针，该指针的增加可以大大增加元素溯源的能力。

```text
结构：
[Header] <--> [A] <--> [B] <--> [C]....

```

#### 菜单如下：
```text
**************************************************************
******************** 欢迎使用图书馆管理系统v1.0 **************
******************** @Author Xing Liu*************************
******************** @Date 2023/04/24 ************************
**************************************************************
请选择服务的种类：
        1、图书信息表的创建和输出。
        2、按照图书价格进行升序排序，并且输出排序后的图书信息。
        3、查找给定图书中价格最贵的图书。
        4、找到指定位置的最喜欢的图书，并输出图书信息。
        5、按照指定的位置，将新购买的图书插入到指定的位置。
        6、输出当前顺序表。
        7、修改指定ISBN的书籍。
        8、删除指定ISBN的书籍。
        0.保留文件并退出系统
请选择:
```

#### 结构定义
```cpp
struct BookItem {
	char ISBN[14] = { 0 };// ISBN 
	char name[256] = { 0 }; // 书名
	float price = 0.0; // 价格
	int capacity = 0; // 总容量，仅对头结点进行操作
	BookItem* next = nullptr;// 下一个元素
	BookItem* front = nullptr;// 前向元素
};
```

#### 函数签名
```cpp
// 从文件books.txt中读取书本信息
// books.txt 内容示例
// 1001456789651,小王子,99
// 1003457831995,微纪元,34
// 1003345678211,我的大学生活,36
void readBooksInfoFromFile(pBooks, &itemCount);

// 销毁列表中所有的元素
void destroy(BookItem* list);

// 通过ISBN号进行删除元素
void deleteItemByISBN(BookItem* list, const char* ISBN);

// 查找指定元素，返回指定Item指针
BookItem* findItemByISBN(const char* ISBN, const BookItem* list);

// 获取当前菜单
// 菜单和展示的菜单序号一一对应
int getMenuId();

// 显示数据表的内容，includEmptyHead参数说明：是否打印头结点
void showTable(const BookItem* list, bool includEmptyHead = true);

// 查找价格最高的书籍
BookItem* findHighestPrice(const BookItem* list);

// 工具函数，将元素克隆出来
BookItem* cloneTo(const BookItem* item);

// 查找指定位置的书籍，index从0开始
BookItem* findBookByIndex(const BookItem* list, int index);

// 排序链表，使用冒泡排序算法
void sortBooks(BookItem* list, int itemCount)

```

### Thanks
**1. Doris**
