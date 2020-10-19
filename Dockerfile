FROM ubuntu:18.04

RUN apt-get -y update

RUN apt-get -y install build-essential
RUN apt-get -y install libcurl4-gnutls-dev


RUN mkdir /home/ANPRCloudSdk

COPY . /home/ANPRCloudSdk/

WORKDIR /home/ANPRCloudSdk/build

RUN make

#Replace 'yourApiKey' with your apiKey.
RUN ./ANPRCloudService yourApiKey

#You can test your production stage if you uncomment the last section.
#Replace 'yourApiKey' with your apiKey.
#RUN ./ANPRCloudService yourApiKey https://api-eu.anpr-cloud.com/prod


