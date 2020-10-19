## Quick test guide

Before you can compile our C++ code you should install the dependencies.

  - build-essential
  - libcurl4-gnutls-dev

```sh
apt-get update
apt-get install build-essential
apt-get install libcurl4-gnutls-dev
```
Then you can clone this repository,change to build directory and run make.

```sh
git clone https://github.com/arh-eu/anprcloud-cpp.git
cd anprcloud-cpp/build
make
```
Now you can run the example program with one or two parameters.

### Test free stage
Test your free stage like this (and replace 'yourApiKey' with your apiKey.):

```sh
./ANPRCloudService yourApiKey
```

### Test production stage
Test your production stage like this (and replace 'yourApiKey' with your apiKey.):

```sh
./ANPRCloudService yourApiKey https://api-eu.anpr-cloud.com/prod
```
## How to use
### Basic example

```cpp
ANPRCloudService service = ANPRCloudService::builder()
            .setUrl("https://api-eu.anpr-cloud.com/free")
            .setApiKey("yourApiKey")
            .build();
            
BinaryImage image("/path/to/your/image.jpg");

ANPRCloudRequest requestANPR_MMR = ANPRCloudRequest::builder()
        .setImage(image)
        .build();

try {
      ANPRCloudResult result = service.execute(requestANPR_MMR);
      if(result.hasVehicle())
      {
          std::vector<Vehicle> vehicles = result.getVehicles();
          for(size_t i=0; i< vehicles.size(); i++)
          {
             if(vehicles[i].hasPlate())
             {
                 Plate p = vehicles[i].getPlate();
                 std::cout<< p.country<< " " << p.text << std::endl;
             }
             if(vehicles[i].hasMmr())
             {
                 Mmr mmr = vehicles[i].getMmr();
                 std::cout<< mmr.make<< " " << mmr.model << std::endl;
             }
          }
      }

  } catch (ANPRCloudSdkException& e) {
      std::cout<<e.what()<<std::endl;
}
```
### Build the ANPRCloudService object
You can set the following parameters for the service:
#### Url
This is the URL of the service. You have to give the full url like : https://api-eu.anpr-cloud.com/free
#### ApiKey
Your secret apiKey. Please make sure you don't leak it!
#### ExecutionTimeoutMs
The maximal execution time of the request in milliseconds.
#### ConnectionTimeoutMs
The maximal connection time in millisecons.

```cpp
ANPRCloudService service = ANPRCloudService::builder()
            .setUrl("https://api-eu.anpr-cloud.com/free")
            .setApiKey("yourApiKey")
            .setExecutionTimeoutMs(10000)
            .setConnectionTimeoutMs(2000)
            .build();
```

### Build the ANPRCloudRequest object
Build the ANPR request as follows
#### Image
The image to be posted to the service
#### Location
The location of the image. It is not necessary, but if you provide it, the service may find a better result, or it will run more quickly.
#### MaxReads
The maximum number of cloud reads, the default value is 1.
#### Service
This can be ANPR or ANPR+MMR. You have to select the desired enum (ANPR or ANPR_MMR).

```cpp
ANPRCloudRequest requestANPR_MMR = ANPRCloudRequest::builder()
            .setImage(image)
            .setLocation("HUN")
            .setMaxReads(1)
            .setService(ServiceType::ANPR_MMR)
            .build();
```

### Execute the request and get the result
The execute function returns only after the call succeded or failed for some reason.
```cpp
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
                       std::cout<< p.country<< " " << p.text << std::endl;
                   }
                   if(vehicles[i].hasMmr())
                   {
                       Mmr mmr = vehicles[i].getMmr();
                       std::cout<< mmr.make<< " " << mmr.model << std::endl;
                   }
                }
            }

        } catch (ANPRCloudSdkException& e) {
            std::cout<<e.what()<<std::endl;
        }
```

