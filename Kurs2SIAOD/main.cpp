#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <map>

using namespace std;

    struct st{ char c;struct st *next;};
    struct st *push(struct st *, char);
    char deleteItems(struct st **);
    int priorityOperation(char);

    void writeQueue(void){
        struct st *OPERS=NULL;

        char a[100] ,outstring[100];
        for(int i=0;i<100;i++){
            outstring[i]=' ';
        }
        int k, point;
        do
        { puts("Enter an arithmetic expression:");
            fflush(stdin);
            gets(a);
            k=point=0;
            while(a[k]!='\0'&&a[k]!='=')
            {
                if(a[k]==')')

                {
                    while((OPERS->c)!='(')

                        outstring[point++]=deleteItems(&OPERS);

                    deleteItems(&OPERS);
                }

                if(a[k]>='a'&&a[k]<='z')

                    outstring[point++]=a[k];

                if(a[k]=='(')

                    OPERS=push(OPERS, '(');
                if(a[k]=='+'||a[k]=='-'||a[k]=='/'||a[k]=='*')

                {

                    if(OPERS==NULL)

                        OPERS=push(OPERS, a[k]);

                    else

                    if(priorityOperation(OPERS->c)<priorityOperation(a[k]))

                        OPERS=push(OPERS, a[k]);

                    else
                    {
                        while((OPERS!=NULL)&&(priorityOperation(OPERS->c)>=priorityOperation(a[k])))
                            outstring[point++]=deleteItems(&OPERS);

                        OPERS=push(OPERS, a[k]);
                    }
                }
                k++;
            }
            while(OPERS!=NULL) {
                outstring[point++] = deleteItems(&OPERS);
            }
            outstring[point]='\0';
            printf("\n%s\n", outstring);
            fflush(stdin);
            puts("\nReplay (y/n)?");
        } while(getchar()!='n');
    }
    struct st *push(struct st *HEAD, char a)
    {
        struct st *PTR;
        if((PTR= static_cast<st *>(malloc(sizeof(struct st)))) == NULL)
        {
            puts("end");exit(-1);
        }
        PTR->c=a;
        PTR->next=HEAD;
        return PTR;
    }
    char deleteItems(struct st **HEAD)
    {
        struct st *PTR;
        char a;
        if(*HEAD==NULL) return '\0';
        PTR=*HEAD;
        a=PTR->c;
        *HEAD=PTR->next;
        free(PTR);
        return a;
    }
    int priorityOperation(char a)
    {
        switch(a)
        {
            case '*':
            case '/':
                return 3;
            case '-':
            case '+':
                return 2;
            case '(':
                return 1;
        }
    }
/////////////////////////////////////
template <typename T>
class Queue
{
private:
    T* p; // динамический массив
    int count; // количество элементов в очереди

public:
    // конструктор по умолчанию
    Queue()
    {
        count = 0; // очередь пустая
    }

    // конструктор копирования
    Queue(const Queue& obj)
    {
        // скопировать obj в текущий объект
        count = obj.count;

        try {
            // попытка выделить память для p
            p = new T[count];
            // заполнить значениями
            for (int i = 0; i < count; i++)
                p[i] = obj.p[i];
        }
        catch (bad_alloc e)
        {
            // если память не выделена, то вывести текст ошибки
            cout << e.what() << endl;
            count = 0; // создать пустую очередь
        }
    }

    // добавить элемент в очередь
    void push(T item)
    {
        T* p2; // объявить дополнительный указатель
        p2 = p; // перенаправить дополнительный указатель на p

        try {
            // попытка выделить новый фрагмент памяти для p, но на 1 больше
            p = new T[count + 1];

            // скопировать данные из участка на который указывает p2 (старые данные)
            // в участок, на который указывает p
            for (int i = 0; i < count; i++)
                p[i] = p2[i];

            // скопировать последний элемент
            p[count] = item;

            // увеличить количество элементов на 1
            count++;

            // освободить предварительно выделенную память
            if (count > 1)
                delete[] p2;
        }
        catch (bad_alloc e)
        {
            // если память не выделена
            cout << e.what() << endl; // вывести сообщение об ошибке

            // вернуть старый указатель на p
            p = p2;
        }
    }

