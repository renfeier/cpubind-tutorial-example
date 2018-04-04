#ifndef  READ_CPUBIND_CONFIG_H
#define  READ_CPUBIND_CONFIG_H

#include <map>
#include <string>

        class CpuBindConfig
		{
           public:
               int gpuCardNums;
               int numaNodeNums;
               std::map<string, vector<int>> nodeCpuListsMap;
               std::map<int, string> gpuToNumaNodeMap;

			public:
        		CpuBindConfig(){};
				CpuBindConfig(const std::string &configPath);
				bool readConfig(const std::string &configPath);
		};
  

#endif // READ_CPUBIND_CONFIG_H
