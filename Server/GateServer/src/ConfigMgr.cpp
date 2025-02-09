#include "ConfigMgr.h"

ConfigMgr::ConfigMgr() {
    auto current_path = std::filesystem::current_path();
    auto config_path = current_path / "config.ini";
    std::cout << "config path is " << config_path << std::endl;

    boost::property_tree::ptree pt;
    boost::property_tree::read_ini(config_path.string(), pt);

    for (const auto& [section_name, section_tree] : pt) {
        for (const auto& [key, value] : section_tree) {
            _config_map[section_name]._section_datas[key] = value.get_value<std::string>();
        }
    }

    //输出
    for (const auto& [section_name, section_info] : _config_map) {
        std::cout << "[" << section_name << "]" << std::endl;
        for (const auto& [key, value] : section_info._section_datas) {
            std::cout << key << "=" << value << std::endl;
        }
    }
}


