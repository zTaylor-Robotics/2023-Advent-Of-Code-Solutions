Use the following commands to build and run the container:

docker build -t cpp-denv:1.0 .

docker run -it --rm --name=aoc --mount type=bind,source=%cd%,target=/src cpp-denv:0.9 bash
