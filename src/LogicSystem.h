#pragma once

#include <map>
#include <string>
#include <functional>
#include <memory>
#include "Singleton.h"


class HttpConnection;
typedef std::function<void(std::shared_ptr<HttpConnection>)> HttpHandler;

class LogicSystem :public Singleton<LogicSystem>
{
    friend class Singleton<LogicSystem>;
public:
    ~LogicSystem() = default;
    bool HandleGet(std::string, std::shared_ptr<HttpConnection>);
    void RegGet(std::string, HttpHandler handler);
private:
    LogicSystem();
    std::map<std::string, HttpHandler> _post_handlers;
    std::map<std::string, HttpHandler> _get_handlers;
};