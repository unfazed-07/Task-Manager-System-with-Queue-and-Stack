#include <bits/stdc++.h>
using namespace std;
 
struct Task {
    string name;
    int priority;     
    string category;  

    bool operator<(const Task& other) const {
        return priority < other.priority;
    }
};
priority_queue<Task> pending;
stack<Task> completed;
stack<Task> redoStack;
 
void addTask() {
    Task t;
    cout << "Task name     : "; getline(cin, t.name);
    cout << "Priority (1=Low 2=Medium 3=High): "; cin >> t.priority; cin.ignore();
    cout << "Category (Work/Personal/Urgent) : "; getline(cin, t.category);
 
    pending.push(t);
 
    while (!redoStack.empty()) redoStack.pop();
 
    cout << "Added: " << t.name << "\n";
}
 
void processTask() {
    if (pending.empty()) { cout << "No pending tasks.\n"; return; }
 
    Task t = pending.top(); 
    pending.pop();
    completed.push(t);
    while (!redoStack.empty()) redoStack.pop();
 
    cout << "Processed: " << t.name << " [Priority " << t.priority << "]\n";
}
 
void undoTask() {
    if (completed.empty()) { cout << "Nothing to undo.\n"; return; }
 
    Task t = completed.top();
    completed.pop();
    redoStack.push(t);  
    pending.push(t);
 
    cout << "Undo: \"" << t.name << "\" moved back to pending.\n";
}
 
void redoTask() {
    if (redoStack.empty()) { cout << "Nothing to redo.\n"; return; }
 
    Task t = redoStack.top();
    redoStack.pop();
 
    priority_queue<Task> temp;
    bool removed = false;
    while (!pending.empty()) {
        Task cur = pending.top(); pending.pop();
        if (!removed && cur.name == t.name) { removed = true; continue; }
        temp.push(cur);
    }
    pending = temp;
 
    completed.push(t);
    cout << "Redo: \"" << t.name << "\" marked completed again.\n";
}
 
void searchTask() {
    cout << "Enter keyword: ";
    string keyword; getline(cin, keyword);
    bool found = false;
 
    priority_queue<Task> temp = pending;
    while (!temp.empty()) {
        Task t = temp.top(); temp.pop();
        if (t.name.find(keyword) != string::npos) {
            cout << "[Pending  ] " << t.name << " | " << t.category << " | Priority " << t.priority << "\n";
            found = true;
        }
    }
 
    stack<Task> stemp = completed;
    while (!stemp.empty()) {
        Task t = stemp.top(); stemp.pop();
        if (t.name.find(keyword) != string::npos) {
            cout << "[Completed] " << t.name << " | " << t.category << "\n";
            found = true;
        }
    }
 
    if (!found) cout << "No task found with keyword: " << keyword << "\n";
}
 
void showStats() {
    int high = 0, med = 0, low = 0;
 
    priority_queue<Task> temp = pending;
    while (!temp.empty()) {
        Task t = temp.top(); temp.pop();
        if (t.priority == 3) high++;
        else if (t.priority == 2) med++;
        else low++;
    }
 
    cout << "\n--- Stats ---\n";
    cout << "Pending   : " << (high + med + low) << " (High:" << high << " Med:" << med << " Low:" << low << ")\n";
    cout << "Completed : " << completed.size() << "\n";
    cout << "Total     : " << (high + med + low + (int)completed.size()) << "\n";
}
 
void display() {
    cout << "\n-- Pending (high priority first) --\n";
    if (pending.empty()) { cout << "None\n"; }
    else {
        priority_queue<Task> temp = pending;
        int i = 1;
        while (!temp.empty()) {
            Task t = temp.top(); temp.pop();
            cout << i++ << ". [P" << t.priority << "] " << t.name << " | " << t.category << "\n";
        }
    }
 
    cout << "\n-- Completed --\n";
    if (completed.empty()) { cout << "None\n"; }
    else {
        stack<Task> temp = completed;
        int i = 1;
        while (!temp.empty()) {
            Task t = temp.top(); temp.pop();
            cout << i++ << ". " << t.name << " | " << t.category << "\n";
        }
    }
}
 
int main() {
    int choice;
    while (true) {
        cout << "\n1. Add Task\n2. Process Task\n3. Undo\n4. Redo\n5. Display\n6. Search\n7. Stats\n8. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();
 
        switch (choice) {
            case 1: addTask();     break;
            case 2: processTask(); break;
            case 3: undoTask();    break;
            case 4: redoTask();    break;
            case 5: display();     break;
            case 6: searchTask();  break;
            case 7: showStats();   break;
            case 8: return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}
