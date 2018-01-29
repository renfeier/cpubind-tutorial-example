#include <opencv2/opencv.hpp>
#include "readCpuBindConfig.hpp"
#include "glog/logging.h"

namespace sensetime
{
    namespace SAF
    {
    	CpuBindConfig::CpuBindConfig(const std::string &configPath)
    	{
    		readConfig(configPath);
    	}

    	bool CpuBindConfig::readConfig(const std::string &configPath)
		{
    		nodeCpuListMap.clear();
            gpuToNumaNodeMap.clear();
            cv::FileStorage root;
            if (!root.open(configPath.c_str(), cv::FileStorage::READ)) {
            	LOG(FATAL) << "read cpubind_config.xml failed";
                return false;
            }
            gpuCardNums = (int)root["gpu_card_nums"];
            numaNodeNums = (int)root["numa_node_nums"];

            // read node cpulist
            cv::FileNode nodeFN;
            for (int i = 0; i < numaNodeNums; i++) {
                string nodefn = "cpulist_node" + std::to_string(i);
                string nodename = "node" + std::to_string(i);
                nodeFN = root[node];
                std::vector<int> nodecpulistVec;
                for (cv::FileNodeIterator iter = nodeFN.begin(); iter != nodeFN.end(); iter++)
                {
                    nodecpulistVec.push_back(int(*iter));
                }
                nodeCpuListMap[nodename]= nodecpulistVec;
            }
            // read gpu to node map
            cv::FileNode gpunodemapFN = root["map_gpu_to_node"];
            for (int j = 0; j < gpuCardNums; j++) {
                string gpuindex = "gpuCard" + std::to_string(j);
                gpuToNumaNodeMap[j] = (string)gpunodemapFN[gpuindex];

            }
            return true;
		}

    } // namespace SAF
} // namespace sensetime

