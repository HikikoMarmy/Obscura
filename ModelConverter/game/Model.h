#pragma once

#include <vector>
#include <map>
#include "Texture.h"
#include "Mesh.h"
#include "assimp/scene.h"
#include "packfile.h"
#include <filesystem>

class Model {
public:
    Model(std::filesystem::path filename);
    void ExtractModel();
private:
    bool isCharacterModel;
    std::filesystem::path exportFolder;
    std::filesystem::path exportFilename;
    PK2_HEAD* pakFile;
    std::vector<Texture *> textures;
    std::vector<Mesh> vectorMeshes;
    SGDFILEHEADER *sgdTop;
    SGDFILEHEADER *sgdCurr;
    SGDPROCUNITHEADER *s_ppuhVUVN;
    SGDCOORDINATEDESC *sgdCoordinate;
    SGDVUMATERIALDESC *sgdMaterial;

    aiScene *scene;
    std::vector<aiMesh*> aiMeshes;
    std::vector<std::vector<unsigned int>> aiMeshesIndex;
    std::vector<aiNode*> aiNodes;
    std::vector<aiMaterial*> aiMaterials;
    std::vector<aiTexture*> aiTextures;

    void ConvertToNodeBinaryTree();
    void ReadTextures();
    int ReadTex0TextureIndex(SGDPROCUNITDATA *pProcData, std::string materialName);
    void CreateModelNodes();
    void CalculateBoneTransforms();
    void ReadSGD(PK2_HEAD* mdlPak);
    void TraverseProcUnit(SGDFILEHEADER *sgd);
    void SgSortUnitPrim(SGDPROCUNITHEADER *pHead);
    void HandleVUVNDataBlock(SGDPROCUNITHEADER *pHead);
    void HandleMaterialDataBlock(SGDPROCUNITHEADER *pHead);
    void HandleCoordinateDataBlock(SGDPROCUNITHEADER *pHead);
    void HandleBoundingBoxDataBlock(SGDPROCUNITHEADER *pHead);
    void HandleMeshDataBlock(SGDPROCUNITHEADER *pHead);
    void HandleGsImageDataBlock(SGDPROCUNITHEADER *pHead);
    void HandleTri2DataBlock(SGDPROCUNITHEADER *pHead);
    int FindMaterialIndex(SGDPROCUNITDATA *pProcData);
    void BuildScene();
    void HandleFlatMesh(int meshIndex, Vector3& vertex, Vector3& normal);
    void HandleNVLMesh(int meshIndex, Vector3& vertex, Vector3& normal);
    void HandleWeightedMesh(int meshIndex, int currentPoint, Vector3& vertex, Vector3& normal, aiMesh* mesh);
    void HandleUniqueMesh(int meshIndex, Vector3& vertex, Vector3& normal);
    SGDCOORDINATE* GetCurrentCoordinate();
    Matrix4x4 GetCoordinateMatrix(int iCoordId);
};