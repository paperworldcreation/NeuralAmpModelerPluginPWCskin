#include "NAMMetadata.h"
#include <fstream>
#include <stdexcept>

NAMMetadata::NAMMetadata()
{
  // Initialize default values
}

NAMMetadata::NAMMetadata(const std::filesystem::path& namModelPath)
{
  if (!std::filesystem::exists(namModelPath))
    throw std::runtime_error("NAM model file does not exist: " + namModelPath.string());

  std::ifstream i(namModelPath);
  nlohmann::json j;
  try
  {
    i >> j;
  }
  catch (const nlohmann::json::parse_error& e)
  {
    throw std::runtime_error("Failed to parse NAM model JSON: " + std::string(e.what()));
  }

  ParseJson(j);
}

void NAMMetadata::ParseJson(const nlohmann::json& json)
{
  if (json.contains("version"))
    mVersion = json["version"].get<std::string>();

  if (json.contains("metadata")) {
    const auto& metadata = json["metadata"];
    if (metadata.contains("name"))
      mName = metadata["name"].get<std::string>();
    if (metadata.contains("modeled_by"))
      mModeledBy = metadata["modeled_by"].get<std::string>();
    if (metadata.contains("gear_type"))
      mGearType = metadata["gear_type"].get<std::string>();
    if (metadata.contains("gear_make"))
      mGearMake = metadata["gear_make"].get<std::string>();
    if (metadata.contains("gear_model"))
      mGearModel = metadata["gear_model"].get<std::string>();
    if (metadata.contains("tone_type"))
      mToneType = metadata["tone_type"].get<std::string>();
    // Parse other metadata fields here
  }
}
