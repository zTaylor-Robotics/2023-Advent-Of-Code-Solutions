Use the following commands to build and run the container:

#enter the directory which has the docker file
docker-compose up -d

#after the container is built:
docker-compose exec -it aoc bash

#navigate to the /src and the desired puzzle and part
debug                     #targets a shell script which debugs, builds, and runs the project
