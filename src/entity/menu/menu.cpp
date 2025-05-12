#include "../../../include/entity/menu/Menu.h"
#include <iostream>

Menu::Menu(TaskManager& manager) : manager(manager) {
    auto taskHandler = std::make_unique<TaskHandler>(manager);
    handlerChain = std::move(taskHandler);
}

void Menu::displayMainMenu() {
    while (true) {
        std::cout << "\n=== TaskMaster Pro ===\n";
        std::cout << "1. Projects Management\n";
        std::cout << "2. Categories Management\n";
        std::cout << "3. Search Tasks by Category\n";
        std::cout << "4. Export Data\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: projectsManagementMenu(); break;
            case 2: categoriesManagementMenu(); break;
            case 3: searchTasksByCategory(); break;
            case 4: exportDataMenu(); break;
            case 5: return;
            default: std::cout << "Invalid choice!\n";
        }
    }
}

void Menu::projectsManagementMenu() {
    while (true) {
        std::cout << "\n=== Projects Management ===\n";
        std::cout << "1. Create Project\n";
        std::cout << "2. List Projects\n";
        std::cout << "3. Add Task to Project\n";
        std::cout << "4. Back to Main Menu\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: createProjectMenu(); break;
            case 2: listProjectsMenu(); break;
            case 3: addTaskToProjectMenu(); break;
            case 4: return;
            default: std::cout << "Invalid choice!\n";
        }
    }
}

void Menu::categoriesManagementMenu() {
    while (true) {
        std::cout << "\n=== Categories Management ===\n";
        std::cout << "1. Create Category\n";
        std::cout << "2. List Categories\n";
        std::cout << "3. Assign Category to Task\n";
        std::cout << "4. Back to Main Menu\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: createCategoryMenu(); break;
            case 2: listCategoriesMenu(); break;
            case 3: assignCategoryToTaskMenu(); break;
            case 4: return;
            default: std::cout << "Invalid choice!\n";
        }
    }
}

void Menu::createProjectMenu() {
    std::string name;
    std::cout << "Enter project name: ";
    std::getline(std::cin, name);

    auto project = manager.createProject(name);
    std::cout << "Project '" << project->getName() << "' created successfully!\n";
}

void Menu::listProjectsMenu() {
    auto projects = manager.getProjects();
    if (projects.empty()) {
        std::cout << "No projects found.\n";
        return;
    }

    for (size_t i = 0; i < projects.size(); ++i) {
        std::cout << i + 1 << ". " << projects[i]->getName()
                 << " (Tasks: " << projects[i]->getTasks().size() << ")\n";
    }
}

void Menu::addTaskToProjectMenu() {
    auto projects = manager.getProjects();
    if (projects.empty()) {
        std::cout << "No projects available. Please create a project first.\n";
        return;
    }

    std::cout << "Select project:\n";
    listProjectsMenu();
    std::cout << "Enter project number: ";

    size_t projectIndex;
    std::cin >> projectIndex;
    std::cin.ignore();

    if (projectIndex < 1 || projectIndex > projects.size()) {
        std::cout << "Invalid project number!\n";
        return;
    }

    std::string title, description;
    int priority;

    std::cout << "Enter task title: ";
    std::getline(std::cin, title);

    std::cout << "Enter task description: ";
    std::getline(std::cin, description);

    std::cout << "Enter task priority (0 for none): ";
    std::cin >> priority;
    std::cin.ignore();

    auto task = manager.createTask(title, description, priority);
    projects[projectIndex - 1]->addTask(std::unique_ptr<Task>(task));
    std::cout << "Task added to project '" << projects[projectIndex - 1]->getName() << "' successfully!\n";
}

void Menu::createCategoryMenu() {
    std::string name;
    std::cout << "Enter category name: ";
    std::getline(std::cin, name);

    auto category = manager.createCategory(name);
    std::cout << "Category '" << category->getName() << "' created successfully!\n";
}

