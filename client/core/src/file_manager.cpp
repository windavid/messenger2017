#include "file_manager.h"

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <path_settings.h>
#include <fstream>

namespace m2 {
namespace core {

using namespace boost::property_tree;

FileManager::FileManager()
    : fileManagerConfigName_("file-manager.json")
{
    std::string managerFileName(GetManagerPath("files") + fileManagerConfigName_);

    std::fstream file(managerFileName, std::ios_base::out |
                                       std::ios_base::app);

    if (!file) {                        // If config file doesn't exist
        file.close();
        InitJsonFile(managerFileName);
    } else {
        file.close();
        ReadFoldersPath(managerFileName);
    }

}

const std::string FileManager::GetStandartFilePath(m2::core::FileManager::FileType type)
{
    std::string downloadFolderPath;
    std::string del;

#ifdef _WIN32 || _WIN64
    del = "\\";
    downloadFolderPath = getenv("USERPROFILE");
#else
    del = "/";
    downloadFolderPath = getenv("HOME");
#endif

    downloadFolderPath.append(del).append("Downloads").append("m2 files");
    switch (type) {
    case PIC:
        downloadFolderPath.append(del).append("Pictures");
        break;
    case AUDIO:
        downloadFolderPath.append(del).append("Audio");
        break;
    case VIDEO:
        downloadFolderPath.append(del).append("Video");
        break;
    case ANOTHER_DOC:
        downloadFolderPath.append(del).append("Documents");
        break;
    default:
        downloadFolderPath.append(del).append("Documents");
        break;
    }

    boost::filesystem::path p(downloadFolderPath);
    if (!boost::filesystem::exists(p))
        boost::filesystem::create_directories(p);

    return downloadFolderPath;
}

void FileManager::InitJsonFile(std::string &fileName)
{
    std::fstream stream(fileName, std::ios_base::out |
                                  std::ios_base::trunc);
    try {
        ptree fileTree, standartPath;

        picDownloadFolder_ = GetStandartFilePath(PIC);
        audioDownloadFolder_ = GetStandartFilePath(AUDIO);
        videoDownloadFolder_ = GetStandartFilePath(VIDEO);
        docDownloadFolder_ = GetStandartFilePath(ANOTHER_DOC);

        standartPath.put("pic", picDownloadFolder_);
        standartPath.put("audio", audioDownloadFolder_);
        standartPath.put("video", videoDownloadFolder_);
        standartPath.put("doc", docDownloadFolder_);

        fileTree.add_child("standart_path", standartPath);
        write_json(stream, fileTree);
    } catch (std::exception &ex) {
        std::cerr << "Alarm! Initing exeption: " << ex.what() << std::endl;
    }

    stream.close();
}

void FileManager::ReadFoldersPath(std::string &fileName)
{

}

}
}

