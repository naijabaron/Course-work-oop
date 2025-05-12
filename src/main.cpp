#include "../include/entity/menu/Menu.h"
#include "../include/service/TaskManager.h"

int main() {
    TaskManager manager;
    Menu menu(manager);

    auto project = manager.createProject("Main Project");
    manager.createCategory("Work");
    manager.createCategory("Personal");

    RionRule highPriorityRule(
        "Set due date for high priority",
        [](const Task& task) { return task.getPriority() > 5; },
        [](Task& task) { task.setDueDate(std::time(nullptr) + 86400); } // +1 день
    );
    project->addRule(highPriorityRule);

    menu.displayMainMenu();

    return 0;
}
