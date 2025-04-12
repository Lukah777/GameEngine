#pragma once
#define ZLIB_WINAPI
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include "../Libs/zLib/zlib.h"
struct SDL_Surface;


namespace Engine
{
    class Unzipper
    {
    private:
        static constexpr uint32_t kZipSignature = 0x06054b50;

#pragma pack(1)
        struct ZipHeader
        {
            uint32_t signature = 0;
            uint16_t diskIndex = 0;
            uint16_t StartDisk = 0;
            uint16_t numFiles = 0;
            uint16_t totalFiles = 0;
            uint32_t dirSize = 0;
            uint32_t dirOffset = 0;
            uint16_t commentLength = 0;
        };
#pragma pack()

        static constexpr uint32_t kFileSignature = 0x02014b50;

#pragma pack(1)
        struct FileHeader
        {
            uint32_t signature = 0;
            uint16_t versionMade = 0;
            uint16_t versionNeeded = 0;
            uint16_t flag = 0;
            uint16_t compression = 0;
            uint16_t time = 0;
            uint16_t date = 0;
            uint32_t crcCode = 0;
            uint32_t compressedSize = 0;
            uint32_t uncompressedSize = 0;
            uint16_t nameLength = 0;
            uint16_t extraLength = 0;
            uint16_t commentLength = 0;
            uint16_t startDisk;
            uint16_t internalAttributes = 0;
            uint32_t externalAttributes = 0;
            uint32_t dataOffset = 0;
        };
#pragma pack()

        static constexpr uint32_t kDataSignature = 0x04034b50;

#pragma pack(1)
        struct DataHeader
        {
            uint32_t signature = 0;
            uint16_t version = 0;
            uint16_t flag = 0;
            uint16_t compression = 0;
            uint16_t time = 0;
            uint16_t data = 0;
            uint32_t crcCode = 0;
            uint32_t compressedSize = 0;
            uint32_t uncompressedSize = 0;
            uint16_t nameLength = 0;
            uint16_t extraLength = 0;
        };
#pragma pack()

        SDL_Surface* pImageSurface;
        std::unordered_map<std::string, SDL_Surface*> m_pImages;
        std::unordered_map<std::string, std::string> m_pXMLs;
        std::unordered_map<std::string, std::string> m_pTMXs;
        std::unordered_map<std::string, std::string> m_pLuas;


    public:
        void Unzip();
        SDL_Surface* GetUnzippedImgs(std::string file)
        {
            return m_pImages[file];
        }
        std::string GetUnzippedXML(std::string file)
        {
            return m_pXMLs[file];
        }
        std::string GetUnzippedTMX(std::string file)
        {
            return m_pTMXs[file];
        }
        std::string GetUnzippedLua(std::string file)
        {
            return m_pLuas[file];
        }
        void CloseUnzipper();
    };
}