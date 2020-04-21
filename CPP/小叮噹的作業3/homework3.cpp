#include <iostream>
#include <string>
#include <cstdlib>

#include <sstream>
#include <fstream>

struct book
{
	char* book_name;
	char* author;
	int price;
	
	book* left_node;
	book* right_node;	
};

book* new_book(const std::string);
bool search_data(int,int, bool, std::string, book*);
bool delete_data(const std::string, book*);
void print_data(book*);
void print_Big5(book*);
void clean_all(book*);
void read_file();

int main()
{
	book* root = NULL;
	int compare_way = 0;

	std::string input;
	while( std::getline(std::cin, input) )
	{
		//check first char
		switch(input.c_str()[0])
		{
		case 'I':
			std::cout << "=== 輸入 ===" << std::endl;

			compare_way = atoi(&input.c_str()[2]);
			if(compare_way == 0)
				std::cout << "=== error input ===" << std::endl;
			else {

				book* new_node = new_book(input);

				//insert to tree	

				if(root == NULL)
					root = new_node;
				else {
					book* pointer = root;

					while(true) {

						if (((compare_way == 1) && (0 > strcmp(new_node->book_name, pointer->book_name))) ||
							((compare_way == 2) && (0 > strcmp(new_node->author, pointer->author))) ||
							((compare_way == 3) && (new_node->price < pointer->price)) )
						{
							if(pointer->right_node == NULL) {
								pointer->right_node = new_node;
								break;
							}
							pointer = pointer->right_node;
						}
						else if (compare_way > 0 && compare_way < 4) {
							if(pointer->left_node == NULL) {
								pointer->left_node = new_node;
								break;
							}
							pointer = pointer->left_node;
						}
						else
							std::cerr << "=== error ===" << std::endl;
					}
				}
			}
			print_data(root);
			break;
		case '?':
		{
			std::cout << "=== 查詢 ===" << std::endl;

			int compare_way = atoi(&input.c_str()[2]);

			int start = input.find("\"");
			int end = input.find("\"",start + 1);
			std::string data = input.substr(start + 1, end - start - 1);

			int price = atoi(&input.c_str()[4]);

			if(compare_way > 0 && compare_way < 4) {
				if(search_data(compare_way, price, false, data, root))
					std::cout << "是" << std::endl;
				else
					std::cout << "否" << std::endl;
			}
			else
				std::cerr << "=== error ===" << std::endl;
		}
			break;
		case 'D':
			std::cout << "=== 刪除 ===" << std::endl;

			compare_way = atoi(&input.c_str()[2]);
			delete_data(input, root);
			break;
		case 'P':
			std::cout << "=== 列印 ===" << std::endl;
			print_data(root);
			break;
		case 'B':
			std::cout << "=== 列印內碼 ===" << std::endl;
			print_Big5(root);
			break;
		case 'C':
			std::cout << "=== 清除 ===" << std::endl;
			clean_all(root);
			root = NULL;
			break;
		case 'R':
			std::cout << "=== 讀檔 ===" << std::endl;
			break;
		default:
			std::cout << "=== error input ===" << std::endl;
		}
	}

	clean_all(root);
	root = NULL;
}

book* new_book(const std::string input)
{
	book* out = new book();

	//book name
	int start = input.find("\"");
	int end = input.find("\"",start + 1);
	
	std::string str = input.substr(start + 1, end - start - 1);
	out->book_name = new char[str.length() + 1];
	strcpy(out->book_name, str.c_str());

	//author
	start = input.find("\"",end + 1);
	end = input.find("\"",start + 1);
	
	str = input.substr(start + 1, end - start - 1);
	out->author = new char[str.length() + 1];
	strcpy(out->author, str.c_str());

	out->price = atoi(&input.c_str()[end + 1]);

	out->left_node = out->right_node = NULL;

	return out;
}

bool search_data(int compare_way,int price, bool is_any, std::string data, book* root)
{
	if(root == NULL)
		return is_any;

	if( ((compare_way == 1) && (0 == data.compare(root->book_name))) ||
		((compare_way == 2) && (0 == data.compare(root->author))) ||
		((compare_way == 3) && (price == root->price)) )
	{
		is_any = true;
		std::cout << root->book_name << " " << root->author << " " << root->price << std::endl;
	}
	else if(compare_way < 1 || compare_way > 3)
		std::cout << "== error input ==" << std::endl;

	is_any = search_data(compare_way, price, is_any, data, root->left_node);
	is_any = search_data(compare_way, price, is_any, data, root->right_node);

	return is_any;
}

bool delete_data(const std::string input, book* root)
{

	return true;
}

void print_data(book* root)
{
	if(root != NULL) {
		print_data(root->left_node);

		std::cout << root->book_name << " " << root->author << " " << root->price << std::endl;

		print_data(root->right_node);
	}
}
void print_Big5(book* root)
{
	if(root != NULL) {
		print_Big5(root->left_node);

		for(int i = 0; i < strlen(root->book_name); ++i)
			std::cout << "(" << (int)(root->book_name[i * 2]) << ", " << (int)(root->book_name[i * 2 + 1]) << ")  ";
		std::cout << std::endl;

		for(int i = 0; i < strlen(root->author); ++i)
			std::cout << "(" << (int)(root->author[i * 2]) << ", " << (int)(root->author[i * 2 + 1]) << ")  ";
		std::cout << std::endl;

		std::cout << root->price << std::endl;
	
		print_Big5(root->right_node);
	}
}

void clean_all(book* root)
{
	if(root != NULL) {
		clean_all(root->left_node);
		clean_all(root->right_node);
		
		delete[] root->book_name;
		delete[] root->author;
		delete root;
	}
}
/*
void
readFromStream (std::istream &stream,std::string streamName)
{
	std::ostringstream ss;
	ss << stream.rdbuf();
	std::string const source = ss.str();
 
	std::string::const_iterator next = source.begin();
 
 
 
	Dictionary dictionary;
	Dictionary::iterator iterDic;
 
	dictionary = newDictionary(next,source.end());
	printDic(dictionary);
 
 
 
 
 
	for(iterDic = dictionary.begin();iterDic != dictionary.end();++iterDic)
		delete[] *iterDic;
 
	//std::cout << source << std::endl;
}
 
void read_file(char **filenames,int num)
{
	std::cout << "--- read form Files ---" << std::endl;
	for(int cnt = 0;cnt < num;++cnt)
	{
		std::ifstream file(filenames[cnt]);
 
		if(file.fail())
		{
			std::cerr << "cannot open file: " << filenames[cnt] << std::endl;
			continue;
		}
 
		std::cout << "-- read from file: " << filenames[cnt] << std::endl;
		readFromStream(file,filenames[cnt]);
	}
}*/

