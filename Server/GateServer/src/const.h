#pragma once

#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <memory>
#include <iostream>
#include "Singleton.h"
#include <functional>
#include <unordered_map>
#include <map>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <filesystem>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

enum ErrorCodes {
    Success         = 0,
    Error_Json      = 1001,
    RPCFalied       = 1002,
};

class ConfigMgr;
extern ConfigMgr gCfgMgr;