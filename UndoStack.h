#pragma once
#include "Student.h"
#include <iostream>
using namespace std;
struct Action
{
    int kind;
    Student before,after;
}
;
class UndoStack
{
    struct Node
    {
        Action a;
        Node*next;
        Node(const Action&x,Node*n):a(x),next(n)
        {
        }
    }
    ;
    Node*top=nullptr;
    public:UndoStack()=default;
    UndoStack(const UndoStack&)=delete;
    UndoStack&operator=(const UndoStack&)=delete;
    ~UndoStack()
    {
        Action a;
        while(pop(a))
        {
        }
    }
    void push(const Action&a)
    {
        top=new Node(a,top);
    }
    bool pop(Action&a)
    {
        if(!top)return false;
        Node*n=top;
        a=n->a;
        top=n->next;
        delete n;
        return true;
    }
    void show()const
    {
        for(Node*n=top;n;n=n->next)cout<<"Action "<<n->a.kind<<" on ID "<<n->a.before.id<<'\n';
    }
    void peek()const
    {
        if(top)cout<<"Latest action type: "<<top->a.kind<<" ID "<<top->a.before.id<<'\n';
        else cout<<"History empty.\n";
    }
}
;
