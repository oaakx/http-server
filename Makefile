# Variables
CPP=g++


# Testing
test: test_request

test_request:
	$(info == Running: test_request)
	${CPP} -o tests/test_request tests/test_request.cpp request.cpp
	./tests/test_request


# Misc
clean:
	rm tests/test_request