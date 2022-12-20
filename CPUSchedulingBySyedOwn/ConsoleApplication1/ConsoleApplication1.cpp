#include<iostream>
#include"PriorityScheduling.h"
#include "RoundRobbin.h"
#include <Windows.h>
#include <conio.h>
using namespace std;

template<class T>

struct Node
{
	T BurstTime;
	Node<T>* next;
	string ProcessName;
	T ArrivalTime;
	T EndTime;
	T WaitingTime;
	T TurnAroundTime;
};
template <class T>
class SyedOwnDynamicQueue
{
	Node<T>* front, * rear;
	float ProcessCount;

public:

	SyedOwnDynamicQueue()
	{
		front = NULL;
		rear = NULL;
		ProcessCount = 0;

	}

	void enqueue(string name, T burst_time, T arrival)
	{
		ProcessCount++;
		Node <T>* NewProcess = new Node<T>;
		NewProcess->ProcessName = name;
		NewProcess->BurstTime = burst_time;
		NewProcess->ArrivalTime = arrival;
		if (isEmpty())
		{
			NewProcess->next = NULL;
			front = rear = NewProcess;

		}
		else
		{
			rear->next = NewProcess;
			NewProcess->next = NULL;
			rear = NewProcess;
		}
		ProcessEndTimeCalc();
		WaitingTimeCalc();
		TurnArroundTimeCalc();

	}

	double avgWtime() {
		double t = 0;
		Node<T>* x = front;
		while (x != NULL) {
			t += x->WaitingTime;
			x = x->next;
		}
		double a = t / ProcessCount;
		return a;
	}
	void DisplayProcesses()
	{
		Node<T>* n = new Node<T>;
		n = front;
		while (n != NULL) {
			cout << "\nProcesses: " << n->ProcessName << "      Arrival Time: " << n->ArrivalTime
				<< "      Burst Time: " << n->BurstTime << "      Wait Time: " << n->WaitingTime
				<< "      End Time: " << n->EndTime << "      TurnAround Time: " << n->TurnAroundTime << endl;
			n = n->next;
		}
		cout << "\nAvg Waiting Time: " << avgWtime();
		cout << "\nProcess Count: " << ProcessCount;

	}
	bool isEmpty()
	{
		return front == NULL;
	}
	void WaitingTimeCalc() {
		Node <T>* abc = front;

		if (abc == front)
		{
			abc->WaitingTime = 0;
		}

		while (abc->next != NULL) { //WT = PrevProcessEndTIME  -  NEWProcessAT
			int x;
			if ((abc->EndTime - abc->next->ArrivalTime) < 0) // If NewProcessAT  > PrevProcessENDTIME
				abc->next->WaitingTime = 0;

			else if (abc->EndTime == abc->next->ArrivalTime) // If NewProcessAT  =  PrevProcessENDTIME
				abc->next->WaitingTime = 0;

			else  // If NewProcessAT  < PrevProcessENDTIME
				abc->next->WaitingTime = abc->EndTime - abc->next->ArrivalTime; //WT = PrevProcessEndTIME  -  NEWProcessAT
			abc = abc->next;
		}
	}
	void ProcessEndTimeCalc() { // EndTime = PrevProcessEndTime + NewProcessBurstTime
		Node <T>* abc = front;

		if (abc == front)
		{
			abc->EndTime = abc->ArrivalTime + abc->BurstTime;
		}

		while (abc->next != NULL) {
			if (abc->next->ArrivalTime > abc->EndTime) // IF NewProccessAT  >  PrevProcessENDTIME
				abc->next->EndTime = abc->next->ArrivalTime + abc->next->BurstTime;

			else if (abc->next->ArrivalTime < abc->EndTime) // IF NewProccessAT  <  PrevProcessENDTIME
				abc->next->EndTime = abc->EndTime + abc->next->BurstTime;

			else
				abc->next->EndTime = abc->EndTime + abc->next->BurstTime; // IF NewProccessAT  =  PrevProcessENDTIME
			abc = abc->next;
		}
	}

	void TurnArroundTimeCalc() { // TAT = WT + BT
		Node<T>* x = front;
		while (x != NULL) {
			x->TurnAroundTime = x->WaitingTime + x->BurstTime;
			x = x->next;
		}
	}
	void ShortestJobFirst(string name, int burst_time, T arrival) {
		ProcessCount++;
		Node <T>* NewProcess = new Node<T>;
		Node <T>* temp = front;

		NewProcess->ProcessName = name;
		NewProcess->BurstTime = burst_time;
		NewProcess->ArrivalTime = arrival;
		NewProcess->next = NULL;

		if (isEmpty())
		{
			front = rear = NewProcess;
			ProcessEndTimeCalc();
			WaitingTimeCalc();
			TurnArroundTimeCalc();
			return;
		}

		while (temp->next) {
			if (burst_time < temp->next->BurstTime) {
				break;
			}
			temp = temp->next;

		}
		if (temp != front) {

			NewProcess->next = temp->next;
			temp->next = NewProcess;
			ProcessEndTimeCalc();
			WaitingTimeCalc();
			TurnArroundTimeCalc();
		}
		else {
			if (front->BurstTime < burst_time) {
				ProcessCount--;
				enqueue(name, burst_time, arrival);
				delete NewProcess;
			}
			else {

				NewProcess->next = front;
				front = NewProcess;
				ProcessEndTimeCalc();
				WaitingTimeCalc();
				TurnArroundTimeCalc();
			}
		}



		Node<T>* xyz = front;
		while (xyz->next != NULL)
		{
			xyz = xyz->next;
		}
		rear = xyz;
	}



