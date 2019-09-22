# Variables
CPP=g++
OUTPUT=http-server

# Testing
test: test_request

test_request:
	$(info == Running: test_request)
	${CPP} -o tests/test_request tests/test_request.cpp request.cpp
	./tests/test_request


# Building
build: main.cpp server.cpp response.cpp request.cpp uri.cpp args.cpp
	${CPP} -o ${OUTPUT} -pthread main.cpp server.cpp response.cpp request.cpp uri.cpp args.cpp

# Misc
clean:
	rm http-server