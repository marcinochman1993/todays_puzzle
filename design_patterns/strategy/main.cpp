// g++ -std=c++14 main.cpp -o strategy -ljsoncpp

#include <json/json.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <sstream>


using ProgramOptions = std::map<std::string, std::string>;

class IFileParser
{
public:
  virtual ProgramOptions parse(const std::string&) = 0;
};

class JsonParser: public IFileParser
{
public:
  ProgramOptions parse(const std::string&) override;
};

class KeyValueFileParser: public IFileParser
{
public:
  ProgramOptions parse(const std::string&) override;
};


ProgramOptions KeyValueFileParser::parse(const std::string& filePath)
{
  ProgramOptions options;
  std::ifstream file{filePath};
  while(file)
  {
    std::string key, value, line;
    std::getline(file, line);
    std::istringstream oss{line};

    if(!line.empty())
    {
      oss >> key >> value;

      options.insert(make_pair(key, value));

    }
  }

  return options;
}

ProgramOptions JsonParser::parse(const std::string& filePath)
{
  ProgramOptions options;
  std::ifstream file{filePath};

  Json::Value jsonContent;

  file >> jsonContent;

  for(auto& key: jsonContent.getMemberNames())
  {
    auto& value = jsonContent[key];

    if(value.isString())
      options.insert(std::make_pair(key, value.asString()));
  }


  return options;
}

bool isJson(const std::string& jsonPath)
{
  auto dotIdx = jsonPath.rfind('.');

  if(dotIdx == std::string::npos)
    return false;

  auto fileExtension = jsonPath.substr(dotIdx + 1);

  return fileExtension == "json";
}


ProgramOptions parseFile(const std::string& filePath)
{
  std::unique_ptr<IFileParser> parser;

  if(isJson(filePath))
  {
    parser.reset(new JsonParser{});
  }
  else
  {
    parser.reset(new KeyValueFileParser{});
  }


  return parser->parse(filePath);
}


int main(int argc, char* argv[])
{
  if(argc <= 1)
  {
    std::cerr << "Program run with invalid number of arguments\n";
  }
  else
  {
    ProgramOptions options = parseFile(argv[1]);

    for(auto& keyValuePair: options)
    {
      std::cout << keyValuePair.first << ": "
                << keyValuePair.second << std::endl;
    }
  }
}
