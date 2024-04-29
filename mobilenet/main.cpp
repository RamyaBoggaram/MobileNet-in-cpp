#include "utils.h"
#include <string>
int main()
{
  const char *testListFile = "../data/test_list.txt";
    const char *testLabelsFile = "../data/test_labels.txt";
    const char *testImageSet = "../data/images/";
//const std::string filepath = "/home/keystone/mobilenet-master/data/images/";
   // test(testListFile, testLabelsFile, testImageSet, filepath);
    test(testListFile, testLabelsFile, testImageSet);
    return 0;
}
