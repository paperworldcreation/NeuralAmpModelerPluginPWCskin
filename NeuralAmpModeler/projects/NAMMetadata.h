#pragma once

#include <string>
#include <filesystem>
#include "json.hpp"

class NAMMetadata
{
public:
  NAMMetadata();
  NAMMetadata(const std::filesystem::path& namModelPath);

  // Getters for accessing metadata fields
  const std::string& GetVersion() const { return mVersion; }
  const std::string& GetName() const { return mName; }
  const std::string& GetModeledBy() const { return mModeledBy; }
  const std::string& GetGearType() const { return mGearType; }
  const std::string& GetGearMake() const { return mGearMake; }
  const std::string& GetGearModel() const { return mGearModel; }
  const std::string& GetToneType() const { return mToneType; }
  // Add getters for other metadata fields as needed

private:
  void ParseJson(const nlohmann::json& json);

  // Member variables to store metadata
  std::string mVersion;
  std::string mName;
  std::string mModeledBy;
  std::string mGearType;
  std::string mGearMake;
  std::string mGearModel;
  std::string mToneType;
  // Add other member variables for date, loudness, gain, etc.
};