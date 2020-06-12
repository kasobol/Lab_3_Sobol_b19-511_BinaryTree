#pragma once

#include <exception>
#include <complex>

#include "BinPrint.h"

using namespace std;

bool operator <(const complex<double> a1, const complex<double> a2)
{
    if (a1.real() * a1.real() + a1.imag() * a1.imag() < a2.real() * a2.real() + a2.imag() * a2.imag())
    {
        return true;
    }
    return false;
}

string to_string(complex<double> a)
{
    return "(" + to_string(a.real()) + "," + to_string(a.imag()) + ")";
}
string to_string(string str)
{
    return str;
}

template<class T>
struct Node
{
    Node(T Data, Node* LeftNode, Node* RightNode, Node* PrevNode)
    {
        this->Data = Data;
        this->LeftNode = LeftNode;
        this->RightNode = RightNode;
        this->PrevNode = PrevNode;
    }
    T Data;
    Node* LeftNode;
    Node* RightNode;
    Node* PrevNode;

    Node* FlashNode;
    ~Node()
    {
        delete LeftNode;
        delete RightNode;
    }
    
};

template<class T>
struct List
{
    List(Node<T>* Data, List* Next)
    {
        this->Data = Data;
        this->Next = Next;
    }
    Node<T>* Data;
    List<T>* Next;
    ~List()
    {
        delete Next;
    }
};

template<class T>
class BinaryTree
{
public:
    Node<T>* head;

    BinaryTree()
    {
        head = nullptr;
    }

