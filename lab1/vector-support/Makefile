all: vector-mem.O0 vector-mem.O1 vector-mem.O2 vector-mem.O3 vector-simd


vector-mem.O0: vector-mem.cc
	g++ -fPIC -O0 -o vector-mem.O0 vector-mem.cc
vector-mem.O1: vector-mem.cc
	g++ -fPIC -O1 -o vector-mem.O1 vector-mem.cc
vector-mem.O2: vector-mem.cc
	g++ -fPIC -O2 -o vector-mem.O2 vector-mem.cc
vector-mem.O3: vector-mem.cc
	g++ -fPIC -O3 -o vector-mem.O3 vector-mem.cc

vector-simd: vector-mem.cc
	#g++ -fPIC -mavx512f -O3 -o vector-simd vector-mem.cc
	g++ -fPIC -mavx -O3 -o vector-simd vector-mem.cc
	@echo Proveu tambe amb les opcions -mavx2 i -mavx

run: vector-mem.O0 vector-mem.O1 vector-mem.O2 vector-mem.O3 vector-simd
	@echo Running -O0 version
	(time ./vector-mem.O0)
	@echo; echo
	@echo Running -O1 version
	(time ./vector-mem.O1)
	@echo; echo
	@echo Running -O2 version
	(time ./vector-mem.O2)
	@echo; echo
	@echo Running -O3 version
	(time ./vector-mem.O3)
	@echo; echo
	@echo Running avx512 version... why does it fail?
	(time ./vector-simd)


clean: 
	rm -f vector-mem.O0 vector-mem.O1 vector-mem.O2 vector-mem.O3 \
            vector-simd
