#include "fichier.hpp"

#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags


void DoTheSceneProcessing(const aiScene* scene){
	std::cout << "scene "<<scene<< std::endl;
	std::cout << "&scene "<<&scene<< std::endl;
	std::cout << "scene->mMeshes "<< scene->mMeshes << std::endl;
}

void DoTheErrorLogging( const char* error){
	std::cout << "ErrorLogging: "<< error	<< std::endl;
}

bool DoTheImportThing( const std::string& pFile)
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


	/*const aiScene* scene = importer.ReadFile( pFile,
		aiProcess_CalcTangentSpace );
*/

	std::cout << "scene "<< scene << std::endl;

	// If the import failed, report it
	if( !scene)
	{
		DoTheErrorLogging( importer.GetErrorString());
		return false;
		std::cout << "Problème de chargement du fichier 3D" << std::endl;
	}
	
	// Now we can access the file's contents.
	DoTheSceneProcessing( scene);
	// We're done. Everything will be cleaned up by the importer destructor
	return true;
}



int main () {
	const aiScene* scene = NULL;
	const std::string String = "bed1.obj";
	std::cout << "String "<< String << std::endl;
	const std::string& refString = String; 
	bool wesh =  DoTheImportThing(refString);

		return 1;
}