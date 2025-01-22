#pragma once 

#include "const.h"

struct SectionInfo{
    SectionInfo() = default;

    SectionInfo(const SectionInfo& section_info) {
        _section_datas = section_info._section_datas;
    }

    SectionInfo& operator=(const SectionInfo& section_info) {
        if (this == &section_info) {
            return *this;
        }
        _section_datas = section_info._section_datas;
        return *this;
    }

    ~SectionInfo() {
        _section_datas.clear();
    };

    std::map<std::string, std::string> _section_datas;

    std::string operator[](const std::string& key) {
        if (_section_datas.find(key) != _section_datas.end()) {
            return _section_datas[key];
        }

        return "";
    }

};

class ConfigMgr {
public:

    ConfigMgr();

    ConfigMgr(const ConfigMgr& config_mgr) {
        _config_map = config_mgr._config_map;
    }

    ConfigMgr& operator=(const ConfigMgr& config_mgr) {
        if (this == &config_mgr) {
            return *this;
        }
        _config_map = config_mgr._config_map;
        return *this;
    }

    ~ConfigMgr() {
        _config_map.clear();
    }
    SectionInfo operator[](const std::string& key) {
        if (_config_map.find(key) != _config_map.end()) {
            return _config_map[key];
        }

        return SectionInfo();
    }
private:
    std::unordered_map<std::string, SectionInfo> _config_map;
};