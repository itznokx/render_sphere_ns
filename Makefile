all:
	g++ raycasting.cpp -w -lSDL2 -o raycasting
	./raycasting
rm:
	rm *.o
	rm *.out
	rm *.h.gch