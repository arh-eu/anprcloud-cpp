Table of contents
=================

* [Quick test guide](#quick-test-guide)
   * [Build the example](#build-the-example)
      * [Test free stage](#test-free-stage)
      * [Test production stage](#test-production-stage)
   * [Build with Docker](#build-with-docker)
* [How to use](#how-to-use)
   * [Basic example](#basic-example)
   * [Build the ANPRCloudService object](#build-the-anprcloudservice-object)
      * [Url](#url)
      * [ApiKey](#apikey)
      * [ExecutionTimeoutMs](#executiontimeoutms)
      * [ConnectionTimeoutMs](#connectiontimeoutms)
   * [Build the ANPRCloudRequest object](#build-the-anprcloudrequest-object)
      * [Image](#image)
      * [Location](#location)
      * [MaxReads](#maxreads)
      * [Service](#service)
   * [Execute the request and get the result](#execute-the-request-and-get-the-result)
* [Thanks](#thanks)

## Quick test guide
### Build the example
Before you can compile our C++ code you should install the dependencies.

  - build-essential
  - libcurl4-gnutls-dev

```sh
apt-get update
apt-get install build-essential
apt-get install libcurl4-gnutls-dev
```
Then you can clone this repository, change to build directory and run make.

```sh
git clone https://github.com/arh-eu/anprcloud-cpp.git
cd anprcloud-cpp/build
make
```
Now you can run the example program with one or two parameters.

#### Test free stage
Test your free stage like this (and replace 'yourApiKey' with your apiKey):

```sh
./ANPRCloudService yourApiKey
```
You will see the following result.
```sh
HUN MDD955
DEU TÜX5000 Opel Astra
```

#### Test production stage
Test your production stage like this (and replace 'yourApiKey' with your apiKey):

```sh
./ANPRCloudService yourApiKey https://api-eu.anpr-cloud.com/prod
```
### Build with Docker
If you have docker installed on your system, you can test the sdk with the attached Dockerfile.
Change to anprcloud-cpp directory.
```sh
cd anprcloud-cpp
```
Please open the Dockerfile and replace 'yourApiKey' with your apiKey. Then build the image with the following command.

```sh
docker build -t cloudtest:latest .
```
The last build step is the running of the example code. The output shall look similar to this.
<pre><code>Step 9/9 : RUN ./ANPRCloudService yourApiKey
 ---> Running in 417c5946db85
<b>HUN MDD955</b>
<b>DEU TÜX5000 Opel Astra</b>
Removing intermediate container 417c5946db85
 ---> 0af5dc555bdd
Successfully built 0af5dc555bdd
Successfully tagged cloudtest:latest
</code></pre>

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
          for(size_t i=0; i < vehicles.size(); i++)
          {
             if(vehicles[i].hasPlate())
             {
                 Plate p = vehicles[i].getPlate();
                 std::cout<< p.country << " " << p.text << " ";
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
The maximal connecting time in milliseconds.

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
## Thanks
For parsing the cloud result this example uses Niels Lohmann's JSON parser for C++.
You can reach the project here: https://github.com/nlohmann/json

