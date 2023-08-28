#include <aws/core/Aws.h>
#include <iostream>
int main(int argc, char** argv)
{
   Aws::SDKOptions options;
   std::cout << "Running a pure-aws test instantiation to test the aws-cpp-sdk install.\nA failure may manifest as a hang.\n\n";
   std::cout << "\t* Testing InitAPI()\n";
   Aws::InitAPI(options);
   std::cout << "\t\t* Passed.\n";
   std::cout << "\t* Testing ShutdownAPI()\n";
   Aws::ShutdownAPI(options);
   std::cout << "\t\t* Passed.\n";
   return 0;
}