    // вытянуть первый элемент из очереди
    T pop()
    {
        if (count == 0)
            return 0;

        // заполнить элемент, который вытягивается из очереди
        T item;

        item = p[0];

        // сформировать новый участок памяти, который на 1 меньше
        try {
            T* p2;

            // попытка выделить пам'ять
            p2 = new T[count - 1];

            count--; // уменьшить количество элементов в очереди

            // p=>p2
            for (int i = 0; i < count; i++)
                p2[i] = p[i + 1]; // копируются все кроме первого элемента

            // освободить участок, на который указывает p
            if (count > 0)
                delete[] p;

            // перенаправить p на p2
            p = p2;

            // вернуть item
            return item;
        }
        catch (bad_alloc e)
        {
            // если память не выделилась, то вернуть 0
            cout << e.what() << endl;
            return 0;
        }
    }

    // операторная функция operator=(),
    // реализует присваивание объектов типа Queue
    Queue& operator=(const Queue& obj)
    {
        T* p2; // указатель на дополнительную память

        try {
            // попытка выделить новый участок памяти для p2
            p2 = new T[obj.count];

            // если память выделена успешно,
            // можно освобождать предварительно выделенную память для p
            if (count > 0)
                delete[] p;

            // скопировать obj в текущий объект
            p = p2; // перенаправить p на p2
            count = obj.count;

            // заполнить значениями
            for (int i = 0; i < count; i++)
                p[i] = obj.p[i];
        }
        catch (bad_alloc e)
        {
            // если память не выделилась, то вывести соответствующее сообщение
            cout << e.what() << endl;
        }
        return *this; // вернуть текущий объект
    }

    // деструктор
    ~Queue()
    {
        if (count > 0)
            delete[] p;
    }

    // взять первый элемент из очереди не вытягивая его
    T GetItem()
    {
        if (count > 0)
            return p[0];
        else
            return 0;
    }

    // очистка очереди
    void clear()
    {
        if (count > 0)
        {
            delete[] p;
            count = 0;
        }
    }

    bool IsEmpty()
    {
        return count == 0;
    }

    // количество элементов в очереди
    int GetN()
    {
        return count;
    }

    // метод, выводящий очередь
    void print(const char* objName)
    {
        cout << "Object: " << objName << endl;
        for (int i = 0; i < count; i++)
            cout << p[i] << "\t";
        cout << endl;
    }

    void queueStart(Queue Q1){
        bool chec=true;
        do {
            int num=0;
            cout<<"Select options :\n"<<"1 - Enter element\n"<<"2 - Return first\n"<<"3 - Return size\n"<<"4 - Print queue\n"<<"5 - Delete queue\n";
            cin>>num;
            switch (num){
                case 0:{
                    chec= false;
                    break;
                }
                case 1:{
                    int a;
                    cin>>a;
                    cout<<"\n";
                    Q1.push(a);
                    break;
                }
                case 2:{
                    int d=Q1.GetItem();
                    cout<<d;
                    cout<<"\n";
                    break;
                }
                case 3:{
                    cout<<Q1.GetN();
                    cout<<"\n";
                    break;
                }
                case 4:{
                    Q1.print("Q1");
                    cout<<"\n";
                    break;
                }
                case 5:{
                    Q1.clear();
                    cout<<"\n";
                    break;
                }
            }
        }while(chec!= false);
    }
};
struct Node                           //или просто Звено списка
    {
       int x;                           //инфо данные структуры
       Node *Next;                      //Указатель не следующее звено
    };

//КЛАСС СПИСОК

