#pragma once
#include "Student.h"
struct Metrics
{
    long long comparisons=0,swaps=0;
    double ms=0;
}
;
int compareStudents(const Student&,const Student&,int);
void bubble(Student*,int,int,Metrics&);
void selection(Student*,int,int,Metrics&);
void insertion(Student*,int,int,Metrics&);
int linear(const Student*,int,int,long long&);
int binary(const Student*,int,int,long long&);
void sortRun(Student*,int,int,int,Metrics&);
