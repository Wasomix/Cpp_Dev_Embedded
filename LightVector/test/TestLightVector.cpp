#include "TestLightVector.h"

TestLightVector::TestLightVector()
{
    for(uint8_t i=0; i<C_NUMBER_OF_DATA_IN_TEST_VECTOR; i++){
        vectorTestOfData[i] = i+2;
    }
}

void TestLightVector::RunAllTests()
{
    TestReserve();
    TestSize();
    TestAt();
    TestPushBack();
    TestPopBack();
}

void TestLightVector::TestReserve()
{
    string str("Test Reserve:");
    PrintTestHeader(str);
    LightVector<int> vectorTest;
    uint32_t desiredSize = 1;

    for(uint8_t i=0; i<3; i++){
        desiredSize = i;
        vectorTest.reserve(desiredSize);
        IsSizeCorrect(desiredSize, vectorTest);
    }
    desiredSize = 2;
    vectorTest.reserve(desiredSize);
    PrintTwoNewLines();
}

void TestLightVector::TestSize()
{
    string str("Test Size:");
    PrintTestHeader(str);
    TestReserve();
    PrintTwoNewLines();
}

void TestLightVector::TestAt()
{
    string str("Test At:");
    PrintTestHeader(str);
    LightVector<int> vectorTest;
    bool testFailed = false;
    cout << "Value Read: " << vectorTest.at(1) << endl;
    PrintTestResult(testFailed);
    PrintTwoNewLines();
}

void TestLightVector::TestPushBack()
{
    string str("Test Push_back:");
    PrintTestHeader(str);
    LightVector<int> vectorTest;
    uint32_t desiredSize = 2;
    vectorTest.reserve(desiredSize);
    bool testFailed = false;
    FillVectorWithData(vectorTest, testFailed);
    PrintTestResult(testFailed);
    PrintTwoNewLines();
}

void TestLightVector::TestPopBack()
{
    string str("Test Pop_back:");
    PrintTestHeader(str);
    LightVector<int> vectorTest;
    uint32_t desiredSize = 2;

    vectorTest.reserve(desiredSize);
    bool testFailed = false;
    FillVectorWithData(vectorTest, testFailed);
    uint32_t numberOfPositionsToRemove = 2;
    RemoveNElementsFromVector(vectorTest, numberOfPositionsToRemove);
    ReadElementsFromVectorAndCompareThem(vectorTest, testFailed);
    PrintTestResult(testFailed);
    PrintTwoNewLines();
}

void TestLightVector::FillVectorWithData(LightVector<int>& vectorTest,
                                         bool& testFailed)
{
    for(int i=0; i<6; i++){
        vectorTest.push_back(vectorTestOfData[i]);
        cout << "Data Read: " << vectorTest.at(uint32_t(i)) << endl;
        if(BothDataAreDifferent(vectorTestOfData[i], vectorTest.at(uint32_t(i)))){
            testFailed = true;
        }
    }
}

void TestLightVector::RemoveNElementsFromVector(LightVector<int> &vectorTest,
                                                 const uint32_t& numberOfPositionsToRemove)
{
    for(uint32_t i=0; i<numberOfPositionsToRemove; i++){
        vectorTest.pop_back();
    }
}

void TestLightVector::ReadElementsFromVectorAndCompareThem(LightVector<int> &vectorTest,
                                                           bool& testFailed)
{
    const uint32_t& numberOfDataInVector = vectorTest.GetNumberOfElements();
    cout << "Data Read After pop back" << endl;

    for(uint32_t i=0; i<numberOfDataInVector; i++){
        if(BothDataAreDifferent(vectorTestOfData[i], vectorTest.at(i))){
            testFailed = true;
        }
        cout << "Data Read: " << vectorTest.at(i) << endl;
    }
}

void TestLightVector::IsSizeCorrect(const uint32_t& desiredSize,
                                    LightVector<int>& vectorTest)
{
    uint32_t vectorSize = vectorTest.size();
    bool testFailed = false;
    if(vectorSize != desiredSize){
        testFailed = true;
    }

    PrintTestResult(testFailed);
}

void TestLightVector::PrintTestHeader(string& str)const
{
    cout << str << endl;
}

void TestLightVector::PrintTwoNewLines()const
{
    cout << endl << endl;
}

void TestLightVector::PrintTestResult(bool testFailed)const
{
    if(testFailed){
        cout << "Test Failed!!" << endl;
    } else {
        cout << "Test Ok!!" << endl;
    }
}
