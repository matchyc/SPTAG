// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#ifndef _SPTAG_VECTORINDEX_H_
#define _SPTAG_VECTORINDEX_H_

#include "Common.h"
#include "SearchQuery.h"
#include "VectorSet.h"
#include "MetadataSet.h"
#include "inc/Helper/SimpleIniReader.h"
#include <unordered_set>
#include "inc/Core/Common/IQuantizer.h"

namespace SPTAG
{

class IAbortOperation
{
public:
    virtual bool ShouldAbort() = 0;
};

class VectorIndex
{
public:
    std::string current_test_config;
    std::string save_file_name;
    std::string stat_res_path;
    std::string current_query_suffix;

    void SetQuerySuffix(std::string s) {
        current_query_suffix = s;
    }
    VectorIndex() {
        // ofs.open("/home/cm/projects/ann/exp_result/spann_cmp/query_0_50.bin", std::ofstream::out | std::ios_base::binary | std::ios::app);
        // int32_t dummy_num = 10, dummy_dim = 10;
        // GetOfs().write((char*)&dummy_num, sizeof(int32_t));
        // GetOfs().write((char*)&dummy_dim, sizeof(int32_t));
        // std::remove("/home/cm/projects/ann/exp_result/spann_visited_vec.bin");
        // ofs.open("/home/cm/projects/ann/exp_result/spann_visited_vec.bin", std::ofstream::out | std::ios_base::binary | std::ios::app);
    }

    virtual ~VectorIndex();

    virtual ErrorCode BuildIndex(const void* p_data, SizeType p_vectorNum, DimensionType p_dimension, bool p_normalized = false, bool p_shareOwnership = false) = 0;
    
    virtual ErrorCode AddIndex(const void* p_data, SizeType p_vectorNum, DimensionType p_dimension, std::shared_ptr<MetadataSet> p_metadataSet, bool p_withMetaIndex = false, bool p_normalized = false) = 0;

    virtual ErrorCode DeleteIndex(const void* p_vectors, SizeType p_vectorNum) = 0;

    virtual ErrorCode SearchIndex(QueryResult& p_results, bool p_searchDeleted = false) const = 0;
    
    virtual ErrorCode RefineSearchIndex(QueryResult &p_query, bool p_searchDeleted = false) const = 0;

    virtual ErrorCode SearchTree(QueryResult &p_query) const = 0;

    virtual ErrorCode RefineIndex(std::shared_ptr<VectorIndex>& p_newIndex) = 0;

    virtual float AccurateDistance(const void* pX, const void* pY) const = 0;
    virtual float ComputeDistance(const void* pX, const void* pY) const = 0;
    virtual const void* GetSample(const SizeType idx) const = 0;
    virtual bool ContainSample(const SizeType idx) const = 0;
    virtual bool NeedRefine() const = 0;
   
    virtual DimensionType GetFeatureDim() const = 0;
    virtual SizeType GetNumSamples() const = 0;
    virtual SizeType GetNumDeleted() const = 0;

    virtual DistCalcMethod GetDistCalcMethod() const = 0;
    virtual IndexAlgoType GetIndexAlgoType() const = 0;
    virtual VectorValueType GetVectorValueType() const = 0;

    virtual std::string GetParameter(const char* p_param, const char* p_section = nullptr) const = 0;
    virtual ErrorCode SetParameter(const char* p_param, const char* p_value, const char* p_section = nullptr) = 0;
    virtual ErrorCode UpdateIndex() = 0;

    virtual bool IsReady() const { return m_bReady; }
    virtual void SetReady(bool p_ready) { m_bReady = p_ready; }

    virtual std::shared_ptr<std::vector<std::uint64_t>> CalculateBufferSize() const;

    virtual ErrorCode SaveIndex(std::string& p_config, const std::vector<ByteArray>& p_indexBlobs);

    virtual ErrorCode SaveIndex(const std::string& p_folderPath);

    virtual ErrorCode SaveIndexToFile(const std::string& p_file, IAbortOperation* p_abort = nullptr);

    virtual ErrorCode BuildIndex(std::shared_ptr<VectorSet> p_vectorSet, std::shared_ptr<MetadataSet> p_metadataSet, bool p_withMetaIndex = false, bool p_normalized = false, bool p_shareOwnership = false);
    
    virtual ErrorCode BuildIndex(bool p_normalized = false) { return ErrorCode::Undefined; }

    virtual ErrorCode AddIndex(std::shared_ptr<VectorSet> p_vectorSet, std::shared_ptr<MetadataSet> p_metadataSet, bool p_withMetaIndex = false, bool p_normalized = false);

    virtual ErrorCode DeleteIndex(ByteArray p_meta);

    virtual ErrorCode MergeIndex(VectorIndex* p_addindex, int p_threadnum, IAbortOperation* p_abort);
    
    virtual const void* GetSample(ByteArray p_meta, bool& deleteFlag);

    virtual ErrorCode SearchIndex(const void* p_vector, int p_vectorCount, int p_neighborCount, bool p_withMeta, BasicResult* p_results) const;

    virtual void ApproximateRNG(std::shared_ptr<VectorSet>& fullVectors, std::unordered_set<SizeType>& exceptIDS, int candidateNum, Edge* selections, int replicaCount, int numThreads, int numTrees, int leafSize, float RNGFactor, int numGPUs);

    static void SortSelections(std::vector<Edge>* selections);

    virtual std::string GetParameter(const std::string& p_param, const std::string& p_section = "Index") const;
    virtual ErrorCode SetParameter(const std::string& p_param, const std::string& p_value, const std::string& p_section = "Index");

    virtual ByteArray GetMetadata(SizeType p_vectorID) const;
    virtual MetadataSet* GetMetadata() const;
    virtual void SetMetadata(MetadataSet* p_new);

