#include <iostream>
#include <bits/stdc++.h>

using namespace std;


// Размер хеш-таблицы
#define TABLE_SIZE 13
// Используется во второй хэш-функции.
#define PRIME 10

struct product{
    int key=-1;
    string title="new";
    float price=-1;
};
product setProduct(int key,string title,float price){
    product tmp;
    tmp.key=key;
    tmp.title=title;
    tmp.price=price;
    return tmp;
}

class DoubleHash
{
    // Указатель на массив, содержащий сегменты
    product *hashTable;
    int curr_size;
public:
    // функция для проверки заполненности хеш-таблицы
    bool isFull()
    {
        // если размер хеша достигает максимального размера
        return (curr_size == TABLE_SIZE);
    }
    // функция для вычисления первого хеша
    int hash1(int key)
    {
        return (key % TABLE_SIZE);
    }
    // функция для вычисления второго хеша
    int hash2(int key)
    {
        return (PRIME - (key % PRIME));
    }
    DoubleHash()
    {
        hashTable = new product[TABLE_SIZE];
        curr_size = 0;
        for (int i=0; i<TABLE_SIZE; i++)
            hashTable[i].key = -1;
    }
    // функция для вставки ключа в хеш-таблицу
    void insertHash(product key)
    {
        // если хеш-таблица заполнена
        if (isFull())
            return;
        // получить индекс из первого хэша
        int index = hash1(key.key);
        // если происходит столкновение
        if (hashTable[index].key != -1)
        {
            // получаем index2 из второго хэша
            int index2 = hash2(key.key);
            int i = 1;
            while (true)
            {
                // получить новый индекс
                int newIndex = (index + i * index2) % TABLE_SIZE;
                // если нет столкновения, сохраняем
                // ключ
                cout<<"A collision occurred : "<<index<<" and "<<index2<<endl;
                if (hashTable[newIndex].key == -1)
                {
                    hashTable[newIndex].key = key.key;
                    hashTable[newIndex].title = key.title;
                    hashTable[newIndex].price=key.price;
                    break;
                }
                i++;
            }
        }
            // если не происходит столкновения
        else{
            hashTable[index].key = key.key;
            hashTable[index].title = key.title;
            hashTable[index].price=key.price;
        }
        curr_size++;
    }
    // функция для отображения хеш-таблицы
    void displayHash(bool chek)
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            if (hashTable[i].key != -1) {
                if (chek == true) {
                    cout << i << " --> ";
                }
                cout << hashTable[i].key << " " << hashTable[i].title << " " << hashTable[i].price << endl;
            } //else
                //if(chek== true)
                //cout << i << endl;
        }
    }
    void deleteProduct(int search){
        for (int i = 0; i < TABLE_SIZE; i++)
        {
                if (hashTable[i].key==search) {
                    cout <<hashTable[i].key<< " - element delete.\n";
                    hashTable[i].key=-1;
                    hashTable[i].price=0;
                    hashTable[i].title="";
                    return;
                }
        }
        cout<<"Element not found.\n";
    }
    void searchElemant(int search){
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            if (hashTable[i].key==search) {
                cout << i <<"-->"<<hashTable[i].key<<" "<<hashTable[i].title<<" "<<hashTable[i].price<<endl;
                return;
            }
        }
        cout<<"Element not found.\n";
    }
};
int main()
{
    cout<<"Practical work 3.Group IKBO-10-19.Gluchov Vladimir"<<endl;
    bool chec=true;
    DoubleHash h;
    while(chec==true){
        cout<<"Selected operating mode:\n"<<"0. End of work.\n"<<"1. Enter element.\n"<<"2. Delete element.\n"<<"3. Print table.\n"
            <<"4. Search element.\n";
        int num;
        cin>>num;
        switch (num) {
            case 0: {
                chec = false;
                break;
            }
            case 1:{
                cout<<"Enter number :"<<endl;
                int number;
                cin>>number;
                cout<<"Enter title :"<<endl;
                string title;
                cin>>title;
                cout<<"Enter price :"<<endl;
                int price;
                cin>>price;
                h.insertHash(setProduct(number ,title ,price));
                break;
            }
            case 2:{
                cout<<"Enter number element :"<<endl;
                int search;
                cin>>search;
                h.deleteProduct(search);
                break;
            }
            case 3:{
                h.displayHash(true);
                break;
            }
            case 4:{
                cout<<"Enter number element :"<<endl;
                int search;
                cin>>search;
                h.searchElemant(search);
                break;
            }

        }
    }
    return 0;
}
