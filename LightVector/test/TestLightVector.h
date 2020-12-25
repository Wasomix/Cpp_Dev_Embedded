#ifndef TESTLIGHTVECTOR_H
#define TESTLIGHTVECTOR_H

#include <iostream>
#include "../header/LightVector.h"

using namespace std;

class TestLightVector {
public:
    TestLightVector()/*=default*/;
    ~TestLightVector()=default;
    void RunAllTests();

private:
    void TestReserve();
    void TestSize();
    void TestAt();
    void TestPushBack();    
    void TestPopBack();
    void FillVectorWithData(LightVector<int>& vectorTest,
                            bool& testFailed);
    void RemoveNElementsFromVector(LightVector<int>& vectorTest,
                                    const uint32_t& numberOfPositionsToRemove);
    void ReadElementsFromVectorAndCompareThem(LightVector<int>& vectorTest,
                                              bool& testFailed);
    void IsSizeCorrect(const uint32_t& desiredSize,
                       LightVector<int>& vectorTest);
    template<class T>
    bool BothDataAreDifferent(T value1, T value2){
        return value1 != value2;
    }
    void PrintTestHeader(string& str)const;
    void PrintTwoNewLines()const;
    void PrintTestResult(bool testFailed)const;

private:
    static const uint8_t C_NUMBER_OF_DATA_IN_TEST_VECTOR = 10;
    int vectorTestOfData[C_NUMBER_OF_DATA_IN_TEST_VECTOR];
};

#endif
