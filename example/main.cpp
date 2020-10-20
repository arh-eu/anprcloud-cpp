#include "anprcloudservice.h"
#include <iostream>

using namespace anprcloud;

struct CloudParams
{
    std::string apiKey;
    std::string url;
};

CloudParams getParams(int argc, char *argv[]);


int main(int argc, char *argv[])
{
    CloudParams params = getParams(argc, argv);

    ANPRCloudService service = ANPRCloudService::builder()
            .setUrl(params.url)
            .setApiKey(params.apiKey)
            .setExecutionTimeoutMs(10000)
            .setConnectionTimeoutMs(2000)
            .build();

    BinaryImage no_mmr("../images/example1.jpg");
    BinaryImage deu("../images/example2.jpg");

    ANPRCloudRequest requestANPR = ANPRCloudRequest::builder()
            .setImage(no_mmr)
            .setLocation("HUN")
            .setMaxReads(1)
            .setService(ServiceType::ANPR)
            .build();

    ANPRCloudRequest requestANPR_MMR = ANPRCloudRequest::builder()
            .setImage(deu)
            .setLocation("DEU")
            .setMaxReads(1)
            .setService(ServiceType::ANPR_MMR)
            .build();    


    std::vector<ANPRCloudRequest> reqs;
    reqs.push_back(requestANPR);
    reqs.push_back(requestANPR_MMR);

    for(size_t i=0; i < reqs.size(); i++)
    {
        try {
            ANPRCloudResult result = service.execute(reqs[i]);
            if(result.hasVehicle())
            {
                std::vector<Vehicle> vehicles = result.getVehicles();
                for(size_t i=0; i< vehicles.size(); i++)
                {
                   if(vehicles[i].hasPlate())
                   {
                       Plate p = vehicles[i].getPlate();
                       std::cout<< p.country<< " " << p.text << " ";
                   }
                   if(vehicles[i].hasMmr())
                   {
                       Mmr mmr = vehicles[i].getMmr();
                       std::cout<< mmr.make<< " " << mmr.model;
                   }
                   std::cout << std::endl;
                }
            }

        } catch (ANPRCloudSdkException& e) {
            std::cout<<e.what()<<std::endl;
        }
    }

    return 0;
}

CloudParams getParams(int argc, char *argv[])
{
    CloudParams params;
    params.url = "https://api-eu.anpr-cloud.com/free";
    if( argc == 1 || argc > 3) //print the help and exit
    {
        std::cerr << "usage: ./ANPRCloudService yourApiKey [url]"<<std::endl;
        std::cerr << "default url for testing: https://api-eu.anpr-cloud.com/free" <<std::endl<<std::endl;
        std::cerr << "example with default url: ./ANPRCloudService 6avexOzYdTj5rnm7umR77MEmcAFqxEC6U7ScwX17"<<std::endl;
        std::cerr << "example with custom  url: ./ANPRCloudService 6avexOzYdTj5rnm7umR77MEmcAFqxEC6U7ScwX17 https://api-eu.anpr-cloud.com/free"<<std::endl;
        exit(0);
    }
    if(argc > 1)
    {
        params.apiKey = argv[1];
    }
    if(argc == 3)
    {
        params.url = argv[2];
    }
    return params;
}

