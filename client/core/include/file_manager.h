#pragma once

#include <string>

namespace m2 {
namespace core {
    class FileManager
    {
    public:
        enum FileType {
            PIC,
            AUDIO,
            VIDEO,
            ANOTHER_DOC
        };
        FileManager();
        const std::string GetStandartFilePath(FileType type);

        void SaveInStandartDir();
        void SaveInCustomDir();

    protected:
        void InitJsonFile(std::string &fileName);
        void ReadFoldersPath(std::string &fileName);

    private:
        const std::string fileManagerConfigName_;

        std::string picDownloadFolder_;
        std::string audioDownloadFolder_;
        std::string videoDownloadFolder_;
        std::string docDownloadFolder_;
    };
}
}
