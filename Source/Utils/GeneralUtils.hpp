/* GeneralUtils.hpp */
#pragma once
#include <vector>

#define SAFE_DELETE(a) if( (a) != NULL ) delete (a); (a) = NULL;
#define SAFE_DELETE_ARRAY(a) if( (a) != NULL ) delete[] (a); (a) = NULL;

namespace Util { namespace Gen {

	// Delete all the allocated arrays
	template<typename T> void clearVectorOfArray(std::vector<T>& vec) 
	{    
		for ( int i = 0; i < vec.size(); i++ ) 
		{       
			SAFE_DELETE_ARRAY(vec[i]);
		}    
		vec.clear(); 
	}

	// Delete all the allocated (single) contents
	template<typename T> void clearVectorOfContent(std::vector<T>& vec) 
	{    
		for ( int i = 0; i < vec.size(); i++ ) 
		{       
			SAFE_DELETE(vec[i]);
		}    
		vec.clear(); 
	}

}}