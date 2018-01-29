#ifndef  SENSETIME_SAF_READ_CPUBIND_CONFIG_H
#define  SENSETIME_SAF_READ_CPUBIND_CONFIG_H

#include <map>
#include <string>

namespace sensetime
{
    namespace SAF
    {

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
    } // namespace SAF
} // namespace sensetime

#endif // SENSETIME_SAF_READ_CPUBIND_CONFIG_H