class List
{
    Node *Head, *Tail;                  //Указатели на начало списка и на конец
public:
     List():Head(NULL),Tail(NULL){};    //Инициализация указателей как пустых
     ~List();                           //Деструктор для освобождения памяти от всего что будет
     void Add(int x);                   //Функция заполнения структуры Node и добавления её в список как элемента
     void Show();                       //Функция отображения списка List
     void del();
     int showFirst();//Функция изъятия элемента
     void deleteList();

 };
 int size=0;

List::~List() //ДЕСТРУКТОР ДЛЯ ОЧИСТКИ ПАМЯТИ
{
 Node *temp = Head;                     //Временный указатель на начало списка
 while (temp != NULL)                   //Пока в списке что-то есть

   {
     temp = Head->Next;                 //Резерв адреса на следующий элемент списка

     delete Head;                       //Освобождение памяти от первой структуры как элемента списка

     Head = temp;                       //Сдвиг начала на следующий адрес, который берем из резерва

   }
}


//ФУНКЦИЯ ЗАПОЛНЕНИЯ ИНФОРМАЦИОННЫХ ПОЛЕЙ СТРУКТУРЫ NODE И ДОБАВЛЕНИЯ ЭТОЙ СТРУКТУРЫ В СПИСОК

void List::Add(int x)
{
    Node *temp = new Node;              //Выделение памяти для нового звена списка
    temp->x = x;                        //Временное запоминание принятого параметра x
    size++;
    temp->Next = NULL;                  //Указание, что следующее звено новосозданной структуры пока пустое

    if (Head != NULL)                   //Если список не пуст
    {
        Tail->Next = temp;              //Указание, что следующее звено списка это новосозданная структура
        Tail = temp;
    }     else Head = Tail = temp;      //Если список не пуст, добавление первого элемента
}

//ФУНКЦИЯ ОТОБРАЖЕНИЯ СПИСКА НА ЭКРАНЕ
void List::Show()
{
    Node *temp = Head;                  //Временный указатель на начало списка
     while (temp != NULL)               //Пока в списке что-то встречается
     {
         cout << temp->x << " ";        //Выводим значения из списка на экран
         temp = temp->Next;             //Сдвигаем указатель на начало на адрес следующего элемента
     }
    cout << endl;
}

void List::deleteList(){
    while(Head!=NULL){
        Head=Head->Next;
        size--;
    }
}

//ФУНКЦИЯ ИЗЪЯТИЯ ЭЛЕМЕНТА ИЗ ОЧЕРЕДИ
void List::del()
{
    if (Head != NULL)                   //Если список не пустой
    {
        Node *temp = Head;              //Обращаемся к началу списка с помощью вспомогательного указателя
        //cout <<  Head->x << endl;
        Head = Head->Next;              //Сдвиг начала списка
        size--;
        delete temp;                    //Освобождение памяти от предыдущего звена списка
    }
}

int List::showFirst(){
    if(Head !=NULL){
        return Head->x;
    }
}
void listQueue(){
    bool chec=true;
    List Que;
    do {
        int num=0;
        cout<<"Select options :\n"<<"1 - Enter element\n"<<"2 - Return first\n"<<"3 - Return size\n"<<"4 - Print queue\n"<<"5 - Delete queue\n";
        cin>>num;
        switch (num){
            case 0:{
                chec= false;
                break;
            }
            case 1:{
                int a;
                cin>>a;
                cout<<"\n";
                Que.Add(a);
                break;
            }
            case 2:{
                int d=Que.showFirst();
                cout<<d;
                cout<<"\n";
                break;
            }
            case 3:{
                cout<<size;
                cout<<"\n";
                break;
            }
            case 4:{
                Que.Show();
                cout<<"\n";
                break;
            }
            case 5:{
                Que.deleteList();
                cout<<"\n";
                break;
            }
        }
    }while(chec!= false);
}
//////////////////////////////////////////////////////////////////////////
/////////////

/////////////////////
int main() {
    cout<<"Practical work 1.Group IKBO-10-19.Gluchov Vladimir"<<endl;
    Queue<int> Q1;
    Q1.queueStart(Q1);
    listQueue();
    writeQueue();
    return 0;
}
