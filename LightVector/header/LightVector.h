/*
 * LightVector.h
 *
 *  Created on: Dic 18, 2020
 *      Author: Sergio Ferrándiz
 *      email: sergio.ferrandiz@gmail.com
 *
 * This class aims to implement a reduced version from vector from standard
 * library.
 *
 * LightVector can be especially useful for embedded systems due to take
 * advantage of the safety provided by vector from standard library.
 */

#ifndef LIGHTVECTOR_H
#define LIGHTVECTOR_H

#include "../../Common/header/DataTypes.h"

template<class T>
class LightVector{
public:
    LightVector():vectorOfData_(nullptr), totalPositions_(0), currentPosition_(0){}
    ~LightVector();
    void reserve(uint32_t desiredSize);
    uint32_t size();
    void push_back(T element);
    void pop_back();
    T& at(const uint32_t& indexElement);
    void clear();
    const uint32_t& GetNumberOfElements();

private:
    bool IsDesiredSizeGreaterThanCurrentSize(const uint32_t& desiredSize) const;
    void PushBackNewElement(T element);
    T& GetElement(const uint32_t& indexElement);
    T& GetDefaultElement();
    void DeleteArrayAndResetCurrentPositionAndVectorSize();
    void ResetCurrentPositon();
    void ResetTotalVectorSize();
    void IncreaseCurrentPosition();
    void DecreaseCurrentPosition();
    bool IsVectorEmpty();
    bool IsIndexInsideVectorRange(const uint32_t& indexElement);
    void CopyDataAndAllocateMemory(const uint32_t& desiredSize);
    void AllocateMemoryToVectorOfData(const uint32_t& desiredSize);
    void AllocateMemoryTo(T **ptr, const uint32_t& desiredSize);
    void UpdateVectorSize(const uint32_t& desiredSize);
    bool IsItAnArray(const uint32_t& desiredSize);
    void CopyDataFromCurrentVectorIntoAuxiliaryVector(T * auxiliaryVector);
    void CopyDataFromAuxiliaryVectorIntoCurrentVector(T * auxiliaryVector);
    void CopyDataFromSourceIntoDestiny(T *vectorSource, T * vectorDestiny);
	void DeleteVector(T ** vectorOfData);
	void DeleteArrayOfElements(T ** vectorOfData);
    void DeleteSingleElement(T ** singleElement);

private:
    T * vectorOfData_;
    uint32_t totalPositions_;
    uint32_t currentPosition_;
};

template<class T>
LightVector<T>::~LightVector()
{
    if(vectorOfData_!= nullptr){
        DeleteVector(&vectorOfData_);
    }
}

template<class T>
void LightVector<T>::reserve(uint32_t desiredSize){
    if(IsDesiredSizeGreaterThanCurrentSize(desiredSize)){
        CopyDataAndAllocateMemory(desiredSize);
    }
}

template<class T>
uint32_t LightVector<T>::size(){
    return totalPositions_;
}

template<class T>
void LightVector<T>::push_back(T element){
    const uint32_t desiredSize = currentPosition_ + 1;
    if(IsDesiredSizeGreaterThanCurrentSize(desiredSize)){
        reserve(desiredSize);
    }

    PushBackNewElement(element);
    IncreaseCurrentPosition();
}

template<class T>
void LightVector<T>::pop_back(){
    DecreaseCurrentPosition();
    CopyDataAndAllocateMemory(currentPosition_);
}

template<class T>
T& LightVector<T>::at(const uint32_t& indexElement){
    if(IsIndexInsideVectorRange(indexElement)){
        return GetElement(indexElement);
    } else {
        return GetDefaultElement();
    }
}

template<class T>
void LightVector<T>::clear(){
    DeleteArrayAndResetCurrentPositionAndVectorSize();
}

template<class T>
const uint32_t& LightVector<T>::GetNumberOfElements(){
    return currentPosition_;
}

template<class T>
bool LightVector<T>::IsDesiredSizeGreaterThanCurrentSize(const uint32_t& desiredSize) const {
    return desiredSize > totalPositions_;
}

template<class T>
void LightVector<T>::PushBackNewElement(T element){
    vectorOfData_[currentPosition_] = element;
}

