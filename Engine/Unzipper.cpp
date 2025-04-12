#include "Unzipper.h"
#include "SDL.h"
#include "SDL_image.h"
#include "../BLD/BleachNew.h"

void Engine::Unzipper::Unzip()
{
    // Open the assets zip
    std::fstream fileStream;
    fileStream.open("../Assets.zip", std::ios::in | std::ios::binary);

    if (!fileStream.is_open())
    {
        std::cout << "Open failed." << std::endl;
        return;
    }

    // Read the zip header
    ZipHeader zipHeader;
    std::streamoff zipHeaderOffset = -static_cast<std::streamoff>(sizeof(zipHeader));
    fileStream.seekg(zipHeaderOffset, std::ios::end);
    fileStream.read(reinterpret_cast<char*>(&zipHeader), sizeof(zipHeader));

    if (zipHeader.signature != kZipSignature)
    {
        std::cout << "Zip signature failed." << std::endl;
        fileStream.close();
        return;
    }

    // Read the directory data
    // An array of file headers
    char* pDirData = BLEACH_NEW_ARRAY(char,zipHeader.dirSize);
    memset(pDirData, 0, zipHeader.dirSize);
    std::streamoff dirOffset = zipHeader.dirOffset;
    fileStream.seekg(dirOffset, std::ios::beg);
    fileStream.read(pDirData, zipHeader.dirSize);

    // Read the file headers
    FileHeader* pFileHeader = reinterpret_cast<FileHeader*>(pDirData);

    for (int iFile = 0; iFile < zipHeader.numFiles; ++iFile)
    {
        if (pFileHeader->signature != kFileSignature)
        {
            std::cout << "File signature failed." << std::endl;
            fileStream.close();
            BLEACH_DELETE_ARRAY(pDirData);
            return;
        }

        char* pNameData = reinterpret_cast<char*>(pFileHeader + 1);
        char* pFileName = BLEACH_NEW_ARRAY(char,pFileHeader->nameLength+1);

        memcpy(pFileName, pNameData, pFileHeader->nameLength);
        pFileName[pFileHeader->nameLength] = NULL;

        std::cout << pFileName << std::endl;

        // Get the data header and unzip the file
        DataHeader dataHeader;
        fileStream.seekg(pFileHeader->dataOffset, std::ios::beg);
        fileStream.read(reinterpret_cast<char*>(&dataHeader), sizeof(dataHeader));

        if (dataHeader.signature != kDataSignature)
        {
            std::cout << "Data signature failed." << std::endl;
            BLEACH_DELETE_ARRAY(pDirData);
            BLEACH_DELETE_ARRAY(pFileName);
            fileStream.close();
            return;
        }

        fileStream.seekg(dataHeader.nameLength, std::ios::cur);

        // Alocate enough data for the uncompressed data
        // plus one more bye to add a null-terminator just in case the file is text
        char* pUncompressedData = BLEACH_NEW_ARRAY(char,dataHeader.uncompressedSize + 1);
        if (dataHeader.compression == Z_DEFLATED)
        {
            char* pCompressedData = BLEACH_NEW_ARRAY(char,dataHeader.compressedSize);
            fileStream.read(pCompressedData, dataHeader.compressedSize);

            z_stream zStream;

            zStream.next_in = (Bytef*)pCompressedData;
            zStream.avail_in = (uInt)dataHeader.compressedSize;

            zStream.next_out = (Byte*)pUncompressedData;
            zStream.avail_out = (uInt)dataHeader.uncompressedSize;

            zStream.zalloc = (alloc_func)0;
            zStream.zfree = (free_func)0;

            int zStatus = inflateInit2(&zStream, -MAX_WBITS);

            if (zStatus == Z_OK)
            {
                zStatus = inflate(&zStream, Z_FINISH);
                inflateEnd(&zStream);

                // You have to end the inflation AGAIN
                inflateEnd(&zStream);
            }
            BLEACH_DELETE_ARRAY(pCompressedData);
        }
        else
        {
            // Data is alread uncompressed so just read it
            fileStream.read(pUncompressedData, dataHeader.uncompressedSize);
        }

        // Append the null-terminator just in case it is text
        pUncompressedData[dataHeader.uncompressedSize] = NULL;

        //Figure out what kind of file and sort as needed (imagees, or just as in and put in text map/default map
        std::string pFileNameStr = pFileName;
        if (pFileNameStr.find(".xml") != std::string::npos)
        {
            m_pXMLs.emplace("../" + pFileNameStr, pUncompressedData);
        }
        else if (pFileNameStr.find(".tmx") != std::string::npos)
        {
            m_pTMXs.emplace("../" + pFileNameStr, pUncompressedData);
        }
        else if (pFileNameStr.find(".lua") != std::string::npos)
        {
            m_pLuas.emplace("../" + pFileNameStr, pUncompressedData);
        }
        else if (pFileNameStr.find(".png") != std::string::npos || pFileNameStr.find(".jpg") != std::string::npos || pFileNameStr.find(".gif") != std::string::npos)
        {
            //read with RWops                                                                       //$ Move back into image 
            SDL_RWops* pRWops = SDL_RWFromMem(pUncompressedData, dataHeader.uncompressedSize);

            pImageSurface = IMG_Load_RW(pRWops, 0);
            
            m_pImages.emplace(pFileName, pImageSurface);
            
            SDL_FreeRW(pRWops);
        }

        // Continue to the next file header
        pFileHeader = reinterpret_cast<FileHeader*>(pNameData + pFileHeader->nameLength);

        BLEACH_DELETE_ARRAY(pFileName);
        BLEACH_DELETE_ARRAY(pUncompressedData);

    }

    // Close the assets zip
    BLEACH_DELETE_ARRAY(pDirData);
    fileStream.close();
    return;
}

void Engine::Unzipper::CloseUnzipper()      //$ Move m_pImages out of unzipper and this is not needed
{
    //SDL_FreeSurface(pImageSurface);
}