void Menu::listCategoriesMenu() {
    auto categories = manager.getCategories();
    if (categories.empty()) {
        std::cout << "No categories found.\n";
        return;
    }

    for (size_t i = 0; i < categories.size(); ++i) {
        std::cout << i + 1 << ". " << categories[i]->getName()
                 << " (Tasks: " << categories[i]->getTasks().size() << ")\n";
    }
}

void Menu::assignCategoryToTaskMenu() {
    auto categories = manager.getCategories();
    if (categories.empty()) {
        std::cout << "No categories available. Please create a category first.\n";
        return;
    }

    auto projects = manager.getProjects();
    if (projects.empty()) {
        std::cout << "No projects available. Please create a project first.\n";
        return;
    }

    std::cout << "Select project:\n";
    listProjectsMenu();
    std::cout << "Enter project number: ";
    size_t projectIndex;
    std::cin >> projectIndex;
    std::cin.ignore();

    if (projectIndex < 1 || projectIndex > projects.size()) {
        std::cout << "Invalid project number!\n";
        return;
    }

    auto tasks = projects[projectIndex - 1]->getTasks();
    if (tasks.empty()) {
        std::cout << "No tasks in this project.\n";
        return;
    }

    std::cout << "Select task:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << i + 1 << ". " << tasks[i]->getTitle();
        if (!tasks[i]->getCategory().empty()) {
            std::cout << " [Category: " << tasks[i]->getCategory() << "]";
        }
        std::cout << "\n";
    }
    std::cout << "Enter task number: ";
    size_t taskIndex;
    std::cin >> taskIndex;
    std::cin.ignore();

    if (taskIndex < 1 || taskIndex > tasks.size()) {
        std::cout << "Invalid task number!\n";
        return;
    }

    std::cout << "Select category:\n";
    listCategoriesMenu();
    std::cout << "Enter category number: ";
    size_t categoryIndex;
    std::cin >> categoryIndex;
    std::cin.ignore();

    if (categoryIndex < 1 || categoryIndex > categories.size()) {
        std::cout << "Invalid category number!\n";
        return;
    }

    categories[categoryIndex - 1]->addTask(tasks[taskIndex - 1]);
    std::cout << "Category '" << categories[categoryIndex - 1]->getName()
             << "' assigned to task '" << tasks[taskIndex - 1]->getTitle() << "'\n";
}

void Menu::searchTasksByCategory() {
    auto categories = manager.getCategories();
    if (categories.empty()) {
        std::cout << "No categories available.\n";
        return;
    }

    std::cout << "Select category to search:\n";
    listCategoriesMenu();
    std::cout << "Enter category number: ";
    size_t categoryIndex;
    std::cin >> categoryIndex;
    std::cin.ignore();

    if (categoryIndex < 1 || categoryIndex > categories.size()) {
        std::cout << "Invalid category number!\n";
        return;
    }

    auto tasks = categories[categoryIndex - 1]->getTasks();
    if (tasks.empty()) {
        std::cout << "No tasks in this category.\n";
        return;
    }

    std::cout << "\nTasks in category '" << categories[categoryIndex - 1]->getName() << "':\n";
    for (const auto& task : tasks) {
        std::cout << " - ";
        task->display();
        std::cout << "\n";
    }
}

void Menu::exportDataMenu() {
    std::cout << "Select export destination:\n";
    std::cout << "1. Analytics\n";
    std::cout << "2. Database\n";
    std::cout << "Choose an option: ";

    int choice;
    std::cin >> choice;
    std::cin.ignore();

    try {
        auto projects = manager.getProjects();
        if (!projects.empty()) {
            auto tasks = projects[0]->getTasks();
            if (!tasks.empty()) {
                switch (choice) {
                    case 1:
                        manager.exportTaskData(tasks[0], "analytics");
                        std::cout << "Data exported to Analytics\n";
                        break;
                    case 2:
                        manager.exportTaskData(tasks[0], "database");
                        std::cout << "Data exported to Database\n";
                        break;
                    default:
                        std::cout << "Invalid choice!\n";
                }
            } else {
                std::cout << "No tasks to export.\n";
            }
        } else {
            std::cout << "No projects found.\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Export failed: " << e.what() << "\n";
    }
}