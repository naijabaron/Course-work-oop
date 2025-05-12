#ifndef MENU_H
#define MENU_H

#include "../command/CreateTaskCommand.h"
#include "../handler/Handler.h"
#include "../../service/TaskHandler.h"
#include "../../service/TaskManager.h"
#include <algorithm>
#include <memory>
#include <iostream>
#include <limits>

class Menu {
    TaskManager& manager;
    std::unique_ptr<Handler> handlerChain;

public:
    explicit Menu(TaskManager& manager);
    void displayMainMenu();

private:
    void projectsManagementMenu();
    void categoriesManagementMenu();
    void createProjectMenu();
    void listProjectsMenu();
    void addTaskToProjectMenu();
    void createCategoryMenu();
    void listCategoriesMenu();
    void assignCategoryToTaskMenu();
    void searchTasksByCategory();
    void exportDataMenu();
};

#endif // MENU_H