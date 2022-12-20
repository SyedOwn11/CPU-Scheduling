#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct ready_queue_struct
{
    string name = "--";
    int burst_time = 0;
    int arrival_time = 0;
    int time_after_this_executed = 0;
};

struct process_struct
{
    string name = "--";
    int burst_time = 0;
    int arrival_time = 0;
    int completion_time = 0;
    int turn_around_time = 0;
    int waiting_time = 0;
};

class rrb
{
private:
    vector<process_struct> process_arr;
    vector<ready_queue_struct> _rqueue;
    double avg = 0;
    int _last_returned = -1;

    bool allburst_zero(vector<ready_queue_struct> _arr)
    {
        for (int i = 0; i < _arr.size(); i++)
        {
            if (_arr[i].burst_time > 0)
                return false;
        }
        return true;
    }

    int return_first_available(vector<ready_queue_struct> _arr, int _time)
    {
        for (int i = 0; i < _arr.size(); i++)
        {
            if (_arr[i].arrival_time <= _time && _arr[i].burst_time != 0)
            {
                return i;
            }
        }
        return -1;
    }

    int return_available_pindex(vector<ready_queue_struct> _arr, int _time)
    {
        if (_last_returned == -1)
        {
            _last_returned = return_first_available(_arr, _time);
            return _last_returned;
        }

        int i = _last_returned + 1;
        i = i % _arr.size();
        do
        {
            if (_arr[i].arrival_time <= _time && _arr[i].burst_time != 0)
            {
                _last_returned = i;
                return i;
            }
            i++;
            i = i % _arr.size();
        } while (i != _last_returned + 1);


        return -1;
    }

    vector<ready_queue_struct> update_n_arrange(vector<ready_queue_struct> _arr, int _tquanta)
    {
        int _time = 0; // to comapre with the arrival time of process to ensure the process is arrived 
        vector<ready_queue_struct> _parr;
        while (!allburst_zero(_arr))
        {
            ready_queue_struct _temp;
            int i = return_available_pindex(_arr, _time);
            if (i != -1)
            {
                _temp.name = _arr[i].name;
                if (_arr[i].burst_time >= _tquanta)
                {
                    _arr[i].burst_time -= _tquanta;
                    _temp.burst_time = _arr[i].burst_time;
                    _time += _tquanta;
                }
                else if (_arr[i].burst_time > 0)
                {
                    _temp.burst_time = 0;
                    _time += _arr[i].burst_time;
                    _arr[i].burst_time = 0;
                }
            }
            else
            {
                _time += _tquanta;
            }
            _temp.time_after_this_executed = _time;
            _parr.push_back(_temp);


        }
        return _parr;
    }

    vector<ready_queue_struct> Arrange_in_readyqueue(string _name, int _burst_time, int _arrival_time, int _tquanta)
    {
        static vector<ready_queue_struct> process_arr_copy;
        static vector<ready_queue_struct> process_arr;
        ready_queue_struct _struct;
        _struct.name = _name;
        _struct.burst_time = _burst_time;
        _struct.arrival_time = _arrival_time;
        process_arr_copy.push_back(_struct);
        reverse(process_arr_copy.begin(), process_arr_copy.end());
        process_arr = update_n_arrange(process_arr_copy, _tquanta);
        return process_arr;
    }

    void update_completion_time(vector<process_struct>& _inarray, vector<ready_queue_struct>& _fromarray)
    {
        for (int i = 0; i < _fromarray.size(); i++)
        {
            if (_fromarray[i].burst_time == 0 && _fromarray[i].name != "--")
            {
                for (int j = 0; j < _inarray.size(); j++)
                {
                    if (_fromarray[i].name == _inarray[j].name)
                    {
                        _inarray[j].completion_time = _fromarray[i].time_after_this_executed;
                        break;
                    }
                }
            }
        }
    }

    void update_waiting_ta_time(vector<process_struct>& _arr)
    {
        avg = 0;
        for (int i = 0; i < _arr.size(); i++)
        {
            _arr[i].turn_around_time = _arr[i].completion_time - _arr[i].arrival_time;
            _arr[i].waiting_time = _arr[i].turn_around_time - _arr[i].burst_time;
            avg += _arr[i].waiting_time;
        }
        avg /= _arr.size();
    }

public:
    void Round_Robbin_Schedule(string _name, int _burst_time, int _arrival_time, int _tquanta)
    {
        _rqueue = Arrange_in_readyqueue(_name, _burst_time, _arrival_time, _tquanta);
        //static vector<process_struct> process_arr;
        process_struct temp;
        temp.name = _name;
        temp.burst_time = _burst_time;
        temp.arrival_time = _arrival_time;
        process_arr.push_back(temp);
        update_completion_time(process_arr, _rqueue);
        update_waiting_ta_time(process_arr);
    }

    vector<process_struct> return_rrb_schedule()
    {
        return process_arr;
    }
    vector<ready_queue_struct> return_cpu_queue()
    {
        return _rqueue;
    }
    double return_average_waitingtime()
    {
        return avg;
    }
};

