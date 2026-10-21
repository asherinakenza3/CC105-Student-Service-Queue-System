#pragma once
#include <iostream>
using namespace std;
class ServiceQueue
{
    struct Node
    {
        int id,priority;
        Node*next;
        Node(int i,int p):id(i),priority(p),next(nullptr)
        {
        }
    }
    ;
    Node*front=nullptr,*back=nullptr;
    bool prioritized;
    public:explicit ServiceQueue(bool p):prioritized(p)
    {
    }
    ServiceQueue(const ServiceQueue&)=delete;
    ServiceQueue&operator=(const ServiceQueue&)=delete;
    ~ServiceQueue()
    {
        int x;
        while(dequeue(x))
        {
        }
    }
    bool contains(int id)const
    {
        for(Node*n=front;n;n=n->next)if(n->id==id)return true;
        return false;
    }
    bool erase(int id)
    {
        Node*prev=nullptr;
        Node*n=front;
        while(n&&n->id!=id)
        {
            prev=n;
            n=n->next;
        }
        if(!n)return false;
        if(prev)prev->next=n->next;
        else front=n->next;
        if(back==n)back=prev;
        delete n;
        return true;
    }
    void enqueue(int id,int priority)
    {
        Node*n=new Node(id,priority);
        if(prioritized&&front&&priority>front->priority)
        {
            n->next=front;
            front=n;
            return;
        }
        if(prioritized)
        {
            Node*p=front;
            while(p&&p->next&&p->next->priority>=priority)p=p->next;
            if(p)
            {
                n->next=p->next;
                p->next=n;
                if(!n->next)back=n;
                return;
            }
        }
        if(back)back->next=n;
        else front=n;
        back=n;
    }
    bool dequeue(int&x)
    {
        if(!front)return false;
        Node*n=front;
        x=n->id;
        front=n->next;
        if(!front)back=nullptr;
        delete n;
        return true;
    }
    void peek()const
    {
        if(front)cout<<"Next student: "<<front->id<<'\n';
        else cout<<"Queue empty.\n";
    }
    void show()const
    {
        for(Node*n=front;n;n=n->next)cout<<n->id<<" (priority "<<n->priority<<") -> ";
        cout<<"END\n";
    }
}
;
