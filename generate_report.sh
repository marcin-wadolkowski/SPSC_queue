#!/bin/bash
lcov --directory build --zerocounters
ctest --test-dir build
lcov --rc geninfo_unexecuted_blocks=1 --directory build --capture --output-file coverage.info --ignore-errors mismatch
lcov --remove coverage.info '/usr/*' '/gtest/*' --output-file coverage_filtered.info
genhtml coverage_filtered.info --output-directory report --ignore-errors empty