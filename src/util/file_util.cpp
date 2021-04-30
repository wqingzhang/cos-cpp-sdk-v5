
#include "util/file_util.h"

#include <sys/types.h>
#include <sys/stat.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "cos_defines.h"
#include "cos_sys_config.h"
#include "util/codec_util.h"
#include "util/string_util.h"

namespace qcloud_cos {

std::string FileUtil::GetFileContent(const std::string& local_file_path) {
    std::ifstream file_input(local_file_path.c_str(), std::ios::in | std::ios::binary);
    std::ostringstream out;

    out << file_input.rdbuf();
    std::string content = out.str();

    file_input.close();
    file_input.clear();

    return content;
}

uint64_t FileUtil::GetFileLen(const std::string& local_file_path) {
    std::ifstream file_input(local_file_path.c_str(), std::ios::in | std::ios::binary);
    file_input.seekg(0, std::ios::end);
    uint64_t file_len = file_input.tellg();
    file_input.close();
    return file_len;
}

bool FileUtil::IsDirectoryExists(const std::string& path) {
    struct stat info;
    if (0 == stat(path.c_str(), &info) && info.st_mode & S_IFDIR) {
        return true;
    } else {
        return false;
    }
}

bool FileUtil::IsDirectory(const std::string& path) {
    return IsDirectoryExists(path);
}

std::string FileUtil::GetDirectory(const std::string& path) {
    size_t found = path.find_last_of("/\\");
    return (path.substr(0, found));
}

} //namespace qcloud_cos
