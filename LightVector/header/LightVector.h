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
    ~LightVector(){
        if(vectorOfData_!= nullptr){
            DeleteArray(&vectorOfData_);
        }
    }

    void reserve(uint32_t desiredSize){
        if(IsDesiredSizeGreaterThanCurrentSize(desiredSize)){
            CopyDataAndAllocateMemory(desiredSize);
        }
    }

    uint32_t size(){
        return totalPositions_;
    }

    void push_back(T element){
        const uint32_t desiredSize = currentPosition_ + 1;
        if(IsDesiredSizeGreaterThanCurrentSize(desiredSize)){
            reserve(desiredSize);
        }

        PushBackNewElement(element);
        IncreaseCurrentPosition();
    }    

    // TODO: Implement it
    void pop_back(){
        DecreaseCurrentPosition();
        CopyDataAndAllocateMemory(currentPosition_);
    }

    T& at(const uint32_t& indexElement){
        if(IsIndexInsideVectorRange(indexElement)){
            return GetElement(indexElement);
        } else {
            return GetDefaultElement();
        }
    }

    // TODO: Implement it
    void clear(){

    }

    const uint32_t& GetNumberOfElements(){
        return currentPosition_;
    }

private:
    bool IsDesiredSizeGreaterThanCurrentSize(const uint32_t& desiredSize) const {
        return desiredSize > totalPositions_;
    }

    void PushBackNewElement(T element){
        vectorOfData_[currentPosition_] = element;
    }

    T& GetElement(const uint32_t& indexElement){
        return vectorOfData_[indexElement];
    }

    T& GetDefaultElement(){
        uint32_t desiredSize = 1;
        AllocateMemoryTo(&vectorOfData_, desiredSize);
        return *vectorOfData_;
    }

    void IncreaseCurrentPosition(){
        if(currentPosition_<totalPositions_){
            currentPosition_++;
        }
    }

    void DecreaseCurrentPosition(){
        if(currentPosition_>0){
            currentPosition_--;
        }
    }

    bool IsVectorEmpty(){
        return currentPosition_ == 0;
    }

    bool IsIndexInsideVectorRange(const uint32_t& indexElement){
        return indexElement < currentPosition_;
    }

    void CopyDataAndAllocateMemory(const uint32_t& desiredSize){
        T * auxiliaryVector = nullptr;
        AllocateMemoryTo(&auxiliaryVector, totalPositions_);
        CopyDataFromCurrentVectorIntoAuxiliaryVector(auxiliaryVector);
        DeleteArray(&vectorOfData_);
        AllocateMemoryToVectorOfData(desiredSize);
        CopyDataFromAuxiliaryVectorIntoCurrentVector(auxiliaryVector);
        UpdateVectorSize(desiredSize);
    }

    void AllocateMemoryToVectorOfData(const uint32_t& desiredSize){
        AllocateMemoryTo(&vectorOfData_, desiredSize);
    }

    void AllocateMemoryTo(T **ptr, const uint32_t& desiredSize){
        if(IsItAnArray(desiredSize)){
            *ptr = new T[desiredSize];
        } else {
            *ptr = new T;
        }
    }

    void UpdateVectorSize(const uint32_t& desiredSize){
        totalPositions_ = desiredSize;
    }

    bool IsItAnArray(const uint32_t& desiredSize){
        const uint32_t C_MINIMUM_ARRAY_SIZE = 2;
        return desiredSize>=C_MINIMUM_ARRAY_SIZE;
    }

    void CopyDataFromCurrentVectorIntoAuxiliaryVector(T * auxiliaryVector){
        CopyDataFromSourceIntoDestiny(vectorOfData_, auxiliaryVector);
    }

    void CopyDataFromAuxiliaryVectorIntoCurrentVector(T * auxiliaryVector){
        CopyDataFromSourceIntoDestiny(auxiliaryVector, vectorOfData_);
    }

    void CopyDataFromSourceIntoDestiny(T *vectorSource, T * vectorDestiny) {
        for(uint32_t i=0; i<currentPosition_; i++){
            vectorDestiny[i] = vectorSource[i];
        }
    }

    void DeleteArray(T ** vectorOfData){
        if(*vectorOfData != nullptr){
            if(IsItAnArray(totalPositions_)){
                delete [] *vectorOfData;
            } else {
                delete *vectorOfData;
            }
            vectorOfData = nullptr;
        }
    }

    void DeleteSingleElement(T * ptr){
        delete ptr;
        ptr = nullptr;
    }

private:
    T * vectorOfData_;
    uint32_t totalPositions_;
    uint32_t currentPosition_;
};

#endif // LIGHTVECTOR_H
