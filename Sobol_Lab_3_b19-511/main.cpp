#include "Tests.h"
using namespace std;

int main()
{
    Test_Add();
    Test_Search();
    Test_Remove();
    Test_SaveString();
    Test_FirmWare();
    Test_SubTree();
    Test_SearchSubEntry();

    string str;
    std::cout << "\nIf you want to use - press \"e\", else - press \"p\"\n";
    cin >> str;
    if (str != "e")
    {
        std::cout << "\nGOODbye";
        return 0;
    }

    cout << endl;

    BinaryTree<int> *tree = new BinaryTree<int>("100#50#200#25#75#150#300#400#350#");
    /*tree->Add(100);
    tree->Add(50);
    tree->Add(200);
    tree->Add(25);
    tree->Add(75);
    tree->Add(150);
    tree->Add(300);
    tree->Add(400);
    tree->Add(350);*/
    cout << "THE TREE: " << endl;
    tree->Print();

    do
    {
        system("color 7");
        try
        {
            char fun;

            cout << "\nEnter: 1 - Add, 2 - Search, 3 - Remove, 4 - SaveString, 5 - SubTree 6 - CheckSubTreeEntry 7 - SaveString_Mine\n";
            cin >> fun;

            switch (fun)
            {
            case '1':
            {
                int add = 175;
                tree->Add(add);
                cout << "Add: " << add << endl;
                tree->Print();
            }
            break;
            case '2':
            {
                int search = 300;
                cout << "Search: " << search << endl;
                cout << tree->Search(search) << endl;
            }
            break;
            case '3':
            {
                Node<int>* remove = tree->head;
                cout << "Remove: " << remove->Data << endl;
                tree->Remove(remove);
                tree->Print();
            }
            break;
            case '4':
            {
                string str_travers = "NLR";
                cout << "SaveString: str_travers - " << str_travers << endl;
                cout << tree->SaveString(str_travers) << endl;
            }
            break;
            case '5':
            {
                Node<int>* root = tree->head->RightNode->RightNode;
                cout << "SubTree: root - " << root->Data << endl;
                BinaryTree<int> *subtree = tree->SubTree(root);
                cout << "SubTree: " << endl;
                subtree->Print();
                cout << "Now Tree: " << endl;
                tree->Print();
            }
            break;
            case '6':
            {
                BinaryTree<int> *subtree = new BinaryTree<int>("100#50#200#300#400#");
                cout << "SubTree: " << endl;
                subtree->Print();
                cout << "Entry: " << tree->SearchSubEntry(subtree) << endl;
            }
            break;
            case '7':
            {
                cout << "SaveString_Mine:(Record by levels, the same tree is recreated in the same order)  - " << endl;
                cout << tree->SaveString_For_Me(); // Дерево обходится по уровням - в том же порядке записи его можно воссоздать(в отличии от обходов "Корень", "Лево", "Право");
            }
            break;
            }
        }
        catch (exception ex)
        {
            system("color 4");
            std::cout << "\n" << "ERROR !!!";
            std::cout << "\n" << ex.what() << endl;
        }

        std::cout << "\nIf you want to exit - press \"e\", else - press \"p\"" << endl;

        std::cin >> str;

    } while (str != "e");

    delete tree;

    std::cout << "\nGOODbye" << endl;
}
