#include "Registry.h"
#include "UndoStack.h"
#include "ServiceQueue.h"
#include "Algorithms.h"
#include "Benchmark.h"
#include "Input.h"
#include <iostream>
using namespace std;
Student inputStudent()
{
    Student s;
    s.id=number("Student ID (1-999999): ",1,999999);
    s.name=line("Full name: ");
    s.service=line("Service (Assessing/Clearance/Transcript): ");
    s.priority=number("Priority (0 regular, 1 graduating, 2 PWD/senior): ",0,2);
    return s;
}
int main()
{
    Registry registry;
    UndoStack history;
    ServiceQueue regular(false),priority(true);
    for(;;)
    {
        cout<<"\n=== UNIVERSITY STUDENT SERVICE & QUEUE SYSTEM ===\n1 Add student  2 Edit student  3 Delete student  4 List students\n5 Enqueue service  6 Process queue  7 View queues  8 Undo\n9 Search IDs  10 Sort records  11 Benchmark  12 History  0 Exit\n";
        int op=number("Choice: ",0,12);
        if(!op)break;
        if(op==1)
        {
            Student s=inputStudent();
            if(registry.add(s))
            {
                history.push(
                {
                    1,s,s
                }
                );
                cout<<"Added.\n";
            }
            else cout<<"Duplicate ID.\n";
        }
        else if(op==2)
        {
            int id=number("ID: ",1,999999);
            Student*p=registry.find(id);
            if(!p)
            {
                cout<<"Not found.\n";
                continue;
            }
            Student old=*p;
            p->name=line("New name: ");
            p->service=line("New service: ");
            p->priority=number("New priority (0-2): ",0,2);
            regular.erase(id);
            priority.erase(id);
            history.push(
            {
                2,old,*p
            }
            );
            cout<<"Updated (previous pending queue ticket, if any, removed; enqueue again).\n";
        }
        else if(op==3)
        {
            int id=number("ID: ",1,999999);
            Student old;
            if(registry.remove(id,old))
            {
                regular.erase(id);
                priority.erase(id);
                history.push(
                {
                    3,old,old
                }
                );
                cout<<"Deleted (pending tickets removed).\n";
            }
            else cout<<"Not found.\n";
        }
        else if(op==4)registry.display();
        else if(op==5)
        {
            int id=number("Student ID: ",1,999999);
            Student*p=registry.find(id);
            if(!p)
            {
                cout<<"Student not found.\n";
                continue;
            }
            if(regular.contains(id)||priority.contains(id))
            {
                cout<<"Student already queued.\n";
                continue;
            }
            if(p->priority)priority.enqueue(id,p->priority);
            else regular.enqueue(id,0);
            cout<<"Queued.\n";
        }
        else if(op==6)
        {
            int id;
            if(priority.dequeue(id)||regular.dequeue(id))cout<<"Serving student "<<id<<'\n';
            else cout<<"Both queues empty.\n";
        }
        else if(op==7)
        {
            cout<<"Priority: ";
            priority.show();
            cout<<"Regular: ";
            regular.show();
            cout<<"Next priority: ";
            priority.peek();
            cout<<"Next regular: ";
            regular.peek();
        }
        else if(op==8)
        {
            Action a;
            if(!history.pop(a))
            {
                cout<<"Nothing to undo.\n";
                continue;
            }
            if(a.kind==1)
            {
                Student old;
                registry.remove(a.before.id,old);
                regular.erase(a.before.id);
                priority.erase(a.before.id);
            }
            else if(a.kind==2)
            {
                Student*p=registry.find(a.before.id);
                if(p)*p=a.before;
                else cout<<"Record missing; update could not be restored.\n";
            }
            else if(!registry.add(a.before))cout<<"Could not restore deleted record.\n";
            cout<<"Undo processed (registry changes only; queue tickets are not restored).\n";
        }
        else if(op==9)
        {
            int n;
            Student*a=registry.snapshot(n);
            int id=number("Search ID: ",1,999999);
            long long c=0;
            int idx=linear(a,n,id,c);
            cout<<"Linear: "<<(idx>=0?"Found":"Not found")<<", comparisons="<<c<<'\n';
            Metrics m;
            insertion(a,n,1,m);
            c=0;
            idx=binary(a,n,id,c);
            cout<<"Binary (sorted copy): "<<(idx>=0?"Found":"Not found")<<", comparisons="<<c<<'\n';
            delete[]a;
        }
        else if(op==10)
        {
            int n;
            Student*a=registry.snapshot(n);
            int t=number("1 Bubble 2 Selection 3 Insertion: ",1,3);
            int field=number("Sort field: 1 ID, 2 Name, 3 Priority: ",1,3);
            Metrics m;
            sortRun(a,n,t,field,m);
            cout<<"Sorted records:\n";
            for(int i=0;i<n;i++)cout<<a[i].id<<" | "<<a[i].name<<" | priority "<<a[i].priority<<'\n';
            cout<<"Comparisons "<<m.comparisons<<" Swaps "<<m.swaps<<" Time(ms) "<<m.ms<<'\n';
            delete[]a;
        }
        else if(op==11)benchmark();
        else if(op==12)
        {
            history.peek();
            history.show();
        }
    }
}