    virtual std::string GetIndexName() const 
    { 
        if (m_sIndexName == "") return Helper::Convert::ConvertToString(GetIndexAlgoType());
        return m_sIndexName; 
    }
    virtual void SetIndexName(std::string p_name) { m_sIndexName = p_name; }

    virtual void SetQuantizerFileName(std::string p_QuantizerFileName) { m_sQuantizerFile = p_QuantizerFileName; }

    virtual void SetQuantizerADC(bool enableADC) {
        if (m_pQuantizer) m_pQuantizer->SetEnableADC(enableADC);
    }

    virtual void SetQuantizer(std::shared_ptr<SPTAG::COMMON::IQuantizer> quantizer) = 0;

    virtual ErrorCode LoadQuantizer(std::string p_quantizerFile);

    static std::shared_ptr<VectorIndex> CreateInstance(IndexAlgoType p_algo, VectorValueType p_valuetype);

    static ErrorCode LoadIndex(const std::string& p_loaderFilePath, std::shared_ptr<VectorIndex>& p_vectorIndex);

    static ErrorCode LoadIndexFromFile(const std::string& p_file, std::shared_ptr<VectorIndex>& p_vectorIndex);

    static ErrorCode LoadIndex(const std::string& p_config, const std::vector<ByteArray>& p_indexBlobs, std::shared_ptr<VectorIndex>& p_vectorIndex);

    static std::uint64_t EstimatedVectorCount(std::uint64_t p_memory, DimensionType p_dimension, VectorValueType p_valuetype, SizeType p_vectorsInBlock, SizeType p_maxmeta, IndexAlgoType p_algo, int p_treeNumber, int p_neighborhoodSize);

    static std::uint64_t EstimatedMemoryUsage(std::uint64_t p_vectorCount, DimensionType p_dimension, VectorValueType p_valuetype, SizeType p_vectorsInBlock, SizeType p_maxmeta, IndexAlgoType p_algo, int p_treeNumber, int p_neighborhoodSize);

    virtual std::shared_ptr<std::vector<std::uint64_t>> BufferSize() const = 0;

    virtual std::shared_ptr<std::vector<std::string>> GetIndexFiles() const = 0;

    virtual ErrorCode SaveConfig(std::shared_ptr<Helper::DiskIO> p_configout) = 0;

    virtual ErrorCode SaveIndexData(const std::vector<std::shared_ptr<Helper::DiskIO>>& p_indexStreams) = 0;

    virtual ErrorCode LoadConfig(Helper::IniReader& p_reader) = 0;

    virtual ErrorCode LoadIndexData(const std::vector<std::shared_ptr<Helper::DiskIO>>& p_indexStreams) = 0;

    virtual ErrorCode LoadIndexDataFromMemory(const std::vector<ByteArray>& p_indexBlobs) = 0;

    virtual ErrorCode DeleteIndex(const SizeType& p_id) = 0;

    virtual ErrorCode RefineIndex(const std::vector<std::shared_ptr<Helper::DiskIO>>& p_indexStreams, IAbortOperation* p_abort) = 0;

    inline bool HasMetaMapping() const { return nullptr != m_pMetaToVec; }

    inline SizeType GetMetaMapping(std::string& meta) const;
    void UpdateMetaMapping(const std::string& meta, SizeType i);

    void BuildMetaMapping(bool p_checkDeleted = true);

    std::ofstream& GetOfs() { return ofs;};
    std::string GetSaveFileName() { return VectorIndex::save_file_name;};
    std::string GetStatResPath() { return stat_res_path; }
    void SetSaveFileName(std::string s) { 
        save_file_name = s; 
    };
    void SetStatResPath(std::string s) {
        stat_res_path = s;
    };
    
    void PrepareOfstream() {
#ifdef OUTPUT_PT
        // save_file_name = "/home/cm/projects/ann/exp_result/" + save_file_name + ".bin";
        LOG(Helper::LogLevel::LL_Info, "File name %s \n", save_file_name.c_str());
        // if (GetOfs().is_open()) {
        //     GetOfs().close();
        // }
        GetOfs().open(GetSaveFileName().c_str(), std::ofstream::trunc | std::ofstream::out | std::ios_base::binary);
        if(!GetOfs().is_open()) {
            LOG(Helper::LogLevel::LL_Error, "Open file %s error.", save_file_name.c_str());
            exit(-1);
        }

        int32_t dummy_num = 10, dummy_dim = 10;
        GetOfs().write((char*)&dummy_num, sizeof(int32_t));
        GetOfs().write((char*)&dummy_dim, sizeof(int32_t));
#endif // DEBUG
        // GetOfs().close();
        // GetOfs().write(GetSaveFileName().c_str(), 10);
    };
private:
    ErrorCode LoadIndexConfig(Helper::IniReader& p_reader);

    ErrorCode SaveIndexConfig(std::shared_ptr<Helper::DiskIO> p_configOut);

protected:
    bool m_bReady = false;
    std::string m_sIndexName = "";
    std::string m_sMetadataFile = "metadata.bin";
    std::string m_sMetadataIndexFile = "metadataIndex.bin";
    std::string m_sQuantizerFile = "quantizer.bin";
    std::shared_ptr<MetadataSet> m_pMetadata;
    std::shared_ptr<void> m_pMetaToVec;

public:
    int m_iDataBlockSize = 1024 * 1024;
    int m_iDataCapacity = MaxSize;
    int m_iMetaRecordSize = 10;
    std::ofstream ofs;
    std::shared_ptr<SPTAG::COMMON::IQuantizer> m_pQuantizer = nullptr;
};


} // namespace SPTAG

#endif // _SPTAG_VECTORINDEX_H_
