test.exe: test.cpp sqlite.cpp 
	$(CXX) -lm -lz -lsqlite3 $+ -o $@
clean:
	rm -vf *.exe 
