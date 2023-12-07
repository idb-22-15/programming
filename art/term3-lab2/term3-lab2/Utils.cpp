#pragma once
#include <msclr/marshal_cppstd.h>
#include <string>

class Utils {
 public:
  static std::string ConvertSystemStringToStd(System::String ^ systemString) {
    msclr::interop::marshal_context context;
    return context.marshal_as<std::string>(systemString);
  }
};