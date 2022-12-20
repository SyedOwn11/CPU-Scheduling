#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

struct process_structu
{
    string name = "";
    int burst_time = 0;
    int priority = 0;
    int arrival_time = 0;
    int completion_time = 0;
    int turn_around_time = 0;
    int waiting_time = 0;
};

struct queue_struct
{
    string name = "--";
    int burst_time = 0;
    int completion_time = 0;
};

class ps
{
    vector<process_structu> arr;
    vector<queue_struct> p_queue;
    double avg;

    int min_pos(vector<process_structu>& a, int _from)
    {
        int min = _from;
        for (int i = _from + 1; i < a.size(); i++)
        {
            if (a[min].priority > a[i].priority)
                min = i;
        }
        return min;
    }

    void swap(process_structu& a, process_structu& b)
    {
        process_structu c = a;
        a = b;
        b = c;
    }

    void Selection_Sort(vector<process_structu>& _arr)
    {
        for (int i = 0; i < _arr.size(); i++)
        {
            swap(_arr[i], _arr[min_pos(_arr, i)]);
        }
    }

    void update_completion_time(vector<process_structu>& _arr)
    {

        //int prev_time = 0;
        for (int i = 0; i < _arr.size(); i++)
        {
            if (i == 0)
                _arr[i].completion_time = _arr[i].arrival_time + _arr[i].burst_time;
            else
            {
                _arr[i].completion_time = _arr[i - 1].completion_time + arr[i].burst_time;
            }

            // prev_time += _arr[i].burst_time;
             //_arr[i].completion_time = prev_time;
        }
    }

    void update_waiting_n_turnarround_time(vector<process_structu>& _arr)
    {
        avg = 0;
        for (int i = 0; i < _arr.size(); i++)
        {
            int wt;
            if (i == 0)
                wt = 0;
            else {
                wt = _arr[i - 1].completion_time - _arr[i].arrival_time; // 
            }

            if (wt < 0) {
                wt = 0;
            }
            _arr[i].waiting_time = wt;
            _arr[i].turn_around_time = _arr[i].waiting_time + _arr[i].burst_time; 
            avg += _arr[i].waiting_time;
        }
        avg /= _arr.size();
    }

    void make_p_queue(vector<process_structu> _arr)
    {
        vector<queue_struct> _pqueue;
        for (int i = 0; i < _arr.size(); i++)
        {
            queue_struct temp;
            temp.name = _arr[i].name;
            temp.burst_time = _arr[i].burst_time;
            temp.completion_time = _arr[i].completion_time;
            _pqueue.push_back(temp);
        }
        p_queue = _pqueue;
    }

public:

    void priority_schedule(string _name, int _burst_time, int _priority, int _arrival_time)
    {
        process_structu _parray_struct;
        _parray_struct.name = _name;
        _parray_struct.burst_time = _burst_time;
        _parray_struct.priority = _priority;
        _parray_struct.arrival_time = _arrival_time;
        arr.push_back(_parray_struct);
        Selection_Sort(arr);
        update_completion_time(arr);
        make_p_queue(arr);
        update_waiting_n_turnarround_time(arr);
    }

    vector<process_structu> return_ps_array()
    {
        return arr;
    }

    vector<queue_struct> return_p_queue()
    {
        return p_queue;
    }

    double return_averge_waiting_time()
    {
        return avg;
    }
};

