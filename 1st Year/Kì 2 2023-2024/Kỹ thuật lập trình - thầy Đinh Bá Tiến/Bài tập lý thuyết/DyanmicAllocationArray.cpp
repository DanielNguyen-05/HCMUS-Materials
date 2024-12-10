#include <iostream>
#include <cstring>
#include <string>

struct Book
{
    int ID;
    char* title;
    double price;
};

void inputList(Book* &store, int num)
{    
    std::cout << "Nhập số lượng sách: ";
    std::cin >> num;
    store = new Book[num];
    for (int i = 0; i < num; i++) 
    {
        std::cout << "\n" << "Nhập thông tin cho sách thứ " << i + 1 << ":" << "\n";
        std::cout << "ID: ";
        std::cin >> store[i].ID;
        // std::cin >> (store + i)->ID;

        std::cout << "Title: ";
        std::cin.ignore();
        char new_title[1000];
        std::cin.getline(new_title, 1000);
        store[i].title = new char[strlen(new_title) + 1];
        strcpy (store[i].title, new_title);

        // std::cout << "Title: ";
        // std::cin.ignore();
        // store[i].title = new char[1000];
        // std::cin.getline(store[i].title, 1000, '\n');

        // std::cout << "Title: ";
        // std::cin.ignore();
        // std::string new_title;
        // getline(std::cin, new_title);
        // int len = new_title.size();
        // store[i].title = new char[len + 1];
        // strcpy (store[i].title, new_title.c_str());

        std::cout << "Price: ";
        std::cin >> store[i].price;
    }

}

void outputList(Book* store, int num)
{
    std::cout << "\n" << "Thông tin về sách:" << "\n";
    for (int i = 0; i < num; i++) 
    {
        std::cout << "Sách " << i + 1 << ":\n";
        std::cout << "ID: " << store[i].ID << "\n";
        std::cout << "Title: " << store[i].title << "\n";
        std::cout << "Price: " << store[i].price << "\n\n";
    }
}

void deleteList (Book* &store, int num)
{
    for (int i = 0; i < num; i++)
    {
        delete[] store[i].title;
    }
    delete[] store;
}

int main()
{
    int num;
    Book* store;

    inputList (store, num);
    outputList(store, num);
    deleteList(store, num);

    return 0;
}