	void FirstComeFirstServe(string name, int burst_time, T arrival) {
		ProcessCount++;
		Node <T>* NewProcess = new Node<T>;
		Node <T>* temp = front;

		NewProcess->ProcessName = name;
		NewProcess->BurstTime = burst_time;
		NewProcess->ArrivalTime = arrival;
		NewProcess->next = NULL;

		if (isEmpty())
		{
			front = rear = NewProcess;
			ProcessEndTimeCalc();
			WaitingTimeCalc();
			TurnArroundTimeCalc();
			return;
		}

		while (temp->next) {
			if (arrival < temp->next->BurstTime) {
				break;
			}
			temp = temp->next;

		}
		if (temp != front) {

			NewProcess->next = temp->next;
			temp->next = NewProcess;
			ProcessEndTimeCalc();
			WaitingTimeCalc();
			TurnArroundTimeCalc();
		}
		else {
			if (front->ArrivalTime < arrival) {
				ProcessCount--;
				enqueue(name, burst_time, arrival);
				delete NewProcess;
			}
			else {

				NewProcess->next = front;
				front = NewProcess;
				ProcessEndTimeCalc();
				WaitingTimeCalc();
				TurnArroundTimeCalc();
			}
		}
		Node<T>* xyz = front;
		while (xyz->next != NULL)
		{
			xyz = xyz->next;
		}
		rear = xyz;
	}


	void Graphics() {

		cout << "\n\n\n\t\t _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _";
		cout << "\n\t\t|\t      Theme\t\t    |\n\t\t|Enter 1 for Black and Green theme  |"
			<< "\n\t\t|Enter 2 for Black and Yellow theme | ";
		cout << "\n\t\t|Enter 3 for Black and Red theme    |\n\t\t|Enter 4 for White and Aqua theme   |";
		cout << "\n\t\t|Enter 5 for Black and Aqua theme   | ";
		cout << "\n\t\t|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n\nYour Choice for theme: ";
		int theme;
		cin >> theme;
		switch (theme) {
		case 1:system("color 0A");
			break;
		case 2:system("color 06");
			break;
		case 3:system("color 04");
			break;
		case 4:system("color f3");
			break;
		case 5:system("color 03");
			break;
		default:system("color 0f");
			break;
		}
	}
};

