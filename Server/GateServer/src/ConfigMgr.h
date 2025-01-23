#pragma once 

#include "const.h"

struct SectionInfo{
    SectionInfo(){}

    SectionInfo(const SectionInfo& section_info) {
        _section_datas = section_info._section_datas;
    }

    SectionInfo& operator=(const SectionInfo& section_info) {
        if (this == &section_info) {
            return *this;
        }
        this->_section_datas = section_info._section_datas;
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

    

    ConfigMgr(const ConfigMgr& config_mgr) {
        _config_map = config_mgr._config_map;
    }

    ConfigMgr& operator=(const ConfigMgr& config_mgr) {
        if (this == &config_mgr) {
            return *this;
        }
        this->_config_map = config_mgr._config_map;
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

    static ConfigMgr& Inst() {
        static ConfigMgr instance;
        return instance;
    }
private:
    ConfigMgr();
    std::map<std::string, SectionInfo> _config_map;
};