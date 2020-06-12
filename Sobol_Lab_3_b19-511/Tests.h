#pragma once

#include "BinaryTree.h"

void Test_Add()
{
    BinaryTree<int> *tree = new BinaryTree<int>();
    tree->Add(100);
    tree->Add(10);
    tree->Add(200);
    tree->Add(500);
    tree->Add(0);
    tree->Add(3333);
    tree->Add(100);
    if (tree->SaveString_For_Me() == "100#10#200#0#100#500#3333#")
    {
        cout << "Test_Add: GOOD" << endl;
    }
    else
    {
        cout << "Test_Add: FAIL" << endl;
    }
    delete tree;
}
void Test_Search()
{
    BinaryTree<int> *tree = new BinaryTree<int>();
    tree->Add(100);
    tree->Add(10);
    tree->Add(200);
    tree->Add(500);
    tree->Add(0);
    tree->Add(3333);
    tree->Add(100);
    Node<int> *node = tree->Search(500);
    if (node->Data == 500)
    {
        cout << "Test_Search: GOOD" << endl;
    }
    else
    {
        cout << "Test_Search: FAIL" << endl;
    }
    delete tree;
}

void Test_Remove()
{
    BinaryTree<int> *tree = new BinaryTree<int>();
    tree->Add(100);
    tree->Add(10);
    tree->Add(200);
    tree->Add(500);
    tree->Add(0);
    tree->Add(3333);
    tree->Add(100);
    tree->Remove(tree->head);
    if (tree->SaveString_For_Me() == "10#0#200#100#500#3333#")
    {
        cout << "Test_Remove: GOOD" << endl;
    }
    else
    {
        cout << "Test_Remove: FAIL" << endl;
    }
    delete tree;
}

void Test_SaveString()
{
    BinaryTree<int> *tree = new BinaryTree<int>();
    tree->Add(100);
    tree->Add(10);
    tree->Add(200);
    tree->Add(500);
    tree->Add(0);
    tree->Add(3333);
    tree->Add(100);
    string str = tree->SaveString("LRN");
    if (str == "0#10#100#3333#500#200#100#")
    {
        cout << "Test_SaveString: GOOD" << endl;
    }
    else
    {
        cout << "Test_SaveString: FAIL" << endl;
    }
    delete tree;
}

void Test_FirmWare()
{
    BinaryTree<int> *tree = new BinaryTree<int>();
    tree->Add(100);
    tree->Add(10);
    tree->Add(200);
    tree->Add(500);
    tree->Add(0);
    tree->Add(3333);
    tree->Add(100);
    tree->Firmware("LRN");
    string str = "";
    Node<int>* tmp = tree->start_FlashNode;
    while (tmp != nullptr)
    {
        str = str + to_string(tmp->Data) + "#";
        tmp = tmp->FlashNode;
    }

    if (str == "0#10#100#3333#500#200#100#")
    {
        cout << "Test_FirmWare: GOOD" << endl;
    }
    else
    {
        cout << "Test_FrimWare: FAIL" << endl;
    }
    delete tree;
}

void Test_SubTree()
{
    BinaryTree<int> *tree = new BinaryTree<int>();
    tree->Add(100);
    tree->Add(10);
    tree->Add(200);
    tree->Add(500);
    tree->Add(0);
    tree->Add(3333);
    tree->Add(100);
    BinaryTree<int> *subtree = tree->SubTree(tree->head->RightNode);
    if (tree->SaveString_For_Me() == "100#10#0#" && subtree->SaveString_For_Me() == "200#100#500#3333#")
    {
        cout << "Test_SubTree: GOOD" << endl;
    }
    else
    {
        cout << "Test_SubTree: FAIL" << endl;
    }
    delete tree;
}

void Test_SearchSubEntry()
{
    BinaryTree<int> *tree = new BinaryTree<int>();
    tree->Add(100);
    tree->Add(10);
    tree->Add(200);
    tree->Add(500);
    tree->Add(0);
    tree->Add(3333);
    tree->Add(100);
    BinaryTree<int> *subtree = new BinaryTree<int>();
    subtree->Add(100);
    subtree->Add(200);
    subtree->Add(500);
    subtree->Add(3333);
    if (tree->SearchSubEntry(subtree))
    {
        cout << "Test_SearchSubEntry: GOOD" << endl;
    }
    else
    {
        cout << "Test_SearchSubEntry: FAIL" << endl;
    }
    delete tree;
    delete subtree;
}