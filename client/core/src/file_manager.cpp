#include "file_manager.h"

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
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

    file.seekg(0, std::ios::end);
    if (file.tellg() == 0) {
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

    downloadFolderPath.append(del).append("Downloads").append(del).append("m2 files");
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
        std::cerr << "Alarm! Initing exception: " << ex.what() << std::endl;
    }

    stream.close();
}

void FileManager::ReadFoldersPath(std::string &fileName)
{
    std::ifstream stream(fileName);

    picDownloadFolder_.clear();
    audioDownloadFolder_.clear();
    videoDownloadFolder_.clear();
    docDownloadFolder_.clear();

    try {
        ptree fileTree;

        read_json(stream, fileTree);

        picDownloadFolder_ = fileTree.get<std::string>("standart_path.pic");
        audioDownloadFolder_ = fileTree.get<std::string>("standart_path.audio");
        videoDownloadFolder_ = fileTree.get<std::string>("standart_path.video");
        docDownloadFolder_ = fileTree.get<std::string>("standart_path.doc");

    } catch (std::exception &ex) {
        std::cerr << "Alarm! Reading exception: " << ex.what() << std::endl;
    }
}

}
}

