#include <bits/stdc++.h>
using namespace std;

queue<string> pending;
stack<string> completed;

void addTask(string task) {
    pending.push(task);
    cout <<"Task added:"<<task<<endl;
}
void processTask() {
if (pending.empty()) {
    cout<<"No tasks to process\n";
    return;
}
string task = pending.front();
pending.pop();
completed.push(task);
cout << "Processed task: " << task << endl;
}

void undoTask() {
if (completed.empty()) {
    cout << "Nothing to undo\n";
    return;
}

string task = completed.top();
completed.pop();
pending.push(task);
cout << "Undo done. Task moved back: " << task << endl;
}
void display() {
cout <<"\nPending Tasks:\n";
if (pending.empty()) cout << "None\n";
else {
queue<string> temp = pending;
while (!temp.empty()) {
    cout << temp.front() << endl;
    temp.pop();
}
}
cout <<"\nCompleted Tasks:\n";
if (completed.empty()) cout << "None\n";
else {
    stack<string> temp = completed;
while (!temp.empty()) {
    cout << temp.top() << endl;
    temp.pop();
}
}
}

int main() {
int choice;
string task;

while (true) {
cout << "\n1. Add Task\n2. Process Task\n3. Undo\n4. Display\n5. Exit\n";
cout << "Enter choice: ";
cin >> choice;

cin.ignore();

switch (choice) {
    case 1:
        cout << "Enter task: ";
        getline(cin, task);
        addTask(task);
        break;

    case 2:
        processTask();
        break;

    case 3:
        undoTask();
        break;

    case 4:
        display();
        break;

    case 5:
        return 0;

    default:
        cout << "Invalid choice\n";
}
}
}
