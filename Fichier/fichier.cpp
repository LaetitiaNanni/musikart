#include "fichier.hpp"

#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags



//std::vector<glimac::ShapeVertex> m_Vertices; 

/*Afficher la scène*/
void DoTheSceneProcessing(const aiScene* scene){

	std::cout << "scene "<<scene<< std::endl;
	std::cout << "&scene "<<&scene<< std::endl;
	std::cout << "*scene->mMeshes "<<*scene->mMeshes<< std::endl;
	std::cout << "scene->mMeshes "<< *scene->mMeshes << std::endl;
	std::cout << "scene->mNumMeshes "<< scene->mNumMeshes << std::endl;
	std::cout << "scene->mRootNode "<< scene->mRootNode << std::endl;

	for (int i = 0; i< scene->mNumMeshes; ++i){
		std::cout << "(scene->mMeshes[i])"<< (scene->mMeshes[i]) << std::endl;
	}


}

/*Afficher les erreurs lors de l'import de fichier 3D*/
void DoTheErrorLogging( const char* error){
	std::cout << "ErrorLogging: "<< error	<< std::endl;
}

/*bool DoTheImportThing( const std::string& pFile)
{
	// Create an instance of the Importer class
	Assimp::Importer importer;
	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll
	// propably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile( pFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	
	// If the import failed, report it
	if( !scene)
	{
		DoTheErrorLogging( importer.GetErrorString());
		return false;
		std::cout << "Problème de chargement du fichier 3D" << std::endl;
	}
	
	// Now we can access the file's contents.
	DoTheSceneProcessing(scene);
	// We're done. Everything will be cleaned up by the importer destructor
	return true;
}

*/

std::vector<glimac::ShapeVertex> DoTheImportThing(const std::string& sFilePath){


	std::vector<glimac::ShapeVertex> m_Vertices; 

   	Assimp::Importer importer; 
   	const aiScene* scene = importer.ReadFile( sFilePath,  
    	aiProcess_CalcTangentSpace       |  
      	aiProcess_Triangulate            | 
      	aiProcess_JoinIdenticalVertices  | 
      	aiProcess_SortByPType); 

   	if(!scene) 
   	{ 
    	std::cerr << "Erreur d'importation" << std::endl;
    	return m_Vertices; 
   	} 

   	bool t=false;
   	std::cout << scene->mNumMeshes << " meshes" << std::endl;

   	// on parcourt les meshes
   	for(int i=0; i<scene->mNumMeshes;++i) { 
    	aiMesh* mesh = scene->mMeshes[i]; 
      	int iMeshFaces = mesh->mNumFaces; 

      	for(int j=0;j<iMeshFaces;++j) { 

        	const aiFace& face = mesh->mFaces[j]; 
         	
         	for(int k=0;k<3;++k) { 
         		
         		glimac::ShapeVertex vertex;
				vertex.position.x = mesh->mVertices[face.mIndices[k]].x;
				vertex.position.y = mesh->mVertices[face.mIndices[k]].y;
				vertex.position.z = mesh->mVertices[face.mIndices[k]].z;

				//std::cout << "Position done" << vertex.position.x << "  " <<vertex.position.y << "  "<<vertex.position.z << std::endl;
				
				if (mesh->HasTextureCoords(0)) {
					vertex.texCoords.x = mesh->mTextureCoords[0][face.mIndices[k]].x;
					vertex.texCoords.y = mesh->mTextureCoords[0][face.mIndices[k]].y;

					if(!t){
						std::cout << "Textures reperees" << std::endl;
						t=true;
					}
				}
				else {
					vertex.texCoords.x = mesh->mVertices[face.mIndices[k]].x;
					vertex.texCoords.y = mesh->mVertices[face.mIndices[k]].y;
				}
				vertex.normal.x = mesh->HasNormals() ? mesh->mNormals[face.mIndices[k]].x : vertex.normal.x=1.0f;
				vertex.normal.y = mesh->HasNormals() ? mesh->mNormals[face.mIndices[k]].y : vertex.normal.y=1.0f;
				vertex.normal.z = mesh->HasNormals() ? mesh->mNormals[face.mIndices[k]].z : vertex.normal.z=1.0f;
				
				// std::cout << "Normal done" << std::endl;
				m_Vertices.push_back(vertex);

        	} 
      	}  
   	} 

   	return m_Vertices;
}