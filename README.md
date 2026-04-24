# SPSC queue
The SPSC queue is implemented on top of std::queue, allowing the user to choose either a deque or a list as the underlying container. All tests currently use int as the element type. To support other element types, an extra line needs to be added at the end of spsc_queue.cpp.

## How to build
```bash
git clone https://github.com/marcin-wadolkowski/SPSC_queue.git
cd SPSC_queue/
mkdir build
cd build/
cmake ..
make
```

The CMake command includes a CONTAINER parameter that allows switching to a list as the underlying container; the default is a deque.

```bash
git clone https://github.com/marcin-wadolkowski/SPSC_queue.git
cd SPSC_queue/
mkdir build
cd build/
cmake .. -DCONTAINER=list
make
```

## How to run sample application

```bash
./bin/spsc_queue
```

The output should be:
```bash
0 1 2 3 4 5 6 7 8 9
```

## How to run the tests

```bash
./spsc_tests
```
or
```bash
ctest
```
or
```bash
ctest -V
```

## How to generate a code coverage report

To generate a code coverage report, you need to install lcov. Then run the generate_report.sh script. It assumes you’re in the project’s root directory, that a build subdirectory already exists, and it will place the results in a report subdirectory. Additionally, the files coverage.info and coverage_filtered.info will be generated.