template<class T>
T& LightVector<T>::GetElement(const uint32_t& indexElement){
    return vectorOfData_[indexElement];
}

template<class T>
T& LightVector<T>::GetDefaultElement(){
    uint32_t desiredSize = 1;
    AllocateMemoryTo(&vectorOfData_, desiredSize);
    return *vectorOfData_;
}

template<class T>
void LightVector<T>::DeleteArrayAndResetCurrentPositionAndVectorSize(){
    DeleteVector(&vectorOfData_);
    ResetCurrentPositon();
    ResetTotalVectorSize();
}

template<class T>
void LightVector<T>::ResetCurrentPositon(){
    currentPosition_ = 0;
}

template<class T>
void LightVector<T>::ResetTotalVectorSize(){
    totalPositions_ = 0;
}

template<class T>
void LightVector<T>::IncreaseCurrentPosition()
{
    if(currentPosition_<totalPositions_){
        currentPosition_++;
    }
}

template<class T>
void LightVector<T>::DecreaseCurrentPosition()
{
    if(currentPosition_>0){
        currentPosition_--;
    }
}

template<class T>
bool LightVector<T>::IsVectorEmpty()
{
    return currentPosition_ == 0;
}

template<class T>
bool LightVector<T>::IsIndexInsideVectorRange(const uint32_t& indexElement)
{
    return indexElement < currentPosition_;
}

template<class T>
void LightVector<T>::CopyDataAndAllocateMemory(const uint32_t& desiredSize)
{
    T * auxiliaryVector = nullptr;
    AllocateMemoryTo(&auxiliaryVector, totalPositions_);
    CopyDataFromCurrentVectorIntoAuxiliaryVector(auxiliaryVector);
    DeleteVector(&vectorOfData_);
    AllocateMemoryToVectorOfData(desiredSize);
    CopyDataFromAuxiliaryVectorIntoCurrentVector(auxiliaryVector);
    UpdateVectorSize(desiredSize);
}

template<class T>
void LightVector<T>::AllocateMemoryToVectorOfData(const uint32_t& desiredSize)
{
    AllocateMemoryTo(&vectorOfData_, desiredSize);
}

template<class T>
void LightVector<T>::AllocateMemoryTo(T **ptr, const uint32_t& desiredSize)
{
    if(IsItAnArray(desiredSize)){
        *ptr = new T[desiredSize];
    } else {
        *ptr = new T;
    }
}

template<class T>
void LightVector<T>::UpdateVectorSize(const uint32_t& desiredSize)
{
    totalPositions_ = desiredSize;
}

template<class T>
bool LightVector<T>::IsItAnArray(const uint32_t& desiredSize)
{
    const uint32_t C_MINIMUM_ARRAY_SIZE = 2;
    return desiredSize>=C_MINIMUM_ARRAY_SIZE;
}

template<class T>
void LightVector<T>::CopyDataFromCurrentVectorIntoAuxiliaryVector(T * auxiliaryVector)
{
    CopyDataFromSourceIntoDestiny(vectorOfData_, auxiliaryVector);
}

template<class T>
void LightVector<T>::CopyDataFromAuxiliaryVectorIntoCurrentVector(T * auxiliaryVector)
{
    CopyDataFromSourceIntoDestiny(auxiliaryVector, vectorOfData_);
}

template<class T>
void LightVector<T>::CopyDataFromSourceIntoDestiny(T *vectorSource, T * vectorDestiny)
{
    for(uint32_t i=0; i<currentPosition_; i++){
        vectorDestiny[i] = vectorSource[i];
    }
}

template<class T>
void LightVector<T>::DeleteVector(T ** vectorOfData)
{
    if(*vectorOfData != nullptr){
        if(IsItAnArray(totalPositions_)){
			DeleteArrayOfElements(vectorOfData);
        } else {
			DeleteSingleElement(vectorOfData);
        }
    }
}

template<class T>
void LightVector<T>::DeleteArrayOfElements(T ** vectorOfData)
{
	delete [] *vectorOfData;
	*vectorOfData = nullptr;
}

template<class T>
void LightVector<T>::DeleteSingleElement(T ** singleElement){
	delete *singleElement;
	*singleElement = nullptr;
}

#endif // LIGHTVECTOR_H
