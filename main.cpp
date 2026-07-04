#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <thread>
#include <chrono>

class Task {
public:
    std::string name;
    int priority;
    int duration_ms;

    Task(const std::string& n, int p, int d)
        : name(n), priority(p), duration_ms(d) {}

    bool operator<(const Task& other) const {
        return priority < other.priority;
    }
};

class TaskQueue {
private:
    std::priority_queue<Task> queue;

public:
    void push(const Task& task) {
        queue.push(task);
    }

    Task pop() {
        Task t = queue.top();
        queue.pop();
        return t;
    }

    std::size_t size() const {
        return queue.size();
    }

    bool empty() const {
        return queue.empty();
    }
};

int main() {
    TaskQueue tq;

    tq.push(Task("Send email report",      2, 300));
    tq.push(Task("Backup database",        5, 800));
    tq.push(Task("Update user cache",      3, 200));
    tq.push(Task("Process payment batch",  8, 600));
    tq.push(Task("Clean temp files",       1, 100));
    tq.push(Task("Generate PDF invoice",   6, 400));
    tq.push(Task("Sync remote config",     4, 250));
    tq.push(Task("Critical system alert", 10, 150));

    std::cout << "=== TaskQueue: " << tq.size() << " tasks queued ===\n\n";

    while (!tq.empty()) {
        Task t = tq.pop();
        std::cout << "[priority " << t.priority << "] Running: " << t.name
                  << " (" << t.duration_ms << "ms)";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(t.duration_ms));
        std::cout << " -> done\n";
    }

    std::cout << "\nAll tasks completed.\n";
    return 0;
}
