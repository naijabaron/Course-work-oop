cmake_minimum_required(VERSION 3.31)
project(task_manager)

set(CMAKE_CXX_STANDARD 20)

add_executable(task_manager src/main.cpp
        include/entity/observer/Observer.h
        include/Observable.h
        include/ExportStrategy.h
        include/service/AnalyticsExport.h
        include/service/DatabaseExport.h
        include/factory/TaskFactory.h
        include/decorator/PriorityTaskDecorator.h
        include/entity/command/Command.h
        include/decorator/TaskDecorator.h
        include/entity/logger/Logger.h
        include/entity/task/TaskStatus.h
        include/entity/task/TadTask.h
        include/factory/TadTaskFactory.h
        include/entity/rules/RionRule.h
        include/entity/project/Project.h
        include/entity/category/Category.h
        include/entity/reminder/Reminder.h
        include/service/ExportService.h
        include/entity/user/User.h
        include/service/TaskManager.h
        include/entity/command/CreateTaskCommand.h
        include/entity/handler/Handler.h
        include/service/TaskHandler.h
        include/entity/menu/Menu.h
        include/entity/task/Task.h
        src/entity/user/User.cpp
        src/entity/category/Category.cpp
        src/entity/menu/menu.cpp
        src/service/AnalyticsExport.cpp
        src/service/DatabaseExport.cpp
)
