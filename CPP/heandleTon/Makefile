example1: main.cpp singleTon.so libclass_test.so
	$(CXX) $(CXXFLAGS) -g -o example1 main.cpp -L. -lclass_test -ldl

singleTon.so: singleTon.cpp
	$(CXX) $(CXXFLAGS) -g -shared  -fPIC -o singleTon.so  singleTon.cpp

libclass_test.so: class_test.cpp
	$(CXX) $(CXXFLAGS) -shared  -fPIC  -o libclass_test.so class_test.cpp
clean:
	rm -f example1 singleTon.so libclass_test.so

.PHONY: clean
