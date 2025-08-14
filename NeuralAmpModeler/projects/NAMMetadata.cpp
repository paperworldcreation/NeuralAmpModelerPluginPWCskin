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

  if (json.contains("metadata"))
  {
    const auto& metadata = json["metadata"];
    if (metadata.contains("name") && metadata["name"].is_string())
      mName = metadata["name"].get<std::string>();
    else
      mName = "n/a";

    if (metadata.contains("modeled_by") && metadata["modeled_by"].is_string())
      mModeledBy = metadata["modeled_by"].get<std::string>();
    else
      mModeledBy = "n/a";

    if (metadata.contains("gear_type") && metadata["gear_type"].is_string())
      mGearType = metadata["gear_type"].get<std::string>();
    else
      mGearType = "n/a";

    if (metadata.contains("gear_make") && metadata["gear_make"].is_string())
      mGearMake = metadata["gear_make"].get<std::string>();
    else
      mGearMake = "n/a";

    if (metadata.contains("gear_model") && metadata["gear_model"].is_string())
      mGearModel = metadata["gear_model"].get<std::string>();
    else
      mGearModel = "n/a";

    if (metadata.contains("tone_type") && metadata["tone_type"].is_string())
      mToneType = metadata["tone_type"].get<std::string>();
    else
      mToneType = "n/a";
    // Parse other metadata fields here
  }
}