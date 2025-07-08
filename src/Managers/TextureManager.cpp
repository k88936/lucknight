//
// Created on 7/4/25.
//

#include "TextureManager.h"
#include <QImage>
#include <algorithm>
#include <QRegularExpression>

TextureManager::~TextureManager()
{
    clearCache();
}

Texture* TextureManager::getTextures(const std::string& directory, int index, const Texture::Config& config)
{
    // Make sure the directory path is normalized
    QString qDir = QString::fromStdString(directory);
    if (!qDir.endsWith('/'))
    {
        qDir += '/';
    }
    std::string normalizedDir = qDir.toStdString();

    // Get all files in the directory if not already cached
    if (directoryCache.find(normalizedDir) == directoryCache.end())
    {
        directoryCache[normalizedDir] = getFilesInDirectory(normalizedDir);
    }

    const auto& files = directoryCache[normalizedDir];

    // Check if index is valid
    if (files.empty())
    {
        qWarning() << "TextureManager: No files found in directory:"
            << QString::fromStdString(normalizedDir);
        return nullptr;
    }

    if (index < 0 || index >= static_cast<int>(files.size()))
    {
        qWarning() << "TextureManager: Invalid index" << index
            << "for directory:" << QString::fromStdString(normalizedDir)
            << "(valid range: 0 to" << files.size() - 1 << ")";
        return nullptr;
    }

    // Get the file path for the requested index
    std::string filePath = files[index];

    // Check if the texture is already cached
    if (textureCache.find(filePath) != textureCache.end())
    {
        return textureCache[filePath];
    }

    // Load the texture
    Texture* texture = loadTexture(filePath, config);
    if (texture)
    {
        textureCache[filePath] = texture;
    }

    return texture;
}

Texture* TextureManager::getTexture(const std::string& file, const Texture::Config& config)
{
    Texture* texture;
    if (textureCache.contains(file))
    {
        texture = textureCache[file];
    }
    else
    {
        // Load the texture
        texture = loadTexture(file, config);
        if (texture)
        {
            textureCache[file] = texture;
        }
    }
    return texture;
}

std::vector<Texture*> TextureManager::getAllTextures(const std::string& directory, const Texture::Config& config)
{
    std::vector<Texture*> textures;

    // Make sure the directory path is normalized
    std::string normalizedDir = directory;
    if (!normalizedDir.empty() && normalizedDir.back() != '/')
    {
        normalizedDir += '/';
    }
    // Get all files in the directory if not already cached
    if (directoryCache.find(normalizedDir) == directoryCache.end())
    {
        directoryCache[normalizedDir] = getFilesInDirectory(normalizedDir);
    }

    const auto& files = directoryCache[normalizedDir];

    // Load all textures
    for (const auto& file : files)
    {
        // Check if the texture is already cached
        if (textureCache.contains(file))
        {
            textures.push_back(textureCache[file]);
        }
        else
        {
            // Load the texture
            Texture* texture = loadTexture(file, config);
            if (texture)
            {
                textureCache[file] = texture;
                textures.push_back(texture);
            }
        }
    }

    return textures;
}

void TextureManager::clearCache()
{
    // Delete all cached textures
    for (auto& [path, texture] : textureCache)
    {
        delete texture;
    }
    textureCache.clear();
    directoryCache.clear();
}

int TextureManager::getTextureCount(const std::string& directory)
{
    // Make sure the directory path is normalized
    QString qDir = QString::fromStdString(directory);
    if (!qDir.endsWith('/'))
    {
        qDir += '/';
    }
    std::string normalizedDir = qDir.toStdString();

    // Get all files in the directory if not already cached
    if (directoryCache.find(normalizedDir) == directoryCache.end())
    {
        directoryCache[normalizedDir] = getFilesInDirectory(normalizedDir);
    }

    return static_cast<int>(directoryCache[normalizedDir].size());
}

Texture* TextureManager::loadTexture(const std::string& filePath, const Texture::Config& config)
{
    QImage image(QString::fromStdString(filePath));
    if (image.isNull())
    {
        qWarning() << "TextureManager: Failed to load texture:" << QString::fromStdString(filePath);
        return nullptr;
    }

    // Create a new texture (1 frame, raw size, scale 1.0)
    return new Texture{.image = image, .config = config};
}

bool TextureManager::compareFilenames(const QString& a, const QString& b)
{
    // Try to extract numbers from filenames for natural sorting
    QRegularExpression re("(\\d+)");

    // Extract the base name without path or extension
    QString baseA = QFileInfo(a).completeBaseName();
    QString baseB = QFileInfo(b).completeBaseName();

    // Try to find numbers in the filenames
    auto matchA = re.match(baseA);
    auto matchB = re.match(baseB);

    // If both have numbers, compare numerically
    if (matchA.hasMatch() && matchB.hasMatch())
    {
        int numA = matchA.captured(1).toInt();
        int numB = matchB.captured(1).toInt();
        return numA < numB;
    }

    // Otherwise, compare lexicographically
    return a < b;
}

std::vector<std::string> TextureManager::getFilesInDirectory(const std::string& directory)
{
    std::vector<std::string> filePaths;

    namespace fs = std::filesystem;
    fs::path dirPath(directory);

    if (!fs::exists(dirPath))
    {
        std::cerr << "TextureManager: Directory does not exist: " << directory << std::endl;
        return filePaths;
    }

    // Get all files with supported extensions
    for (const auto& entry : fs::directory_iterator(dirPath))
    {
        if (entry.is_regular_file())
        {
            std::string ext = entry.path().extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            if (ext == ".png" || ext == ".jpg" || ext == ".jpeg")
            {
                filePaths.push_back(entry.path().string());
            }
        }
    }

    // Sort filenames using natural sorting
    std::sort(filePaths.begin(), filePaths.end(),
              [](const std::string& a, const std::string& b)
              {
                  return compareFilenames(QString::fromStdString(a), QString::fromStdString(b));
              });

    return filePaths;
}
