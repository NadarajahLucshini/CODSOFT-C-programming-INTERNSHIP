#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    string description;
    bool completed;

    Task(string desc) : description(desc), completed(false) {}
};

class ToDoList {
private:
    vector<Task> tasks;

public:
    void addTask(const string& description) {
        tasks.push_back(Task(description));
        cout << "Task added: " << description << endl;
    }

    void viewTasks() {
        if (tasks.empty()) {
            cout << "No tasks in the list." << endl;
            return;
        }

        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << (tasks[i].completed ? "[Completed] " : "[Pending] ") << tasks[i].description << endl;
        }
    }

    void markTaskCompleted(int taskNumber) {
        if (taskNumber < 1 || taskNumber > tasks.size()) {
            cout << "Invalid task number." << endl;
            return;
        }
        tasks[taskNumber - 1].completed = true;
        cout << "Task marked as completed: " << tasks[taskNumber - 1].description << endl;
    }

    void removeTask(int taskNumber) {
        if (taskNumber < 1 || taskNumber > tasks.size()) {
            cout << "Invalid task number." << endl;
            return;
        }
        cout << "Task removed: " << tasks[taskNumber - 1].description << endl;
        tasks.erase(tasks.begin() + taskNumber - 1);
    }
};

int main() {
    ToDoList todoList;
    int choice;
    string description;
    int taskNumber;

    while (true) {
        cout << "\nTo-Do List Menu:\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Remove Task\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter the task description: ";
            getline(cin, description);
            todoList.addTask(description);
            break;
        case 2:
            todoList.viewTasks();
            break;
        case 3:
            cout << "Enter the task number to mark as completed: ";
            cin >> taskNumber;
            todoList.markTaskCompleted(taskNumber);
            break;
        case 4:
            cout << "Enter the task number to remove: ";
            cin >> taskNumber;
            todoList.removeTask(taskNumber);
            break;
        case 5:
            cout << "Exiting the program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
