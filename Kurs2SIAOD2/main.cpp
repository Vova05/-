#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>
#include <stack>
#include <queue>

struct Node {
    int data;
    int height;
    std::unique_ptr<Node> left = nullptr;
    std::unique_ptr<Node> right = nullptr;

    Node(const int& x, const int& y, std::unique_ptr<Node>&& p = nullptr, std::unique_ptr<Node>&& q = nullptr) :
            data(x),
            height(y),
            left(std::move(p)),
            right(std::move(q)) {}

    Node(const int& data) : data(data), height(1) {}

};
std::unique_ptr<Node> root = nullptr;
class Meaw{
public:
int height(std::unique_ptr<Node>& root) {
    if (!root) return 0;
    return root->height;
}

void rightRotate(std::unique_ptr<Node>& y) {
    std::unique_ptr<Node> x = std::move(y->left);
    std::unique_ptr<Node> T2 = std::move(x->right);


    x->right = std::move(y);
    x->right->left = std::move(T2);

// Задаем новую высоту
    x->right->height = std::max(height(x->right->left), height(x->right->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y = std::move(x);
}

void leftRotate(std::unique_ptr<Node>& x) {
    std::unique_ptr<Node> y = std::move(x->right);
    std::unique_ptr<Node> T2 = std::move(y->left);

    y->left = std::move(x);
    y->left->right = std::move(T2);

// Задаем новую высоту
    y->left->height = std::max(height(y->left->left), height(y->left->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x = std::move(y);

}

int heightDiff(std::unique_ptr<Node>& root) {
    if (!root) return 0;

    return height(root->left) - height(root->right);
}

void insert(std::unique_ptr<Node>& root, const int& theData) {
    std::unique_ptr<Node> newNode = std::make_unique<Node>(theData);
// BST
    if (root == nullptr) {
        root = std::move(newNode);
        return;
    }

    else if (theData < root->data) {
        insert(root->left, theData);
    }

    else {
        insert(root->right, theData);
    }

    root->height = 1 + std::max(height(root->left), height(root->right));

// узнаем балансировку
    int balance = heightDiff(root);

// Левый кейс с лева
    if (balance > 1 && root->left && theData < root->left->data)
        rightRotate(root);

// правый кейс с права
    if (balance < -1 && root->right && theData > root->right->data)
        leftRotate(root);

// левый кейс с права
    if (balance > 1 && root->left && theData > root->left->data) {
        leftRotate(root->left);
        rightRotate(root);
    }

// правый кейс с лева
    if (balance < -1 && root->right && theData < root->right->data) {
        rightRotate(root->right);
        leftRotate(root);
    }
}

auto findMin(std::unique_ptr<Node>& root) {
    while (root->left != nullptr) root = std::move(root->left);
    return root.get();
}

void deleteNode(std::unique_ptr<Node>& root, const int& theData) {

    if (!root) return;
    else if (theData < root->data) deleteNode(root->left, theData);
    else if (theData > root->data) deleteNode(root->right, theData);

    else {
// Case 1: нет наследников
        if (root->left == nullptr && root->right == nullptr) {
            root = nullptr;
        }

// Case 2: один наследник
        else if (root->left == nullptr) {
            root = std::move(root->left);
        }

        else if (root->right == nullptr) {
            root = std::move(root->right);
        }

// Case 3: два наследника
        else {
            auto temp = findMin(root->right);
            temp->data = root->data;
            deleteNode(root->right, temp->data);
        }
    }
    root->height = 1 + std::max(height(root->left), height(root->right));

    int balance = heightDiff(root);

    if (balance > 1 && heightDiff(root->left) >= 0)
        rightRotate(root);

    if (balance > 1 && heightDiff(root->left) < 0) {
        leftRotate(root->left);
        rightRotate(root);
    }

    if (balance < -1 && heightDiff(root->right) <= 0)
        leftRotate(root);

    if (balance < -1 && heightDiff(root->right) > 0) {
        rightRotate(root->right);
        leftRotate(root);
    }
}

void inorderTraversal(std::unique_ptr<Node>& root) {
    if (!root) {
        inorderTraversal(root->left);
        std::cout << root->data << " ";
        inorderTraversal(root->right);
    }
}
int a=0;
//возвращает сумму элементов дерева
int ReturnSum(std::unique_ptr<Node>& root){
    if (root) {
        ReturnSum(root->left);
        a+= root->data;
        ReturnSum(root->right);
    }
    return a;
}
//
void preorderTraversal(std::unique_ptr<Node>& root) {
    if (root != nullptr) {
        std::cout << root->data << " ";
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void postorderTraversal(std::unique_ptr<Node>& root) {
    if (root != nullptr) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        std::cout << root->data << " ";
    }
}

void DFS(std::unique_ptr<Node>& root) {
    if (!root) return;

    std::stack<Node const *> s;
    s.push(root.get());

    while (!s.empty()) {
        auto p = s.top();
        s.pop();

        if (p->right != nullptr) s.push(p->right.get());
        if (p->left != nullptr) s.push(p->left.get());

        std::cout << p->data << " ";
    }
}

void BFS(std::unique_ptr<Node>& root) {
    if (!root) return;

    std::queue<Node const *> q;
    q.push(root.get());

    while (!q.empty()) {
        auto p = q.front();
        q.pop();

        if (p->left != nullptr) q.push(p->left.get());
        if (p->right != nullptr) q.push(p->right.get());

        std::cout << p->data << " ";
    }
}

bool exists(int d) {
    auto temp = root.get();
    while (temp != nullptr) {
        if (temp->data == d) {
            return true;
        }
        else {
            if (d > temp->data) {
                temp = temp->right.get();
            }
            else {
                temp = temp->left.get();
            }
        }
    }
    return false;
}
};
using namespace std;
int main() {
    cout<<"Practical work 2.Group IKBO-10-19.Gluchov Vladimir"<<endl;
    bool chec=true;
   while(chec==true){
       cout<<"Selected operating mode:\n"<<"0. End of work.\n"<<"1. Build tree.\n"<<"2. Add item.\n"<<"3. Print preorder traversal.\n"
       <<"4. Print postorder traversal.\n"<<"5. Print DFS."<<"6. Print BFS.\n"<<"7. Print the sum of elements\n"
       <<"8. Print height tree\n";
       int num=0;
       cin>>num;
       Meaw obj;
       switch(num){
           case 0:{
               chec=false;
               break;
           }
           case 1:{
               while(true) {
                   int a = 0;
                   cout << "Enter " << endl;
                   cin >> a;
                   obj.insert(root, a);
                   cout << "Next y/n" << endl;
                   char s = ' ';
                   cin >> s;
                   if (s == 'n') {
                       break;
                   }
               }
               break;
           }
           case 2 :{
               int tmp;
               cin>>tmp;
               obj.insert(root,tmp);
               break;
           }
           case 3:{
               cout << "\n";
               cout<<"Preorder traversal : ";
               obj.preorderTraversal(root);
               break;
           }
           case 4:{
               cout << "\n";
               cout<<"Postorder traversal : ";
               obj.postorderTraversal(root);
               break;
           }
           case 5:{
               cout << "\n";
               cout<<"DFS : ";
               obj.DFS(root);
               break;
           }
           case 6:{
               cout << "\n";
               cout<<"BFS : ";
               obj.BFS(root);
               break;
           }
           case 7:{
               cout << "\n";
               cout<<"Sum tree : ";
               obj.ReturnSum(root);
               cout<<obj.a<<"\n";
               break;
           }
           case 8:{
               cout<<"Height tree : ";
               cout<<root->height;
               cout<<"\n";
               break;
           }
       }
   }
   return 0;
}