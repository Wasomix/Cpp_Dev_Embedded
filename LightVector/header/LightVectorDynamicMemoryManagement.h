/*
 * LightVectorDynamicMemoryManagement.h
 *
 *  Created on: Jan 6, 2021
 *      Author: Sergio Ferrándiz
 *      email: sergio.ferrandiz@gmail.com
 *
 * This class aims to manage dynamic memory from lighter version
 * of std::vector.
 */

#ifndef LIGHTVECTORDYNAMICMEMORYMANAGEMENT_H
#define LIGHTVECTORDYNAMICMEMORYMANAGEMENT_H

#include "../../Common/header/DataTypes.h"

template<class T>
class LightVectorDynamicMemoryManagement{
public:
    LightVectorDynamicMemoryManagement()=default;
    ~LightVectorDynamicMemoryManagement()=default;
    void DeleteVector(T ** vectorOfData, const uint32_t& totalPositions)const;
    void AllocateMemoryTo(T **ptr, const uint32_t& desiredSize)const;

private:
    bool IsItAnArray(const uint32_t& desiredSize)const;
    void DeleteArrayOfElements(T ** vectorOfData)const;
    void DeleteSingleElement(T ** singleElement)const;

};

template<class T>
void LightVectorDynamicMemoryManagement<T>::AllocateMemoryTo(T **ptr,
                                                             const uint32_t& desiredSize)const
{
    if(IsItAnArray(desiredSize)){
        *ptr = new T[desiredSize];
    } else {
        *ptr = new T;
    }
}

template<class T>
bool LightVectorDynamicMemoryManagement<T>::IsItAnArray(const uint32_t& desiredSize)const
{
    const uint32_t C_MINIMUM_ARRAY_SIZE = 2;
    return desiredSize>=C_MINIMUM_ARRAY_SIZE;
}

template<class T>
void LightVectorDynamicMemoryManagement<T>::DeleteVector(T ** vectorOfData,
                                                         const uint32_t& totalPositions)const
{
    if(*vectorOfData != nullptr){
        if(IsItAnArray(totalPositions)){
			DeleteArrayOfElements(vectorOfData);
        } else {
			DeleteSingleElement(vectorOfData);
        }
    }
}

template<class T>
void LightVectorDynamicMemoryManagement<T>::DeleteArrayOfElements(T ** vectorOfData)const
{
	delete [] *vectorOfData;
	*vectorOfData = nullptr;
}

template<class T>
void LightVectorDynamicMemoryManagement<T>::DeleteSingleElement(T ** singleElement)const
{
	delete *singleElement;
	*singleElement = nullptr;
}

#endif // LIGHTVECTORDYNAMICMEMORYMANAGEMENT_H
