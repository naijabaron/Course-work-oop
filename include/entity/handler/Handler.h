#ifndef HANDLER_H
#define HANDLER_H
#include <memory>


class Handler {
    std::unique_ptr<Handler> next;
public:
    virtual ~Handler() = default;

    void setNext(std::unique_ptr<Handler> handler) {
        next = std::move(handler);
    }

    virtual void handle(const std::string& request) {
        if (next) {
            next->handle(request);
        }
    }
};

#endif //HANDLER_H
