// Unserialization
//
// Modern version using SerializeParams/UnserializeParams.
// Legacy code for versions < 0.8.0 has been removed for code cleanliness.

int NeuralAmpModeler::_UnserializeStateWithKnownVersion(const iplug::IByteChunk& chunk, int startPos)
{
  // We already got through the header before calling this.
  int pos = startPos;

  // Get the version
  WDL_String wVersion;
  pos = chunk.GetStr(wVersion, pos);
  std::string versionStr(wVersion.Get());

  // Read paths
  WDL_String path;
  pos = chunk.GetStr(path, pos);
  mNAMPath.Set(path.Get());
  pos = chunk.GetStr(path, pos);
  mIRPath.Set(path.Get());


  // Unserialize the parameter block written by SerializeParams
  pos = UnserializeParams(chunk, pos);

  // Stage model/IR for loading
  if (mNAMPath.GetLength())
    _StageModel(mNAMPath);
  if (mIRPath.GetLength())
    _StageIR(mIRPath);

  return pos;
}

int NeuralAmpModeler::_UnserializeStateWithUnknownVersion(const iplug::IByteChunk& chunk, int startPos)
{
  // For unknown versions, assume modern format
  return _UnserializeStateWithKnownVersion(chunk, startPos);
}
