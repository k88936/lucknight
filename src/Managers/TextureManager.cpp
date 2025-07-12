#include "TextureManager.h"
#include <QImage>
#include <cassert>
#include <filesystem>
#include <regex>
#include <algorithm>
#include <ranges>
#include <vector>
#include <string>
#include <unordered_map>

namespace fs = std::filesystem;

TextureManager::~TextureManager()
{
    clearCache();
}

Texture* TextureManager::getTextures(const std::string& directory, int index, const Texture::Config& config)
{
    // Normalize directory path
    std::string normalizedDir = directory;
    if (!normalizedDir.empty() && normalizedDir.back() != '/')
    {
        normalizedDir += '/';
    }

    // Cache directory contents if not already cached
    if (!directoryCache.contains(normalizedDir))
    {
        directoryCache[normalizedDir] = getFilesInDirectory(normalizedDir);
    }

    const auto& files = directoryCache[normalizedDir];

    // Validate index
    assert(!files.empty() && "TextureManager: No files found in directory");
    assert(index >= 0 && index < static_cast<int>(files.size()) && "TextureManager: Invalid index for directory");

    // Get file path
    const std::string filePath = files[index];

    // Return cached texture or load new one
    if (textureCache.contains(filePath))
    {
        return textureCache[filePath];
    }

    Texture* texture = loadTexture(filePath, config);
    assert(texture);
    textureCache[filePath] = texture;

    return texture;
}

Texture* TextureManager::getTexture(const std::string& file, const Texture::Config& config)
{
    if (textureCache.contains(file))
    {
        return textureCache[file];
    }

    Texture* texture = loadTexture(file, config);
    assert(texture);
    textureCache[file] = texture;

    return texture;
}

std::vector<const Texture*> TextureManager::getAllTextures(const std::string& directory, const Texture::Config& config)
{
    std::vector<const Texture*> textures;

    std::string normalizedDir = directory;
    if (!normalizedDir.empty() && normalizedDir.back() != '/')
    {
        normalizedDir += '/';
    }

    if (!directoryCache.contains(normalizedDir))
    {
        directoryCache[normalizedDir] = getFilesInDirectory(normalizedDir);
    }

    const auto& files = directoryCache[normalizedDir];

    for (const auto& file : files)
    {
        if (textureCache.contains(file))
        {
            textures.push_back(textureCache[file]);
        }
        else
        {
            Texture* texture = loadTexture(file, config);
            assert(texture);
            textureCache[file] = texture;
            textures.push_back(texture);
        }
    }

    return textures;
}

void TextureManager::clearCache()
{
    for (const auto& texture : textureCache | std::views::values)
    {
        delete texture;
    }
    textureCache.clear();
    directoryCache.clear();
}

int TextureManager::getTextureCount(const std::string& directory)
{
    std::string normalizedDir = directory;
    if (!normalizedDir.empty() && normalizedDir.back() != '/')
    {
        normalizedDir += '/';
    }

    if (directoryCache.find(normalizedDir) == directoryCache.end())
    {
        directoryCache[normalizedDir] = getFilesInDirectory(normalizedDir);
    }

    return static_cast<int>(directoryCache[normalizedDir].size());
}

Texture* TextureManager::loadTexture(const std::string& filePath, const Texture::Config& config)
{
    const QImage image(QString::fromStdString(filePath));
    assert(!image.isNull() && "TextureManager: Failed to load texture");

    return new Texture{.image = image, .config = config};
}

// Helper function for natural sort
bool extractNumberAndCompare(const std::string& a, const std::string& b)
{
    std::string baseA = a.substr(a.find_last_of("/\\") + 1);
    std::string baseB = b.substr(b.find_last_of("/\\") + 1);

    std::regex numRegex("(\\d+)");
    std::smatch matchA, matchB;

    bool hasNumA = std::regex_search(baseA, matchA, numRegex);
    bool hasNumB = std::regex_search(baseB, matchB, numRegex);

    if (hasNumA && hasNumB)
    {
        int numA = std::stoi(matchA[1].str());
        int numB = std::stoi(matchB[1].str());
        return numA < numB;
    }

    return a < b;
}

std::vector<std::string> TextureManager::getFilesInDirectory(const std::string& directory)
{
    std::vector<std::string> filePaths;

    fs::path dirPath(directory);
    assert(fs::exists(dirPath) && "TextureManager: Directory does not exist: ");

    const std::vector<std::string> supportedExtensions = {".jpg", ".jpeg", ".png"};
    for (const auto& entry : fs::directory_iterator(dirPath))
    {
        if (entry.is_regular_file())
        {
            std::string ext = entry.path().extension().string();
            std::ranges::transform(ext, ext.begin(), ::tolower);
            if (std::ranges::find(supportedExtensions, ext) != supportedExtensions.end())
            {
                filePaths.push_back(entry.path().string());
            }
        }
    }
    // Sort using natural order
    std::ranges::sort(filePaths, extractNumberAndCompare);
    return filePaths;
}
