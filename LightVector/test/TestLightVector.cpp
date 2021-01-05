#include "TestLightVector.h"

//#define PRINT_TRACES

TestLightVector::TestLightVector()
{
    for(uint8_t i=0; i<C_NUMBER_OF_DATA_IN_TEST_VECTOR; i++){
        vectorTestOfData[i] = i+2;
    }
}

void TestLightVector::RunAllTests()
{
    TestReserve_Test1();
    TestSize_Test1();
    TestAt_Test1();
    TestPushBack_Test1();
    TestPopBack_Test1();
    TestPopBackLowerLimit_Test2();
    TestClear_Test1();
}

void TestLightVector::TestReserve_Test1()
{
    string str("Test Reserve test 1:");
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

void TestLightVector::TestSize_Test1()
{
    string str("Test Size test 1:");
    PrintTestHeader(str);
    TestReserve_Test1();
    PrintTwoNewLines();
}

void TestLightVector::TestAt_Test1()
{
    string str("Test At test 1:");
    PrintTestHeader(str);
    LightVector<int> vectorTest;
    bool testFailed = false;
#ifdef PRINT_TRACES
    cout << "Value Read: " << vectorTest.at(1) << endl;
#endif
    PrintTestResult(testFailed);
    PrintTwoNewLines();
}

void TestLightVector::TestPushBack_Test1()
{
    string str("Test Push_back test 1:");
    PrintTestHeader(str);
    LightVector<int> vectorTest;
    uint32_t desiredSize = 2;
    vectorTest.reserve(desiredSize);
    bool testFailed = false;
    FillVectorWithData(vectorTest, testFailed);
    PrintTestResult(testFailed);
    PrintTwoNewLines();
}

void TestLightVector::TestPopBack_Test1()
{
    string str("Test Pop_back test 1:");
    PrintTestHeader(str);
    LightVector<int> vectorTest;
    uint32_t desiredSize = 2;

    vectorTest.reserve(desiredSize);
    bool testFailed = false;
    FillVectorWithData(vectorTest, testFailed);
    testFailed = false;
    uint32_t numberOfPositionsToRemove = 2;
    RemoveNElementsFromVector(vectorTest, numberOfPositionsToRemove);
    ReadElementsFromVectorAndCompareThem(vectorTest, testFailed);
    PrintTestResult(testFailed);
    PrintTwoNewLines();
}

void TestLightVector::TestPopBackLowerLimit_Test2()
{
    string str("Test Pop_back test 2:");
    PrintTestHeader(str);
    LightVector<int> vectorTest;
    bool testFailed = false;
    uint32_t numberOfPositionsToRemove = 2;
    RemoveNElementsFromVector(vectorTest, numberOfPositionsToRemove);
    ReadElementsFromVectorAndCompareThem(vectorTest, testFailed);
    PrintTestResult(testFailed);
    PrintTwoNewLines();
}

void TestLightVector::TestClear_Test1()
{
    string str("Test Clear test 1:");
    PrintTestHeader(str);
    LightVector<int> vectorTest;
    uint32_t desiredSize = 2;

    vectorTest.reserve(desiredSize);
    cout << "Size: " << vectorTest.size() << endl;
    vectorTest.clear();
    bool testFailed = vectorTest.size() == 0? false : true;
    PrintTestResult(testFailed);
    PrintTwoNewLines();
}

void TestLightVector::FillVectorWithData(LightVector<int>& vectorTest,
                                         bool& testFailed)
{
    for(int i=0; i<6; i++){
        vectorTest.push_back(vectorTestOfData[i]);
#ifdef PRINT_TRACES
        cout << "Data Read: " << vectorTest.at(uint32_t(i)) << endl;
#endif
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
#ifdef PRINT_TRACES
    cout << "Data Read After pop back" << endl;
#endif
    for(uint32_t i=0; i<numberOfDataInVector; i++){
        if(BothDataAreDifferent(vectorTestOfData[i], vectorTest.at(i))){
            testFailed = true;
        }
#ifdef PRINT_TRACES
        cout << "Data Read: " << vectorTest.at(i) << endl;
#endif
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