    BinaryTree(string str)
    {
        int j = 0;
        
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == '#')
            {
                T a;
                string b = str.substr(j, i - j);
                stringstream ss(b);
                ss >> a;
                Add(a);
                j = i + 1;
            }
        }
    }

    void Print()
    {
        BinTree<T> *tree_print = new BinTree<T>(SaveString_For_Me());
        tree_print->Dump();
        delete tree_print;
    }

    void Add(T elem)
    {
        if (head == nullptr)
        {
            head = new Node<T>(elem, nullptr, nullptr, nullptr);
            return;
        }
        Add(elem, head, head);
    }

    void Add(T elem, Node<T>* &tmp, Node<T>* &tmp_prev)
    {
        if (tmp == nullptr)
        {
            tmp = new Node<T>(elem, nullptr, nullptr, tmp_prev);
            return;
        }
        if (elem < tmp->Data)
        {
            Add(elem, tmp->LeftNode, tmp);
        }
        else
        {
            Add(elem, tmp->RightNode, tmp);
        }
    }

    void NLR(void(*Func)(Node<T>*), Node<T>* tmp)
    {
        if (tmp != nullptr)
        {
            Func(tmp);
            NLR(Func, tmp->LeftNode);
            NLR(Func, tmp->RightNode);
        }
    }
    void NRL(void(*Func)(Node<T>*), Node<T>* tmp)
    {
        if (tmp != nullptr)
        {
            Func(tmp);
            NRL(Func, tmp->RightNode);
            NRL(Func, tmp->LeftNode);
        }
    }
    void LRN(void(*Func)(Node<T>*), Node<T>* tmp)
    {
        if (tmp != nullptr)
        {
            LRN(Func, tmp->LeftNode);
            LRN(Func, tmp->RightNode);
            Func(tmp);
        }
    }
    void LNR(void(*Func)(Node<T>*), Node<T>* tmp)
    {
        if (tmp != nullptr)
        {
            LNR(Func, tmp->LeftNode);
            Func(tmp);
            LNR(Func, tmp->RightNode);
        }
    }
    void RLN(void(*Func)(Node<T>*), Node<T>* tmp)
    {
        if (tmp != nullptr)
        {
            RLN(Func, tmp->RightNode);
            RLN(Func, tmp->LeftNode);
            Func(tmp);
        }
    }
    void RNL(void(*Func)(Node<T>*), Node<T>* tmp)
    {
        if (tmp != nullptr)
        {
            RNL(Func, tmp->RightNode);
            Func(tmp);
            RNL(Func, tmp->LeftNode);
        }
    }

    void Travers(void(*Func)(Node<T>*), string travers_name)
    {
        if (travers_name == "NLR")
        {
            NLR(Func, head);
        }
        else if (travers_name == "NRL")
        {
            NRL(Func, head);
        }
        else if (travers_name == "LRN")
        {
            LRN(Func, head);
        }
        else if (travers_name == "LNR")
        {
            LNR(Func, head);
        }
        else if (travers_name == "RLN")
        {
            RLN(Func, head);
        }
        else if (travers_name == "RNL")
        {
            RLN(Func, head);
        }
        else
        {
            throw exception("Name of travers is WRONG");
        }
    }

    static T elem_search;
    static Node<T>* Search_Node;
    static void Func_Search(Node<T>* tmp)
    {
        if (tmp != nullptr && elem_search == tmp->Data)
        {
            Search_Node = tmp;
            throw exception();
        }
    }
    Node<T>* Search(T elem)
    {
        elem_search = elem;
        try
        {
            NLR(Func_Search, head);
            return nullptr;
        }
        catch (exception ex)
        {
            return Search_Node;
        }
    }

    void Remove(Node<T>* tmp)
    {
        if (tmp == nullptr)
        {
            throw exception("The tree is empty");
        }
        if (tmp->LeftNode == nullptr && tmp->RightNode == nullptr)
        {
            if (tmp->PrevNode->LeftNode == tmp)
            {
                tmp->PrevNode->LeftNode = nullptr;
            }
            else
            {
                tmp->PrevNode->RightNode = nullptr;
            }
            delete tmp;
        }
        else if (tmp->LeftNode != nullptr && tmp->RightNode == nullptr)
        {
            if (tmp->PrevNode == nullptr)
            {
                head = tmp->LeftNode;
                head->PrevNode = nullptr;
                tmp->LeftNode = nullptr;
                delete tmp;
                return;
            }
            Node<T>* help = tmp->PrevNode;
            if (help->LeftNode == tmp)
            {
                help->LeftNode = tmp->LeftNode;
            }
            else
            {
                help->RightNode = tmp->LeftNode;
            }
            tmp->LeftNode->PrevNode = help;
            tmp->LeftNode = nullptr;
            delete tmp;
        }
        else if (tmp->LeftNode == nullptr && tmp->RightNode != nullptr)
        {
            if (tmp->PrevNode == nullptr)
            {
                head = tmp->RightNode;
                head->PrevNode = nullptr;
                tmp->RightNode = nullptr;
                delete tmp;
                return;
            }
            Node<T>* help = tmp->PrevNode;
            if (help->LeftNode == tmp)
            {
                help->LeftNode = tmp->RightNode;
            }
            else
            {
                help->RightNode = tmp->RightNode;
            }
            tmp->RightNode->PrevNode = help;
            tmp->RightNode = nullptr;
            delete tmp;
        }
        else
        {
            Node<T>* node = tmp->LeftNode;
            if (node->RightNode == nullptr)
            {
                tmp->Data = node->Data;
                tmp->LeftNode = node->LeftNode;
                node->LeftNode = nullptr;
                delete node;
            }
            else
            {
                while (node->RightNode != nullptr)
                {
                    node = node->RightNode;
                }
                tmp->Data = node->Data;
                if (node->PrevNode->LeftNode == node)
                {
                    node->PrevNode->LeftNode = nullptr;
                }
                else
                {
                    node->PrevNode->RightNode = nullptr;
                }
            }
        }
    }

    string SaveString_For_Me()
    {
        List<T> *head;
        Node<T>* pointer = this->head;
        head = new List<T>(pointer, nullptr);
        List<T>* tmp = head;
        List<T>* tmp_2 = head;
        while (true)
        {
            if (pointer->LeftNode != nullptr)
            {
                tmp->Next = new List<T>(pointer->LeftNode, nullptr);
                tmp = tmp->Next;
            }
            if (pointer->RightNode != nullptr)
            {
                tmp->Next = new List<T>(pointer->RightNode, nullptr);
                tmp = tmp->Next;
            }
            tmp_2 = tmp_2->Next;
            if (tmp_2 == nullptr)
            {
                break;
            }
            pointer = tmp_2->Data;
        }
        tmp = head;
        string str = "";
        while (tmp != nullptr)
        {
            str = str + to_string(tmp->Data->Data) + "#";
            tmp = tmp->Next;
        }
        delete head;
        return str;
    }

    static string save_string;
    static void Func_SaveString(Node<T>* tmp)
    {
        save_string = save_string + to_string(tmp->Data) + "#";
    }
    string SaveString()
    {
        save_string = "";
        NLR(Func_SaveString, head);
        return save_string;
    }
    string SaveString(string travers_str)
    {
        save_string = "";
        Travers(Func_SaveString, travers_str);
        return save_string;
    }

    static bool Flag;
    static Node<T>* start_FlashNode;
    static Node<T>* FlashNode_;
    static void Func_Firmware(Node<T>* tmp)
    {
        if (Flag)
        {
            if (tmp->LeftNode == nullptr && tmp->RightNode == nullptr || tmp->PrevNode == nullptr)
            {
                FlashNode_ = tmp;
                start_FlashNode = FlashNode_;
                Flag = false;
            }
        }
        tmp->FlashNode = FlashNode_;
        FlashNode_ = tmp;
    }
    void Reverse()
    {
        Node<T>* prev = FlashNode_;
        Node<T>* pointer = prev;
        Node<T>* help = pointer->FlashNode;
        pointer->FlashNode = nullptr;
        pointer = help;

        while (pointer != pointer->FlashNode)
        {
            help = pointer->FlashNode;
            pointer->FlashNode = prev;
            prev = pointer;
            pointer = help;
        }
        pointer->FlashNode = prev;
    }
    Node<T>* Firmware()
    {
        Flag = true;
        FlashNode_ = head;
        NLR(Func_Firmware, head);
        Reverse();
        return start_FlashNode;
    }
    Node<T>* Firmware(string str)
    {
        Flag = true;
        FlashNode_ = head;
        Travers(Func_Firmware, str);
        Reverse();
        return start_FlashNode;
    }

    BinaryTree<T>* SubTree(Node<T>* root)
    {
        BinaryTree<T> *tree = new BinaryTree<T>();
        tree->head = root;
        if (root->PrevNode == nullptr)
        {
            return tree;
        }
        if (root->PrevNode->LeftNode == root)
        {
            root->PrevNode->LeftNode = nullptr;
        }
        else
        {
            root->PrevNode->RightNode = nullptr;
        }
        return tree;
    }

    static Node<T>* root;
    static List<T> *list_head;
    static List<T> *list_tmp;
    static void Func_SearchSubEntry(Node<T>* tmp)
    {
        if (tmp->Data == root->Data)
        {
            if (list_head == nullptr)
            {
                list_head = new List<T>(tmp, nullptr);
                list_tmp = list_head;
            }
            else
            {
                list_tmp->Next = new List<T>(tmp, nullptr);
                list_tmp = list_tmp->Next;
            }
        }
    }
    void Check_SearchSubEntry(Node<T>* tmp_tree, Node<T>* tmp_undertree)
    {
        if (tmp_undertree != nullptr)
        {
            if (tmp_tree == nullptr || tmp_tree->Data != tmp_undertree->Data)
            {
                throw exception();
            }
            else
            {
                Check_SearchSubEntry(tmp_tree->LeftNode, tmp_undertree->LeftNode);
                Check_SearchSubEntry(tmp_tree->RightNode, tmp_undertree->RightNode);
            }
        }
        else
        {
            return;
        }
    }
    bool SearchSubEntry(BinaryTree<T>* tree)
    {
        root = tree->head;
        list_head = nullptr;
        if (root == nullptr)
        {
            return true;
        }
        NLR(Func_SearchSubEntry, head);
        List<T> *tmp = list_head;
        while (tmp != nullptr)
        {
            try
            {
                Check_SearchSubEntry(tmp->Data, tree->head);
                return true;
            }
            catch (exception ex)
            {
            }
            tmp = tmp->Next;
        }
        return false;
    }
    ~BinaryTree()
    {
        delete head;
    }

    /*void Func_MyBalance(Node<T>* tmp)
    {
        if (list_head == nullptr)
        {
            list_head = new List(tmp, nullptr);
            list_tmp = list_head;
        }
        else
        {
            list_tmp->Next = new List(tmp, nullptr);
            list_tmp = list_tmp->Next;
        }
    }*/
    //void My_Balance() // O(nlogn)
    //{
    //    list_head = nullptr;
    //    LNP(Func_MyBalance, head); // Отсортированный список
    //    if (list_head == nullptr)
    //    {
    //        throw exception("The tree is empty");
    //    }
    //    else
    //    {
    //        int count = 0;
    //        tmp = list_head;
    //        while (tmp != nullptr)
    //        {
    //            tmp = tmp->Next;
    //            count++;
    //        }
    //        tmp = list_head;
    //        for (int i = 0; i < count / 2; i++)
    //        {
    //            tmp = tmp->Next;
    //        }
    //    }
    //}
};

template<class T>
T BinaryTree<T>::elem_search;
template<class T>
Node<T>* BinaryTree<T>::Search_Node;
template<class T>
string BinaryTree<T>::save_string;
template<class T>
Node<T>* BinaryTree<T>::FlashNode_;
template<class T>
bool BinaryTree<T>::Flag;
template<class T>
Node<T>* BinaryTree<T>::start_FlashNode;
template<class T>
Node<T>* BinaryTree<T>::root;
template<class T>
List<T>* BinaryTree<T>::list_head;
template<class T>
List<T>* BinaryTree<T>::list_tmp;