void Welcome() {
	cout <<
		"\n\t           _ _ _          _ _ _   _ _ _            _ _ _"
		<< "\n\t|      |  |       |      |       |     | |\\    /| |"
		<< "\n\t|  /\\  |  |_ _ _  |      |       |     | | \\  / | |_ _ _"
		<< "\n\t| /  \\ |  |       |      |       |     | |  \\/  | |"
		<< "\n\t|/    \\|  |_ _ _  |_ _ _ |_ _ _  |_ _ _| |      | |_ _ _"
		<< "\n\t\t\t\t  _ _ _  _ _ _"
		<< "\n\t\t\t\t    |   |     |"
		<< "\n\t\t\t\t    |   |     |"
		<< "\n\t\t\t\t    |   |_ _ _|";


	cout << "\n\t\t\t\t _ _ _   _ _ _"
		<< "\n\t\t\t\t|       |     |  |     |"
		<< "\n\t\t\t\t|       |_ _ _|  |     |"
		<< "\n\t\t\t\t|       |        |     |"
		<< "\n\t\t\t\t|_ _ _  |        |_ _ _|"

		<< "\n\n     _ _ _    _ _ _            _ _ _   _ _ _                      _ _ _   _ _ _"
		<< "\n    |        |       |     |  |       |     \\   |     |  |       |       |     |"
		<< "\n    |_ _ _   |       |_ _ _|  |_ _ _  |      |  |     |  |       |_ _ _  |_ _ _|"
		<< "\n          |  |       |     |  |       |      |  |     |  |       |       |   \\"
		<< "\n     _ _ _|  |_ _ _  |     |  |_ _ _  |_ _ _/   |_ _ _|  |_ _ _  |_ _ _  |    \\\n";

}
int main()
{
	Welcome();
	SyedOwnDynamicQueue<double> SyedOwn;
	SyedOwn.Graphics();


	cout << "\n\n\n\t\t%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
	cout << "\n\t\t%%\t      Processes\t\t%%\n\t\t%%  Enter 1 for FCFS Scheduling     %%"
		<< "\n\t\t%%  Enter 2 for SJF Scheduling      %%";
	cout << "\n\t\t%%  Enter 3 for Priority Scheduling %%\n\t\t%%  Enter 4 for Round Robbin        %%";
	cout << "\n\t\t%%  Enter -1 to Exit                %%";
	cout << "\n\t\t%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\nYour Choice for Scheduling: ";
	int x;
	cin >> x;


	int i = 0;
	while (i != -1) {
		//	system("CLS");
		if (x == -1)
			break;
		else if (x == 1)
		{
			cout << "\nProcess Name: ";
			string pn;
			cin >> pn;
			double bt;

			double at;
			cout << "\Arrival Time: ";
			cin >> at;

			cout << "\nBurst Time: ";
			cin >> bt;
			SyedOwn.FirstComeFirstServe(pn, bt, at);
			SyedOwn.DisplayProcesses();
			cout << "\nEnter -1 to stop or any other number to continue adding Processes: ";
			cin >> i;
		}
		else if (x == 2) {
			cout << "\nProcess Name: ";
			string pn;
			cin >> pn;
			double bt;

			double at;
			cout << "\Arrival Time: ";
			cin >> at;

			cout << "\nBurst Time: ";
			cin >> bt;
			SyedOwn.ShortestJobFirst(pn, bt, at);
			SyedOwn.DisplayProcesses();
			cout << "\nEnter -1 to stop or any other number to continue adding Processes: ";
			cin >> i;
		}
		else if (x == 3) {
			ps obj;
			vector<queue_struct> arr;
			vector<process_structu> arr0;
			bool abc = true;
			while (abc)
			{
				string name;
				int b_time;
				int arvl_time;
				int priority;
				cout << "Enter Process name(-1 to quit): ";
				cin >> name;
				if (name == "-1") {
					x = -1;
					break;
				}
				cout << "Enter Priority: ";
				cin >> priority;
				cout << "Enter Burst time: ";
				cin >> b_time;
				cout << "Enter Arrival time: ";
				cin >> arvl_time;
				obj.priority_schedule(name, b_time, priority, arvl_time);
				arr = obj.return_p_queue();
				arr0 = obj.return_ps_array();

				cout << "Processes List:\nName\tBurst Time\tArrival Time\tCompl Time\tTurn Around Time\tWaiting Time\n";
				for (int i = 0; i <= arr0.size() - 1; i++)
				{
					cout << arr0[i].name << "\t" << arr0[i].burst_time << "\t\t" << arr0[i].arrival_time << "\t\t" << arr0[i].completion_time << "\t\t" << arr0[i].turn_around_time << "\t\t\t" << arr0[i].waiting_time << endl;
				}

				cout << "\nReady Queue:\n";
				cout << "Queue:\t\t";
				for (int i = 0; i <= arr.size() - 1; i++)
				{
					cout << "| " << arr[i].name << "\t";
				}
				cout << "|" << endl;
				cout << "Time:\t\t0";
				for (int i = 0; i <= arr.size() - 1; i++)
				{
					cout << "  " << "\t" << arr[i].completion_time;
				}
				cout << "\nAverage waiting time is: " << obj.return_averge_waiting_time();
				cout << "\n\n";
			}
		}
		else if (x == 4) {
			rrb obj;
			vector<ready_queue_struct> arr;
			vector<process_struct> arr0;
			while (true)
			{
				string name;
				int b_time;
				int arvl_time;
				int t_quanta;
				cout << "Enter process name(-1 to quit): ";
				cin >> name;
				if (name == "-1") {
					x = -1;
					break;
				}
				cout << "Enter Burst time: ";
				cin >> b_time;
				cout << "Enter Arrival time: ";
				cin >> arvl_time;
				cout << "Enter Time quanta: ";
				cin >> t_quanta;
				obj.Round_Robbin_Schedule(name, b_time, arvl_time, t_quanta);
				arr = obj.return_cpu_queue();
				arr0 = obj.return_rrb_schedule();

				cout << "Processes List:\nName\tBurst Time\tArrival Time\tCompl Time\tTurn Around Time\tWaiting Time\n";
				for (int i = 0; i <= arr0.size() - 1; i++)
				{
					cout << arr0[i].name << "\t" << arr0[i].burst_time << "\t\t" << arr0[i].arrival_time << "\t\t" << arr0[i].completion_time << "\t\t" << arr0[i].turn_around_time << "\t\t\t" << arr0[i].waiting_time << endl;
				}

				cout << "\nReady Queue:\n";
				cout << "Queue:\t\t";
				for (int i = 0; i <= arr.size() - 1; i++)
				{
					cout << "| " << arr[i].name << "\t";
				}
				cout << "|" << endl;
				cout << "Time:\t\t0";
				for (int i = 0; i <= arr.size() - 1; i++)
				{
					cout << "  " << "\t" << arr[i].time_after_this_executed;
				}
				cout << "\n";
				cout << "rem bursts:\t";
				for (int i = 0; i <= arr.size() - 1; i++)
				{
					cout << "  " << "\t" << arr[i].burst_time;
				}
				cout << "\nAverage waiting time is: " << obj.return_average_waitingtime();
				cout << "\n\n";
			}
		}
		else {
			cout << "\n%%%%%%%%%%%%%% Invalid Command Entered!!! %%%%%%%%%%%%%%";
			_getch();
		}
	}
}
