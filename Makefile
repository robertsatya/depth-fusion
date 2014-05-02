all:
	g++ `pkg-config --cflags --libs opencv` -o fusion fusion.cpp

clean:
	rm fusion