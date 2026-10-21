#pragma once
#include "Student.h"
#include <iostream>
#include <iomanip>
using namespace std;
class Registry
{
    struct Node
    {
        Student s;
        Node *prev,*next;
        explicit Node(const Student&v):s(v),prev(nullptr),next(nullptr)
        {
        }
    }
    ;
    Node *head=nullptr,*tail=nullptr;
    public:Registry()=default;
    Registry(const Registry&)=delete;
    Registry&operator=(const Registry&)=delete;
    ~Registry()
    {
        clear();
    }
    void clear()
    {
        while(head)
        {
            Node*n=head;
            head=head->next;
            delete n;
        }
        tail=nullptr;
    }
    bool add(const Student&s)
    {
        if(find(s.id))return false;
        Node*n=new Node(s);
        if(tail)
        {
            tail->next=n;
            n->prev=tail;
        }
        else head=n;
        tail=n;
        return true;
    }
    Student*find(int id)
    {
        for(Node*n=head;n;n=n->next)if(n->s.id==id)return &n->s;
        return nullptr;
    }
    bool remove(int id,Student&old)
    {
        for(Node*n=head;n;n=n->next)if(n->s.id==id)
        {
            old=n->s;
            if(n->prev)n->prev->next=n->next;
            else head=n->next;
            if(n->next)n->next->prev=n->prev;
            else tail=n->prev;
            delete n;
            return true;
        }
        return false;
    }
    void display()const
    {
        cout<<left<<setw(10)<<"ID"<<setw(25)<<"Name"<<setw(24)<<"Service"<<"Priority\n";
        for(Node*n=head;n;n=n->next)cout<<setw(10)<<n->s.id<<setw(25)<<n->s.name<<setw(24)<<n->s.service<<n->s.priority<<'\n';
    }
    int size()const
    {
        int c=0;
        for(Node*n=head;n;n=n->next)++c;
        return c;
    }
    Student* snapshot(int&n)const
    {
        n=size();
        Student*a=new Student[n];
        int i=0;
        for(Node*p=head;p;p=p->next)a[i++]=p->s;
        return a;
    }
}
;
